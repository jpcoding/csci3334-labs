# Lab 1: Data Representation — Bit Manipulation
#
#   make                  compile bits.c, then check it
#   make check            just the checker
#   make check P=negate   just one puzzle
#
# check.py answers both questions about a puzzle:
#
#   is it legal?   the operator rules — legal operators, the budget, no loops
#                  or conditionals where they are banned
#   is it right?   your function is called with a few hundred thousand values
#                  and compared against the same answer computed in Python
#
# A failure prints the exact input that broke it. Feed that value back in and
# trace it by hand — that is almost always faster than staring at the code.
#
# Your first build warns about unused parameters once per unfinished puzzle.
# That is not a problem — it is a to-do list. The warnings disappear as you
# start using x and y, and the last one to go is the last puzzle you wrote.
#
# -O0 on purpose: these puzzles are about what you wrote, not about what the
# optimizer can recover from it.

CC     = gcc
CFLAGS = -std=c17 -Wall -Wextra -g -O0

# btest is a second, independent grader kept on the instructor's side. As in
# lab 3, the prerequisite goes through $(wildcard): with the file absent the
# list is empty and `make` still works, instead of dying on a missing target.
BTEST := $(wildcard _instructor/btest.c)

.PHONY: all build check clean

all: build check

build:
	@$(CC) $(CFLAGS) -fsyntax-only bits.c && echo "bits.c compiles."

check: build
	@python3 check.py bits.c $(if $(P),-p $(P)) || true

clean:
	rm -f btest

ifneq ($(BTEST),)
.PHONY: grade

btest: $(BTEST) bits.c
	$(CC) $(CFLAGS) -o $@ $^

# Both graders, so the two implementations keep each other honest.
grade: btest
	-@./btest $(P)
	@python3 check.py bits.c $(if $(P),-p $(P))
endif
