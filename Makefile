TARGET = dist/shell.exe
SRC = main.c utils/parser.c core/shell.c
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
CC = gcc
CFLAGS = -I./include -I./utils

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf $(OBJDIR)