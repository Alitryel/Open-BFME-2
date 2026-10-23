"""Paired Hero integer-map callee repair; baseline objects remain in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/seat-hero-link")
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
            return renames.get(symbol["name"], symbol["name"]), symbol["storage"], symbol["value"]
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


old_name = '?clear@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAEXXZ'
new_name = '?clear@?$_Rb_tree@URva0021A917Element@@U?$pair@$$CBURva0021A917Element@@H@_STL@@U?$_Select1st@U?$pair@$$CBURva0021A917Element@@H@_STL@@@3@U?$less@URva0021A917Element@@@3@V?$allocator@U?$pair@$$CBURva0021A917Element@@H@_STL@@@3@@_STL@@QAEXXZ'
renames = {old_name:new_name}
context=json.loads((BASE/'context.json').read_text())
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
paths=context['paths']; objects={s:build.obj_path(build.ROOT/s) for s in paths}
proofs={}
for s,o in objects.items():
 old=BASE/'before'/o.name
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False),s
 before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
 after={n:(d,z) for n,d,z in lc.comdat_bodies(o)}
 assert before.keys()==after.keys(),s
 changed=[n for n in before if before[n]!=after[n]]
 assert normalized(old,set())==normalized(o,set()),s
 proofs[s]={'before_sha256':sha(old.read_bytes()),'after_sha256':sha(o.read_bytes()),'comdats':len(after),'changed_relocation_digests':changed}
truth=lc.RetailTruth(lc.ledger()); paired={};indices={}
core=('unresolved','duplicates','comdat','addresses','selected')
def clean(r): return not any(r[k] for k in core)
for phase in ('before','after'):
 objs={s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
 x=ck.load_index();ck.refresh(x,list(objs.values()),truth);indices[phase]=x
 paired[phase]={s:ck.check_object(o,x,truth,source=s) for s,o in objs.items()}
for s in paths:
 for k in core:
  assert set(map(repr,paired['after'][s][k]))<=set(map(repr,paired['before'][s][k])),(s,k)
for s in paths[-2:]: assert not clean(paired['before'][s]) and clean(paired['after'][s]),s
sz=ck.source_bytes(set(paths));gains={p:sum(sz[s] for s in paths if clean(paired[p][s])) for p in paired}
assert gains['after']-gains['before']==452,gains
n='??1?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@XZ'
verdicts={p:[(x['objects'][i],d,v) for i,d,v in x['comdat'][n]] for p,x in indices.items()}
assert verdicts['before'][0][2]=='wrong' and verdicts['after'][0][2]=='unknown',verdicts
report={'context':context,'measurement':ck.load_index()['meta'],'object_proofs':proofs,'paired_link':paired,'destructor_verdicts':verdicts,'callee_binding':renames,'legacy_predicted_linked_nonpadding_bytes':gains,'self_strict_current':True,'closed_strict_gain_unmeasured':True,'retained_nondebug_bytes_flags_definitions_and_relocations_identical_except_proven_callee_binding':True}
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: same current providers; legacy +452 B; only native clear binding changed; destructor wrong -> unknown (no proven wrong relocation remains)')
