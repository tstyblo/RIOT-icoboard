/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef PERIPH_SPI_H
#define PERIPH_SPI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#include "periph_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

inline int gpio_read(gpio_t pin)
{
    return ((*(volatile uint32_t*)(IOPORT_GPIO_BASE_DATA + IOPORT_GPIO_ADDR * 0x10000)) & (1 << pin)) ? 1 : 0;
}

inline void gpio_set(gpio_t pin)
{
    *((volatile uint32_t*)(IOPORT_GPIO_BASE_DATA + IOPORT_GPIO_ADDR * 0x10000)) |= (1 << pin);
}

inline void gpio_clear(gpio_t pin)
{
    *((volatile uint32_t*)(IOPORT_GPIO_BASE_DATA + IOPORT_GPIO_ADDR * 0x10000)) &= ~(1 << pin);
}

inline void gpio_toggle(gpio_t pin)
{
    *((volatile uint32_t*)(IOPORT_GPIO_BASE_DATA + IOPORT_GPIO_ADDR * 0x10000)) ^= (1 << pin);
}

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_SPI_ICOSOC_H */
/** @} */
