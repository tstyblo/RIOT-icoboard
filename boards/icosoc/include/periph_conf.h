#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"
#include "mtd.h"

#ifdef __cplusplus
extern "C" {
#endif

// UART
#define UART_NUMOF          2
#define SER_DEV_NUMOF       1
#define CONSOLE_UART_DEV    UART_DEV(0) // do not change this
#define STDIO_UART_DEV      UART_DEV(1) // you can change this
#define UART_RX_DELAY       1000000

// SPI
#define SPI_NUMOF 1
#define PERIPH_SPI_NEEDS_TRANSFER_BYTE  1
#define PERIPH_SPI_NEEDS_TRANSFER_REG   1
#define PERIPH_SPI_NEEDS_TRANSFER_REGS  1

// MTD SPI
#define ICOSOC_NOR_SPI_DEV               SPI_DEV(0)
extern mtd_dev_t *mtd0;
#define MTD_0 mtd0

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
