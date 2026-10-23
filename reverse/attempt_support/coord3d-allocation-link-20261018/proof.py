"""Paired Coord3D allocation-wrapper proof; baseline objects in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/link-seat-20261018")
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s.get("name") in excluded and s.get("section",0) > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    table = struct.unpack_from("<I", data, 8)[0]
    associations = {}
    for i, symbol in enumerate(symbols):
        if symbol.get("aux") and symbol.get("storage") == 3 and symbol.get("section", 0) > 0:
            aux = data[table + 18 * (i + 1):table + 18 * (i + 2)]
            parent, selection = struct.unpack_from("<hB", aux, 12)
            if selection == 5:
                associations[symbol["section"]] = parent
    while True:
        more = {n for n, parent in associations.items() if parent in omitted} - omitted
        if not more: break
        omitted.update(more)
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
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        assert n not in omitted, "removed helper has an incoming local relocation"
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or n in omitted:
            continue
        raw = body(n)
        if section["name"] == ".sxdata":
            # SafeSEH is an unordered symbol-index inventory; link.exe sorts RVAs.
            # Compare the retained symbolic entries including multiplicity.
            raw = repr(sorted([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)
                        if symbols[struct.unpack_from("<I", raw, j)[0]]["section"] not in omitted], key=repr)).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], len(raw) if section["name"] == ".sxdata" else section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)

context = json.loads((BASE / 'context.json').read_text())
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
paths = context['paths']
objects = {s: build.obj_path(build.ROOT / s) for s in paths}
proofs = {}
proxy = '?allocate@?$_STLP_alloc_proxy@PAUCoord3D@@U1@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEPAUCoord3D@@I@Z'
allocator = '?allocate@?$allocator@UCoord3D@@@_STL@@QBEPAUCoord3D@@IPBX@Z'
rebind = '??$__stl_alloc_rebind@UCoord3D@@U1@@_STL@@YAAAV?$allocator@UCoord3D@@@0@AAV10@PBUCoord3D@@@Z'
for source, obj in objects.items():
    old = BASE / 'before' / obj.name
    assert lc.object_current(build.ROOT / source, obj, allow_fresh=False)
    before = {n: (d,z) for n,d,z in lc.comdat_bodies(old)}
    after = {n: (d,z) for n,d,z in lc.comdat_bodies(obj)}
    removed = before.keys() - after.keys()
    assert {proxy, allocator} <= removed <= {proxy, allocator, rebind}
    assert not after.keys() - before.keys()
    assert all(before[n] == after[n] for n in after)
    assert normalized(old, removed) == normalized(obj, set()), source
    proofs[source] = dict(before_sha256=sha(old.read_bytes()), after_sha256=sha(obj.read_bytes()),
        retained_comdats=len(after), removed_comdats={n:before[n] for n in removed})
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase in ('before', 'after'):
    objs = {s: BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
    index = ck.load_index()
    ck.refresh(index, list(objs.values()), truth)
    paired[phase] = {s: ck.check_object(o,index,truth,source=s) for s,o in objs.items()}
core = ('unresolved','duplicates','comdat','addresses','selected')
for s in paths:
    assert paired['before'][s]['comdat'] == [(proxy,'first',None)], paired['before'][s]
    assert all(not paired['before'][s][k] for k in core if k!='comdat')
    assert all(not paired['after'][s][k] for k in core), paired['after'][s]
sizes = ck.source_bytes(set(paths))
report = dict(context=context, measurement=ck.load_index()['meta'], object_proofs=proofs,
    paired_link=paired, legacy_predicted_linked_nonpadding_bytes={'before':0,'after':sum(sizes.values())},
    self_strict_current=True, closed_strict_gain_unmeasured=True,
    retained_nondebug_sections_bytes_flags_definitions_and_symbolic_relocations_identical=True)
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: strict-current objects, retained sections and relocations identical; 8/8 legacy clean, +',sum(sizes.values()),'B')
