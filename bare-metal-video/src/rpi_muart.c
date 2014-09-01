#include <stdint.h>

#include "rpi_muart.h"
#include "rpi_gpio.h"
#include "rpi_systemtimer.h"

/* Create a reference to the Mini UART */
volatile rpi_muart_t *rpi_muart =
  (rpi_muart_t *)RPI_MUART_BASE;

void rpi_muart_init(void) {
  unsigned int tmp;

  /* Set GPIO pin as output. This is done with a read, modify and 
   * write so other configurations don't get wiped! */
  tmp = rpi_gpio[RPI_GPIO_GPFSEL1];
  tmp &= ~(7 << 12);
  tmp |= (2 << 12);
  rpi_gpio[RPI_GPIO_GPFSEL1] = tmp;

  /* Disable the pull up / pull down resistor on GPIO14 (Tx) */
  rpi_gpio[RPI_GPIO_GPPUD] = 0;
  rpi_systemtimer_blocking_delay_us(1);
  rpi_gpio[RPI_GPIO_GPPUDCLK0] = (1 << 14);
  rpi_systemtimer_blocking_delay_us(1);
  rpi_gpio[RPI_GPIO_GPPUDCLK0] = 0;

  /* Enable auxillary peripherals */
  volatile unsigned int *aux_enable = (unsigned int *)RPI_AUX_ENABLE;
  *aux_enable = 1;

  /* Configure Mini UART (115200, 8n1) */
  rpi_muart->irq_enable = 0; /* Ensure interrupts are disabled */
  rpi_muart->irq_stat = 0x06; /* Clear Rx and Tx FIFO */
  rpi_muart->line_ctrl = 3; /* This sets a bit that isn't documented,
			     * but it doesn't work without it! It also
			     * sets the UART to 8 bit mode. */
  rpi_muart->baud = 270; /* 115200 @ 250MHz */
  rpi_muart->extra_ctrl = 0x02; /* Enable Tx */
}

void rpi_muart_puts(char *s) {
  while (*s) {
    /* Wait for room in FIFO */
    while (rpi_muart->line_stat & 0x20 == 0)
      ;
    /* Send character */
    rpi_muart->data = *s++;
  }
}
