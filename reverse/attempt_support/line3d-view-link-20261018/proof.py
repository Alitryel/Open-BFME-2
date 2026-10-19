"""Paired current-object prediction; baseline artifacts are local build evidence."""
import hashlib, json, sys
from pathlib import Path
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc
base = Path("build/seat-line3d-link")
context = json.loads((base / "context.json").read_text())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(ck.INDEX) == context["index_sha256"]
paths = context["paths"]
objects = {s: build.obj_path(build.ROOT / s) for s in paths}
truth = lc.RetailTruth(lc.ledger())
core = ("unresolved", "duplicates", "comdat", "addresses", "selected")
clean = lambda r: not any(r[k] for k in core)
paired = {}
for phase in ("before", "after"):
    objs = {s: base / "before" / o.name if phase == "before" else o for s, o in objects.items()}
    index = ck.load_index()
    ck.refresh(index, list(objs.values()), truth)
    paired[phase] = {s: ck.check_object(o, index, truth, source=s) for s, o in objs.items()}
assert clean(paired["before"][paths[0]])
assert not clean(paired["before"][paths[1]])
assert all(clean(r) for r in paired["after"].values())
sizes = ck.source_bytes(set(paths))
linked = {phase: sum(sizes[s] for s in paths if clean(rows[s])) for phase, rows in paired.items()}
assert linked == {"before": 928, "after": 1557}, linked
bodies = {s: {n: (d, z) for n, d, z in lc.comdat_bodies(o)} for s, o in objects.items()}
for n in ("??_7Line3DClass@@6BRefCountClass@@@", "??_7Line3DClass@@6BMultiListObjectClass@@@"):
    assert bodies[paths[0]][n] == bodies[paths[1]][n], n
report = {"context": context, "measurement": ck.load_index()["meta"], "paired_link": paired,
          "legacy_predicted_linked_nonpadding_bytes": linked, "closed_strict_gain_unmeasured": True,
          "objects": {s: {"before_sha256": sha(base / "before" / o.name), "after_sha256": sha(o)} for s, o in objects.items()},
          "both_current_vtable_bodies_and_relocations_agree": True}
assert sha(ck.INDEX) == context["index_sha256"]
(base / "proof.json").write_text(json.dumps(report, indent=2) + "\n")
print("PASS: paired current objects +629 legacy linked bytes; both Line3D vtables agree")
