# Basic Makefile

target=translator

SRCS_C = \
	main.c

SRCS_H =

CFLAGS = -O0 -g
LFLAGS = -lz -lpthread

OBJS = $(addprefix build/, $(SRCS_C:.c=.o))

all: $(target)

build/%o: %c
	$(MKDIR) -p build
	$(CC) $< $(CFLAGS) -c -o $@

$(target): $(OBJS)
	$(CC) $^ $(LFLAGS) $(CFLAGS) -o $@

clean:
	$(RM) -rf build


# Toolchain
MKDIR=mkdir
CC=gcc
RM=rm
