# Lab 1: Data Representation — Bit Manipulation
#
#   make                 compile bits.c and check the rules
#   make check           just the rules check
#   make check P=negate  just one puzzle
#
# What you get here is the RULES check: legal operators, the operator budget,
# no loops or conditionals where they are banned. It cannot tell you whether
# your answer is correct — that is graded after you submit.
#
# So check your work by hand. Every puzzle comment carries worked examples;
# run them through your expression on paper, and try TMin, TMax, 0 and -1 on
# anything involving signs.
#
# Your first build warns about unused parameters once per unfinished puzzle.
# That is not a problem — it is a to-do list. The warnings disappear as you
# start using x and y, and the last one to go is the last puzzle you wrote.
#
# -O0 on purpose: these puzzles are about what you wrote, not about what the
# optimizer can recover from it.

CC     = gcc
CFLAGS = -std=c17 -Wall -Wextra -g -O0

# The correctness grader is the instructor's and is not in the handout. As in
# lab 3, the prerequisite goes through $(wildcard): with the file absent the
# list is empty and `make` still works, instead of dying on a missing target.
BTEST := $(wildcard _instructor/btest.c)

.PHONY: all build check clean

all: build check

build:
	@$(CC) $(CFLAGS) -fsyntax-only bits.c && echo "bits.c compiles."

check: build
	@python3 dlc.py bits.c $(if $(P),--puzzle $(P))

clean:
	rm -f btest

ifeq ($(BTEST),)
.PHONY: test grade
test grade:
	@echo "There is no local correctness check in this handout — correctness is"
	@echo "graded after you submit. 'make check' tells you whether your answer is"
	@echo "legal; the worked examples in each puzzle comment are how you tell"
	@echo "whether it is right."
else
.PHONY: test grade

btest: $(BTEST) bits.c
	$(CC) $(CFLAGS) -o $@ $^

test: btest
	@./btest $(P)

grade: btest
	-@./btest $(P)
	@python3 dlc.py bits.c $(if $(P),--puzzle $(P))
endif
