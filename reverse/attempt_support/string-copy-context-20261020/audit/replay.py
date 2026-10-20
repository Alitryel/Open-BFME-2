"""Read existing current COFF for the banked string-copy candidates.

Never compiles, changes inputs, writes a receipt, or claims a gate pass.
Materialize and compile a banked candidate through the packet's normal runner
first, then pass its source path and role. JSON goes to stdout.
"""
import argparse
import csv
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / "tools"))
import build
import link_census
from allowed_symbols import Obj, digest

COPY = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
OWNER = "?__copy_trivial@_STL@@YAPAXPBX0PAX@Z"
OWNER_SOURCE = "Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp"
ROLES = {
    "owner": (
        "Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp",
        [
            ("?insertRange@Rva008314E0String@@QAEXPAD00ABUBfmeRangeTag@@@Z", 0x28820, 740),
            ("?replaceRange@Rva008314E0String@@QAEAAV1@PAD000ABUBfmeRangeTag@@@Z", 0x2B050, 501),
        ],
    ),
    "sibling": (
        "Code/Libraries/Source/STLport/Rva008312E0StringReplace.cpp",
        [
            ("?insertRange@Rva008312E0String@@QAEXPAD00ABURva008312E0Tag@@@Z", 0x284D0, 848),
            ("?bfmeReplaceAliasedRange@Rva008312E0String@@QAEAAV1@PAD000ABURva008312E0Tag@@@Z", 0x2AE50, 511),
        ],
    ),
}


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load(source):
    source = (ROOT / source).resolve()
    source.relative_to(ROOT)
    objpath = build.obj_path(source)
    if not build.compile_is_current(source, objpath):
        raise SystemExit("Missing/stale object; use the normal runner first: " + str(source))
    stamps = {
        "source": source.relative_to(ROOT).as_posix(),
        "source_sha256": sha(source),
        "object_sha256": sha(objpath),
        "cl": next((line for line in source.read_text().splitlines()
                    if line.startswith("// cl:")), None),
    }
    return source, Obj(objpath), stamps


def body(obj, name):
    sym = obj.by_name[name]
    raw, span, relocs = obj.body(sym)
    length, pointer = obj.sections[sym["section"] - 1][:2]
    if (raw is None or not obj.is_code(sym) or span != len(raw)
            or sym["value"] + span > length or pointer + length > len(obj.data)):
        raise SystemExit("Invalid COFF extent for " + name)
    code = raw.rstrip(b"\xcc")
    fields = [(at, kind, ref["name"], struct.unpack_from("<i", code, at)[0])
              for at, kind, ref in relocs if at >= 0 and at + 4 <= len(code)]
    if len(fields) != len(relocs):
        raise SystemExit("Relocation crosses function extent: " + name)
    return sym, code, relocs, {
        "section": sym["section"],
        "section_value": sym["value"],
        "section_size": length,
        "function_span": span,
        "body_size": len(code),
        "trailing_cc_bytes": span - len(code),
        "raw_sha256": hashlib.sha256(code).hexdigest(),
        "relocations": fields,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", required=True, help="Materialized .cpp source, relative to repository")
    parser.add_argument("--role", required=True, choices=ROLES)
    args = parser.parse_args()
    base_source, targets = ROLES[args.role]
    loaded = [load(s) for s in (args.source, base_source, OWNER_SOURCE)]
    (_, candidate, candidate_stamp), (_, baseline, base_stamp), (_, owner, owner_stamp) = loaded
    needed = set()
    for _, obj, _ in loaded:
        for sym in obj.functions():
            needed.add(sym["name"])
            needed.update(ref["name"] for _, _, ref in obj.body(sym)[2])
    with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        rows = [row for row in csv.DictReader(handle)
                if row["name"] in needed or build.ledger_object_symbol(row) in needed]
    truth = link_census.RetailTruth(rows)
    output = {
        "scope": "Independent body/provider diagnostics; not a normal gate or link pass",
        "role": args.role,
        "inputs": [candidate_stamp, base_stamp, owner_stamp],
        "bodies": [],
    }
    base_sym, base_code, base_relocs, base_copy = body(baseline, COPY)
    base_copy["name"] = COPY
    base_copy["body_verdict_at_179b0"] = truth._judge(
        0x179B0, base_sym, base_code, base_relocs, 41)
    output["baseline_legacy_copy"] = base_copy
    for name, rva, size in targets + [(COPY, 0x179B0, 41)]:
        sym, code, relocs, record = body(candidate, name)
        comparison = owner if name == COPY else baseline
        comparison_name = OWNER if name == COPY else name
        _, expected, _, comparison_record = body(comparison, comparison_name)
        native = truth._read(rva, size)
        if native is None:
            raise SystemExit("Native extent unreadable")
        masked = bytearray(code)
        field_targets = []
        for at, kind, ref in relocs:
            if at + 4 > len(native):
                continue
            addend = struct.unpack_from("<i", code, at)[0]
            value = struct.unpack_from("<i", native, at)[0]
            target = (rva + at + 4 + value - addend if kind == 20 else
                      (value - addend - build.IMAGE_BASE) & 0xFFFFFFFF)
            field_targets.append(hex(target))
            masked[at:at + 4] = native[at:at + 4]
        exact_mask = bytes(masked) == native
        first_diff = next((i for i, (a, b) in enumerate(zip(masked, native)) if a != b), None)
        record.update({
            "name": name, "native_rva": hex(rva), "native_size": size,
            "same_raw_as_current_owner": code == expected,
            "same_relocations_as_current_owner": record["relocations"] == comparison_record["relocations"],
            "current_owner_sha256": comparison_record["raw_sha256"],
            "current_owner_extent": {
                key: comparison_record[key] for key in
                ("section", "section_value", "section_size", "function_span",
                 "body_size", "trailing_cc_bytes")
            },
            "masked_native_equal": exact_mask,
            "first_masked_diff": first_diff,
            "native_operand_targets": field_targets if exact_mask else None,
            "body_verdict": truth._judge(rva, sym, code, relocs, size),
        })
        if code[:5] == native[:5] == bytes.fromhex("558bec81ec"):
            record["frame_bytes"] = {
                "compiled": hex(struct.unpack_from("<I", code, 5)[0]),
                "native": hex(struct.unpack_from("<I", native, 5)[0]),
            }
        output["bodies"].append(record)
    roots, edges = link_census.object_references(candidate.path)
    reachable, pending = set(roots), list(roots)
    while pending:
        for child in edges.get(pending.pop(), set()):
            if child not in reachable:
                reachable.add(child)
                pending.append(child)
    output["definition_count"] = len(candidate.functions())
    output["known_providers"] = []
    for sym in candidate.functions():
        addresses = truth.addresses(sym["name"])
        if not addresses:
            continue
        raw, span, relocs = candidate.body(sym)
        output["known_providers"].append({
            "name": sym["name"], "size": span,
            "native_candidates": [hex(a) for a in sorted(addresses)],
            "reachable_from_this_object_roots": sym["name"] in reachable,
            "verdict": truth.verdict(sym, raw, relocs, digest(raw, span, relocs), span),
        })
    for source, obj, stamps in loaded:
        if (sha(source) != stamps["source_sha256"] or sha(obj.path) != stamps["object_sha256"]
                or not build.compile_is_current(source, obj.path)):
            raise SystemExit("Inputs moved while auditing: " + str(source))
    print(json.dumps(output, indent=2))


if __name__ == "__main__":
    main()
