"""Paired scoped object/link proof. Requires saved pre-change objects under
build/tree-oclist-link-20261015/before and the recorded census index.
Run from repository root; never rewrites the index or census status.
"""
"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/tree-oclist-link-20261015')
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


removed='??9_Rb_tree_base_iterator@_STL@@QBE_NABU01@@Z'
reports=[]
for source in (BASE/'sources.txt').read_text().splitlines():
 obj=build.obj_path(build.ROOT/source);before=BASE/'before'/obj.name
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 assert set(old)-set(new)=={removed},(source,set(old)-set(new))
 assert not set(new)-set(old)
 assert all(old[n]==new[n] for n in new)
 def helpers(path):
  _,_,symbols=build._object_layout(str(path),path.stat().st_mtime_ns,path.stat().st_size)
  return {s['name'] for s in symbols if s.get('storage')==3 and s['section']>0 and s['name'].startswith('??$?9')}
 added=helpers(obj)-helpers(before)
 helper_details=[]
 data,sections,symbols=build._object_layout(str(obj),obj.stat().st_mtime_ns,obj.stat().st_size)
 for symbol in symbols:
  if symbol['name'] not in added:continue
  section=sections[symbol['section']-1];ptr=section['raw_pointer'];body=data[ptr:ptr+section['raw_size']]
  assert section['reloc_count']==0 and body.hex()=='8b0033c93b020f95c18ac1c3'
  helper_details.append(dict(name=symbol['name'],bytes=body.hex(),relocations=0))
 assert len(helper_details)>=1
 assert normalized(before,{removed})==normalized(obj,added),source+' retained sections differ'
 def bindings(path):
  _,_,symbols=build._object_layout(str(path),path.stat().st_mtime_ns,path.stat().st_size)
  return {(s['name'],s['storage'],s['section']==0,s['value'],s['type']) for s in symbols if s.get('storage') in (2,105) and s['name']!=removed}
 assert bindings(before)==bindings(obj)
 reports.append(dict(source=source,before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(new),removed_comdat=old[removed],private_helpers=helper_details,all_retained_nondebug_bytes_flags_definitions_relocations_unchanged=True,no_incoming_relocations_to_replaced_helpers=True,self_strict_current=True))
 print(source,'PASS',len(new),'retained COMDATs; local helpers',len(added))
(BASE/'object-proof.json').write_text(json.dumps(reports,indent=2)+'\n')

import copy
sources=(BASE/'sources.txt').read_text().splitlines()
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
truth=lc.RetailTruth(lc.ledger())
objects=[build.obj_path(build.ROOT/source) for source in sources]
before_objects=[BASE/'before'/obj.name for obj in objects]
provider='Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_int.cpp'
provider_obj=build.obj_path(build.ROOT/provider)
assert lc.object_current(build.ROOT/provider,provider_obj,allow_fresh=False)
provider_sha=sha(provider_obj.read_bytes())
paired={};indices={};selection={} 
for label,candidates in [('before',before_objects),('after',objects)]:
 index=link_check.load_index()
 link_check.refresh(index,candidates+[provider_obj],truth)
 indices[label]=index
 paired[label]=[link_check.check_object(obj,index,truth,source=source) for source,obj in zip(sources,candidates)]
 copies=sorted(index['comdat'][removed]);losses,rule=lc.keep_rule(copies)
 selection[label]={'copies':copies,'winners':[c for c in copies if not losses[c[0]]],'rule':rule}
assert selection['before']['winners']==selection['after']['winners']
for report,old,new,obj,before in zip(reports,paired['before'],paired['after'],objects,before_objects):
 expected=copy.deepcopy(old)
 matches=[r for r in expected['comdat'] if r[0]==removed]
 assert len(matches)==1
 expected['comdat'].remove(matches[0]);assert expected==new,(report['source'],old,new)
 vb=link_check.new_variants(before,indices['before'],truth);va=link_check.new_variants(obj,indices['before'],truth)
 assert all(v in vb for v in va)
 report['link_preview']={'before':old,'after':new}
 report['variant_findings']={'before':vb,'after':va}
 report['existing_nonpadding_bytes']=link_check.source_bytes({report['source']})[report['source']]
 print(report['source'],'findings',sum(map(len,old.values())),'->',sum(map(len,new.values())))
provider_before=link_check.check_object(provider_obj,indices['before'],truth,source=provider)
provider_after=link_check.check_object(provider_obj,indices['after'],truth,source=provider)
assert provider_before==provider_after
assert sha(provider_obj.read_bytes())==provider_sha
rows=dc.source_rows(sources);row_object=build.row_object
try:
 build.row_object=lambda row: BASE/'before'/row_object(row).name
 before_data=dc.object_facts(rows)
finally:build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
result=dict(index=meta,objects=reports,selection=selection,removed_comdat_copies=len(reports),
 legacy_predicted_linked_bytes_gain=sum(r['existing_nonpadding_bytes'] for r in reports if not any(r['link_preview']['after'].values()) and any(r['link_preview']['before'].values())),
 data_bindings_unchanged=True,preexisting_data_findings=dc.findings(after_data,dc.dl.load()),
 closed_strict_gain_unmeasured=True,provider=dict(source=provider,object_sha256=provider_sha,link_preview=provider_after,self_strict_current=True))
(BASE/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: scoped conflicts removed, all other link findings and object/data bindings preserved')
