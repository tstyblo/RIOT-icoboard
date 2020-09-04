/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cpu_picorv32
 * @ingroup     cpu
 * @brief       Common implementations and headers for picorv32
 * @{
 *
*/

#ifndef CPU_H
#define CPU_H

#include "thread.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Initialization of the CPU
 */
void cpu_init(void);

/**
 * @brief   Initialization of interrupts
 */
void irq_init(void);

int _asm_test(unsigned int a0);
int _asm_test_c(unsigned int a0, unsigned int a1, unsigned int a2);

static inline void cpu_print_last_instruction(void)
{
    /* This function must exist else RIOT won't compile */
}

#ifdef __cplusplus
}
#endif

#endif /* CPU_H */
/** @} */
