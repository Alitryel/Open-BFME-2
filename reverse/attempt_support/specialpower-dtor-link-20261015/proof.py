"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check
BASE=Path('build/specialpower-dtor-link-20261015')
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
            raw = repr([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)
                        if symbols[struct.unpack_from("<I", raw, j)[0]]["section"] not in omitted]).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], len(raw) if section["name"] == ".sxdata" else section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


sources=json.loads((BASE/'sources.json').read_text())
cohort=(BASE/'cohort.txt').read_text().splitlines()
removed={s:set() for s in sources}
removed[sources[0]]={'??1SpecialPowerModuleData@@UAE@XZ','??1BehaviorModuleData@@UAE@XZ','??1ModuleData@@UAE@XZ'}
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
truth=lc.RetailTruth(lc.ledger())
objects={s:build.obj_path(build.ROOT/s) for s in cohort}
for source,obj in objects.items():
    assert lc.object_current(build.ROOT/source,obj,allow_fresh=False),source
proofs={}
for source in sources:
    obj=objects[source];before=BASE/'before'/obj.name
    old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
    new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
    assert set(old)-set(new)==removed[source],(source,set(old)-set(new))
    assert not set(new)-set(old)
    assert all(old[n]==new[n] for n in new)
    assert normalized(before,removed[source])==normalized(obj,set()), source
    def undefined(path):
        st=path.stat();_,_,symbols=build._object_layout(str(path),st.st_mtime_ns,st.st_size)
        return {(v["name"],v["storage"],v["value"],v["type"]) for v in symbols
                if v.get("storage") in (2,105) and v.get("section")==0}
    old_u,new_u=undefined(before),undefined(obj)
    expected_removed={('??1AudioEventRTS@@UAE@XZ',2,0,32),('??1Snapshot@@QAE@XZ',2,0,32)} if removed[source] else set()
    expected_added={('??1SpecialPowerModuleData@@UAE@XZ',2,0,32)} if removed[source] else set()
    assert old_u-new_u==expected_removed
    assert new_u-old_u==expected_added
    receipt=json.loads(obj.with_suffix('.deps.json').read_text())
    if removed[source]:
        assert 'reference/open-bfme-1/inputs/reference/shims/specialpowermoduledata/GameLogic/Module/SpecialPowerModule.h' in receipt['deps']
    proofs[source]=dict(undefined_removed=sorted(old_u-new_u),undefined_added=sorted(new_u-old_u),strict_receipt_sha256=sha(obj.with_suffix('.deps.json').read_bytes()),before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(new),removed_external_sections=sorted(removed[source]),removed_associative_eh_only=bool(removed[source]))
paired={}
for label in ('before','after'):
    candidates={s:(BASE/'before'/obj.name if label=='before' and s in sources else obj) for s,obj in objects.items()}
    index=link_check.load_index()
    link_check.refresh(index,list(candidates.values()),truth)
    paired[label]={s:link_check.check_object(obj,index,truth,source=s) for s,obj in candidates.items()}
assert {s:json.loads(json.dumps(paired['before'][s])) for s in sources}==json.loads((BASE/'link-before.json').read_text())
changes={}
for source in cohort:
    before,after=paired['before'][source],paired['after'][source]
    changes[source]={}
    for key in before:
        a={repr(v) for v in before[key]};b={repr(v) for v in after[key]}
        assert not b-a,(source,key,b-a)
        changes[source][key]=dict(before=len(a),after=len(b),removed=sorted(a-b))
for source in sources:
    obj=objects[source]
    previous={n:{d} for n,d,z in lc.comdat_bodies(BASE/'before'/obj.name)}
    assert not link_check.new_variants(obj,index,truth,previous=previous)
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
sizes=link_check.source_bytes(cohort)
linked={side:sum(sizes.get(s,0) for s,result in results.items() if not any(result.values())) for side,results in paired.items()}
clean={side:[s for s,result in results.items() if not any(result.values())] for side,results in paired.items()}
report=dict(index=meta,sources=proofs,self_strict_current_objects=True,retained_non_debug_bytes_flags_definitions_relocations_unchanged=True,link_preview=paired,delta=changes,legacy_predicted_linked_bytes=linked,legacy_clean_units=clean,closed_strict_gain_unmeasured=True)
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
for source,delta in changes.items(): print(source,{k:(v['before'],v['after']) for k,v in delta.items() if v['before']!=v['after']})
print('PASS: retained sections unchanged; only three destructor copies and dependent EH removed; strict receipts current; legacy predicted linked bytes',linked,'clean units', {k:len(v) for k,v in clean.items()})
