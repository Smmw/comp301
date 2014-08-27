#include <stdint.h>

#include "rpi_systemtimer.h"

volatile rpi_systemtimer_t *rpi_systemtimer =
  (rpi_systemtimer_t *)RPI_SYSTEMTIMER_BASE;

void rpi_systemtimer_blocking_delay_us(uint32_t us) {
  volatile uint32_t time = rpi_systemtimer->counter_lo;

  while ((rpi_systemtimer->counter_lo - time) < us)
    ;
}
