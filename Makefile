CC := gcc
CLFAGS :=

all: elf.c
	$(CC) -o elf $^

clean:
	rm -rf elf

.PHONY: all clean
