#!/usr/bin/env python3
"""Lab 1 checker: is your answer legal, and is it right?

    python3 check.py bits.c              both checks, all twelve puzzles
    python3 check.py bits.c -p negate    just one puzzle
    python3 check.py bits.c --rules      skip the correctness run

The rules half reads each puzzle's own comment — its "Legal ops" and "Max ops"
— and reports what you used against what you are allowed.

The correctness half builds bits.c as a shared library, calls each function
through ctypes, and compares against the same value computed in Python. The
expected values are written in ordinary Python, which is not C: reading them
tells you what the answer is, never how to reach it under the operator rules.
That is the whole exercise, and it is left to you.

Each puzzle runs in its own subprocess with a timeout, so a loop that never
ends or a crash reports against that puzzle instead of taking the checker
down with it.
"""

import argparse
import ctypes
import json
import os
import re
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))

GREEN, RED, DIM, OFF = "\033[32m", "\033[31m", "\033[2m", "\033[0m"
if not sys.stdout.isatty():
    GREEN = RED = DIM = OFF = ""

# ---------------------------------------------------------------- rules

INT_LEGAL = {"!", "~", "&", "^", "|", "+", "<<", ">>"}
ALL_OPS = INT_LEGAL | {"-", "*", "/", "%", "<", ">", "?", ":"}

OPERATORS = [
    "<<=", ">>=", "...",
    "<<", ">>", "&&", "||", "==", "!=", "<=", ">=", "++", "--",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "->",
    "!", "~", "&", "^", "|", "+", "-", "*", "/", "%", "<", ">", "?", ":", "=",
]

# "x >>= b" is a shift plus an assignment; the assignment is not a counted
# operator, so score the token as the shift it is.
COMPOUND = {"<<=": "<<", ">>=": ">>", "+=": "+", "-=": "-", "*=": "*",
            "/=": "/", "%=": "%", "&=": "&", "|=": "|", "^=": "^"}

BANNED_INT = {"if", "while", "for", "switch", "do", "goto", "else"}
BANNED_ALL = {"for", "switch", "goto"}

FLOAT_PUZZLES = {"float_neg", "float_i2f", "float_f2i"}

ORDER = ["bitXor", "tmin", "isTmax", "allOddBits", "negate", "isAsciiDigit",
         "conditional", "isLessOrEqual", "float_neg", "howManyBits",
         "float_i2f", "float_f2i"]
REQUIRED = set(ORDER) - {"float_i2f", "float_f2i"}


def strip_comments(text):
    """Blank out comments and literals, preserving line count."""
    out, i, n = [], 0, len(text)
    while i < n:
        two = text[i:i + 2]
        if two == "/*":
            j = text.find("*/", i + 2)
            j = n if j == -1 else j + 2
            out.append("".join(c if c == "\n" else " " for c in text[i:j]))
            i = j
        elif two == "//":
            j = text.find("\n", i)
            j = n if j == -1 else j
            out.append(" " * (j - i))
            i = j
        elif text[i] in "\"'":
            q, j = text[i], i + 1
            while j < n and text[j] != q:
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(" " * (j - i))
            i = j
        else:
            out.append(text[i])
            i += 1
    return "".join(out)


def parse_headers(raw):
    """Each puzzle's 'Max ops' and, where it names one, its 'Legal ops'."""
    limits, legal = {}, {}
    for block, name in re.findall(
        r"/\*(.*?)\*/\s*(?:int|unsigned)\s+(\w+)\s*\(", raw, re.S
    ):
        m = re.search(r"Max ops:\s*(\d+)", block)
        if m:
            limits[name] = int(m.group(1))
        m = re.search(r"Legal ops:\s*(.+)", block)
        if m:
            toks = {t for t in m.group(1).split() if t in ALL_OPS}
            if toks:
                legal[name] = toks
    return limits, legal


