#!/usr/bin/env python3
"""Scratch: admit the 0x006045A2 BigArchiveMemberInfo map-family fold pins.

Runs tools/decode_calls.py for the candidate body, harvests its `pin: NAME,RVA`
suggestions, and feeds them to pin_admission.add_pins with
fold-proof=the owner unit. Prints per-pin problems; writes nothing unless every
pin is admitted.

  python3 build/note/6045a2_pins.py
  python3 build/note/6045a2_pins.py --dry      # only list the decoded pins
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

SYMBOL = "?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z"
RVA = "0x006045A2"
SOURCE = "Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp"
NOTES = f"fold-proof={SOURCE}"

PIN_RE = re.compile(r"pin:\s*(\S+?),(0x[0-9A-Fa-f]+)")


def main():
    dry = "--dry" in sys.argv
    out = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "decode_calls.py"), SYMBOL,
         "--rva", RVA, "--source", SOURCE],
        cwd=str(ROOT), capture_output=True, text=True).stdout
    pins = []
    for line in out.splitlines():
        for name, addr in PIN_RE.findall(line):
            if (name, addr.lower()) not in [(n, a.lower()) for n, a in pins]:
                pins.append((name, addr))
    print(f"decoded {len(pins)} pin candidate(s):")
    for name, addr in pins:
        print(f"  {addr}  {name}")
    if dry or not pins:
        return 0
    import pin_admission
    problems = pin_admission.add_pins(pins, notes=NOTES)
    if problems:
        print(f"\nREFUSED ({len(problems)} problem(s)):")
        for problem in problems:
            print(f"  {problem}")
        return 1
    print(f"\nadmitted {len(pins)} pin(s) into reverse/symbols.csv")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
