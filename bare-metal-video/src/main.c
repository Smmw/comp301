/*
 * This code demonstrates the use of the video coprocessor on the
 * raspberry pi. The demo makes use of a flashing LED and also a UART
 * for debug purposes.
 *
 * Dan Collins 2014
 * COMP301-14B
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "rpi_gpio.h"
#include "rpi_systemtimer.h"
#include "rpi_uart.h"
#include "rpi_mailbox.h"

void kernel_main(unsigned int r0, unsigned int r1,
		 unsigned int atags) {
#if 0
  /* This memory is below the kernel and stack, and would otherwise
   * be unused. */
  rpi_mailbox_framebuffer_t *framebuf =
    (rpi_mailbox_framebuffer_t *)0x1000;
#endif

  volatile uint32_t *mailbuf = (uint32_t *)0x1000;
  uint32_t fb_x, fb_y;
  
  mailbuf[0] = 8 * 4;
  mailbuf[1] = 0;
  mailbuf[2] = 0x40003;
  mailbuf[3] = 8;
  mailbuf[4] = 0;
  mailbuf[5] = 0;
  mailbuf[6] = 0;
  mailbuf[7] = 0;
  rpi_mailbox_write(8, (uint32_t)mailbuf);
  rpi_mailbox_read(8);

  if (mailbuf[1] != 0x80000000) {
    rpi_uart_puts("Failed to get resolution\n");
    while (1)
      ;
  }

  fb_x = mailbuf[5];
  fb_y = mailbuf[6];
  if (fb_x == 0 || fb_y == 0) {
    rpi_uart_puts("Invalid resolution\n");
    while (1)
      ;
  }

  uint32_t i = 1;
  mailbuf[i++] = 0;
  
  mailbuf[i++] = 0x00048003;
  mailbuf[i++] = 8;
  mailbuf[i++] = 8;
  mailbuf[i++] = fb_x;
  mailbuf[i++] = fb_y;
  
  mailbuf[i++] = 0x00048004;
  mailbuf[i++] = 8;
  mailbuf[i++] = 8;
  mailbuf[i++] = fb_x;
  mailbuf[i++] = fb_y;
  
  mailbuf[i++] = 0x00048005;
  mailbuf[i++] = 4;
  mailbuf[i++] = 4;
  mailbuf[i++] = 16;

  mailbuf[i++] = 0x00048001;
  mailbuf[i++] = 8;
  mailbuf[i++] = 4;
  mailbuf[i++] = 16;
  mailbuf[i++] = 0;

  mailbuf[i++] = 0;

  mailbuf[0] = i * 4;

  rpi_mailbox_write(8, (uint32_t)mailbuf);
  rpi_mailbox_read(8);

  if (mailbuf[1] != 0x80000000) {
    rpi_uart_puts("Failed to set up frame buffer\n");
    while (1)
      ;
  }

#if 0
  /* Frame buffer settings */
  framebuf->phys_width = 1024;
  framebuf->phys_height = 768;
  framebuf->virt_width = 1024;
  framebuf->virt_height = 768;
  framebuf->gpu_pitch = 0;
  framebuf->bit_depth = 16;
  framebuf->x = 0;
  framebuf->y = 0;
  framebuf->gpu_pointer = 0;
  framebuf->gpu_size = 0;
#endif

  /* Set the LED pin as an output and turn it off */
  RPI_GPIO->GPFSEL1 |= (1 << 18);
  RPI_GPIO->GPSET0 = (1 << 16);

  /* Set up uart */
  rpi_uart_init();
  rpi_uart_puts("Video demo starting up\n");

#if 0
  /* Ask the GPU for a frame buffer */
  rpi_mailbox_write(8, (uint32_t)framebuf);
  /* Make sure it was successful */
  if (rpi_mailbox_read(8) != 0) {
    rpi_uart_puts("Failed to get frame buffer from GPU\n");
    while (1)
      ;
  }
#endif

  while(1) {
    RPI_GPIO->GPCLR0 = (1 << 16);
    rpi_systemtimer_blocking_delay_us(500000);

    RPI_GPIO->GPSET0 = (1 << 16);
    rpi_systemtimer_blocking_delay_us(500000);
  }
}

void exit(int code) {
  while(1)
    ;
}
