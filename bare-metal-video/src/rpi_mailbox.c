#include <stdint.h>

#include "rpi_mailbox.h"

/* Create the mailbox registers */
volatile uint32_t *rpi_mailbox_read =
  (uint32_t *)RPI_MAILBOX_READ;
volatile uint32_t *rpi_mailbox_poll =
  (uint32_t *)RPI_MAILBOX_POLL;
volatile uint32_t *rpi_mailbox_sender =
  (uint32_t *)RPI_MAILBOX_SENDER;
volatile uint32_t *rpi_mailbox_status =
  (uint32_t *)RPI_MAILBOX_STATUS;
volatile uint32_t *rpi_mailbox_configuration =
  (uint32_t *)RPI_MAILBOX_CONFIGURATION;
volatile uint32_t *rpi_mailbox_write =
  (uint32_t *)RPI_MAILBOX_WRITE;


uint32_t rpi_mailbox_r(uint8_t channel) {
  uint32_t data;
  uint8_t read_channel;

  /* Read the mailbox until we read the channel we want */
  do {
    while(*rpi_mailbox_status & (1 << 30) == 0)
      ;

    /* Extract channel from mailbox */
    data = *rpi_mailbox_read;
    read_channel = data & 0xf;
  } while (channel != read_channel);

  /* We do the shift after we've read the correct data to save loop
   * cycles */
  data >>= 4;

  return data;
}

void rpi_mailbox_w(uint8_t channel, uint32_t data) {
  while(*rpi_mailbox_status & (1 << 31) == 0)
    ;
  
  /* Combine channel and data */
  data <<= 4;
  data |= channel & 0xf;

  *rpi_mailbox_write = data;
}
