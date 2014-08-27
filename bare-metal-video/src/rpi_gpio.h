/*
 * Register locations for the Raspberry Pi's GPIO.
 * Copied from:
 * http://www.valvers.com/embedded-linux/raspberry-pi/step01-bare-metal-programming-in-cpt1
 *
 * Dan Collins 2014
 */
#ifndef _RPI_GPIO
#define _RPI_GPIO

/* All other values are relative to this one, which is the memory
 * address of the peripheral. */
#define RPI_GPIO_BASE       0x20200000UL

#define RPI_GPIO_GPFSEL0    0
#define RPI_GPIO_GPFSEL1    1
#define RPI_GPIO_GPFSEL2    2
#define RPI_GPIO_GPFSEL3    3
#define RPI_GPIO_GPFSEL4    4
#define RPI_GPIO_GPFSEL5    5

#define RPI_GPIO_GPSET0     7
#define RPI_GPIO_GPSET1     8

#define RPI_GPIO_GPCLR0     10
#define RPI_GPIO_GPCLR1     11

#define RPI_GPIO_GPLEV0     13
#define RPI_GPIO_GPLEV1     14

#define RPI_GPIO_GPEDS0     16
#define RPI_GPIO_GPEDS1     17

#define RPI_GPIO_GPREN0     19
#define RPI_GPIO_GPREN1     20

#define RPI_GPIO_GPFEN0     22
#define RPI_GPIO_GPFEN1     23
 
#define RPI_GPIO_GPHEN0     25
#define RPI_GPIO_GPHEN1     26
 
#define RPI_GPIO_GPLEN0     28
#define RPI_GPIO_GPLEN1     29
 
#define RPI_GPIO_GPAREN0    31
#define RPI_GPIO_GPAREN1    32
 
#define RPI_GPIO_GPAFEN0    34
#define RPI_GPIO_GPAFEN1    35

#define RPI_GPIO_GPPUD      37
#define RPI_GPIO_GPPUDCLK0  38
#define RPI_GPIO_GPPUDCLK1  39

extern volatile unsigned int *rpi_gpio;

/* _RPI_GPIO */
#endif
