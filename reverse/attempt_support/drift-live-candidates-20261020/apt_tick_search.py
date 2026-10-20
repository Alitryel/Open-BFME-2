#!/usr/bin/env python3
"""Scratch: find the inlined isTickAnimation assert copies in retail.

Pattern: push <line>; push <path>; push "this"; call [assert]
Our source's helper asserts at line 0xd3 (211) with kind 0x12; the standalone
copy at 0x6E03A0 asserts 0xd8 (216) with kind 0x13. Count both forms.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

import build

data, sections = build.exe_image()
text = next(s for s in sections if s["name"] == ".text")
print(f".text rva {text['rva']:#x} size {text['size']:#x}")
blob = build.read_pe_bytes(data, sections, text["rva"], text["size"])


def find(line):
    pat = re.compile(
        b"\x68" + line.to_bytes(4, "little") +
        b"\x68...." +
        b"\x68\x64\x77\xce\x00" +
        b"\xff\x15\x34\x77\xe1\x00", re.S)
    out = []
    for m in pat.finditer(blob):
        out.append((text["rva"] + m.start(), blob[m.end():m.end() + 16].hex(" ")))
    return out


for line in (0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9):
    hits = find(line)
    print(f"\nline {line:#x}: {len(hits)} hit(s)")
    for rva, tail in hits[:6]:
        print(f"  {rva:#010x}  {tail}")
