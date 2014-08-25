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

#define GPIO_BASE 0x20200000

#define GPIO_GPFSEL1 1
#define GPIO_GPCLR0 10
#define GPIO_GPSET0 7

volatile unsigned int *gpio = (unsigned int *)GPIO_BASE;
volatile unsigned int timer;

void kernel_main(unsigned int r0, unsigned int r1,
		 unsigned int atags) {
  /* Set the LED pin as an output */
  gpio[GPIO_GPFSEL1] |= (1 << 18);

  while(1) {
    for (timer = 0; timer < 500000; timer++)
      ;

    gpio[GPIO_GPCLR0] = (1 << 16);

    for (timer = 0; timer < 500000; timer++)
      ;

    gpio[GPIO_GPSET0] = (1 << 16);
  }
}

void exit(int code) {
  while(1)
    ;
}
