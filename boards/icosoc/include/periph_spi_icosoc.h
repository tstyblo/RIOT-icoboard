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

void spi_begin();
void spi_end();

uint8_t spi_xfer(uint8_t value);

void flash_write_enable();

void flash_write(int addr, uint8_t *data, int n);

void flash_read(int addr, uint8_t *data, int n);

int flash_wait();

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_SPI_ICOSOC_H */
/** @} */
