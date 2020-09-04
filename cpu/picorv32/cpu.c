/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#define ENABLE_DEBUG 1
#include "debug.h"
#include "cpu.h"
#include "board.h"

extern char _sheap;            /* Heap markers from the ld script */
extern char _eheap;
extern char _sp_isr;

void pm_set_lowest(void)
{
    //
}

void pm_reboot(void)
{
    //
}

void cpu_init(void)
{
    irq_init();

    ICODEBUG("cpu.c - cpu_init - START");
    DEBUG("_sheap=%p, _eheap=%p, _sp_isr=%p\n", &_sheap, &_eheap, &_sp_isr);
    _asm_test(0xff);
    
    /* Initialize clock */
    //clock_init();

    //ICODEBUG("cpu.c - cpu_init - nanostubs_init")
    //nanostubs_init();

    ICODEBUG("cpu.c - cpu_init - puts");
    puts("puts() - test");

    /* Initialize static peripheral */
    stdio_init();
    ICODEBUG("cpu.c - cpu_init - periph_init");
    periph_init();

    ICODEBUG("cpu.c - cpu_init - kernel_init");
    kernel_init();

    ICODEBUG("cpu.c - cpu_init - END");
}

int _asm_test_c(unsigned int a0, unsigned int a1, unsigned int a2)
{
    DEBUG("a0=0x%08x a1=0x%08x a2=0x%08x\n", a0, a1, a2);
    return a0;
}
