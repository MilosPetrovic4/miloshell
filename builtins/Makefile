# builtins/Makefile
CC = gcc
CFLAGS = -Wall -Wextra -I../include

DIR := $(notdir $(CURDIR))
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, ../build/$(DIR)/%.o, $(SRC))

all: prepare_build $(OBJ)

prepare_build:
	@mkdir -p ../build/$(DIR)

../build/$(DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ../build/$(DIR)/*.o
