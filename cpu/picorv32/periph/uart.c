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
 * @brief       Low-level UART implementation
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

static uart_isr_ctx_t isr_ctx[UART_NUMOF];

int uart_init(uart_t dev, __attribute__ ((unused)) uint32_t baudrate,
              uart_rx_cb_t rx_cb, void *arg)
{
    ICODEBUG("uart.c - uart_init - START")

    /* Check for valid UART dev */
    assert(dev < UART_NUMOF);

    isr_ctx[dev].rx_cb = rx_cb;
    isr_ctx[dev].arg = arg;

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
        case SER0_UART_DEV:
            while (len > 0) {
                ICODEBUG("uart.c - uart_write - calling icosoc_ser_write_nb")
                int n = icosoc_ser_write_nb(IOPORT_SER0_ADDR, data, len);
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
        default:
            DEBUG_PUTS("uart_write: unrecognized dev");
            break;
    }

    ICODEBUG("uart.c - uart_write - END")
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
    ICODEBUG("uart.c - icosoc_ser_write_nb - START")
    const uint8_t *p = data;
    int len = *(volatile uint32_t*)(IOPORT_SER_BASE_WRLEN + ser_addr * 0x10000);
    if (len > maxlen) len = maxlen;

    for (int i = 0; i < len; i++)
        *(volatile uint32_t*)(IOPORT_SER_BASE_DATA + ser_addr * 0x10000) = p[i];

    ICODEBUG("uart.c - icosoc_ser_write_nb - END")
    return len;
}

void uart_console_isr(void)
{
    ICODEBUG("uart.c - uart_console_isr - START")
    int len = 0;
    while (1) {
        int8_t data = *(volatile int8_t*)IOPORT_CONSOLE;
        if (data > 0) {
            if (isr_ctx[CONSOLE_UART_DEV].rx_cb) {
                isr_ctx[CONSOLE_UART_DEV].rx_cb(isr_ctx[CONSOLE_UART_DEV].arg, (uint8_t)(data));
            }
            len++;
        }
        else {
            break;
        }
    }

    if (len == 0) {
        DEBUG_PUTS("uart_console_isr: no valid data in IOPORT_CONSOLE");
    }

    ICODEBUG("uart.c - uart_console_isr - END")
}

void uart_ser_isr(uart_t dev)
{
    ICODEBUG("uart.c - uart_ser_isr - START")
    assert(dev < UART_NUMOF);

    int ser_addr;
    switch (dev) {
        case SER0_UART_DEV: ser_addr = IOPORT_SER0_ADDR; break;
        default:
            DEBUG_PUTS("uart_ser_isr: unrecognized dev");
            return;
    }

    ICODEBUG("uart.c - icosoc_ser_isr - 2")
    int avail = *(volatile uint32_t*)(IOPORT_SER_BASE_RDLEN + ser_addr * 0x10000);
    if (avail > 0) {
        ICODEBUG("uart.c - icosoc_ser_isr - 3")
        if (isr_ctx[dev].rx_cb) {
            ICODEBUG("uart.c - icosoc_ser_isr - 4")
            for (int i = 0; i < avail; i++) {
                uint8_t data = *(volatile uint32_t*)(IOPORT_SER_BASE_DATA + ser_addr * 0x10000);
                ICODEBUG2("char: '%c' 0x%X avail=%d", data, data, avail);
                isr_ctx[dev].rx_cb(isr_ctx[dev].arg, data);
            }
        }
    }
    else {
        DEBUG_PUTS("uart_ser_isr: no valid data in the fifo");
    }

    ICODEBUG("uart.c - uart_ser_isr - END")
}

