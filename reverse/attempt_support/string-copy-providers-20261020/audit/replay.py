"""Read current compiled objects; never compile, change inputs, or claim linking.

Materialize the packet's baseline through providers/replay.py, compile it using
the normal runner, then compare it with current production or a prepared case.
JSON is written only to stdout. Every source must stay inside this repository.
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
from allowed_symbols import Obj

PRODUCTION = "Code/Libraries/Source/WWVegas/WWLib/stlport_string_insert_fill.cpp"
LEGACY = "??$Rva000179B0UninitializedCopy@PADPAD@_STL@@YAPADPAD00@Z"
ANCHORS = {
    "?insert@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEXPADID@Z": (0x29530, 662),
    "?fill@_STL@@YAXPAD0ABD@Z": (0x237C0, 48),
    "??$fill_n@I@_STL@@YAPADPADIABD@Z": (0x24970, 37),
    LEGACY: (0x179B0, 41),
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def body(obj, sym):
    raw, span, relocs = obj.body(sym)
    length, pointer = obj.sections[sym["section"] - 1][:2]
    if (raw is None or not obj.is_code(sym) or span <= 0 or span != len(raw)
            or sym["value"] + span > length or pointer <= 0
            or pointer + length > len(obj.data)):
        raise SystemExit("Invalid COFF extent: " + sym["name"])
    code = raw.rstrip(b"\xcc")
    fields, occupied = [], set()
    for offset, kind, ref in relocs:
        width = 2 if kind == 10 else 4
        if offset < 0 or offset + width > len(code):
            raise SystemExit("Relocation outside function: " + sym["name"])
        cells = set(range(offset, offset + width))
        if cells & occupied:
            raise SystemExit("Overlapping relocation: " + sym["name"])
        occupied |= cells
        fields.append({"offset": offset, "kind": kind, "name": ref["name"],
                       "addend": int.from_bytes(code[offset:offset + width], "little", signed=True)})
    record = {"body_size": len(code), "span": span, "trailing_cc": span - len(code),
              "section": sym["section"], "section_offset": sym["value"],
              "body_sha256": sha(code), "span_sha256": sha(raw), "relocations": fields}
    return code, relocs, record


def load(source):
    path = (ROOT / source).resolve()
    path.relative_to(ROOT)
    objpath = build.obj_path(path)
    if not build.compile_is_current(path, objpath):
        raise SystemExit("Missing/stale object; use normal compiler first: " + str(path))
    obj = Obj(objpath)
    functions = obj.functions()
    if len({s["name"] for s in functions}) != len(functions):
        raise SystemExit("Duplicate function name in audited COFF")
    records = {s["name"]: body(obj, s)[2] for s in functions}
    optional = struct.unpack_from("<H", obj.data, 16)[0]
    directives, relocation_names, runtime_data = [], set(), []
    for i, (length, ptr, rptr, nrel, flags) in enumerate(obj.sections):
        section_name = obj.data[20 + optional + i * 40:28 + optional + i * 40].rstrip(b"\0")
        if section_name == b".drectve":
            directives.append(obj.data[ptr:ptr + length].decode("latin-1"))
        if flags & 0xc0 and not section_name.startswith(b".debug"):
            runtime_data.append({"name": section_name.decode("latin-1"), "size": length,
                                 "sha256": sha(obj.data[ptr:ptr + length]) if ptr else None,
                                 "relocation_count": nrel})
        for pos in range(rptr, rptr + 10 * nrel, 10):
            where, index, kind = struct.unpack_from("<IIH", obj.data, pos)
            if index not in obj.symbols:
                raise SystemExit("Invalid relocation symbol index")
            relocation_names.add(obj.symbols[index]["name"])
    names = {s["name"] for s in obj.symbols.values()}
    stamp = {"source": path.relative_to(ROOT).as_posix(), "source_sha256": sha(path.read_bytes()),
             "source_text_sha256": sha(path.read_text().encode("utf-8")),
             "object_sha256": sha(obj.data),
             "runtime_data_sections": runtime_data,
             "cl": next((s for s in path.read_text().splitlines() if s.startswith("// cl:")), None)}
    return path, obj, stamp, records, names, relocation_names, directives


def rebased(sym, relocs):
    return {**sym, "value": 0}, [
        (at, kind, {**ref, "value": ref["value"] - sym["value"]}
         if ref["section"] == sym["section"] and ref["storage"] != 2 else ref)
        for at, kind, ref in relocs]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline-source", required=True)
    parser.add_argument("--candidate-source", default=PRODUCTION)
    args = parser.parse_args()
    loaded = [load(args.baseline_source), load(args.candidate_source)]
    needed = set().union(*(set(item[3]) | item[5] for item in loaded))
    with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        rows = [r for r in csv.DictReader(handle)
                if r["name"] in needed or build.ledger_object_symbol(r) in needed]
    truth = link_census.RetailTruth(rows)
    reports = []
    for _, obj, stamp, records, names, references, directives in loaded:
        anchors, providers = {}, []
        for sym in obj.functions():
            code, relocs, record = body(obj, sym)
            rb_sym, rb_relocs = rebased(sym, relocs)
            addresses = truth.addresses(sym["name"])
            if addresses:
                results = [truth._judge(a, rb_sym, code, rb_relocs, len(code)) for a in sorted(addresses)]
                providers.append({"name": sym["name"], "size": len(code),
                                  "addresses": [hex(a) for a in sorted(addresses)],
                                  "verdict": "retail" if "retail" in results else "unknown" if "unknown" in results else "wrong"})
            if sym["name"] not in ANCHORS:
                continue
            rva, extent = ANCHORS[sym["name"]]
            native = truth._read(rva, extent)
            if native is None:
                raise SystemExit("Unreadable native anchor")
            fields = []
            for field in record["relocations"]:
                at, kind, addend = field["offset"], field["kind"], field["addend"]
                if at + 4 > extent or kind not in (6, 20):
                    continue
                value = struct.unpack_from("<i", native, at)[0]
                target = rva + at + 4 + value - addend if kind == 20 else (value - addend - build.IMAGE_BASE) & 0xffffffff
                fields.append({**field, "native_target_rva": hex(target)})
            anchors[sym["name"]] = {"compiled_size": len(code), "rva": hex(rva), "native_extent": extent,
                                     "native_sha256": sha(native), "resolved_fields": fields,
                                     "whole_body_verdict": truth._judge(rva, rb_sym, code, rb_relocs, extent)}
        if set(anchors) != set(ANCHORS):
            raise SystemExit("Expected anchor omitted")
        reports.append({"input": stamp, "definitions": records, "anchors": anchors,
                        "known_providers": providers,
                        "imports": sorted(n for n in names if n.startswith("__imp_")),
                        "directives": directives})
    before, after = loaded[0][3], loaded[1][3]
    removed, added = sorted(set(before) - set(after)), sorted(set(after) - set(before))
    common = [{"name": n, "same_bytes": before[n]["span_sha256"] == after[n]["span_sha256"]
               and before[n]["span"] == after[n]["span"],
               "same_relocations": before[n]["relocations"] == after[n]["relocations"]}
              for n in sorted(set(before) & set(after))]
    residue = sorted(n for n in loaded[1][4] | loaded[1][5]
                     if n in removed or n.removeprefix("__imp_") in removed)
    output = {"scope": "Read-only exact function/provider delta; not a gate or link pass",
              "objects": reports, "removed": removed, "added": added,
              "common_functions": common, "removed_symbol_residue": residue,
              "all_surviving_bytes_and_relocations_identical": all(r["same_bytes"] and r["same_relocations"] for r in common),
              "same_imports": reports[0]["imports"] == reports[1]["imports"],
              "same_runtime_data": reports[0]["input"]["runtime_data_sections"] == reports[1]["input"]["runtime_data_sections"],
              "same_directives": reports[0]["directives"] == reports[1]["directives"]}
    for path, obj, stamp, *_ in loaded:
        if (sha(path.read_bytes()) != stamp["source_sha256"] or sha(obj.path.read_bytes()) != stamp["object_sha256"]
                or not build.compile_is_current(path, obj.path)):
            raise SystemExit("Audited inputs moved")
    print(json.dumps(output, indent=1))


if __name__ == "__main__":
    main()
