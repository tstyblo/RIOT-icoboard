#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"
#include "mtd.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_CORECLOCK 20000000UL

// UART
#define UART_NUMOF          2
#define IOPORT_CONSOLE      0x30000000
#define SER_DEV_NUMOF       1
#define CONSOLE_UART_DEV    UART_DEV(0) // do not change this
#define SER0_UART_DEV       UART_DEV(1) // do not change this
#define STDIO_UART_DEV      CONSOLE_UART_DEV // this can be changed to SER0_UART_DEV
#define UART_RX_DELAY       1000000
#define IOPORT_SER_BASE_DATA    0x20000000
#define IOPORT_SER_BASE_RDLEN   0x20000004
#define IOPORT_SER_BASE_WRLEN   0x20000008
#define IOPORT_SER0_ADDR        1

// SPI
#define SPI_NUMOF 1
#define IOPORT_SPI_CTRL 0x20000004
#define IOPORT_SPI_DATA 0x20000008
#define PERIPH_SPI_NEEDS_TRANSFER_BYTE  1
#define PERIPH_SPI_NEEDS_TRANSFER_REG   1
#define PERIPH_SPI_NEEDS_TRANSFER_REGS  1

// MTD SPI
#define ICOSOC_NOR_SPI_DEV SPI_DEV(0)
extern mtd_dev_t *mtd0;
#define MTD_0 mtd0

// GPIO
#define GPIO_NUMOF 32
#define IOPORT_GPIO_BASE_DATA   0x20000000
#define IOPORT_GPIO_BASE_DIR    0x20000004
#define IOPORT_GPIO_ADDR        2

// timer
#define TIMER_NUMOF 1

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
