"""Verify existing COFF against the native callers and their shared insertion.

No compilation, ledger writes or identity admission. The mutable copy helper
is inventoried separately because its known 68-byte definition is not the
41-byte native copy provider.
"""
from pathlib import Path
import argparse
import hashlib
import json
import struct
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import build
from allowed_symbols import Obj

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("source")
parser.add_argument("--variant", choices=("V21", "V22"), required=True)
parser.add_argument("--out")
args = parser.parse_args()
source = ROOT / args.source
objpath = build.obj_path(source)
out = (ROOT / args.out if args.out else
       Path(__file__).with_name(args.variant.lower() + ".receipt.json"))
variant = args.variant
name = (f"?bfmeInsert{variant}@BfmeStr{variant}@@QAEPAV1@IPAD"
        + ("I" if variant == "V21" else "") + "@Z")
insert = "?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z"
copy = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
targets = {
    f"?bfmeGrow{variant}@BfmeStr{variant}@@QAEXXZ": 0x23A40,
    f"?bfmeLenErr{variant}@BfmeStr{variant}@@QAEXXZ": 0x69E440,
    "?bfmeMakeOX@@YAHPAX@Z": 0x6F30,
    insert: 0x28820,
    copy: 0x179B0,
    "?__copy_trivial@_STL@@YAPAXPBX0PAX@Z": 0x179B0,
    "?allocate@?$allocator@D@_STL@@SAPADIPBX@Z": 0x307F0,
    "?Rva0069E440Destroy@_STL@@YAXPAD0@Z": 0x69E440,
    "_free": 0x30830,
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def filerecord(path):
    data = path.read_bytes()
    return {"path": path.relative_to(ROOT).as_posix(), "size": len(data),
            "sha256": digest(data)}


def owner_class(text):
    start = text.index("class Rva008314E0String\n{")
    begin = text.index("{", start)
    end, depth = begin + 1, 1
    while depth:
        depth += (text[end] == "{") - (text[end] == "}")
        end += 1
    assert text[end] == ";"
    return text[start:end + 1]


deps = json.loads(objpath.with_suffix(".deps.json").read_text())
assert deps["source"] == hashlib.md5(source.read_bytes()).hexdigest()
assert deps["object"] == hashlib.md5(objpath.read_bytes()).hexdigest()
assert all(hashlib.md5((ROOT / p).read_bytes()).hexdigest() == h
           for p, h in deps["deps"].items())
pe = pefile.PE(str(build.EXE))
base = pe.OPTIONAL_HEADER.ImageBase
assert base == 0x400000
imports = {"__imp__" + imp.name.decode("ascii"): imp.address
           for entry in pe.DIRECTORY_ENTRY_IMPORT for imp in entry.imports
           if imp.name}
o = Obj(objpath)
cs = Cs(CS_ARCH_X86, CS_MODE_32)
cs.detail = True
rows = [(name, 0x2AB40, 149)] if variant == "V21" else [(name, 0x2ABE0, 170)]
rows.append((insert, 0x28820, 740))
proofs = []
for symbol, rva, extent in rows:
    sym = o.by_name[symbol]
    raw, size, relocations = o.body(sym)
    assert raw is not None and len(raw) == size == extent, (symbol, size, extent)
    section_size, pointer = o.sections[sym["section"] - 1][:2]
    assert 0 <= sym["value"] < section_size
    assert sym["value"] + size <= section_size
    assert pointer > 0 and pointer + section_size <= len(o.data)
    native = pe.get_data(rva, extent)
    instructions = list(cs.disasm(native, base + rva))
    assert sum(i.size for i in instructions) == extent
    assert instructions[-1].mnemonic == "ret"
    starts = {i.address: i for i in instructions}
    resolved = bytearray(raw)
    occupied = set()
    fields = []
    for at, kind, ref in relocations:
        assert kind in (0x14, 0x06) and 0 <= at <= extent - 4
        assert not occupied.intersection(range(at, at + 4))
        occupied.update(range(at, at + 4))
        addend = struct.unpack_from("<i" if kind == 0x14 else "<I", raw, at)[0]
        assert addend == 0
        if kind == 0x14:
            ins = starts[base + rva + at - 1]
            assert ins.mnemonic == "call" and bytes(ins.bytes[:1]) == b"\xe8" and ins.size == 5
            target = rva + at + 4 + struct.unpack_from("<i", native, at)[0]
            assert target == targets[ref["name"]], (ref["name"], hex(target))
            detail = {"target_rva": f"0x{target:08X}"}
        else:
            ins = starts[base + rva + at - 2]
            assert ins.mnemonic == "call" and bytes(ins.bytes[:2]) == b"\xff\x15" and ins.size == 6
            target = struct.unpack_from("<I", native, at)[0]
            assert target == imports[ref["name"]]
            detail = {"iat_va": f"0x{target:08X}"}
        resolved[at:at + 4] = native[at:at + 4]
        fields.append({"instruction_offset": f"0x{ins.address - base - rva:X}",
                       "operand_offset": f"0x{at:X}", "kind": kind,
                       "addend": addend, "symbol": ref["name"], **detail})
    assert bytes(resolved) == native
    calls = [i for i in instructions if i.mnemonic == "call"]
    assert len(calls) == len(relocations)
    branches = [i for i in instructions if i.mnemonic.startswith("j")
                and i.operands[0].type == X86_OP_IMM]
    assert all(i.operands[0].imm in starts for i in branches)
    proofs.append({"symbol": symbol, "rva": f"0x{rva:08X}", "extent": extent,
                   "end_rva_exclusive": f"0x{rva + extent:08X}",
                   "ret_offset": f"0x{instructions[-1].address - base - rva:X}",
                   "ret_operand": instructions[-1].op_str,
                   "native_sha256": digest(native), "raw_coff_sha256": digest(raw),
                   "resolved_coff_sha256": digest(bytes(resolved)),
                   "whole_body_and_relocations_exact": True,
                   "coff_section_bytes_after_body": section_size - sym["value"] - size,
                   "all_branches_to_instruction_boundaries_in_body": True,
                   "fixups": fields})
copy_raw, copy_size, copy_relocs = o.body(o.by_name[copy])
assert copy_size == 68
assert digest(copy_raw) == "038f7ab27195d2771e676cdc8f12fddab747c34e92387187933fe182da8fb593"
assert [(at, kind, ref["name"]) for at, kind, ref in copy_relocs] == [
    (57, 0x14, "?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
]
owner_source = ROOT / "Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp"
context = owner_class(source.read_text())
assert context == owner_class(owner_source.read_text())
record = {
    "kind": "read-only complete byte/relocation receipt; not link admission",
    "donor_revision": "92f6bbe8e1dcdb46b5d27da0674313efc822b790",
    "source": filerecord(source), "object": filerecord(objpath),
    "image": filerecord(build.EXE),
    "flags": next(l for l in source.read_text().splitlines() if l.startswith("// cl:")),
    "inline_depth": "MSVC default; no inline_depth pragma",
    "dependency_receipt": {"source_object_headers_current": True, "command_digest": deps["cmd"],
                           "headers": deps["deps"]},
    "owner_class_context": {"source": owner_source.relative_to(ROOT).as_posix(),
                            "definition_identical": True,
                            "definition_sha256": digest(context.encode())},
    "proofs": proofs,
    "copy_provider": {"symbol": copy, "emitted_bytes": copy_size,
                      "native_rva": "0x000179B0", "native_bytes": 41,
                      "whole_body_exact": False,
                      "raw_coff_sha256": digest(copy_raw),
                      "status": "same existing shared-owner 68-byte provider mismatch"},
    "emitted_symbols": sorted(n for n in build.defined_code_symbols(objpath) if n.startswith("?")),
}
out.write_text(json.dumps(record, indent=2) + "\n")
print(json.dumps({"receipt": out.relative_to(ROOT).as_posix(),
                  "exact_bodies": [(p["rva"], p["extent"]) for p in proofs],
                  "mutable_copy_provider": copy_size}))
