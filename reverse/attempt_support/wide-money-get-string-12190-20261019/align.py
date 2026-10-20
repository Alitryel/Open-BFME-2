# align.py -- handoff copy of build/note/insn_align.py (0x12190 diagnostics).
# Run from the repo root: python reverse/attempt_support/wide-money-get-string-12190-20261019/align.py \
#   build/note/stash.dis 0x12190 2802
# The body .dis file comes from build/note/mine_dis.py (capstone, body-relative addresses).
"""insn_align: align the compiled body against retail with difflib.

The alignment key is (mnemonic, operands) with every number masked, so frame
shifts and immediates do not break the pairing; the printed diff shows the raw
operands, so offsets stay visible where it matters.

usage: python build/note/insn_align.py [mine.dis] [rva] [size]
"""
import difflib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import retail_body as RB  # noqa: E402

mine_file = sys.argv[1] if len(sys.argv) > 1 else "build/note/stash.dis"
rva = int(sys.argv[2], 0) if len(sys.argv) > 2 else 0x12190
size = int(sys.argv[3], 0) if len(sys.argv) > 3 else 2802

NUM = re.compile(r"0x[0-9a-f]+|\b\d+\b")


def key(mn, ops):
    return f"{mn} {NUM.sub('#', ops)}".strip()


retail = [(ins.rva - rva, ins.mnem, ins.ops) for ins in RB.disasm(rva, size)]
mine = []
for line in (ROOT / mine_file).read_text(encoding="utf-8", errors="replace").splitlines():
    m = re.match(r"([0-9a-f]{8})\s+((?:[0-9a-f]{2} )+)\s*([a-z0-9_.]+)\s*(.*)$", line)
    if m:
        mine.append((int(m.group(1), 16), m.group(3), m.group(4).strip()))

print(f"retail {len(retail)} insns, mine {len(mine)} insns")
ka = [key(mn, ops) for _, mn, ops in retail]
kb = [key(mn, ops) for _, mn, ops in mine]
sm = difflib.SequenceMatcher(None, ka, kb, autojunk=False)
ops = sm.get_opcodes()
counts = {}
for tag, i1, i2, j1, j2 in ops:
    counts[tag] = counts.get(tag, 0) + max(i2 - i1, j2 - j1)
print("opcode counts:", counts)
print()
for tag, i1, i2, j1, j2 in ops:
    if tag == "equal":
        continue
    print(f"--- {tag} retail[{i1}:{i2}] mine[{j1}:{j2}]  "
          f"(retail +0x{retail[i1][0]:x}..+0x{retail[i2-1][0]:x}, "
          f"mine +0x{mine[j1][0]:x})" if i2 > i1 and j2 > j1 else f"--- {tag} retail[{i1}:{i2}] mine[{j1}:{j2}]")
    for k in range(i1, i2):
        print(f"  R {k:4d} +0x{retail[k][0]:04x} {retail[k][1]} {retail[k][2]}")
    for k in range(j1, j2):
        print(f"  M {k:4d} +0x{mine[k][0]:04x} {mine[k][1]} {mine[k][2]}")
