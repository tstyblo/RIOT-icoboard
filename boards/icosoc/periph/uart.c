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

#include "board.h"
#include "thread.h"
#include "periph/uart.h"

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
    //ICODEBUG("uart.c - uart_write - START")
    size_t i;
    for (i = 0; i < len; i++)
        *(volatile int*)IOPORT_CONSOLE = data[i];

    //ICODEBUG("uart.c - uart_write - END")
}

size_t uart_read(uart_t dev, int8_t *data, size_t len)
{
    unsigned long i = 0;
    //ICODEBUG("uart.c - uart_read - START")
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
            // wait for an input while yielding - this won't work with multiple threads
            if (i++ == _UART_RX_DELAY) {
                i = 0;
                thread_yield();
            }
        }
    }   
    //DEBUG("uart.c - uart_read - END: ret=%d", len);
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
