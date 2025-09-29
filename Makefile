TARGET = shell.exe
SRC = main.c utils/parser.c core/shell.c
OBJDIR = obj
OBJ = $(OBJDIR)/main.o $(OBJDIR)/parser.o $(OBJDIR)/shell.o
CC = gcc
CFLAGS = -I./include -Wall -Wextra -std=c99

all: $(TARGET)

$(TARGET): $(OBJ) | create_dirs
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/parser.o: utils/parser.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/shell.o: core/shell.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR):
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

create_dirs:
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

clean:
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(TARGET)" del /f "$(TARGET)"

rebuild: clean all

.PHONY: all clean rebuild create_dirs