CC = gcc
CFLAGS = -I./include
TARGET = sea.exe
OUT_DIR = bin

# Build the shell
all: $(OUT_DIR)/$(TARGET)

$(OUT_DIR)/$(TARGET): main.c shell.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$(TARGET) main.c shell.c

$(OUT_DIR):
	@if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"

# Clean up
clean:
	@if exist "$(OUT_DIR)\$(TARGET)" del /f "$(OUT_DIR)\$(TARGET)"
	@if exist "$(OUT_DIR)" rmdir "$(OUT_DIR)"

# Run the program
run: $(OUT_DIR)/$(TARGET)
	.\$(OUT_DIR)\$(TARGET)

.PHONY: all clean run
