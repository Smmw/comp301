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

#define GPIO_BASE 0x20200000
#define GPIO_GPFSEL1 1
#define GPIO_GPCLR0 10
#define GPIO_GPSET0 7

#define RPI_SYSTIMER_BASE 0x20003000

typedef struct {
  volatile uint32_t control_status;
  volatile uint32_t counter_lo;
  volatile uint32_t counter_hi;
  volatile uint32_t compare0;
  volatile uint32_t compare1;
  volatile uint32_t compare2;
  volatile uint32_t compare3;
} rpi_sys_timer_t;

volatile unsigned int *gpio = (unsigned int *)GPIO_BASE;
static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

void delay_us(uint32_t us);

void kernel_main(unsigned int r0, unsigned int r1,
		 unsigned int atags) {
  /* Set the LED pin as an output and turn it off */
  gpio[GPIO_GPFSEL1] |= (1 << 18);
  gpio[GPIO_GPSET0] = (1 << 16);

  while(1) {
    gpio[GPIO_GPCLR0] = (1 << 16);
    delay_us(500000);
    gpio[GPIO_GPSET0] = (1 << 16);
    delay_us(500000);
  }
}

void delay_us(uint32_t us) {
  volatile uint32_t ts = rpiSystemTimer->counter_lo;

  while ((rpiSystemTimer->counter_lo - ts) < us)
    ;
}

void exit(int code) {
  while(1)
    ;
}
