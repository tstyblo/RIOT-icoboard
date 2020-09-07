/*
 * Copyright 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_icosoc
 * @ingroup     drivers_periph_uart
 * @{
 *
 * @file        uart.c
 * @brief       Low-level UART implementation that does not require interrupts
 *
 * @author      Tomas Styblo
 * @}
 */

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <inttypes.h>

#define ENABLE_DEBUG 0
#include "debug.h"

#include "board.h"
#include "thread.h"
#include "periph/uart.h"
#include "periph_uart_icosoc.h"

/*
    The icoSoC console UART does not support interrupts.
    The rx_cb callback will be ignored. Use uart_read() instead.
*/
int uart_init(uart_t dev, uint32_t baudrate, uart_rx_cb_t rx_cb, void *arg)
{
    ICODEBUG("uart.c - uart_init - START")

    /* Check for valid UART dev */
    assert(dev < UART_NUMOF);

    ICODEBUG("uart.c - uart_init - END")
    return UART_OK;
}

void uart_write(uart_t dev, const uint8_t *data, size_t len)
{
    ICODEBUG("uart.c - uart_write - START")
    size_t i;
    unsigned long delay_i = 0;

    switch (dev) {
        case CONSOLE_UART_DEV:
            for (i = 0; i < len; i++)
                *(volatile int*)IOPORT_CONSOLE = data[i];
            break;
        default:
            for (int e = 0; e < SER_DEV_NUMOF; e++) {
                if (ser_devices[e].dev == dev) {
                    while (len > 0) {
                        ICODEBUG("uart.c - uart_write - calling icosoc_ser_write_nb")
                        int n = icosoc_ser_write_nb(ser_devices[e].addr, data, len);
                        if (n > 0) {
                            data += n;
                            len -= n;
                        }
                        else {
                            // wait for output while yielding
                            if (delay_i++ == UART_RX_DELAY) {
                                delay_i = 0;
                                thread_yield();
                            }
                        }
                    }
                    break;
                }
            }
    }

    ICODEBUG("uart.c - uart_write - END")
}

size_t uart_read(uart_t dev, int8_t *data, size_t len)
{
    ICODEBUG("uart.c - uart_read - START")
    unsigned long delay_i = 0;
    switch (dev) {
        case CONSOLE_UART_DEV:
            for (size_t rb = 0; rb < len;) {
                int8_t v = *(volatile int8_t*)IOPORT_CONSOLE;
                // DEBUG("uart.c - uart_read - byte: %d rb=%d len=%d", v, rb, len);
                if (v >= 0)
                    data[rb++] = v;
                else if (rb > 0) {
                    // DEBUG("uart.c - uart_read - END: ret=%d", rb);
                    return rb;
                }
                else {
                    // wait for input while yielding
                    if (delay_i++ == UART_RX_DELAY) {
                        delay_i = 0;
                        thread_yield();
                    }
                }
            }
            break;
        default:
            for (int e = 0; e < SER_DEV_NUMOF; e++) {
                if (ser_devices[e].dev == dev) {
                    for (size_t rb = 0; rb < len;) {
                        ICODEBUG("uart.c - uart_read - calling icosoc_ser_read_nb")
                        int n = icosoc_ser_read_nb(ser_devices[e].addr, data + rb, len - rb);
                        if (n > 0) {
                            rb += n;
                        }
                        else if (rb > 0) {
                            return rb;
                        }
                        else {
                            // wait for input while yielding
                            if (delay_i++ == UART_RX_DELAY) {
                                delay_i = 0;
                                thread_yield();
                            }
                        }
                    }
                    break;
                }
            }
    }
            
    ICODEBUG("uart.c - uart_read - END");
    return len;
}

void uart_poweron(uart_t dev)
{
    (void) dev;
}

void uart_poweroff(uart_t dev)
{
    (void) dev;
}

int icosoc_ser_read_nb(int ser_addr, void *data, int maxlen)
{
    ICODEBUG("uart.c - icosoc_ser_read_nb - START")
    uint8_t *p = data;
    int rb = maxlen;
    int avail = *(volatile uint32_t*)(IOPORT_SER_BASE_RDLEN + ser_addr * 0x10000);
    if (avail < rb)
        rb = avail;

    for (int i = 0; i < rb; i++) {
        p[i] = *(volatile uint32_t*)(IOPORT_SER_BASE_DATA + ser_addr * 0x10000);
        ICODEBUG2("char: '%c' 0x%X rb=%d avail=%d maxlen=%d", p[i], p[i], rb, avail, maxlen);
    }
    ICODEBUG("uart.c - icosoc_ser_read_nb - END")
    return rb;
}

int icosoc_ser_write_nb(int ser_addr, const void *data, int maxlen)
{
    const uint8_t *p = data;
    int len = *(volatile uint32_t*)(IOPORT_SER_BASE_WRLEN + ser_addr * 0x10000);
    if (len > maxlen) len = maxlen;

    for (int i = 0; i < len; i++)
        *(volatile uint32_t*)(IOPORT_SER_BASE_DATA + ser_addr * 0x10000) = p[i];

    return len;
}