def find_bodies(clean):
    bodies = {}
    for m in re.finditer(r"^(?:int|unsigned)\s+(\w+)\s*\([^)]*\)\s*\{", clean, re.M):
        name, start = m.group(1), m.end() - 1
        depth, i = 0, start
        while i < len(clean):
            if clean[i] == "{":
                depth += 1
            elif clean[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        bodies[name] = (clean[start + 1:i], clean[:start].count("\n") + 1)
    return bodies


def tokenize_ops(body):
    ops, i, n = [], 0, len(body)
    while i < n:
        for op in OPERATORS:
            if body.startswith(op, i):
                ops.append(op)
                i += len(op)
                break
        else:
            i += 1
    return ops


def check_rules(path, only=None):
    """Return {puzzle: (ok, [messages], used, limit)}."""
    raw = open(path).read()
    limits, legal = parse_headers(raw)
    bodies = find_bodies(strip_comments(raw))
    out = {}
    for name, (body, line) in bodies.items():
        if name not in limits or (only and name != only):
            continue
        is_float = name in FLOAT_PUZZLES
        msgs = []

        words = set(re.findall(r"\b[a-z]+\b", body))
        for kw in sorted(words & (BANNED_ALL if is_float else BANNED_INT)):
            msgs.append(f"uses '{kw}' — not allowed in this puzzle")
        if re.search(r"\b(float|double)\b", body):
            msgs.append("uses a floating-point type — do it with integer operations")
        if re.search(r"\bunion\b", body):
            msgs.append("uses a union — not allowed")
        call = re.search(r"\b(?!if|while|for|switch|return|sizeof\b)(\w+)\s*\(", body)
        if call:
            msgs.append(f"appears to call {call.group(1)}() — not allowed")

        ops = tokenize_ops(body)
        counted = [COMPOUND.get(o, o) for o in ops if o not in ("=", ":")]
        if not is_float:
            allowed = legal.get(name, INT_LEGAL)
            illegal = sorted({o for o in counted if o not in allowed})
            if illegal:
                msgs.append("illegal operator(s): " + " ".join(illegal))
        used = len(counted)
        if used > limits[name]:
            msgs.append(f"{used} operators, limit is {limits[name]}")
        out[name] = (not msgs, msgs, used, limits[name], line)
    return out


# ---------------------------------------------------------------- correctness

def s32(v):
    v &= 0xFFFFFFFF
    return v - (1 << 32) if v >> 31 else v


def u32(v):
    return v & 0xFFFFFFFF


def f32(bits):
    return struct.unpack(">f", struct.pack(">I", u32(bits)))[0]


def bits_of(f):
    return struct.unpack(">I", struct.pack(">f", f))[0]


def expected(name, args):
    """What the answer should be, in plain Python."""
    if name == "bitXor":
        return s32(args[0] ^ args[1])
    if name == "tmin":
        return -2147483648
    if name == "isTmax":
        return 1 if args[0] == 2147483647 else 0
    if name == "allOddBits":
        return 1 if u32(args[0]) & 0xAAAAAAAA == 0xAAAAAAAA else 0
    if name == "negate":
        return s32(-args[0])
    if name == "isAsciiDigit":
        return 1 if 0x30 <= args[0] <= 0x39 else 0
    if name == "conditional":
        return args[1] if args[0] else args[2]
    if name == "isLessOrEqual":
        return 1 if args[0] <= args[1] else 0
    if name == "howManyBits":
        x = args[0]
        if x < 0:
            x = ~x
        return x.bit_length() + 1
    if name == "float_neg":
        uf = u32(args[0])
        f = f32(uf)
        if f != f:                      # NaN passes through unchanged
            return uf
        return bits_of(-f)
    if name == "float_i2f":
        return bits_of(float(args[0]))  # pack() rounds to nearest even, as C does
    if name == "float_f2i":
        f = f32(args[0])
        if f != f or f >= 2147483648.0 or f < -2147483648.0:
            return -2147483648
        return int(f)                   # truncates toward zero
    raise KeyError(name)


# (argument types, return type). float_i2f takes a signed int and returns a bit
# pattern; float_f2i is the other way round. Getting these backwards feeds a
# function arguments it can never receive in C.
SIGS = {
    "bitXor":        ("ii", "i"), "tmin":       ("",  "i"),
    "isTmax":        ("i",  "i"), "allOddBits": ("i", "i"),
    "negate":        ("i",  "i"), "isAsciiDigit": ("i", "i"),
    "conditional":   ("iii", "i"), "isLessOrEqual": ("ii", "i"),
    "float_neg":     ("u",  "u"), "howManyBits": ("i", "i"),
    "float_i2f":     ("i",  "u"), "float_f2i":  ("u", "i"),
}

NASTY = [0, 1, -1, 2, -2, 3, -3, 7, 8, -8, 10, 16, 0x30, 0x39, 0x2F, 0x3A,
         127, 128, 255, 256, 0x55555555, -0x55555556, 0x7FFFFFFF, -2147483648,
         2147483646, -2147483647, 0x1000, -0x1000, 1000, -2000]
NASTY_U = [0x00000000, 0x80000000, 0x7F800000, 0xFF800000,  # ±0, ±inf
           0x7FC00000, 0xFFC00000,                          # NaN
           0x00000001, 0x807FFFFF,                          # denormals
           0x3F800000, 0xBF800000, 0x40400000, 0x4B7FFFFF,
           0x4F000000, 0xCF000000, 0x5F000000]


def prng():
    s = 1
    while True:
        s = (s * 1103515245 + 12345) & 0xFFFFFFFF
        yield s


def run_one(sopath, name, samples):
    """Called in a child process. Returns (checked, first failure or None)."""
    lib = ctypes.CDLL(sopath)
    fn = getattr(lib, name)
    argkinds, retkind = SIGS[name]
    arity = len(argkinds)
    fn.argtypes = [ctypes.c_uint if k == "u" else ctypes.c_int for k in argkinds]
    fn.restype = ctypes.c_uint if retkind == "u" else ctypes.c_int

    # Values must be in range for the parameter's own type, or we are testing
    # something C could never hand the function.
    def coerce(v, k):
        return u32(v) if k == "u" else s32(v)

    pool = NASTY_U if argkinds and argkinds[0] == "u" else NASTY
    rand = prng()
    cases, checked = [], 0
    if arity == 0:
        cases = [()]
    else:
        for v in pool:
            cases.append(tuple(coerce(v, k) for k in argkinds))
        if arity >= 2:
            for a in pool[:12]:
                for b in pool[:12]:
                    vals = [a, b] + [0] * (arity - 2)
                    cases.append(tuple(coerce(v, k) for v, k in zip(vals, argkinds)))
        for _ in range(samples):
            cases.append(tuple(coerce(next(rand), k) for k in argkinds))

    for args in cases:
        got = fn(*args)
        want = expected(name, list(args))
        if retkind == "u":
            got, want = u32(got), u32(want)
        checked += 1
        if got != want:
            return checked, {"args": list(args), "got": got, "want": want}
    return checked, None


def check_correctness(sopath, name, samples, timeout):
    """Run one puzzle in a child so a hang or crash is contained."""
    cmd = [sys.executable, os.path.abspath(__file__), "--child",
           sopath, name, str(samples)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return None, "did not finish — an infinite loop?"
    if r.returncode != 0:
        return None, "crashed while running (segfault or bad memory access)"
    try:
        return json.loads(r.stdout), None
    except json.JSONDecodeError:
        return None, "produced no result"


def build_shared(src):
    so = os.path.join(tempfile.mkdtemp(), "bits.so")
    r = subprocess.run(
        ["gcc", "-std=c17", "-O0", "-shared", "-fPIC", src, "-o", so],
        capture_output=True, text=True)
    return (so, None) if r.returncode == 0 else (None, r.stderr.strip())


# ---------------------------------------------------------------- report

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source", nargs="?", default="bits.c")
    ap.add_argument("-p", "--puzzle")
    ap.add_argument("--rules", action="store_true", help="skip the correctness run")
    ap.add_argument("--samples", type=int, default=20000)
    ap.add_argument("--timeout", type=float, default=20.0)
    ap.add_argument("--child", nargs=3, help=argparse.SUPPRESS)
    args = ap.parse_args()

    if args.child:
        so, name, samples = args.child
        checked, bad = run_one(so, name, int(samples))
        print(json.dumps({"checked": checked, "bad": bad}))
        return 0

    rules = check_rules(args.source, args.puzzle)
    if not rules:
        print(f"no puzzles found in {args.source}", file=sys.stderr)
        return 2

    so = err = None
    if not args.rules:
        so, err = build_shared(args.source)
        if err:
            print(f"\n{RED}{args.source} does not compile{OFF}\n")
            print(err[:1200])
            return 2

    print()
    bad_rules = bad_correct = 0
    total_checked = 0
    for name in ORDER:
        if name not in rules:
            continue
        ok, msgs, used, limit, line = rules[name]
        tag = "" if name in REQUIRED else f" {DIM}(bonus){OFF}"

        verdict, detail = f"{GREEN}OK{OFF}  ", ""
        if not args.rules:
            res, why = check_correctness(so, name, args.samples, args.timeout)
            if why:
                verdict, detail = f"{RED}FAIL{OFF}", why
                bad_correct += 1
            else:
                total_checked += res["checked"]
                if res["bad"]:
                    b = res["bad"]
                    a = ", ".join(str(v) for v in b["args"])
                    verdict = f"{RED}FAIL{OFF}"
                    detail = f"({a}) returned {b['got']}, expected {b['want']}"
                    bad_correct += 1

        print(f"  {verdict}  {name:15}{tag}")
        if detail:
            print(f"          {detail}")
        for m in msgs:
            print(f"          {DIM}rules:{OFF} {m}")
        if not ok:
            bad_rules += 1
        elif args.rules or not detail:
            pass

    print("\n" + "-" * 52)
    if not args.rules:
        print(f"  {total_checked} checks run")
        print(f"  correctness: {'all puzzles pass' if not bad_correct else str(bad_correct) + ' puzzle(s) wrong'}")
    print(f"  rules:       {'all within the rules' if not bad_rules else str(bad_rules) + ' puzzle(s) break the rules'}")
    if bad_rules:
        print(f"  {DIM}operator limits cost bonus points, not correctness points{OFF}")
    print("-" * 52)
    return 1 if (bad_rules or bad_correct) else 0


if __name__ == "__main__":
    sys.exit(main())
