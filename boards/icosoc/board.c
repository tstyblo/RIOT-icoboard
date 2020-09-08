/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

#define ENABLE_DEBUG 0
#include "debug.h"

#include <string.h>
#include "cpu.h"
#include "board.h"
#include "kernel_init.h"
#include "vfs.h"
#include "fs/devfs.h"
#include "timex.h"
#include "mtd_spi_nor.h"

const ser_device_t ser_devices[SER_DEV_NUMOF] = {
    {
        .dev = 1,
        .addr = 1
    }
};

static const mtd_spi_nor_params_t icosoc_nor_params = {
    .opcode = &mtd_spi_nor_opcode_default,
    .wait_chip_erase = 16LU * US_PER_SEC,
    .wait_sector_erase = 40LU * US_PER_MS,
    .wait_32k_erase = 20LU * US_PER_MS,
    .wait_4k_erase = 10LU * US_PER_MS,
    .wait_chip_wake_up = 1LU * US_PER_MS,
    .spi = ICOSOC_NOR_SPI_DEV,
    .cs = 0,
    .addr_width = 3,
    .mode = 0,
    .clk = 0
};

static mtd_spi_nor_t icosoc_nor_dev = {
    .base = {
        .driver = &mtd_spi_nor_driver,
        .page_size = 256,
        .pages_per_sector = 256,
        .sector_count = (16*16) 
        // 16 MByte in total, the filesystem must start at the 1 MByte offset
    },
    .params = &icosoc_nor_params,
};

mtd_dev_t *mtd0 = (mtd_dev_t *)&icosoc_nor_dev;

static devfs_t icosoc_nor_devfs = {
    .path = "/mtd0",
    .f_op = &mtd_vfs_ops,
    .private_data = &icosoc_nor_dev,
};

int icosoc_nor_init(void);

void board_init(void)
{
    ICODEBUG("board.c - board_init - START");

    ICODEBUG("board.c - cpu_init");
    cpu_init();

    ICODEBUG("board.c - icosoc_nor_init");
    icosoc_nor_init();

    ICODEBUG("board.c - kernel_init");
    kernel_init();

    ICODEBUG("board.c - board_init - END");
}

int icosoc_nor_init(void)
{
    ICODEBUG("board.c - icosoc_nor_init - START");
    int res = mtd_init(mtd0);

    if (res >= 0) {
        ICODEBUG("board.c - icosoc_nor_init - devfs_register");
        /* Register DevFS node */
        devfs_register(&icosoc_nor_devfs);
    }

    ICODEBUG("board.c - icosoc_nor_init - END");
    return res;
}
