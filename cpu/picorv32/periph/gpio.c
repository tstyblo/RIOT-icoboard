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
 * @file        gpio.c
 * @brief       Low-level GPIO implementation
 *
 * @author      Tomas Styblo
 * @}
 */

#include <stdlib.h>
#include <unistd.h>

#define ENABLE_DEBUG 0
#include "board.h"
#include "debug.h"

#include "irq.h"
#include "cpu.h"
#include "periph_cpu.h"
#include "periph_conf.h"
#include "periph/gpio.h"

int gpio_init(gpio_t pin, gpio_mode_t mode)
{
    if (pin >= GPIO_NUMOF) {
        return -1;
    }

    switch (mode) {
        case GPIO_IN:
            DEBUG("setting pin: pin=%d mode=GPIO_IN\n", pin);
            *(volatile uint32_t*)(IOPORT_GPIO_BASE_DIR + IOPORT_GPIO_ADDR * 0x10000) &= ~(1 << pin);
            break;
        case GPIO_OUT:
            DEBUG("setting pin: pin=%d mode=GPIO_OUT\n", pin);
            *(volatile uint32_t*)(IOPORT_GPIO_BASE_DIR + IOPORT_GPIO_ADDR * 0x10000) |= (1 << pin);
            break;
        case GPIO_IN_PU:
            DEBUG("setting pin: UNSUPPORTED MODE GPIO_IN_PU: pin=%d\n", pin);
            // not supported
            return -1;
        default:
            DEBUG("setting pin: UNSUPPORTED MODE: pin=%d\n", pin);
            return -1;
    }

    return 0;
}

inline void gpio_write(gpio_t pin, int value)
{
    if (value) {
        gpio_set(pin);
    }
    else {
        gpio_clear(pin);
    }
}

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

