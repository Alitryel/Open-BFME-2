"""Bounded COFF comparison and paired legacy preview; census stays unchanged."""
import copy, hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, 'tools')
import build, link_check as ck, link_census as lc
BASE=Path('build/audio-ref-setter-link-20261015')
def sha(data): return hashlib.sha256(data).hexdigest()
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
assert sha(ck.INDEX.read_bytes()) == ctx['index_sha256']
truth=lc.RetailTruth(lc.ledger())
paths=ctx['paths']
objects=[build.obj_path(build.ROOT/s) for s in paths]
before=[BASE/'before'/obj.name for obj in objects]
name='?rva000A8CE5@Rva000A8C9B@@QAEXPAVOpaqueRefCounted@@@Z'
reports=[]
for source,old,new in zip(paths,before,objects):
    assert lc.object_current(build.ROOT/source,new,allow_fresh=False)
    assert normalized(old,set())==normalized(new,set()),source+' changed nondebug sections'
    old_c={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
    new_c={n:(d,z) for n,d,z in lc.comdat_bodies(new)}
    assert old_c==new_c
    of=lc.object_facts(old,truth);nf=lc.object_facts(new,truth)
    assert of[0]==nf[0] and of[2:]==nf[2:]
    if source==paths[0]:
        assert set(of[1])-set(nf[1])=={name}
        assert set(nf[1])-set(of[1])==set()
        old_layout=build._object_layout(str(old),old.stat().st_mtime_ns,old.stat().st_size)
        new_layout=build._object_layout(str(new),new.stat().st_mtime_ns,new.stat().st_size)
        def choices(layout):
            raw,sections,symbols=layout
            choices=lc._comdat_selections(raw)
            return {s['name']: choices.get(s['section']) for s in symbols if s.get('storage')==2 and s['section']>0}
        oc,nc=choices(old_layout),choices(new_layout)
        assert oc.keys()==nc.keys()
        changes={n:[oc[n],nc[n]] for n in oc if oc[n]!=nc[n]}
        assert changes=={name:[1,2]},changes
    else:
        assert of==nf
        changes={}
    assert not ck.new_variants(new,ck.load_index(),truth,previous={n:{d} for n,d,z in lc.comdat_bodies(old)})
    reports.append(dict(source=source,self_strict_current=True,before_sha256=sha(old.read_bytes()),after_sha256=sha(new.read_bytes()),retained_comdats=len(new_c),all_nondebug_sections_bytes_flags_definitions_and_normalized_relocations_equal=True,selection_changes=changes))
setter_copies=[]
for obj in objects:
    row=next(c for c in lc.object_facts(obj,truth)[0] if c[0]==name)
    setter_copies.append(row)
assert len({(row[1],row[2]) for row in setter_copies})==1,setter_copies
assert all(row[3]=='retail' for row in setter_copies),setter_copies
paired={}
for phase,objs in [('before',before),('after',objects)]:
    index=ck.load_index()
    ck.refresh(index,objs,truth)
    paired[phase]={s:ck.check_object(obj,index,truth,s) for s,obj in zip(paths,objs)}
for source in paths:
    old=paired['before'][source];new=paired['after'][source]
    assert name in old['duplicates'],(source,old)
    expected=copy.deepcopy(old);expected['duplicates'].remove(name)
    assert new==expected,(source,old,new)
amounts=ck.source_bytes(set(paths))
gain=sum(amounts[s] for s in paths if any(paired['before'][s].values()) and not any(paired['after'][s].values()))
report=dict(context=ctx,objects=reports,setter_copies=setter_copies,paired=paired,existing_nonpadding_bytes=amounts,legacy_predicted_linked_bytes_gain=gain,closed_strict_gain_unmeasured=True)
assert sha(ck.INDEX.read_bytes())==ctx['index_sha256']
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
