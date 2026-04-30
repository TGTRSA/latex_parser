CC = gcc
# CFLAGS = -g -O0 -Wall -Wextra
# CFLAGS = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion \
#          -Wformat=2 -Wstrict-prototypes -Wold-style-definition \
#          -Wmissing-prototypes -Wmissing-declarations -Wunreachable-code \
#          -Wcast-align -Wcast-qual -Wwrite-strings \
#          -Wundef -Wpointer-arith -Wbad-function-cast
CFLAGS = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion
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