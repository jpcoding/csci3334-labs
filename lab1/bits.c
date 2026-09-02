/*
 * Lab 1: Data Representation — Bit Manipulation
 *
 * Rules:
 *   - Only allowed: ! ~ & ^ | + << >>
 *   - No loops, conditionals, macros (unless stated)
 *   - No constants larger than 0xFF
 *   - Integer constants 0..255 (0x00..0xFF)
 *   - No casting (unless stated for float problems)
 *   - Max ops per function shown in comment
 *
 * Replace each "return 2;" with your solution.
 */

/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return 2;
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 2;
}

/*
 * isTmax - returns 1 if x is the maximum two's complement integer,
 *   and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    return 2;
}

/*
 * allOddBits - returns 1 if all odd-numbered bits in word are 1
 *   Bits are numbered from 0 (LSB) to 31 (MSB)
 *   Examples: allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    return 2;
}

/*
 * negate - return -x
 *   Example: negate(1) = -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return 2;
}

/*
 * isAsciiDigit - returns 1 if 0x30 <= x <= 0x39 (ASCII '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1, isAsciiDigit(0x3a) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    return 2;
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2, 4, 5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    return 2;
}

/*
 * isLessOrEqual - if x <= y then return 1, else return 0
 *   Example: isLessOrEqual(4, 5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    return 2;
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f. Both the argument and result are
 *   passed as unsigned ints, but they are interpreted as the bit-level
 *   representation of single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    return 2;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but interpreted as
 *   single-precision floating point.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    return 2;
}

/*
 * howManyBits - return the minimum number of bits required to
 *   represent x in two's complement
 *   Examples:
 *     howManyBits(12) = 5      (01100)
 *     howManyBits(298) = 10    (0100101010)
 *     howManyBits(-5) = 4      (1011)
 *     howManyBits(0)  = 1
 *     howManyBits(-1) = 1
 *     howManyBits(0x80000000) = 32
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int howManyBits(int x) {
    return 2;
}

/* float_f2i - Return bit-level equivalent of (int) f for floating point
 *   argument f. Argument is passed as unsigned int, but interpreted as
 *   the bit-level representation of single-precision floating point.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    return 2;
}
