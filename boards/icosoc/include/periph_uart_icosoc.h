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

void icosoc_ser_read(int ser_addr, void *data, int len);
void icosoc_ser_write(int ser_addr, const void *data, int len);
int icosoc_ser_read_nb(int ser_addr, void *data, int maxlen);
int icosoc_ser_write_nb(int ser_addr, const void *data, int maxlen);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_SPI_ICOSOC_H */
/** @} */
