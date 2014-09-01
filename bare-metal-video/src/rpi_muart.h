#ifndef _RPI_MUART
#define _RPI_MUART

#include <stdint.h>

#define RPI_AUX_ENABLE 0x20215004
#define RPI_MUART_BASE 0x20215040

typedef struct {
  volatile uint32_t data;
  volatile uint32_t irq_enable;
  volatile uint32_t irq_stat;
  volatile uint32_t line_ctrl;
  volatile uint32_t modem_ctrl;
  volatile uint32_t line_stat;
  volatile uint32_t modem_stat;
  volatile uint32_t scratch;
  volatile uint32_t extra_ctrl;
  volatile uint32_t extra_stat;
  volatile uint32_t baud;
} rpi_muart_t;

extern volatile rpi_muart_t *rpi_muart;

void rpi_muart_init(void);
void rpi_muart_puts(char *s);

/* _RPI_MUART */
#endif
