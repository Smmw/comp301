#include <stdint.h>

#include "rpi_mailbox.h"
#include "rpi_uart.h"

uint32_t rpi_mailbox_read(uint8_t channel) {
  uint32_t data;
  uint8_t read_channel;

  rpi_uart_puts("Reading from mailbox... ");

  /* Read the mailbox until we read the channel we want */
  do {
    while(RPI_MAILBOX->status & (1 << 30) == 0)
      ;

    /* Extract channel from mailbox */
    data = RPI_MAILBOX->read;
    read_channel = data & 0xf;
  } while (channel != read_channel);

  /* We do the shift after we've read the correct data to save loop
   * cycles */
  data >>= 4;

  rpi_uart_puts("done.\n");

  return data;
}

void rpi_mailbox_write(uint8_t channel, uint32_t data) {
  rpi_uart_puts("Writing to mailbox... ");

  while(RPI_MAILBOX->status & (1 << 31) == 0)
    ;
  
  /* Combine channel and data */
  data <<= 4;
  data |= channel & 0xf;

  RPI_MAILBOX->write = data;
  
  rpi_uart_puts("done.\n");
}
