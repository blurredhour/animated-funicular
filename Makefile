CC      = gcc
TARGET  = chip8
SRCS    = main.c #$(wildcard *.c)
OBJS    = $(SRCS:.c=.o)

CFLAGS  = -Wall -Wextra -std=c11 -g $(shell sdl3-config --cflags)
LDFLAGS = $(shell sdl3-config --libs)

# Add extra SDL libs here if you use them, e.g. -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LDLIBS  = -lm -lSDL3

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
