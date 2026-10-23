"""Bounded paired COFF and local link proof. Run from repository root.
Requires strict before snapshots in build/snapshot-local-link-20261015/before.
Never writes the census index, link status or history.
"""
import hashlib,json,struct,sys,copy
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/snapshot-local-link-20261015')
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded, rename=False):
    def canon(name):
        return name.replace("??1Snapshot@@", "??1Rva00BC6F24Base@@") if rename else name
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    leaders = {}
    for symbol in symbols:
        if symbol.get("storage") == 2 and symbol["section"] > 0:
            leaders.setdefault(symbol["section"], []).append(canon(symbol["name"]))

    def body(n):
        section = sections[n - 1]
        pointer = section["raw_pointer"]
        return data[pointer:pointer + section["raw_size"]] if pointer else b""

    def referent(i):
        symbol = symbols[i]
        n = symbol["section"]
        assert n not in omitted, "removed helper has an incoming nondebug relocation"
        if symbol["storage"] in (2, 105):
            return canon(symbol["name"]), symbol["storage"], symbol["value"]
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


old_name='??1Snapshot@@UAE@XZ'
new_name='??1Rva00BC6F24Base@@UAE@XZ'
sources=(BASE/'sources.txt').read_text().splitlines()
objects=[build.obj_path(build.ROOT/s) for s in sources]
before_objects=[BASE/'before'/obj.name for obj in objects]
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
reports=[]
for i,(source,obj,before) in enumerate(zip(sources,objects,before_objects)):
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False),source
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 renamed=i<4 and old_name in old
 assert set(old)-set(new)==({old_name} if renamed else set()),(source,set(old)-set(new))
 assert set(new)-set(old)==({new_name} if renamed else set()),(source,set(new)-set(old))
 if renamed: assert old[old_name][0]==new[new_name][0],source+' renamed helper changed'
 assert all(old[n]==new[n] for n in set(old)&set(new)),source
 assert normalized(before,set(),rename=i<4)==normalized(obj,set()),source+' sections or relocation referents differ'
 def bindings(path,rename):
  _,_,symbols=build._object_layout(str(path),path.stat().st_mtime_ns,path.stat().st_size)
  return {(s['name'].replace('??1Snapshot@@','??1Rva00BC6F24Base@@') if rename else s['name'],s['storage'],s['section']==0,s['value'],s['type']) for s in symbols if s.get('storage') in (2,105)}
 assert bindings(before,i<4)==bindings(obj,False),source+' bindings differ'
 if i>=4:assert before.read_bytes()==obj.read_bytes()
 reports.append(dict(source=source,before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(new),renamed_cleanup=renamed,all_nondebug_bytes_flags_definitions_relocations_unchanged_except_cleanup_name=True,self_strict_current=True))
 print(source,'PASS',len(new),'COMDATs', 'cleanup renamed' if renamed else 'no callable cleanup emitted')
truth=lc.RetailTruth(lc.ledger())
paired={};indices={};selection={}
for label,candidates in [('before',before_objects),('after',objects)]:
 index=link_check.load_index()
 link_check.refresh(index,candidates,truth)
 indices[label]=index
 paired[label]=[link_check.check_object(obj,index,truth,source=source) for source,obj in zip(sources,candidates)]
 copies=sorted(index['comdat'][old_name]);losses,rule=lc.keep_rule(copies)
 winners=[c for c in copies if not losses[c[0]]]
 selection[label]={'winners_sha256':sha(repr(winners).encode()),'winner_count':len(winners),'rule':rule}
assert selection['before']==selection['after']
provider_helpers={n:(d,z) for n,d,z in lc.comdat_bodies(objects[4])}
assert new_name in provider_helpers
for report,obj in zip(reports,objects):
 if report['renamed_cleanup']:
  helper={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}[new_name]
  assert helper[0]==provider_helpers[new_name][0]
for i,(report,old,new,obj,before) in enumerate(zip(reports,paired['before'],paired['after'],objects,before_objects)):
 expected=copy.deepcopy(old)
 if report['renamed_cleanup']:
  matches=[r for r in expected['comdat'] if r[0]==old_name]
  assert len(matches)==1
  expected['comdat'].remove(matches[0])
 assert expected==new,(report['source'],old,new)
 vb=link_check.new_variants(before,indices['before'],truth);va=link_check.new_variants(obj,indices['before'],truth)
 assert all(v in vb for v in va),(report['source'],vb,va)
 report['link_preview']={'before':old,'after':new}
 report['variant_findings']={'before':vb,'after':va}
 report['existing_nonpadding_bytes']=link_check.source_bytes({report['source']})[report['source']]
 print(report['source'],'findings',sum(map(len,old.values())),'->',sum(map(len,new.values())))
rows=dc.source_rows(sources);row_object=build.row_object
try:
 build.row_object=lambda row: BASE/'before'/row_object(row).name
 before_data=dc.object_facts(rows)
finally:build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
result=dict(index=meta,objects=reports,canonical_snapshot_selection=selection,
 legacy_predicted_linked_bytes_gain=sum(r['existing_nonpadding_bytes'] for r in reports if not any(r['link_preview']['after'].values()) and any(r['link_preview']['before'].values())),
 existing_address_view_provider=sources[4],cleanup_digest=provider_helpers[new_name],
 data_bindings_unchanged=True,preexisting_data_findings=dc.findings(after_data,dc.dl.load()),closed_strict_gain_unmeasured=True)
(BASE/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: three conflicts removed; cleanup bytes and all retained code/data preserved')
