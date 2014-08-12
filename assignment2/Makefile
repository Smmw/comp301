# Basic Makefile

target=scheduler

SRCS_C = \
	main.c \
	list.c

SRCS_H =

CFLAGS=-Os

OBJS = $(addprefix build/, $(SRCS_C:.c=.o))

all: output/$(target)

build/%o: %c
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -c -o $@

output/$(target): $(OBJS)
	$(MKDIR) -p output
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) -rf build
	$(RM) -rf output


# Toolchain
MKDIR=mkdir
CC=gcc
RM=rm
