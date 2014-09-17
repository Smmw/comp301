/*
 * Register locations for the Raspberry Pi's VideoCore Mailbox.
 * Based on:
 * http://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/screen01.html
 *
 * Dan Collins
 */
#ifndef _RPI_MAILBOX
#define _RPI_MAILBOX

#include <stdint.h>

#define RPI_MAILBOX_BASE 0x2000B880UL
#define RPI_MAILBOX ((rpi_mailbox_t *)RPI_MAILBOX_BASE)

typedef struct {
  volatile uint32_t read;
  volatile uint32_t RESERVED0[3];
  volatile uint32_t poll;
  volatile uint32_t sender;
  volatile uint32_t status;
  volatile uint32_t configuration;
  volatile uint32_t write;
} rpi_mailbox_t;

typedef struct {
  /* Physical width and height of display. */
  uint32_t phys_width;
  uint32_t phys_height;
  /* Width and height of virtual display. The GPU will scale this to
   * fit onto the physical display. */
  uint32_t virt_width;
  uint32_t virt_height;
  /* Number of bytes per row. This is provided by the GPU. */
  uint32_t gpu_pitch;
  /* Number of bits per pixel. Valid values include (but my not be
   * limited to) 16, 24 and 32. */
  uint32_t bit_depth;
  /* Offset from the top left corner to start drawing from. */
  uint32_t x;
  uint32_t y;
  /* Pointer to the GPU frame buffer and the number of bytes in the
   * buffer. These are provided by the GPU. */
  uint32_t gpu_pointer;
  uint32_t gpu_size;
} rpi_mailbox_framebuffer_t;

uint32_t rpi_mailbox_read(uint8_t channel);
void rpi_mailbox_write(uint8_t channel, uint32_t data);

/* _RPI_MAILBOX */
#endif
