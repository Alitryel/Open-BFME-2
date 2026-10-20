"""Read-only receipt for the 740-byte insertion and existing 501-byte replacement.

Uses already compiled COFF; does not compile, alter a ledger, or admit names.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/build.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
import build
from allowed_symbols import Obj

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--source", default="Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp")
parser.add_argument("--out", default=str(Path(__file__).with_suffix(".json")))
args = parser.parse_args()
SOURCE = ROOT / args.source
IMAGE = build.EXE
OBJ = build.obj_path(SOURCE)
OUT = ROOT / args.out
BASE = 0x400000
REL32, DIR32 = 0x14, 0x06
NAMES = {
    "copy": "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z",
    "insert": "?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z",
    "replace": "?replaceBase@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z",
    "alias": "?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z",
}
TARGETS = {
    NAMES["copy"]: 0x179B0,
    "?__copy_trivial@_STL@@YAPAXPBX0PAX@Z": 0x179B0,
    "?allocate@?$allocator@D@_STL@@SAPADIPBX@Z": 0x307F0,
    "?Rva0069E440Destroy@_STL@@YAXPAD0@Z": 0x69E440,
    "_free": 0x30830,
    "?erase@Rva008314E0String@@QAEPADPAD0@Z": 0x12150,
    NAMES["insert"]: 0x28820,
    NAMES["replace"]: 0x2A730,
}


def hashes(data):
    return {"md5": hashlib.md5(data).hexdigest(), "sha256": hashlib.sha256(data).hexdigest()}


def file_record(path):
    raw = path.read_bytes()
    return {"path": path.relative_to(ROOT).as_posix(), "length": len(raw), **hashes(raw)}


def git(*args):
    return subprocess.check_output(["git", *args], cwd=ROOT, text=True).strip()


image = IMAGE.read_bytes()
pe = pefile.PE(data=image)
assert pe.OPTIONAL_HEADER.ImageBase == BASE
imports = {
    "__imp__" + imp.name.decode("ascii"): (imp.address, entry.dll.decode("ascii"))
    for entry in pe.DIRECTORY_ENTRY_IMPORT
    for imp in entry.imports
    if imp.name is not None
}
o = Obj(OBJ)
cs = Cs(CS_ARCH_X86, CS_MODE_32)
cs.detail = True
receipt = {
    "kind": "independent bounded byte-and-relocation receipt, not link admission",
    "revision": git("rev-parse", "HEAD"),
    "bfme1_committed_pointer": git("ls-tree", "HEAD", "reference/open-bfme-1").split()[2],
    "source": file_record(SOURCE),
    "object": file_record(OBJ),
    "image": file_record(IMAGE),
    "prior_bank": (file_record(ROOT / "reverse/attempts/0x00028820.cpp")
                   if (ROOT / "reverse/attempts/0x00028820.cpp").exists() else None),
    "flags": next(line for line in SOURCE.read_text().splitlines() if line.startswith("// cl:")),
    "functions": [],
}

deps_path = OBJ.with_suffix(".deps.json")
deps = json.loads(deps_path.read_text())
assert deps["source"] == receipt["source"]["md5"]
assert deps["object"] == receipt["object"]["md5"]
stale = [
    name for name, digest in deps["deps"].items()
    if hashlib.md5((ROOT / name).read_bytes()).hexdigest() != digest
]
assert not stale, stale
receipt["compile_receipt"] = {
    "path": deps_path.relative_to(ROOT).as_posix(),
    "command_digest": deps["cmd"],
    "source_and_object_current": True,
    "header_digests_current": True,
    "headers": deps["deps"],
}

targets = [(NAMES["insert"], 0x28820, 740)]
targets.append((NAMES["alias"], 0x2B050, 501))
for name, rva, extent in targets:
    sym = o.by_name[name]
    raw, size, relocs = o.body(sym)
    section_size, pointer = o.sections[sym["section"] - 1][:2]
    assert raw is not None and len(raw) == size == extent
    assert 0 <= sym["value"] < section_size and sym["value"] + size <= section_size
    assert pointer > 0 and pointer + section_size <= len(o.data)
    native = pe.get_data(rva, extent)
    assert len(native) == extent
    instructions = list(cs.disasm(native, BASE + rva))
    assert sum(ins.size for ins in instructions) == extent
    assert instructions[-1].mnemonic == "ret"
    starts = {ins.address: ins for ins in instructions}
    fields, fixed = [], bytearray(raw)
    occupied = set()
    for at, kind, ref in relocs:
        assert 0 <= at <= extent - 4
        assert not (occupied & set(range(at, at + 4)))
        occupied.update(range(at, at + 4))
        addend = struct.unpack_from("<i" if kind == REL32 else "<I", raw, at)[0]
        assert addend == 0
        if kind == REL32:
            ins = starts[BASE + rva + at - 1]
            assert ins.mnemonic == "call" and ins.size == 5 and ins.bytes[0] == 0xE8
            actual = rva + at + 4 + struct.unpack_from("<i", native, at)[0]
            assert actual == TARGETS[ref["name"]], (ref["name"], hex(actual))
            resolved = {"target_rva": f"0x{actual:08X}"}
        elif kind == DIR32:
            ins = starts[BASE + rva + at - 2]
            assert ins.mnemonic == "call" and ins.size == 6 and bytes(ins.bytes[:2]) == b"\xff\x15"
            actual = struct.unpack_from("<I", native, at)[0]
            expected, dll = imports[ref["name"]]
            assert actual == expected
            resolved = {"iat_va": f"0x{actual:08X}", "dll": dll}
        else:
            raise AssertionError(f"Unexpected relocation type {kind}")
        fixed[at:at + 4] = native[at:at + 4]
        fields.append({
            "instruction_offset": f"0x{ins.address - BASE - rva:X}",
            "operand_offset": f"0x{at:X}",
            "kind": "REL32" if kind == REL32 else "DIR32",
            "addend": addend,
            "symbol": ref["name"],
            **resolved,
        })
    assert bytes(fixed) == native
    calls = [ins for ins in instructions if ins.mnemonic == "call"]
    assert len(calls) == len(relocs)
    branches = [
        ins for ins in instructions
        if ins.mnemonic.startswith("j") and ins.operands[0].type == X86_OP_IMM
    ]
    assert all(BASE + rva <= ins.operands[0].imm < BASE + rva + extent
               and ins.operands[0].imm in starts for ins in branches)
    following = pe.get_data(rva + extent, 16)
    cc_count = next((i for i, byte in enumerate(following) if byte != 0xCC), len(following))
    receipt["functions"].append({
        "name": name, "rva": f"0x{rva:08X}", "extent": extent,
        "end_rva_exclusive": f"0x{rva + extent:08X}",
        "file_offset": f"0x{pe.get_offset_from_rva(rva):X}",
        "coff_section_bytes_after_extent": section_size - sym["value"] - extent,
        "ret_offset": f"0x{instructions[-1].address - BASE - rva:X}",
        "ret_operand": instructions[-1].op_str,
        "retail_cc_bytes_after_extent_up_to_16": cc_count,
        "retail_body": hashes(native), "raw_coff_body": hashes(raw),
        "resolved_coff_body": hashes(bytes(fixed)),
        "instruction_count": len(instructions), "call_count": len(calls),
        "all_noncall_branches_in_extent_at_instruction_boundaries": True,
        "noncall_branch_count": len(branches),
        "complete_byte_and_relocation_match": True,
        "fixups": fields,
    })
receipt["emitted_copy_helper_bytes"] = o.body(o.by_name[NAMES["copy"]])[1]
receipt["relocation_field_count"] = sum(len(f["fixups"]) for f in receipt["functions"])
OUT.write_text(json.dumps(receipt, indent=2) + "\n")
print(f"Verified {len(receipt['functions'])} complete bodies / {receipt['relocation_field_count']} fixups")
print(OUT.relative_to(ROOT).as_posix())
