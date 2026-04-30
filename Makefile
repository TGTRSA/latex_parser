CC = gcc
CFLAGS = -g -O0 -Wall -Wextra
LDFLAGS = -g -O0
OBJS = main.o lexer.o parser.o
TARGET = lexer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean