/*
 * Copyright (C) 2017 Ken Rabold
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
 * @brief           CPU specific configuration options
 *
 * @author          Tomas Styblo
 */

#ifndef CPU_CONF_H
#define CPU_CONF_H

/**
 * @name Configuration of default stack sizes
 * @{
 */
#ifndef THREAD_EXTRA_STACKSIZE_PRINTF
#define THREAD_EXTRA_STACKSIZE_PRINTF   (512)
#endif
#ifndef THREAD_STACKSIZE_DEFAULT
#define THREAD_STACKSIZE_DEFAULT        (1024*8)
#endif
#ifndef THREAD_STACKSIZE_IDLE
#define THREAD_STACKSIZE_IDLE           (512)
#endif
/** @} */

/**
 * @brief   Declare the heap_stats function as available
 */
#define HAVE_HEAP_STATS

/**
 * @brief   This arch uses the inlined irq API.
 */
#define IRQ_API_INLINED     (1)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_H */
/** @} */
