"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys,re
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/light-ctor-owner-link-20261015')
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
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or section["name"]==".sxdata" or n in omitted:
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

def safeseh(obj):
 stat=obj.stat()
 data,sections,symbols=build._object_layout(str(obj),stat.st_mtime_ns,stat.st_size)
 found=[]
 for section in sections:
  if section['name']!='.sxdata': continue
  raw=data[section['raw_pointer']:section['raw_pointer']+section['raw_size']]
  for j in range(0,len(raw),4):
   sym=symbols[struct.unpack_from('<I',raw,j)[0]];sec=sections[sym['section']-1]
   body=data[sec['raw_pointer']:sec['raw_pointer']+sec['raw_size']]
   found.append((sym['name'],sym['value'],sha(body)))
 return Counter(found)

sources=json.loads((BASE/'sources.json').read_text())
context=json.loads((BASE/'context.json').read_text())
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
truth=lc.RetailTruth(lc.ledger())
objects=[build.obj_path(build.ROOT/s) for s in sources]
before_objects=[BASE/'before'/obj.name for obj in objects]
reports=[]
for i,(source,obj,before) in enumerate(zip(sources,objects,before_objects)):
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False),source
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 removed=set(old)-set(new)
 assert not set(new)-set(old)
 assert not any(old[n]!=new[n] for n in new),source
 assert bool(removed)==(i==0),(source,removed)
 old_sections=normalized(before,removed);new_sections=normalized(obj,set())
 assert not new_sections-old_sections,(source,'added or changed retained sections',new_sections-old_sections)
 removed_ancillary=list((old_sections-new_sections).elements())
 old_seh=safeseh(before);new_seh=safeseh(obj)
 assert not new_seh-old_seh,(source,'new or changed SafeSEH handler')
 removed_seh=list((old_seh-new_seh).elements())
 assert [r[0] for r in removed_seh]==(['__ehhandler$??1RenderObjClass@@UAE@XZ'] if i==0 else [])
 reports.append(dict(source=source,self_strict_current=True,before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),removed_comdats={n:old[n] for n in removed},retained_comdats=len(new),retained_nondebug_sections_identical=True,removed_ancillary_sections=removed_ancillary,removed_safeseh_handlers=removed_seh))
paired={}
for label,candidates in [('before',before_objects),('after',objects)]:
 index=link_check.load_index()
 link_check.refresh(index,candidates,truth)
 paired[label]=[link_check.check_object(obj,index,truth,source=source) for source,obj in zip(sources,candidates)]
for report,before,after,obj,old_obj in zip(reports,paired['before'],paired['after'],objects,before_objects):
 report['link_preview']={'before':before,'after':after}
 report['affected_existing_nonpadding_bytes']=link_check.source_bytes({report['source']})[report['source']]
 previous={n:{d} for n,d,z in lc.comdat_bodies(old_obj)}
 variants=link_check.new_variants(obj,index,truth,previous=previous)
 report['new_variant_diagnostics']=variants
 assert not variants,(report['source'],variants)
 for kind in before:
  if isinstance(before[kind],list):
   added=[item for item in after[kind] if item not in before[kind]]
   assert not added or (report['source'].endswith('/collect.cpp') and kind=='comdat' and added==[('?Set_Collision_Type@RenderObjClass@@UAEXH@Z','first',None)]),(report['source'],kind,added)
 report['legacy_findings_removed']=sum(len(v) if isinstance(v,list) else int(bool(v)) for v in before.values())-sum(len(v) if isinstance(v,list) else int(bool(v)) for v in after.values())
rows=dc.source_rows(sources)
row_object=build.row_object
moved={'?Set_Native_Screen_Size@RenderObjClass@@UAEXM@Z','?dup_005ad93a@@YAXXZ'}
try:
 build.row_object=lambda row: BASE/'before'/row_object({**row,'source':sources[0]} if row['name'] in moved else row).name
 before_data=dc.object_facts(rows)
finally: build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data,'data-reference facts changed'
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
report=dict(context=context,objects=reports,legacy_predicted_linked_bytes_gain=sum(r['affected_existing_nonpadding_bytes'] for r in reports if not any(r['link_preview']['after'].values()) and any(r['link_preview']['before'].values())),data_facts_unchanged=True,preexisting_data_findings=dc.findings(after_data,dc.dl.load()),closed_strict_gain_unmeasured=True)
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
for r in reports:
 print(r['source'], 'removed COMDATs',len(r['removed_comdats']), 'legacy findings removed',r['legacy_findings_removed'],'remaining', {k:len(v) if isinstance(v,list) else v for k,v in r['link_preview']['after'].items()})
print('Legacy preview linked nonpadding byte gain:',report['legacy_predicted_linked_bytes_gain'])
