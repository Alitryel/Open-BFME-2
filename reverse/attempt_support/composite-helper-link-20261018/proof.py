"""Paired CompositeRenderObjClass helper repair; baseline objects remain in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/seat-composite-link")
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

context = json.loads((BASE/'context.json').read_text())
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
paths = context['paths']; objects = {s:build.obj_path(build.ROOT/s) for s in paths}
proofs={}; removed_all=set()
for s,o in objects.items():
 old=BASE/'before'/o.name
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False),s
 before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
 after={n:(d,z) for n,d,z in lc.comdat_bodies(o)}
 removed=before.keys()-after.keys();removed_all.update(removed)
 assert not after.keys()-before.keys()
 assert all(before[n]==after[n] for n in after),s
 assert normalized(old,removed)==normalized(o,set()),s
 proofs[s]=dict(before_sha256=sha(old.read_bytes()),after_sha256=sha(o.read_bytes()),removed_comdats={n:before[n] for n in removed},retained_comdats=len(after))
truth=lc.RetailTruth(lc.ledger());indices={};paired={}
for phase in ('before','after'):
 objs={s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
 x=ck.load_index();ck.refresh(x,list(objs.values()),truth)
 paired[phase]={s:ck.check_object(o,x,truth,source=s) for s,o in objs.items()};indices[phase]=x
core=('unresolved','duplicates','comdat','addresses','selected')
def clean(r):return not any(r[k] for k in core)
assert not clean(paired['before'][paths[-1]])
assert clean(paired['after'][paths[-1]])
for s in paths[:-1]:
 for k in core:
  assert set(map(repr,paired['after'][s][k])) <= set(map(repr,paired['before'][s][k])),(s,k)
def holder(x,n):
 cs={i:(d,v) for i,d,v in x['comdat'].get(n,())};ds=set(cs)|set(x['strong'].get(n,()))
 if not ds:return None
 h=x['selection']['exceptions'].get(n,min(ds));h=h if h is None or h in ds else min(ds)
 return None if h is None else (x['objects'][h],cs.get(h,'strong'))
selections={}
for n in sorted(removed_all):
 a=holder(indices['before'],n);b=holder(indices['after'],n)
 if ck.is_referenced(indices['before'],n):
  assert b is not None,n
  assert a==b or (n=='?Is_Empty@StringClass@@QBE_NXZ' and b[1][1]=='retail'),(n,a,b)
 selections[n]={'before':a,'after':b}
sz=ck.source_bytes(set(paths))
gains={phase:sum(sz[s] for s in paths if clean(paired[phase][s])) for phase in paired}
assert gains['after']-gains['before']==1930,gains
report=dict(context=context,measurement=ck.load_index()['meta'],object_proofs=proofs,paired_link=paired,
 reachable_kept_definitions=selections,legacy_predicted_linked_nonpadding_bytes=gains,
 self_strict_current=True,closed_strict_gain_unmeasured=True,retained_nondebug_sections_bytes_flags_definitions_and_symbolic_relocations_identical=True)
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: 25 strict rows; retained nondebug sections exact; reachable providers preserved; legacy +1930 B linked')
