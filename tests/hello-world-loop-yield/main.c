/*
 * Copyright (C) 2014 Freie Universität Berlin
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application with looping and yielding test
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 * @author      Tomas Styblo
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include "board.h"
#include "cpu.h"

int main(void)
{
    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);

    for (unsigned int i = 0; i < 10; i++) {
        puts("Hello World!");
        thread_yield();
    }

    return 0;
}
