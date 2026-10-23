"""Paired virtual-base deleting-wrapper proof; baseline objects in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/virtual-base-link-20261018")
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
paths=context['paths']; objects={s:build.obj_path(build.ROOT/s) for s in paths}
changed='??_GRva005CC5E5@@UAEPAXI@Z'; added='??_DRva005CC5E5@@QAEXXZ'
proofs={}
for i,(s,o) in enumerate(objects.items()):
 old=BASE/'before'/o.name
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False)
 before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
 after={n:(d,z) for n,d,z in lc.comdat_bodies(o)}
 if i==0:
  assert after.keys()-before.keys()=={added} and not before.keys()-after.keys()
  assert {n for n in before if before[n]!=after[n]}=={changed}
  assert before[changed][1]==42 and after[changed][1]==31 and after[added][1]==28
  assert normalized(old,{changed})==normalized(o,{changed,added})
 else:
  assert old.read_bytes()==o.read_bytes()
 assert after[changed][0]=='5ba8f308a96c'
 proofs[s]=dict(before_sha256=sha(old.read_bytes()),after_sha256=sha(o.read_bytes()),deleting_wrapper=after[changed])
truth=lc.RetailTruth(lc.ledger());paired={}
for phase in ('before','after'):
 objs={s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
 x=ck.load_index();ck.refresh(x,list(objs.values()),truth)
 paired[phase]={s:ck.check_object(o,x,truth,source=s) for s,o in objs.items()}
core=('unresolved','duplicates','comdat','addresses','selected')
assert all(not paired['before'][paths[0]][k] for k in core)
assert all(paired['before'][s]['comdat']==[(changed,'first',None)] for s in paths[1:])
assert all(not paired['after'][s][k] for s in paths for k in core)
sizes=ck.source_bytes(set(paths));gain=sum(sizes[s] for s in paths[1:])
assert gain==1019
rows=dc.source_rows(paths)
old_row_object=build.row_object
try:
 build.row_object=lambda row: BASE/'before'/old_row_object(row).name
 unread=[];before_data=dc.findings(dc.object_facts(rows,unread),dc.dl.load());assert not unread
finally:
 build.row_object=old_row_object
unread=[];after_data=dc.findings(dc.object_facts(rows,unread),dc.dl.load());assert not unread
assert before_data==after_data
result=dict(unchanged_data_findings=after_data,context=context,objects=proofs,source_bytes=sizes,legacy_paired_gain=gain,paired=paired,self_strict=True,closed_strict=False)
Path(__file__).with_name('proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: retained sections/relocations unchanged; three units +%d legacy linked bytes; self-strict objects, closure unmeasured'%gain)
