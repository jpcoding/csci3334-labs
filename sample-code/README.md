# Sample code

Small, standalone C programs from the lectures. Each lecture has its own
directory so you can compile, run and edit the examples without picking them
out of the slides.

```text
sample code/
  lecture02/   bits, bytes, characters and integers
  lecture03/   addresses, pointers, arrays and strings
  lecture04/   structs, alignment, unions and bit fields
  lecture05/   integer arithmetic, overflow and the bugs it causes
  lecture06/   x86-64 registers, data movement and addressing
```

## Lecture 2

The files follow the order of the slides:

| File | Slides |
|------|--------|
| `01-notations.c` | Writing the Same Number Three Ways · Telling `printf` What You Handed It |
| `02-characters.c` | One Byte, Two Readings · Characters Are Just Numbers |
| `03-bitwise.c` | Bitwise Operations, One Column at a Time · De Morgan's Laws · Shifting Bits |
| `04-masks.c` | Test, Set, Clear, Toggle |
| `05-integers.c` | What Two's Complement Means · Sign Extension · Truncation · Size of Integer Types |
| `06-byte-order.c` | Byte Ordering (Endianness) |
| `07-single-number.c` | Bit Tricks in the Wild |

## Lecture 3

Addresses printed by these are whatever that run happened to get — they change
every time you run them, which is itself worth seeing.

| File | Slides |
|------|--------|
| `01-pointers.c` | Pointers Demystified · Three Things, Kept Straight · Two Pointers, One Object |
| `02-arrays.c` | Pointer Arithmetic · An Array Is Not a Pointer · Arrays Decay to Pointers |
| `03-strings.c` | Strings Are Char Arrays |
| `04-2d-arrays.c` | Two-Dimensional Arrays · Why the Order Matters |
| `05-stack.c` | The Stack |
| `06-double-pointers.c` | Why `char **argv` · A Matrix, Two Ways |

## Lecture 4

| File | Slides |
|------|--------|
| `00-print-binary.c` | Warm-Up: Printing a Number in Binary · Run It: Old Friends in Binary |
| `01-structs.c` | Three Arrays, or One? · Filling One In |
| `02-pointers.c` | Structs Through a Pointer · Passing One to a Function |
| `03-layout.c` | The `offsetof` Macro · An Array Multiplies It |
| `04-nested.c` | Structs Inside Structs |
| `05-union.c` | A Union Holds One Member at a Time · Why You Would Want That · The Other Use: The Same Bytes, Read Twice |
| `06-file-header.c` | When the Layout Is Not Yours to Choose |
| `07-aos-soa.c` | AI Systems Connection |
| `08-bitfields.c` | — (Practice 4; bit fields are mentioned, not lectured) |

`00-print-binary.c` is the warm-up. Keep `print_binary` around — it comes back
later in the course.

`07-aos-soa.c` is a timing program, so the Makefile builds it with `-O2`. Your
numbers will not match the slide's; the byte counts will.

## Lecture 5

| File | Slides |
|------|--------|
| `00-rewind.c` | Rewind: The Box From Lecture 2 · The Odometer Rolls Over |
| `01-wrap.c` | Overflow Is a Clock, Not a Crash |
| `01b-promotion.c` | The Size of the Box Decides |
| `02-signed.c` | Adding Two Signed Bytes · Ask Before You Add |
| `03-intmin.c` | `INT_MIN` Has No Twin |
| `04-average.c` | The Midpoint That Overflowed · Run It: A Negative Array Index |
| `05-compare.c` | Signed and Unsigned: Do Not Guess · Run It: The Check That Let It Through |
| `06-alloc.c` | The Allocation That Wraps |
| `07-shift.c` | Division · Shifting a Negative Is Not Dividing It |
| `08-quantize.c` | AI Systems Connection · Run It: The Accumulator That Wrapped |
| `09-ubsan.c` | Find It Before It Finds You |

`00-rewind.c` reuses `print_binary` from lecture 4, narrowed to one byte.

`01b-promotion.c` is built for running live: four numbered sections, and a
header comment listing types to swap in and what each one changes.

`09-ubsan.c` is deliberately broken. `make ubsan` builds the sanitized version:

```bash
make ubsan && ./09-ubsan-san 2147483647 1
```

`05-compare.c` switches `-Wsign-compare` off with a pragma so the bug can run
at all. That warning is the real defence — never write the pragma yourself.

## Building

Everything at once, from the lecture directory:

```bash
make        # build them all
make run    # build, then run each in order
make clean  # remove the binaries
```

Or one at a time:

```bash
gcc -std=c17 -Wall -Wextra -Werror 03-bitwise.c -o 03-bitwise
./03-bitwise
```

Every example compiles clean with those flags. If yours does not, the warning
is telling you something — read it before you silence it.

## Lecture 6

These are the first programs meant to be **read as assembly**, not only run.
`make asm` emits Intel-syntax x86-64; `make dis` adds the byte encodings.
Both work on an Apple Silicon Mac — clang cross-compiles — though the x86-64
binaries themselves will not run there.

| File | Slides |
|------|--------|
| `01-first-look.c` | Run It: Get the Assembly Yourself · Run It: One Line of C, One Addressing Mode · Your First Whole Function · A Loop, Line by Line · Run It: The Bytes Are Right There |
| `02-lea.c` | Run It: `lea` as the Cheap Multiplier |
| `03-shapes.c` | The Four Shapes, in a Register |
| `04-sizes.c` | Run It: Writing Through the Narrow Names |

