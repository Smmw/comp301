/*
 * Rasberry Pi UART peripheral.
 * Dan Collins 2014
 */
#ifndef _RPI_UART
#define _RPI_UART

#include <stdint.h>

#define RPI_UART_BASE 0x20201000UL
#define RPI_UART ((rpi_uart_t *)RPI_UART_BASE)

typedef struct {
  volatile uint32_t DR;
  volatile uint32_t RSRECR;
  volatile uint32_t RESERVED0[4];
  volatile uint32_t FR;
  volatile uint32_t RESERVED1;
  volatile uint32_t ILPR;
  volatile uint32_t IBRD;
  volatile uint32_t FBRD;
  volatile uint32_t LCRH;
  volatile uint32_t CR;
  volatile uint32_t IFLS;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
  volatile uint32_t RESERVED2[13];
  volatile uint32_t ITCR;
  volatile uint32_t ITIP;
  volatile uint32_t ITOP;
  volatile uint32_t TDR;
} rpi_uart_t;

void rpi_uart_init(void);
void rpi_uart_puts(char *s);

/* _RPI_UART */
#endif
