/*
 * Register locations for the Raspberry Pi's System Timer
 * Copied from:
 * http://www.valvers.com/embedded-linux/raspberry-pi/step03-bare-metal-programming-in-c-pt3
 *
 * Dan Collins 2014
 */
#ifndef _RPI_SYSTIMER
#define _RPI_SYSTIMER

#include <stdint.h>

#define RPI_SYSTEMTIMER_BASE 0x20003000

typedef struct {
  volatile uint32_t control_status;
  volatile uint32_t counter_lo;
  volatile uint32_t counter_hi;
  volatile uint32_t compare0;
  volatile uint32_t compare1;
  volatile uint32_t compare2;
  volatile uint32_t compare3;
} rpi_systemtimer_t;

extern volatile rpi_systemtimer_t *rpi_systemtimer;

void rpi_systemtimer_blocking_delay_us(uint32_t us);

/* _RPI_SYSTIMER */
#endif
