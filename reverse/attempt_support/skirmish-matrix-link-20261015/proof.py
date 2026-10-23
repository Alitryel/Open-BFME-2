"""Recheck the bounded link repair using the preserved build/ snapshots."""
import hashlib
import json
import shutil
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, "tools")
import build
import link_census as lc
import link_check

BASE = Path("build/skirmish-matrix-link-20261015")
REMOVED = "??0Matrix3D@@QAE@ABVVector3@@@Z"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    leaders = {}
    for symbol in symbols:
        if symbol.get("storage") == 2 and symbol["section"] > 0:
            leaders.setdefault(symbol["section"], []).append(symbol["name"])

    def body(n):
        section = sections[n - 1]
        pointer = section["raw_pointer"]
        return data[pointer:pointer + section["raw_size"]] if pointer else b""

    def referent(i):
        symbol = symbols[i]
        n = symbol["section"]
        assert n not in omitted, "removed helper has an incoming nondebug relocation"
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or n in omitted:
            continue
        raw = body(n)
        if section["name"] == ".sxdata":
            raw = repr([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


paths = (BASE / "sources.txt").read_text().splitlines()
objects = [build.obj_path(build.ROOT / p) for p in paths]
assert all(lc.object_current(build.ROOT / p, o, allow_fresh=False) for p, o in zip(paths, objects))
meta = json.loads((BASE / "index-meta.json").read_text())
assert sha(link_check.INDEX.read_bytes()) == meta["sha256"]
before = BASE / "before" / objects[0].name
after = objects[0]
old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(after)}
assert set(old) - set(new) == {REMOVED} and not set(new) - set(old)
assert all(old[n] == new[n] for n in new)
assert normalized(before, {REMOVED}) == normalized(after, set())
truth = lc.RetailTruth(lc.ledger())
bf, af = lc.object_facts(before, truth), lc.object_facts(after, truth)
assert all(set(bf[i]) == set(af[i]) for i in (1, 2, 3))
for obj in objects[1:]:
    assert obj.read_bytes() == (BASE / "before" / obj.name).read_bytes()
paired = {}
for label in ("before", "after"):
    index = link_check.load_index()
    objs = [BASE / "before" / obj.name for obj in objects] if label == "before" else objects
    link_check.refresh(index, objs, truth)
    paired[label] = {p: link_check.check_object(o, index, truth, p) for p, o in zip(paths, objs)}
assert not any(paired["after"][paths[0]].values())
assert paired["before"][paths[0]]["comdat"] == [(REMOVED, "retail", "wrong")]
assert sum(map(len, paired["before"][paths[0]].values())) == 1
for path in paths[1:]:
    assert paired["before"][path] == paired["after"][path]
providers = json.loads((BASE / "providers.json").read_text())
provider_bodies = [x for x in lc.comdat_bodies(objects[1]) if x[0] == REMOVED]
assert provider_bodies == [(REMOVED, "9ec9e58d0816", 112)]
index = link_check.load_index()
remaining = [(i, d, v) for i, d, v in index["comdat"][REMOVED] if index["objects"][i] != objects[0].name]
assert len(remaining) == 2 and all(d == provider_bodies[0][1] for _, d, _ in remaining)
report = {
    "base_commit": (BASE / "base.txt").read_text().strip(), "index": meta,
    "sources": paths, "removed_helper": {"name": REMOVED, "digest_size": old[REMOVED]},
    "object_before_sha256": sha(before.read_bytes()), "object_after_sha256": sha(after.read_bytes()),
    "strict_current_receipts": True, "retained_comdats": new,
    "all_remaining_nondebug_sections_and_symbolic_relocations_equal": True,
    "strong_undefined_weak_sets_equal": True, "witness_object_unchanged": True,
    "indexed_providers": providers, "retained_witness_constructor": provider_bodies,
    "paired_findings": paired, "legacy_existing_linked_bytes_before": 0,
    "legacy_existing_linked_bytes_after": link_check.source_bytes({paths[0]})[paths[0]],
    "new_authored_cpp_bytes": 0, "closed_strict_gain_claimed": False,
}
shutil.copy2(after, BASE / "object-after.obj")
shutil.copy2(after.with_suffix(".deps.json"), BASE / "receipt-after.json")
(BASE / "object-proof.json").write_text(json.dumps(report, indent=2) + "\n")
print("PASS: only unreferenced constructor removed; all other sections/relocations equal; LEGACY +%d existing linked bytes"
      % report["legacy_existing_linked_bytes_after"])
