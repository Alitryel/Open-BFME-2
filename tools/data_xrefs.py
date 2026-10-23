#!/usr/bin/env python3
"""Every global the game's code touches: address, size bound, access widths
and referencing functions, from retail bytes alone (no Ghidra needed).

Disassembles every function in reverse/ghidra_functions.csv (capstone) and
records each absolute address in a data section that an instruction uses:
a memory operand with no base or index register ([disp32]), or an immediate
that is a data address (push offset, mov reg, offset). For each address:

  size_bound  distance to the next referenced address in the same section,
              an upper bound on the global's size (an array or struct
              accessed only through its base can be larger than what the
              references show, never smaller than its widest access)
  widths      the operand widths seen at that address (1/2/4/8/10 bytes);
              8 with float instructions suggests a double, 10 a long double
  kinds       read/write/address-taken
  callers     the functions that reference it (by count), which pick a
              definition's home unit

Writes reverse/data_xrefs.tsv. Identity evidence and sizing input for data
definitions; never byte proof by itself.

  python3 tools/data_xrefs.py [--out reverse/data_xrefs.tsv]
"""
import argparse
import collections
import csv
import sys
from pathlib import Path

import capstone
import pefile
from capstone import x86

ROOT = Path(__file__).resolve().parents[1]
EXE = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "files" / "game.dat"
FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--out", default=str(ROOT / "reverse" / "data_xrefs.tsv"))
    args = ap.parse_args(argv)
    pe = pefile.PE(str(EXE), fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    image = pe.get_memory_mapped_image()
    data_sections = []
    for section in pe.sections:
        name = section.Name.rstrip(b"\0").decode(errors="replace")
        executable = section.Characteristics & 0x20000000
        if not executable:
            start = section.VirtualAddress
            data_sections.append((name, start, start + max(section.Misc_VirtualSize, section.SizeOfRawData)))

    def section_of(rva):
        for name, start, end in data_sections:
            if start <= rva < end:
                return name
        return None

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    refs = collections.defaultdict(lambda: {"widths": set(), "kinds": set(), "callers": collections.Counter(), "float": False})
    with FUNCTIONS.open(encoding="utf-8", newline="") as handle:
        functions = [(int(r["rva"], 16), int(r["size"])) for r in csv.DictReader(handle) if r["size"].isdigit()]
    for start, size in functions:
        code = image[start:start + size]
        for insn in md.disasm(code, base + start):
            is_float = insn.mnemonic.startswith("f")
            for index, op in enumerate(insn.operands):
                if op.type == x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                    address = op.mem.disp & 0xFFFFFFFF
                    rva = address - base
                    if section_of(rva):
                        entry = refs[rva]
                        entry["widths"].add(op.size)
                        entry["kinds"].add("write" if index == 0 and insn.mnemonic.startswith(("mov", "fst", "inc", "dec", "add", "sub", "or", "and", "xor")) else "read")
                        entry["callers"][start] += 1
                        entry["float"] |= is_float
                elif op.type == x86.X86_OP_IMM:
                    rva = (op.imm & 0xFFFFFFFF) - base
                    if section_of(rva):
                        entry = refs[rva]
                        entry["kinds"].add("address")
                        entry["callers"][start] += 1
    ordered = sorted(refs)
    with open(args.out, "w", encoding="utf-8", newline="\n") as out:
        out.write("rva\tsection\tsize_bound\twidths\tfloat\tkinds\tref_count\tcallers\n")
        for i, rva in enumerate(ordered):
            entry = refs[rva]
            section = section_of(rva)
            following = next((r for r in ordered[i + 1:i + 2] if section_of(r) == section), None)
            bound = (following - rva) if following else ""
            callers = ",".join(f"0x{c:08X}" for c, _ in entry["callers"].most_common(12))
            out.write(f"0x{rva:08X}\t{section}\t{bound}\t{','.join(map(str, sorted(entry['widths'])))}\t"
                      f"{int(entry['float'])}\t{','.join(sorted(entry['kinds']))}\t"
                      f"{sum(entry['callers'].values())}\t{callers}\n")
    print(f"data_xrefs: {len(ordered):,} referenced data addresses from {len(functions):,} functions -> {args.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
