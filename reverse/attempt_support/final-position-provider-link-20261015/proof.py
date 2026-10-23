"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check
BASE=Path('build/final-position-provider-link-20261015')
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

sources=json.loads((BASE/'sources.json').read_text())
removed={s:set() for s in sources}
removed[sources[0]]={'?setFinalPosition@AIUpdateInterface@@QAEXPBUCoord3D@@@Z'}
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
assert link_check.load_index()['meta']==meta['measurement']
truth=lc.RetailTruth(lc.ledger())
objects={s:build.obj_path(build.ROOT/s) for s in sources}
proofs={}
for source,obj in objects.items():
    before=BASE/'before'/obj.name
    assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
    old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
    raw_new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
    new=raw_new
    assert len(new)==len(raw_new)
    assert set(old)-set(new)==removed[source], (source,set(old)-set(new))
    assert not set(new)-set(old), (source,set(new)-set(old))
    assert all(old[n]==new[n] for n in new)
    assert normalized(before,removed[source])==normalized(obj,set()), source
    proofs[source]=dict(before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(new),removed_unused_externals=sorted(removed[source]))
paired={}
for label in ('before','after'):
    candidates={s:(BASE/'before'/obj.name if label=='before' else obj) for s,obj in objects.items()}
    index=link_check.load_index()
    link_check.refresh(index,list(candidates.values()),truth)
    paired[label]={s:link_check.check_object(obj,index,truth,source=s) for s,obj in candidates.items()}
assert json.loads(json.dumps(paired['before']))==json.loads((BASE/'link-before.json').read_text())
changes={}
for source,obj in objects.items():
    before,after=paired['before'][source],paired['after'][source]
    changes[source]={}
    for key in before:
        a={repr(v) for v in before[key]};b={repr(v) for v in after[key]}
        assert not b-a,(source,key,b-a)
        changes[source][key]=dict(before=len(a),after=len(b),removed=sorted(a-b))
    previous={n:{d} for n,d,z in lc.comdat_bodies(BASE/'before'/obj.name)}
    assert not link_check.new_variants(obj,index,truth,previous=previous)
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
sizes=link_check.source_bytes(sources)
linked={side:sum(sizes[s] for s,result in results.items() if not any(result.values())) for side,results in paired.items()}
report=dict(index=meta,sources=proofs,self_strict_current=True,all_other_sections_bytes_flags_definitions_relocations_unchanged=True,link_preview=paired,delta=changes,legacy_predicted_linked_bytes=linked,closed_strict_gain_unmeasured=True)
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
for source,delta in changes.items(): print(source,{k:(v['before'],v['after']) for k,v in delta.items()})
print('PASS: only the unused legacy setFinalPosition removed; all retained nondebug sections unchanged; strict receipts current; legacy predicted linked bytes',linked)
