#include "rpi_gpio.h"

volatile unsigned int *rpi_gpio =
  (unsigned int *)RPI_GPIO_BASE;
