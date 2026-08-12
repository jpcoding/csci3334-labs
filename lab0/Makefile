.PHONY: all clean test

CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Werror -g -O0

all: hello leaky llist

hello: hello.c
	$(CC) $(CFLAGS) -o $@ $<

leaky: leaky.c
	$(CC) $(CFLAGS) -o $@ $<

llist: llist.c
	$(CC) $(CFLAGS) -o $@ $<

test: all
	@echo "=== Testing hello ==="
	./hello
	@echo ""
	@echo "=== Testing leaky ==="
	./leaky
	@echo ""
	@echo "=== Testing llist ==="
	./llist
	@echo ""
	@echo "=== Valgrind leaky ==="
	valgrind --leak-check=full ./leaky 2>&1 | grep -E "definitely|indirectly|ERROR"
	@echo ""
	@echo "=== Valgrind llist ==="
	valgrind --leak-check=full ./llist 2>&1 | grep -E "definitely|indirectly|ERROR"

clean:
	rm -f hello leaky llist
