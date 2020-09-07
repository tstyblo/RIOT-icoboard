#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"
#include "mtd.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_CORECLOCK 20000000U

// UART
#define UART_NUMOF 1
#define _UART_RX_DELAY 1000000

// SPI
#define SPI_NUMOF 1
#define PERIPH_SPI_NEEDS_TRANSFER_BYTE  1
#define PERIPH_SPI_NEEDS_TRANSFER_REG   1
#define PERIPH_SPI_NEEDS_TRANSFER_REGS  1

// MTD SPI
#define ICOSOC_NOR_SPI_DEV SPI_DEV(0)
extern mtd_dev_t *mtd0;
#define MTD_0 mtd0

// timer
#define TIMER_NUMOF 1

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
