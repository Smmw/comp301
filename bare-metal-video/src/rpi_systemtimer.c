#include <stdint.h>

#include "rpi_systemtimer.h"

void rpi_systemtimer_blocking_delay_us(uint32_t us) {
  uint32_t time = RPI_SYSTEMTIMER->counter_lo;

  while ((RPI_SYSTEMTIMER->counter_lo - time) < us)
    ;
}
