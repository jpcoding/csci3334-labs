# Lecture 2 examples. `make` builds them all; `make run` runs them in order.
CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -Werror
PROGS   = 01-notations 02-characters 03-bitwise 04-masks 05-integers 06-byte-order \
          07-single-number

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

run: all
	@for p in $(PROGS); do \
	    echo "=== $$p ==="; ./$$p; echo; \
	done

clean:
	rm -f $(PROGS)

.PHONY: all run clean
