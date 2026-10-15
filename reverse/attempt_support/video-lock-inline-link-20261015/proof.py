"""Paired video-lock object proof; baseline snapshots live in ignored build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, 'tools')
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path('build/video-lock-inline-link-20261015')
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

context=json.loads((BASE/'context.json').read_text())
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
source=context['source']; obj=build.obj_path(build.ROOT/source)
old=BASE/'before'/obj.name
assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
name='??0BFMEDX8DeviceLock@@QAE@XZ'
before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
after={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
assert before.keys()-after.keys()=={name}
assert not after.keys()-before.keys()
assert all(before[n]==after[n] for n in after)
assert normalized(old,{name})==normalized(obj,set())
truth=lc.RetailTruth(lc.ledger()); paired={}
for phase,o in [('before',old),('after',obj)]:
    ind=ck.load_index();ck.refresh(ind,[o],truth)
    paired[phase]=ck.check_object(o,ind,truth,source=source)
assert json.loads(json.dumps(paired['before']))==context['before_link']
assert sum(len(v) for v in paired['before'].values())==1
assert not any(paired['after'].values())
assert not ck.new_variants(obj,ind,truth,{n:{d} for n,(d,z) in before.items()})
rows=dc.source_rows([source]); row_object=build.row_object
try:
    build.row_object=lambda row: old
    old_data=dc.object_facts(rows)
finally:
    build.row_object=row_object
new_data=dc.object_facts(rows)
assert old_data==new_data
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
report=dict(context=context,before_sha256=sha(old.read_bytes()),after_sha256=sha(obj.read_bytes()),
    paired_link=paired,retained_comdats=len(after),removed_comdat=dict(name=name,body=before[name]),
    retained_nondebug_sections_identical=True,no_incoming_nondebug_relocations_to_removed_copy=True,
    data_bindings_unchanged=True,data_findings=dc.findings(new_data,dc.dl.load()),
    self_strict_current=True,closed_strict_gain_unmeasured=True,
    existing_nonpadding_bytes_locally_unblocked=ck.source_bytes({source})[source])
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
