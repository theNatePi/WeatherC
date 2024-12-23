CC = gcc
CFLAGS = -Wall -Wextra -I include/ -llgpio
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Find all .c files in SRCDIR
SOURCES := $(shell find $(SRCDIR) -name '*.c')
# Generate object file names
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# Name of your executable
TARGET = $(BINDIR)/main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)