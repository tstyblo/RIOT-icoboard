/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "cpu.h"
#include "board.h"

#define ENABLE_DEBUG 0
#include "debug.h"

extern char _sheap;            /* Heap markers from the ld script */
extern char _eheap;
extern char _sp;
extern char _sp_isr;

void pm_reboot(void)
{
    //
}

void cpu_init(void)
{
    ICODEBUG("cpu.c - cpu_init - START");
    irq_init();
    
    ICODEBUG("cpu.c - periph_init");
    periph_init();

    ICODEBUG("cpu.c - stdio_init");
    stdio_init();

    DEBUG("_sheap=%p _eheap=%p _sp=%p _sp_isr=%p\n", &_sheap, &_eheap, &_sp, &_sp_isr);

    ICODEBUG("cpu.c - cpu_init - END");
}

int _asm_test_c(unsigned int a0, unsigned int a1, unsigned int a2)
{
    DEBUG("a0=0x%08x a1=0x%08x a2=0x%08x\n", a0, a1, a2);
    return a0;
}
