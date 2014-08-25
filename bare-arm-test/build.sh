#!/bin/bash
# This should probably be done in a Makefile, but I was lazy...

# Build Environment
export PATH=$PATH:~/Downloads/gcc-arm-none-eabi-4_8-2014q1/bin

# Create the objects
arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c main.c -o main.o
arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c cstartup.c -o cstartup.o
arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c startup.S -o startup.o

# Link it all together
arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -Wl,-T,rpi.x main.o cstartup.o startup.o -o kernel.elf

# Create the binary
arm-none-eabi-objcopy -O binary kernel.elf kernel.img

