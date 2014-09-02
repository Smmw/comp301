/*
 * Raspberry Pi GPIO peripheral.
 * Dan Collins 2014
 */
#ifndef _RPI_GPIO
#define _RPI_GPIO

#include <stdint.h>

#define RPI_GPIO_BASE 0x20200000UL
#define RPI_GPIO ((rpi_gpio_t *)RPI_GPIO_BASE)

typedef struct {
  volatile uint32_t GPFSEL0;
  volatile uint32_t GPFSEL1;
  volatile uint32_t GPFSEL2;
  volatile uint32_t GPFSEL3;
  volatile uint32_t GPFSEL4;
  volatile uint32_t GPFSEL5;
  volatile uint32_t RESERVED0;
  volatile uint32_t GPSET0;
  volatile uint32_t GPSET1;
  volatile uint32_t RESERVED1;
  volatile uint32_t GPCLR0;
  volatile uint32_t GPCLR1;
  volatile uint32_t RESERVED2;
  volatile uint32_t GPLEV0;
  volatile uint32_t GPLEV1;
  volatile uint32_t RESERVED3;
  volatile uint32_t GPEDS0;
  volatile uint32_t GPEDS1;
  volatile uint32_t RESERVED4;
  volatile uint32_t GPREN0;
  volatile uint32_t GPREN1;
  volatile uint32_t RESERVED5;
  volatile uint32_t GPFEN0;
  volatile uint32_t GPFEN1;
  volatile uint32_t RESERVED6;
  volatile uint32_t GPHEN0;
  volatile uint32_t GPHEN1;
  volatile uint32_t RESERVED7;
  volatile uint32_t GPLEN0;
  volatile uint32_t GPLEN1;
  volatile uint32_t RESERVED8;
  volatile uint32_t GPAREN0;
  volatile uint32_t GPAREN1;
  volatile uint32_t RESERVED9;
  volatile uint32_t GPAFEN0;
  volatile uint32_t GPAFEN1;
  volatile uint32_t RESERVED10;
  volatile uint32_t GPPUD;
  volatile uint32_t GPPUDCLK0;
  volatile uint32_t GPPUDCLK1;
} rpi_gpio_t;

/* TODO: Could possibly write an abstraction layer to make it easier
 * to configure GPIO pins. There's a lot of functionality to consider,
 * which makes it farily complex */

/* _RPI_GPIO */
#endif
