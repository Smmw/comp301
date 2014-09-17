#include <stdint.h>

#include "rpi_uart.h"
#include "rpi_gpio.h"
#include "rpi_systemtimer.h"

/* Credit to http://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C#include.2Fuart.h */
void rpi_uart_init(void) {
  /* Make sure UART is disabled so that we can change parameters */
  RPI_UART->CR = 0;

  /* Configure GPIO for Tx(GPIO14) and Rx(GPIO15) */
  /* Disable pull up/down for GPIO14/15 */
  RPI_GPIO->GPPUD = 0;
  rpi_systemtimer_blocking_delay_us(1); /* TODO: This should only be
					 * 150 clock cycles */
  RPI_GPIO->GPPUDCLK0 = (1 << 14) | (1 << 15);
  rpi_systemtimer_blocking_delay_us(1);
  RPI_GPIO->GPPUDCLK0 = 0;

  /* Clear UART interrupt flags */
  RPI_UART->ICR = 0x7ff;

  /* Set baud rate to 115200.
   * BAUDDIV = (FUARTCLK / (16 * baud))
   *         = (3MHz / (16 * 115200))
   *         = 1.627604167
   * IBRD    = 1
   * FBRD    = IBRD * ((0.627604167 * 64) + 0.5)
   *         = 40.666666
   *         = 41
   */
  RPI_UART->IBRD = 1;
  RPI_UART->FBRD = 41;

  /* Enable FIFO, 8bit transmission (1 stop, no parity) */
  RPI_UART->LCRH = 0x70;
  /* Mask all interrupts */
  RPI_UART->IMSC = 0x7f2;
  /* Enable transmitter. TODO: Enable receiver. */
  RPI_UART->CR = 0x0101;
}

static void putc(char c) {
  /* Wait for room in transmit FIFO */
  while (RPI_UART->FR & (1 << 5))
    ;

  RPI_UART->DR = c;
}

void rpi_uart_puts(char *s) {
  while (*s)
    putc(*s++);
}
