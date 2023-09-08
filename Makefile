# User-defined compiler (default to gcc)
CC ?= gcc

# Library source and header file
SRC = log4embedded.c
HDR = log4embedded.h

# Output dynamic library name and version
LIB_NAME = log4embedded.so
LIB_VERSION = 1

# Source and object files directory
HDR_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

# Debug and release compiler flags
COMMON_C_FLAGS = -Wall -Wextra -Werror -shared -fPIC -fdiagnostics-color -pedantic -I$(HDR_DIR)/
DEBUG_CFLAGS = $(COMMON_C_FLAGS) -g -O0 -DDEBUG 
RELEASE_CFLAGS = $(COMMON_C_FLAGS) -s -O3

# By default, build the release version
all: release

# Debug build
debug: CFLAGS = $(DEBUG_CFLAGS)
debug: $(LIB_DIR)/$(LIB_NAME)

# Release build
release: CFLAGS = $(RELEASE_CFLAGS)
release: $(LIB_DIR)/$(LIB_NAME)

# mkdir /lib directory if does not exist
$(LIB_DIR)/$(LIB_NAME): $(OBJ_DIR)/$(SRC:.c=.o)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Wl,-soname,$(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION) -o $@ $^ -lc

# mkdir /obj directory if does not exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_DIR)/$(HDR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION)

install:
	cp $(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION) /usr/local/lib/
	ln -sf /usr/local/lib/$(LIB_NAME).$(LIB_VERSION) /usr/local/lib/$(LIB_NAME)
	ldconfig

uninstall:
	rm -f /usr/local/lib/$(LIB_NAME).$(LIB_VERSION) /usr/local/lib/$(LIB_NAME)

.PHONY: all debug release clean install uninstall
