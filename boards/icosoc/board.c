/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

#include <string.h>
#include "cpu.h"
#include "board.h"

void board_init(void)
{
    _asm_test(0xff);
    ICODEBUG("board.c - board_init - START");

    /* Initialize CPU and clocks */
    cpu_init();

    /* Configure GPIOs for LEDs */
    //gpio_init(LED0_PIN, GPIO_OUT);
    //gpio_init(LED1_PIN, GPIO_OUT);
    //gpio_init(LED2_PIN, GPIO_OUT);

    /* Turn all the LEDs off */
    //LED0_OFF;
    //LED1_OFF;
    //LED2_OFF;
    ICODEBUG("board.c - board_init - END");
}
