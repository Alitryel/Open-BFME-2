"""Paired partition-provider repair; baseline objects remain under build/."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,"tools")
import build,link_check as ck,link_census as lc
BASE=Path("build/seat8-partition")
partition='??$__unguarded_partition@PAVRva0021915B@@V1@URva0021B753@@@_STL@@YAPAVRva0021915B@@PAV1@0V1@URva0021B753@@@Z'
fallback='?__unguarded_partition@_STL@@YAPAVRva0021915B@@PAV2@0V2@URva0021B753@@@Z'
fallback_directive=('/alternatename:'+partition+'='+fallback).encode()
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
        if section["name"] == ".drectve":
            # MSVC adds a fallback for the explicit specialization declaration.
            # Its real template definition is supplied by the rowed provider;
            # check that definition and the exact directive delta below.
            raw = b" ".join(t for t in raw.split() if t != fallback_directive)
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
        found.append(repr((section["name"], section["characteristics"], len(raw) if section["name"] in (".sxdata", ".drectve") else section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)

paths=['Code/Libraries/Source/WWVegas/WWLib/stlport_rva0021915b_sort.cpp','Code/Libraries/Source/WWVegas/WWLib/stlport_unguarded_partition_rva0021915B.cpp']
objects={s:build.obj_path(build.ROOT/s) for s in paths}
index_hash=sha(ck.INDEX.read_bytes())
proofs={}
assert partition in {n for n,d,z in lc.comdat_bodies(objects[paths[1]])}
old_aliases=ck.alternate_names(BASE/'before'/objects[paths[0]].name)
new_aliases=ck.alternate_names(objects[paths[0]])
assert partition not in old_aliases
assert new_aliases == dict(old_aliases, **{partition:fallback})
for s,obj in objects.items():
 old=BASE/'before'/obj.name
 assert lc.object_current(build.ROOT/s,obj,allow_fresh=False)
 before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
 after={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 removed=before.keys()-after.keys()
 assert not after.keys()-before.keys()
 assert all(before[n]==after[n] for n in after)
 assert (partition in removed) == (s==paths[0])
 assert normalized(old,removed)==normalized(obj,set()),s
 proofs[s]=dict(before_sha256=sha(old.read_bytes()),after_sha256=sha(obj.read_bytes()),removed_comdats={n:before[n] for n in sorted(removed)},retained_comdats=len(after))
truth=lc.RetailTruth(lc.ledger())
paired={}
for phase in ('before','after'):
 objs={s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
 index=ck.load_index();ck.refresh(index,list(objs.values()),truth)
 paired[phase]={s:ck.check_object(o,index,truth,source=s) for s,o in objs.items()}
core=('unresolved','duplicates','comdat','addresses','selected')
def clean(r):return all(not r[k] for k in core)
assert [clean(paired['before'][s]) for s in paths]==[True,False]
assert all(clean(paired['after'][s]) for s in paths)
sizes=ck.source_bytes(set(paths))
counts={phase:sum(sizes[s] for s in paths if clean(paired[phase][s])) for phase in paired}
assert counts=={'before':847,'after':964},counts
assert sha(ck.INDEX.read_bytes())==index_hash
report=dict(measurement=index['meta'],index_sha256=index_hash,object_proofs=proofs,paired_link=paired,legacy_predicted_linked_nonpadding_bytes=counts,gain=117,self_strict_current=True,closed_strict_gain_unmeasured=True,compiler_fallback_added={partition:fallback},retained_nondebug_code_data_bytes_flags_definitions_symbolic_relocations_identical=True,other_directives_identical=True)
(Path(__file__).parent/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: strict15/15; retained sections and relocations identical; paired legacy847->964, +117 B.')
