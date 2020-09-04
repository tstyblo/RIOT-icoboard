/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_picorv32
 * @{
 *
 * @file        cpu.c
 * @brief       Implementation of the CPU IRQ management for picorv32
 *
 * @author      Tomas Styblo
 * @}
 */

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#define ENABLE_DEBUG 1
#include "debug.h"
#include "cpu.h"
#include "irq.h"
#include "irq_arch.h"
#include "panic.h"
#include "sched.h"

volatile int picorv32_in_isr = 0;

/**
 * @brief   ISR trap vector
 */
void trap_entry(void);

void irq_init(void)
{
    /* Setup trap handler function */
    *(volatile int *)IRQ_HANDLER_ADDR = &trap_entry;

    /* Enable all interrupts */
    irq_enable();
}

/**
 * @brief Global trap and interrupt handler
 */
void handle_trap(unsigned int ra, unsigned int irqs_pending)
{
    int irq_serviced = 0;
    DEBUG("thread_arch.c - handle_trap - ra=%08x, irqs_pending=%08x\n", ra, irqs_pending);
    
    /*  Tell RIOT to set sched_context_switch_request instead of
     *  calling thread_yield(). */
    picorv32_in_isr = 1;

    /* There may be multiple pending interrupts. */
    if ((irqs_pending & IRQ_MASK_TIMER) == IRQ_MASK_TIMER) {
        irq_serviced = 1;
        // TODO
    }
    if ((irqs_pending & IRQ_MASK_EBREAK) == IRQ_MASK_EBREAK) {
        irq_serviced = 1;
        sched_context_switch_request = 1;
    }
    if ((irqs_pending & IRQ_MASK_BUS_ERROR) == IRQ_MASK_BUS_ERROR) {
        irq_serviced = 1;
        core_panic(PANIC_GENERAL_ERROR, "BUS Error (Unaligned Memory Access)");
    }

    if (irq_serviced != 1) {
        core_panic(PANIC_GENERAL_ERROR, "Unhandled trap");
    }

    /* Check if context change was requested */
    if (sched_context_switch_request) {
        sched_run();
        if (sched_active_thread) {
            DEBUG("thread_arch.c - handle_trap - sched_active_thread=%p, pid=%d, name=%s, stack_start=%p sp=%p\n",
                  sched_active_thread, sched_active_thread->pid, sched_active_thread->name, sched_active_thread->stack_start, sched_active_thread->sp);
        }
        else {
            DEBUG("thread_arch.c - handle_trap - sched_active_thread is NULL\n");
        }
    }

    /* ISR done - no more changes to thread states */
    picorv32_in_isr = 0;
}

