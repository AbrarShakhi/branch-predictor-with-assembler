# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -Iheaders

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Detect OS and set executable name
ifeq ($(OS),Windows_NT)
    BIN := main.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        BIN := main.out
    else ifeq ($(UNAME_S),Darwin)  # macOS
        BIN := main.out
    else
        BIN := main.out
    endif
endif

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Link object files into final executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Phony targets
.PHONY: all clean
