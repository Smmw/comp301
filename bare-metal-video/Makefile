# Makefile to build for the Raspberry Pi
# Dan Collins 2014

# Project C sources
SRCS_C = \
	main.c \
	cstubs.c \
	cstartup.c \
	rpi_systemtimer.c \
	rpi_uart.c

# Project Assembly sources
SRCS_S = \
	startup.S

# Project headers
SRCS_H = \
	rpi_gpio.h \
	rpi_systemtimer.h \
	rpi_muart.h

# List of object files we need to make
OBJS = $(addprefix build/, $(SRCS_C:.c=.o))
OBJS += $(addprefix build/, $(SRCS_S:.S=.o))

# Dependancies
DEPS := $(OBJS:.o=.d)

# Compiler Flags
CFLAGS = -O0 --std=gnu99
CFLAGS += -mfpu=vfp -mfloat-abi=hard 
CFLAGS += -march=armv6zk -mtune=arm1176jzf-s
CFLAGS += -nostartfiles

# Linker Flags
LFLAGS = -Wl,-T,rpi.x

#
# Build Rules
#
.PHONY: all clean

all: output/kernel.elf

-include $(DEPS)

build/%.o: src/%.c
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -MMD -c -o $@

build/%.o: src/%.S
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -MMD -c -o $@

output/kernel.elf: $(OBJS)
	$(MKDIR) -p output
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
	$(OBJCOPY) -O binary output/kernel.elf output/kernel.img

clean:
	$(RM) -rf build
	$(RM) -rf output

# Tools
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
MKDIR = mkdir
RM = rm
