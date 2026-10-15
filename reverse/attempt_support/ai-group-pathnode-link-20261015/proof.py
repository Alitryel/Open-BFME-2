"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/ai-group-pathnode-link-20261015')
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

sources=(BASE/'sources.txt').read_text().splitlines()
removed_helpers={'?getNext@PathNode@@QAEPAV1@XZ','?isKindOf@ThingTemplate@@QBEII@Z'}
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
truth=lc.RetailTruth(lc.ledger())
reports=[]
for source in sources:
 obj=build.obj_path(build.ROOT/source)
 before=BASE/'before'/obj.name
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 assert set(old)-set(new)==removed_helpers,(set(old)-set(new))
 assert not set(new)-set(old)
 assert all(old[n]==new[n] for n in new)
 assert normalized(before,removed_helpers)==normalized(obj,set())
 def bindings(path):
  _,_,symbols=build._object_layout(str(path),path.stat().st_mtime_ns,path.stat().st_size)
  return {(s['name'],s['storage'],s['section']==0,s['value'],s['type']) for s in symbols if s.get('storage') in (2,105) and s['name'] not in removed_helpers}
 assert bindings(before)==bindings(obj)
 indices={};paired={}
 for label,candidate in [('before',before),('after',obj)]:
  index=link_check.load_index();link_check.refresh(index,[candidate],truth)
  indices[label]=index
  paired[label]=link_check.check_object(candidate,index,truth,source=source)
 before_link,after_link=paired['before'],paired['after']
 expected={**before_link,'comdat':[x for x in before_link['comdat'] if x[0] not in removed_helpers]}
 assert after_link==expected,(before_link,after_link)
 assert {x[0] for x in before_link['comdat'] if x[0] in removed_helpers}==removed_helpers
 selection={}
 for name in removed_helpers:
  old_copies=indices['before']['comdat'].get(name,[])
  new_copies=indices['after']['comdat'].get(name,[])
  losses,rule=lc.keep_rule(old_copies);new_losses,new_rule=lc.keep_rule(new_copies)
  assert all(losses[i]==lost for i,lost in new_losses.items())
  assert [x for x in old_copies if not losses[x[0]]]==[x for x in new_copies if not new_losses[x[0]]]
  selection[name]=dict(before_copies=old_copies,after_copies=new_copies,remaining_selection_unchanged=True)
 variants_before=link_check.new_variants(before,indices['before'],truth)
 variants_after=link_check.new_variants(obj,indices['before'],truth)
 assert all(v in variants_before for v in variants_after)
 rows=dc.source_rows([source]);row_object=build.row_object
 try:
  build.row_object=lambda row:BASE/'before'/row_object(row).name
  before_data=dc.object_facts(rows)
 finally:build.row_object=row_object
 after_data=dc.object_facts(rows)
 assert before_data==after_data
 reports.append(dict(source=source,self_strict_current=True,before_object_sha256=sha(before.read_bytes()),after_object_sha256=sha(obj.read_bytes()),
  removed_comdats={n:old[n] for n in sorted(removed_helpers)},retained_comdats=len(new),all_retained_nondebug_bytes_flags_definitions_relocations_equal=True,
  no_retained_relocations_to_removed_helpers=True,external_and_weak_bindings_equal=True,data_facts_equal=True,link_preview=paired,selection=selection,
  variants_before=variants_before,variants_after=variants_after,existing_nonpadding_bytes=link_check.source_bytes({source})[source]))
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
(BASE/'object-proof.json').write_text(json.dumps(dict(index=meta,objects=reports,legacy_linked_gain=0,closed_strict_gain_unmeasured=True),indent=2)+'\n')
print('PASS: two unused conflicting copies removed; all retained COMDATs/nondebug sections, relocations, bindings and data facts identical; remaining providers unchanged; no new variants')
