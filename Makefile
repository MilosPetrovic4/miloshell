CC = gcc
CFLAGS = -Wall -Wextra -I./include
SUBDIRS = builtins utils shortcuts

# BUILTINS_OBJS = $(wildcard build/builtins/*.o)
# UTILS_OBJS = $(wildcard build/utils/*.o)
# SHORTCUTS_OBJS = $(wildcard build/shortcuts/*.o)

BUILTINS_OBJS = build/builtins/bcompile.o build/builtins/cd.o
UTILS_OBJS = build/utils/utils.o build/utils/forker.o
SHORTCUTS_OBJS = build/shortcuts/cmd_history.o

SUB_OBJS = $(BUILTINS_OBJS) $(UTILS_OBJS) $(SHORTCUTS_OBJS)

MAIN = miloshell
MAIN_OBJ = build/miloshell.o
TARGET = bin/miloshell

.PHONY: all clean

all: subdirs $(SUB_OBJS) $(MAIN_OBJ) $(TARGET)

subdirs:
	$(MAKE) -C builtins
	$(MAKE) -C utils
	$(MAKE) -C shortcuts

$(BUILTINS_OBJS):
	$(MAKE) -C builtins

$(UTILS_OBJS):
	$(MAKE) -C utils

$(SHORTCUTS_OBJS):
	$(MAKE) -C shortcuts

$(MAIN_OBJ): $(MAIN).c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJ) $(SUB_OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(MAKE) -C builtins clean
	$(MAKE) -C utils clean
	$(MAKE) -C shortcuts clean
	rm -rf build bin
