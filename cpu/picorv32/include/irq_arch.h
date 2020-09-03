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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable all maskable interrupts
 */
static inline unsigned int irq_enable(void)
{
    return 0;
}

/**
 * @brief Disable all maskable interrupts
 */
static inline __attribute__((always_inline)) unsigned int irq_disable(void)
{
    return 0;
}

/**
 * @brief Restore the state of the IRQ flags
 */
static inline void irq_restore(unsigned int state)
{
    state = 1;
}

/**
 * @brief See if the current context is inside an ISR
 */
static inline int irq_is_in(void)
{
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* IRQ_ARCH_H */
/** @} */
