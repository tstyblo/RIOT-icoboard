/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef BOARD_H
#define BOARD_H

#include "stdio.h"
#include "periph_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

// xtimer
#define MODULE_XTIMER_ON_ZTIMER 1
//#define XTIMER_DEV          (TIMER_DEV(0))
//#define XTIMER_HZ           CLOCK_CORECLOCK
//#define XTIMER_WIDTH        (32)
//#define XTIMER_CHAN         (0)

// ztimer
#define CONFIG_ZTIMER_USEC_TYPE     ZTIMER_TYPE_PERIPH_TIMER
#define CONFIG_ZTIMER_USEC_DEV      (TIMER_DEV(0))
#define CONFIG_ZTIMER_USEC_BASE_FREQ CLOCK_CORECLOCK
#define CONFIG_ZTIMER_USEC_WIDTH    (32)

#if defined ENABLE_DEBUG && ENABLE_DEBUG
#define ICODEBUG(msg) \
    { \
        const unsigned char s[] = msg "\n"; \
        for (int i = 0; s[i] != '\0'; i++) \
            *(volatile int*)IOPORT_CONSOLE = s[i]; \
    }
#define ICODEBUG2(format, ...) printf (format "\n", ## __VA_ARGS__) ;
#else
#define ICODEBUG(msg) ;
#define ICODEBUG2(format, ...) ;
#endif

void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
