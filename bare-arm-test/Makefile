# Makefile to build for the Raspberry Pi
# Dan Collins 2014

# Project C sources
SRCS_C = \
	main.c \
	cstubs.c \
	cstartup.c

# Project Assembly sources
SRCS_S = \
	startup.S

# Project headers
SRCS_H =

# List of object files we need to make
# You wont need to edit this
OBJS = $(addprefix build/, $(SRCS_C:.c=.o))
OBJS += $(addprefix build/, $(SRCS_S:.S=.o))

# Compiler Flags
CFLAGS = -O0 --std=gnu99
CFLAGS += -mfpu=vfp -mfloat-abi=hard 
CFLAGS += -march=armv6zk -mtune=arm1176jzf-s
CFLAGS += -nostartfiles

# Linker Flags
LFLAGS = -Wl,-T,rpi.x

.PHONY: all clean

all: output/kernel.elf

build/%.o: %.c
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -c -o $@

build/%.o: %.S
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -c -o $@

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
