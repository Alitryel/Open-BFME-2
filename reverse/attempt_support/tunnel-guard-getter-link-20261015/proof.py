"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/tunnel-guard-getter-link-20261015')
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

sources=[
 'Code/GameEngine/Source/GameLogic/AI/AITNGuardReturnStateOnEnter.cpp',
 'Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp',
 'Code/GameEngine/Source/GameLogic/AI/AIAttackApproachComputePath.cpp',
 'Code/GameEngine/Source/GameClient/InGameUIIdleWorker.cpp',
]
getter='?getContainedBy@Object@@QAEPAV1@XZ'
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
truth=lc.RetailTruth(lc.ledger())
objects=[build.obj_path(build.ROOT/s) for s in sources]
before_objects=[BASE/'before'/obj.name for obj in objects]
reports=[]
for source,obj,before in zip(sources,objects,before_objects):
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 assert set(old)-set(new)=={getter}, (source,set(old)-set(new))
 assert not set(new)-set(old)
 assert all(old[n]==new[n] for n in new)
 assert normalized(before,{getter})==normalized(obj,set()),source+' retained section difference'
 reports.append(dict(source=source,self_strict_current=True,
  before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),
  removed_comdat=dict(name=getter,body=old[getter]),retained_comdats=len(new),
  all_retained_sections_bytes_flags_definitions_relocations_unchanged=True,
  no_incoming_nondebug_relocations_to_getter=True))
paired={}
for label,candidates in [('before',before_objects),('after',objects)]:
 index=link_check.load_index()
 link_check.refresh(index,candidates,truth)
 paired[label]=[link_check.check_object(obj,index,truth,source=source) for source,obj in zip(sources,candidates)]
for report,before,after,obj,old_obj in zip(reports,paired['before'],paired['after'],objects,before_objects):
 removed=[x for x in before['comdat'] if x[0]==getter]
 assert len(removed)==1,(report['source'],before)
 expected={**before,'comdat':[x for x in before['comdat'] if x[0]!=getter]}
 assert after==expected,(report['source'],before,after)
 previous={name:{digest} for name,digest,size in lc.comdat_bodies(old_obj)}
 assert not link_check.new_variants(obj,index,truth,previous=previous)
 report['link_preview']={'before':before,'after':after}
 report['affected_existing_nonpadding_bytes']=link_check.source_bytes({report['source']})[report['source']]
rows=dc.source_rows(sources)
row_object=build.row_object
try:
 build.row_object=lambda row: BASE/'before'/row_object(row).name
 before_data=dc.object_facts(rows)
finally:
 build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data,'data-reference debt changed'
data_findings=dc.findings(after_data,dc.dl.load())
assert len(data_findings)==3,data_findings
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
report=dict(index=meta,objects=reports,removed_comdat_copies=len(reports),
 legacy_predicted_linked_bytes_gain=sum(r['affected_existing_nonpadding_bytes'] for r in reports
  if not any(r['link_preview']['after'].values()) and any(r['link_preview']['before'].values())),
 data_bindings_unchanged=True,preexisting_data_findings=data_findings,
 closed_strict_gain_unmeasured=True)
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
