CC = C:/msys64/ucrt64/bin/gcc.exe
CFLAGS = -I./include -Wall -std=c23
TARGET = sea.exe
OUT_DIR = bin

all: $(OUT_DIR)/$(TARGET)

$(OUT_DIR)/$(TARGET): main.c shell.c utils/execute.c utils/parser.c utils/builtins.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ main.c shell.c utils/execute.c utils/parser.c utils/builtins.c

$(OUT_DIR):
	@powershell -Command "if (!(Test-Path '$(OUT_DIR)')) { New-Item -ItemType Directory -Path '$(OUT_DIR)' }"

clean:
	@powershell -Command "if (Test-Path '$(OUT_DIR)') { Remove-Item -Recurse -Force '$(OUT_DIR)' }"

run: $(OUT_DIR)/$(TARGET)
	.\$(OUT_DIR)\$(TARGET)

.PHONY: all clean run
