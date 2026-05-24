CC = gcc
CFLAGS = -Iinclude -Wall -O2
TARGET = build/myproject
SRC = $(wildcard src/*.c)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
