/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup         cpu_picorv32
 * @{
 *
 * @file
 * @brief           Implementation of the kernels irq interface
 *
 * @author          Tomas Styblo
 */

#ifndef IRQ_ARCH_H
#define IRQ_ARCH_H

#include <stdint.h>
#include "cpu_conf.h"
#include "cpu.h"
#include "periph/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

// this address is specified in icosoc firmware.S
// - NO LONGER NEEDED as we use custom PROGADDR_IRQ now
#define IRQ_HANDLER_ADDR 0x0000000000000008

#define IRQ_TIMER           0
#define IRQ_EBREAK          1
#define IRQ_BUS_ERROR       2
#define IRQ_UART_CONSOLE    3
#define IRQ_UART_SER0       4

#define IRQ_MASK_TIMER          (1 << IRQ_TIMER)
#define IRQ_MASK_EBREAK         (1 << IRQ_EBREAK)
#define IRQ_MASK_BUS_ERROR      (1 << IRQ_BUS_ERROR)
#define IRQ_MASK_UART_CONSOLE   (1 << IRQ_UART_CONSOLE)
#define IRQ_MASK_UART_SER0      (1 << IRQ_UART_SER0)

extern volatile int picorv32_in_isr;

unsigned int _picorv32_maskirq(unsigned volatile int);
unsigned int _picorv32_waitirq(void);
unsigned int _picorv32_timer(unsigned volatile int);
uint64_t __attribute__ ((noinline)) _rdcycle_read(void);

void handle_trap(unsigned int ra, unsigned int irqs_pending);
void timer_isr(void);
void uart_console_isr(void);
void uart_ser_isr(uart_t dev);

/**
 * @brief Enable all maskable interrupts
 */
static inline unsigned int irq_enable(void)
{
    return _picorv32_maskirq(0);
}

/**
 * @brief Disable all maskable interrupts
 */
static inline __attribute__((always_inline)) unsigned int irq_disable(void)
{
    return _picorv32_maskirq(1);
}

/**
 * @brief Restore the state of the IRQ flags
 */
static inline void irq_restore(unsigned int state)
{
    _picorv32_maskirq(state);
}

/**
 * @brief See if the current context is inside an ISR
 */
static inline int irq_is_in(void)
{
    return picorv32_in_isr;
}

#ifdef __cplusplus
}
#endif

#endif /* IRQ_ARCH_H */
/** @} */
