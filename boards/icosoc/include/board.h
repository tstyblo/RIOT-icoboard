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

#define IOPORT_CONSOLE  0x30000000
#define IOPORT_SPI_CTRL 0x20000004
#define IOPORT_SPI_DATA 0x20000008
#define IOPORT_GPIO_BASE_DATA 0x20000000
#define IOPORT_GPIO_BASE_DIR  0x20000004
#define IOPORT_GPIO_ADDR      2

#define IOPORT_SER_BASE_DATA    0x20000000
#define IOPORT_SER_BASE_RDLEN   0x20000004
#define IOPORT_SER_BASE_WRLEN   0x20000008

typedef struct {
    uint8_t dev;
    uint8_t addr;
} ser_device_t;

extern const ser_device_t ser_devices[SER_DEV_NUMOF];

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
void timer_isr(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
