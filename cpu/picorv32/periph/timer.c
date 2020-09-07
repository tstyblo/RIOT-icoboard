/*
 * Copyright 2017 Ken Rabold
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_fe310
 * @{
 *
 * @file        timer.c
 * @brief       Low-level timer implementation
 *
 * @author      Ken Rabold
 * @}
 */

#include <stdlib.h>
#include <unistd.h>

#include "cpu.h"
#include "periph_cpu.h"
#include "periph_conf.h"
#include "irq_arch.h"
#include "periph/timer.h"

static timer_isr_ctx_t timer_isr_ctx;

int timer_init(tim_t dev, unsigned long freq, timer_cb_t cb, void *arg)
{
    if (dev != 0) {
        return -1;
    }

    if (freq != CLOCK_CORECLOCK) {
        return -1;
    }

    timer_isr_ctx.cb = cb;
    timer_isr_ctx.arg = arg;

    /* reset timer counter */
    _picorv32_timer(0);

    return 0;
}

int timer_set(tim_t dev, int channel, unsigned int timeout)
{
    if (dev != 0 || channel != 0) {
        return -1;
    }

    unsigned int state = irq_disable();
    _picorv32_timer(timeout);
    irq_restore(state);
    
    return 0;
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
    // unimplemented
    return -1;
}

int timer_set_periodic(tim_t dev, int channel, unsigned int value, uint8_t flags) {
    // unimplemented
    return -1;
}

int timer_clear(tim_t dev, int channel)
{
    if (dev != 0 || channel != 0) {
        return -1;
    }

    _picorv32_timer(0);

    return 0;
}

unsigned int timer_read(tim_t dev)
{
    // unimplemented
    return -1;
}

void timer_start(tim_t dev)
{
    // unimplemented
    return -1;
}

void timer_stop(tim_t dev)
{
    // unimplemented
    return -1;
}

void timer_isr(void)
{
    /* Call timer callback function */
    if (timer_isr_ctx.cb) {
        timer_isr_ctx.cb(timer_isr_ctx.arg, 0);
    }
}
