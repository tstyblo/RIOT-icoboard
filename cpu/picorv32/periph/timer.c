/*
 * Copyright 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_picorv32
 * @{
 *
 * @file        timer.c
 * @brief       Low-level timer implementation
 *
 * @author      Tomas Styblo
 * @}
 */

#include <stdlib.h>
#include <unistd.h>

#define ENABLE_DEBUG 0
#include "debug.h"
#include "board.h"

#include "cpu.h"
#include "periph_cpu.h"
#include "periph_conf.h"
#include "irq_arch.h"
#include "periph/timer.h"

static timer_isr_ctx_t timer_isr_ctx;

int timer_init(tim_t dev, unsigned long freq, timer_cb_t cb, void *arg)
{
    DEBUG("timer.c - timer_init(): dev=%d, freq=%lu, cb=%p, arg=%p\n", dev, freq, cb, arg);
    if (dev != 0) {
        return -1;
    }

    if (freq != CLOCK_CORECLOCK) {
        puts("ERROR: timer_init: freq != CLOCK_CORECLOCK\n");
        return -1;
    }

    timer_isr_ctx.cb = cb;
    timer_isr_ctx.arg = arg;

    /* reset timer counter */
    timer_clear(dev, 0);

    return 0;
}

int timer_set(tim_t dev, int channel, unsigned int timeout)
{
    DEBUG("timer.c - timer_set(): dev=%d, channel=%d, timeout=%u\n", dev, channel, timeout);
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
    DEBUG("timer.c - timer_set_absolute(): dev=%d, channel=%d, value=%u\n", dev, channel, value);
    if (dev != 0 || channel != 0) {
        return -1;
    }

    uint32_t now = timer_read(dev);
    timer_set(dev, channel, abs(now-value));

    return 0;
}

int timer_set_periodic(tim_t dev, int channel, __attribute__ ((unused)) unsigned int value,
                       __attribute__ ((unused)) uint8_t flags)
{
    if (dev != 0 || channel != 0) {
        return -1;
    }

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
    if (dev != 0) {
        return -1;
    }

    uint64_t volatile rdcycle = _rdcycle_read();
    uint32_t *p_res = (uint32_t *) &rdcycle;

#if 0
    uint8_t *p = (uint8_t *) &rdcycle;
    for (int i = 0; i < 8; i++) {
        printf("p[%d] p=%p v=0x%02X\n", i, p + i, *(p+i));
    }
#endif

    return *p_res;
}

void timer_start(tim_t dev)
{
    if (dev != 0) {
        return;
    }

    // The timer device is always running.
}

void timer_stop(tim_t dev)
{
    if (dev != 0) {
        return;
    }

    timer_clear(dev, 0);

    // We can't really power down the timer device.
}

void timer_isr(void)
{
    /* Call timer callback function */
    if (timer_isr_ctx.cb) {
        timer_isr_ctx.cb(timer_isr_ctx.arg, 0);
    }
    else {
        puts("ERROR: timer callback is NULL");
    }
}

