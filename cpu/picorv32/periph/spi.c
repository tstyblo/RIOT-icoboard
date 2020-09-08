/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_icosoc
 * @ingroup     drivers_periph_spi
 *
 * @{
 *
 * @file        spi.c
 * @brief       Low-level SPI driver implementation
 *
 * @author      Tomas Styblo
 *
 * @}
 */

#include "board.h"
#include "mutex.h"
#include "assert.h"
#include "periph/spi.h"
#include "periph_spi_icosoc.h"

#define ENABLE_DEBUG        (0)
#include "debug.h"

static mutex_t lock;

void spi_begin(void)
{   
    DEBUG_PUTS("spi_begin");
    *(volatile uint32_t*)IOPORT_SPI_CTRL &= ~8;
}   
    
void spi_end(void)
{
    DEBUG_PUTS("spi_end");
    *(volatile uint32_t*)IOPORT_SPI_CTRL |= 8;
}       
            
uint8_t spi_xfer(uint8_t value)
{
    *(volatile uint32_t*)IOPORT_SPI_DATA = value;
    return *(volatile uint32_t*)IOPORT_SPI_DATA;
}           
            
void flash_write_enable(void)
{
    spi_begin();
    spi_xfer(0x06);
    spi_end();
}

void flash_write(int addr, uint8_t *data, int n)
{
    spi_begin();
    spi_xfer(0x02);
    spi_xfer(addr >> 16);
    spi_xfer(addr >> 8);
    spi_xfer(addr);
    while (n--)
        spi_xfer(*(data++));
    spi_end();
}

void flash_read(int addr, uint8_t *data, int n)
{
    spi_begin();
    spi_xfer(0x03);
    spi_xfer(addr >> 16);
    spi_xfer(addr >> 8);
    spi_xfer(addr);
    while (n--)
        *(data++) = spi_xfer(0);
    spi_end();
}

int flash_wait(void)
{
    while (1)
    {
        spi_begin();
        spi_xfer(0x05);
        int status = spi_xfer(0);
        spi_end();
        
        if ((status & 0x01) == 0)
            break;
    }

    return 0;
}


void spi_init(spi_t dev)
{
    DEBUG("spi_init: dev=%d\n", dev);

    /* make sure given bus device is valid */
    assert(dev < SPI_NUMOF);

    /* initialize the buses lock */
    mutex_init(&lock);
}


void spi_init_pins(spi_t dev)
{
    assert(dev < SPI_NUMOF);
    // unused
}

int spi_init_cs(spi_t dev, __attribute__ ((unused)) spi_cs_t cs)
{
    DEBUG("spi_init_cs: dev=%d\n", dev);
    (void)dev;
    assert(dev < SPI_NUMOF);

    return SPI_OK;
}

int spi_acquire(spi_t dev, spi_cs_t cs, __attribute__ ((unused)) spi_mode_t mode,
                __attribute__ ((unused)) spi_clk_t clk)
{
    DEBUG("spi_acquire: dev=%d\n", dev);
    (void)cs;
    assert(dev < SPI_NUMOF);

    mutex_lock(&lock);

    return SPI_OK;
}

void spi_release(spi_t dev)
{
    DEBUG("spi_release: dev=%d\n", dev);
    (void)dev;

    mutex_unlock(&lock);
}

void spi_transfer_bytes(spi_t dev, __attribute__ ((unused)) spi_cs_t cs, bool cont,
                        const void *out_, void *in_, size_t len)
{
    DEBUG("spi_transfer_bytes: dev=%d out_=%p in_=%p cont=%d, len=%d\n", dev, out_, in_, cont, len);
    assert(dev < SPI_NUMOF);
    assert((out_ || in_) && len > 0);

    const uint8_t *out = out_;
    uint8_t *in = in_;
    uint8_t junk;
    static int in_session = 0;

    if (!in_session) {
        spi_begin();
        in_session = 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (out) {
            *(volatile uint32_t*)IOPORT_SPI_DATA = out[i];
            // DEBUG("spi_xfer - OUT: 0x%X\n", out[i]);
        }
        else {
            *(volatile uint32_t*)IOPORT_SPI_DATA = 0;
        }
        if (in) {
            in[i] = *(volatile uint32_t*)IOPORT_SPI_DATA;
            // DEBUG("spi_xfer - IN: 0x%X\n", in[i]);
        }
        else {
            junk = *(volatile uint32_t*)IOPORT_SPI_DATA;
        }
    }

    if (in_session && !cont) {
        spi_end();
        in_session = 0;
    }
}
