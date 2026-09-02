#!/usr/bin/env python3
"""dlc — the rules checker for Lab 1.

btest tells you whether your answers are right. This tells you whether you got
them the legal way: only the permitted operators, under the operator budget, no
loops or conditionals, no constants above 0xFF.

    python3 tests/dlc.py bits.c
    python3 tests/dlc.py bits.c --puzzle negate

Operator limits and the puzzle list are read out of the comment headers in
bits.c, so editing a header here changes what is enforced.
"""

import re
import sys

# Puzzles whose headers say "also if, while" — the float ones get ordinary C.
FLOAT_PUZZLES = {"float_neg", "float_i2f", "float_f2i"}

INT_LEGAL = {"!", "~", "&", "^", "|", "+", "<<", ">>"}
ALL_OPS = INT_LEGAL | {"-", "*", "/", "%", "<", ">", "?", ":"}

# Longest first: the tokenizer takes the first match, so "<<" must beat "<".
OPERATORS = [
    "<<=", ">>=", "...",
    "<<", ">>", "&&", "||", "==", "!=", "<=", ">=", "++", "--",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "->",
    "!", "~", "&", "^", "|", "+", "-", "*", "/", "%", "<", ">", "?", ":", "=",
]

# "x >>= b" is a shift plus an assignment. The assignment is not one of the
# counted operators, so score the token as the shift it actually is — the
# original CS:APP dlc does the same, and the canonical howManyBits solution is
# written with >>=. Illegal bases stay illegal: *= is still a multiply.
COMPOUND = {"<<=": "<<", ">>=": ">>", "+=": "+", "-=": "-", "*=": "*",
            "/=": "/", "%=": "%", "&=": "&", "|=": "|", "^=": "^"}

BANNED_KEYWORDS_INT = {"if", "while", "for", "switch", "do", "goto", "else"}
BANNED_KEYWORDS_ALL = {"for", "switch", "goto"}


def strip_comments(text):
    """Blank out comments and string/char literals, preserving line count."""
    out, i, n = [], 0, len(text)
    while i < n:
        two = text[i : i + 2]
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
    """Pull 'Max ops: N' and 'Legal ops: ...' out of each puzzle's comment.

    Some puzzles are tighter than the global set — bitXor allows only ~ and &,
    isTmax bans the shifts — and that restriction IS the exercise. Honour the
    per-puzzle list whenever the header spells one out.
    """
    limits, legal = {}, {}
    for block, name in re.findall(
        r"/\*(.*?)\*/\s*(?:int|unsigned)\s+(\w+)\s*\(", raw, re.S
    ):
        m = re.search(r"Max ops:\s*(\d+)", block)
        if m:
            limits[name] = int(m.group(1))
        m = re.search(r"Legal ops:\s*(.+)", block)
        if m:
            toks = {tok for tok in m.group(1).split() if tok in ALL_OPS}
            # "Any integer/unsigned operations ..." names no operators; those
            # puzzles keep the float rules instead.
            if toks:
                legal[name] = toks
    return limits, legal


def find_bodies(clean):
    """Return {name: (body_text, first_line_number)} by brace matching."""
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
        bodies[name] = (clean[start + 1 : i], clean[: start].count("\n") + 1)
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


def check(path, only=None):
    raw = open(path).read()
    limits, legal_ops = parse_headers(raw)
    bodies = find_bodies(strip_comments(raw))

    problems = 0
    print()
    for name, (body, line) in bodies.items():
        if only and name != only:
            continue
        if name not in limits:
            continue

        is_float = name in FLOAT_PUZZLES
        limit = limits[name]
        msgs = []

        words = set(re.findall(r"\b[a-z]+\b", body))
        banned = BANNED_KEYWORDS_ALL if is_float else BANNED_KEYWORDS_INT
        for kw in sorted(words & banned):
            msgs.append(f"uses '{kw}' — not allowed in this puzzle")

        if re.search(r"\b(float|double)\b", body):
            msgs.append("uses a floating-point type — the whole point is to "
                        "do it with integer operations")
        if re.search(r"\bunion\b", body):
            msgs.append("uses a union — not allowed")
        call = re.search(r"\b(?!if|while|for|switch|return|sizeof\b)(\w+)\s*\(",
                         body)
        if call:
            msgs.append(f"appears to call {call.group(1)}() — not allowed")

        ops = tokenize_ops(body)
        # '=' is assignment, not an operator, and ':' only shows up with '?'.
        counted = [COMPOUND.get(o, o) for o in ops if o not in ("=", ":")]

        if not is_float:
            allowed = legal_ops.get(name, INT_LEGAL)
            illegal = sorted({o for o in counted if o not in allowed})
            if illegal:
                msgs.append("illegal operator(s): " + " ".join(illegal))

        if len(counted) > limit:
            msgs.append(f"{len(counted)} operators, limit is {limit}")

        if not is_float:
            for lit in re.findall(r"\b0[xX]([0-9a-fA-F]+)\b", body):
                if int(lit, 16) > 0xFF:
                    msgs.append(f"constant 0x{lit} exceeds 0xFF")
                    break
            else:
                for lit in re.findall(r"(?<![\w.])(\d+)(?![\w.])", body):
                    # Shift distances are the one place a big-looking decimal
                    # is fine; 31 and 24 are well under the limit anyway.
                    if int(lit) > 0xFF:
                        msgs.append(f"constant {lit} exceeds 255")
                        break

        if msgs:
            problems += 1
            print(f"  \033[31mFAIL\033[0m  {name}  (line {line})")
            for m in msgs:
                print(f"          {m}")
        else:
            note = "" if not counted else f"{len(counted)}/{limit} ops"
            print(f"  \033[32mOK\033[0m    {name:<14s} {note}")

    print()
    print("-------------------------------------------")
    if problems:
        print(f"{problems} puzzle(s) break the rules.")
        print("These cost bonus points, not correctness points — but fix them:")
        print("the operator budget is the actual exercise.")
    else:
        print("All puzzles within the rules.")
    print("-------------------------------------------")
    return 1 if problems else 0


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    src = args[0] if args else "bits.c"
    puzzle = None
    if "--puzzle" in sys.argv:
        puzzle = sys.argv[sys.argv.index("--puzzle") + 1]
    sys.exit(check(src, puzzle))
