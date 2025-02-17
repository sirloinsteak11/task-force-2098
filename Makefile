CC = gcc
CFLAGS = -g -Wall -fsanitize=address -fsanitize=undefined

SRC = $(wildcard ./*.c)
OBJ = $(SRC:%.c=%.o)


TARGET = game

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean: 
	rm $(TARGET) $(OBJ)

.PHONY: run clean