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

//#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined ENABLE_DEBUG && ENABLE_DEBUG
#define ICODEBUG(msg) \
    { \
        const unsigned char s[] = msg "\n"; \
        for (int i = 0; s[i] != '\0'; i++) \
            *(volatile int*)0x30000000 = s[i]; \
    }
#define ICODEBUG2(format, ...) printf (format "\n", ## __VA_ARGS__) ;
#else
#define ICODEBUG(msg) ;
#define ICODEBUG2(format, ...) ;
#endif

/**
 * @name    Macros for controlling the on-board LEDs
 * @{
 */
#define LED0_PIN            GPIO_PIN(0, 22) /* Red */
#define LED1_PIN            GPIO_PIN(0, 19) /* Green */
#define LED2_PIN            GPIO_PIN(0, 21) /* Blue */

#define LED0_ON             gpio_clear(LED0_PIN)
#define LED0_OFF            gpio_set(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)

#define LED1_ON             gpio_clear(LED1_PIN)
#define LED1_OFF            gpio_set(LED1_PIN)
#define LED1_TOGGLE         gpio_toggle(LED1_PIN)

#define LED2_ON             gpio_clear(LED2_PIN)
#define LED2_OFF            gpio_set(LED2_PIN)
#define LED2_TOGGLE         gpio_toggle(LED2_PIN)
/** @} */

/**
 * @brief   Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

/**
 * @brief   Initialize the board clock to use PLL and faster SPI access.
 */
void board_init_clock(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
