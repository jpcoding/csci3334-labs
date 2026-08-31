# Sample code

Small, standalone C programs from the lectures. Each lecture has its own
directory so you can compile, run and edit the examples without picking them
out of the slides.

```text
sample code/
  lecture01/   introduction examples
  lecture02/   bits, bytes, characters and integers
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

`bit-basics.c` is a scratch file that touches a bit of everything — handy for
experimenting, not tied to any one slide.

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
