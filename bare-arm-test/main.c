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

#define GPIO_BASE 0x20200000

#define GPIO_GPFSEL1 1
#define GPIO_GPCLR0 10
#define GPIO_GPSET0 7

volatile unsigned int *gpio = (unsigned int *)GPIO_BASE;
volatile unsigned int timer;

void kernel_main(unsigned int r0, unsigned int r1,
		 unsigned int atags) {
  unsigned int i;
  unsigned int *ctr;

  /* Set the LED pin as an output and turn it off */
  gpio[GPIO_GPFSEL1] |= (1 << 18);
  gpio[GPIO_GPSET0] = (1 << 16);

  /* Allocate memory for the counters */
  ctr = (unsigned int *)malloc(2 * sizeof(unsigned int));
  if (ctr == NULL) {
    while(1)
      ;
  }

  /* Zero the counters */
  for (i = 0; i < 2; i++)
    ctr[i] = 0;

  while(1) {
    for (ctr[0] = 0; ctr[0] < 500000; ctr[0]++)
      ;

    gpio[GPIO_GPCLR0] = (1 << 16);

    for (ctr[1] = 0; ctr[1] < 500000; ctr[1]++)
      ;

    gpio[GPIO_GPSET0] = (1 << 16);
  }
}

void exit(int code) {
  while(1)
    ;
}
