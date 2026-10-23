"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check
BASE=Path('build/timed-control-link-20261015')
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

ctx=json.loads((BASE/'context.json').read_text())
sources=ctx['sources']
name='??1Rva00211E75@@QAE@XZ'
removed={sources[0]:set(),sources[1]:{name}}
assert sha(link_check.INDEX.read_bytes())==ctx['index_sha256']
assert link_check.load_index()['meta']==ctx['index_meta']
truth=lc.RetailTruth(lc.ledger())
objects={s:build.obj_path(build.ROOT/s) for s in sources}
proofs={}
old_bodies={}
for source,obj in objects.items():
    before=BASE/'before'/obj.name
    receipt=json.loads(before.with_suffix('.deps.json').read_text())
    assert receipt['version']==2
    assert hashlib.md5(before.read_bytes()).hexdigest()==receipt['object']
    assert hashlib.md5((BASE/'before'/Path(source).name).read_bytes()).hexdigest()==receipt['source']
    assert all(hashlib.md5((build.ROOT/p).read_bytes()).hexdigest()==d for p,d in receipt['deps'].items())
    assert build.compile_is_current(build.ROOT/source,obj,strict=True)
    after_receipt=json.loads(obj.with_suffix('.deps.json').read_text())
    assert all(receipt[k]==after_receipt[k] for k in ('cmd','path','version','inventory','search_roots','retry_dirs'))
    old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
    new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
    old_bodies[source]=old[name]
    assert set(old)-set(new)==removed[source],(source,set(old)-set(new))
    assert not set(new)-set(old),(source,set(new)-set(old))
    assert all(old[n]==new[n] for n in new)
    assert normalized(before,removed[source])==normalized(obj,set()),source
    if not removed[source]: assert (BASE/'before'/Path(source).name).read_bytes()==(build.ROOT/source).read_bytes()
    old_undef={s['name'] for s in lc._coff_symbols(before.read_bytes()) if s['section']==0 and s['storage']==2}
    new_undef={s['name'] for s in lc._coff_symbols(obj.read_bytes()) if s['section']==0 and s['storage']==2}
    assert new_undef==old_undef,(source,new_undef-old_undef,old_undef-new_undef)
    proofs[source]=dict(before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),before_receipt_sha256=sha(before.with_suffix('.deps.json').read_bytes()),after_receipt_sha256=sha(obj.with_suffix('.deps.json').read_bytes()),strict_current=True,retained_comdats=len(new),removed_unused_externals=sorted(removed[source]))
assert old_bodies[sources[0]]==old_bodies[sources[1]]
paired={}
for label in ('before','after'):
    candidates={s:(BASE/'before'/obj.name if label=='before' else obj) for s,obj in objects.items()}
    index=link_check.load_index()
    link_check.refresh(index,list(candidates.values()),truth)
    paired[label]={s:link_check.check_object(obj,index,truth,source=s) for s,obj in candidates.items()}
assert json.loads(json.dumps(paired['before']))==ctx['before']
changes={}
for source,obj in objects.items():
    before,after=paired['before'][source],paired['after'][source]
    changes[source]={}
    for key in before:
        a={repr(v) for v in before[key]};b={repr(v) for v in after[key]}
        assert not b-a,(source,key,b-a)
        if key=='duplicates': assert after[key]==[n for n in before[key] if n!=name]
        else: assert after[key]==before[key],(source,key)
        changes[source][key]=dict(before=len(a),after=len(b),removed=sorted(a-b))
    previous={n:{d} for n,d,z in lc.comdat_bodies(BASE/'before'/obj.name)}
    assert not link_check.new_variants(obj,index,truth,previous=previous)
assert not any(paired['after'][sources[0]].values())
assert sha(link_check.INDEX.read_bytes())==ctx['index_sha256']
sizes=link_check.source_bytes(sources)
linked={side:sum(sizes[s] for s,result in results.items() if not any(result.values())) for side,results in paired.items()}
assert linked=={'before':0,'after':276},linked
report=dict(context=ctx,sources=proofs,identical_destructor_before=old_bodies,all_other_sections_bytes_flags_definitions_relocations_unchanged=True,link_preview=paired,delta=changes,legacy_predicted_linked_bytes=linked,authored_cpp_bytes_added=0,self_strict_placement_gain_unmeasured=True,closed_strict_gain_unmeasured=True)
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
for source,delta in changes.items(): print(source,{k:(v['before'],v['after']) for k,v in delta.items()})
print('PASS: one unused inline destructor removed; all retained nondebug sections identical; strict receipts current; legacy predicted linked bytes',linked)
