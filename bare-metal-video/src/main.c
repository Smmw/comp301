/*
 * This is a simple test of bare metal code running on ARM and QEMU.
 * It will be similar to the raspberry pi in the hopes that I can port
 * MINIX to the raspberry pi.
 *
 * This project was copied from:
 * http://imvoid.wordpress.com/2013/05/17/bare-metal-programming-for-arm-versatilepb-hello-world/
 *
 * Dan Collins 2014
 * COMP301-14B
 */
#include <stdlib.h>
#include <stdint.h>

#include "rpi_gpio.h"
#include "rpi_systemtimer.h"

void kernel_main(unsigned int r0, unsigned int r1,
		 unsigned int atags) {
  /* Set the LED pin as an output and turn it off */
  rpi_gpio[RPI_GPIO_GPFSEL1] |= (1 << 18);
  rpi_gpio[RPI_GPIO_GPSET0] = (1 << 16);

  while(1) {
    rpi_gpio[RPI_GPIO_GPCLR0] = (1 << 16);
    rpi_systemtimer_blocking_delay_us(500000);

    rpi_gpio[RPI_GPIO_GPSET0] = (1 << 16);
    rpi_systemtimer_blocking_delay_us(500000);
  }
}

void exit(int code) {
  while(1)
    ;
}
