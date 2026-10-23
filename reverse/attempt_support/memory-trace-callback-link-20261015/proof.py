"""Paired callback identity repair proof; run at repository root.
Requires the saved pre-change objects in build/memory-callback-link-20261015/before.
Never writes the census index or status. See readme.md for scope and provenance.
"""
import copy, hashlib, json, struct, subprocess, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check, data_check as dc
BASE = Path('build/memory-callback-link-20261015')
OLD = '?Rva00031420Callback@@YAXPBD@Z'
NEW = '?rva00031420@@YAXPBD@Z'
CTOR = '??0Rva00033B90Allocator@@QAE@PAXI_N000@Z'
def sha(data): return hashlib.sha256(data).hexdigest()
def rename(name): return NEW if name == OLD else name
def normalized(obj):
    excluded = set()
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    leaders = {}
    for symbol in symbols:
        if symbol.get("storage") == 2 and symbol["section"] > 0:
            leaders.setdefault(symbol["section"], []).append(rename(symbol["name"]))

    def body(n):
        section = sections[n - 1]
        pointer = section["raw_pointer"]
        return data[pointer:pointer + section["raw_size"]] if pointer else b""

    def referent(i):
        symbol = symbols[i]
        n = symbol["section"]
        assert n not in omitted, "removed helper has an incoming nondebug relocation"
        if symbol["storage"] in (2, 105):
            return rename(symbol["name"]), symbol["storage"], symbol["value"]
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


sources = (BASE/'sources.txt').read_text().splitlines()
objects = [build.obj_path(build.ROOT/s) for s in sources]
previous = [BASE/'before'/o.name for o in objects]
meta = json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256'], 'measurement index changed'
reports=[]
def bindings(obj):
    _, _, syms = build._object_layout(str(obj),obj.stat().st_mtime_ns,obj.stat().st_size)
    return {(rename(s['name']),s['storage'],s['section']==0,s['value'],s['type'])
            for s in syms if s.get('storage') in (2,105)}
for source, old, new in zip(sources,previous,objects):
    assert lc.object_current(build.ROOT/source,new,allow_fresh=False),source
    assert normalized(old)==normalized(new),source+' nondebug sections differ beyond callback rename'
    assert bindings(old)==bindings(new),source+' external bindings differ beyond callback rename'
    reports.append(dict(source=source,before_sha256=sha(old.read_bytes()),after_sha256=sha(new.read_bytes()),
       all_nondebug_section_bytes_flags_definitions_and_normalized_relocations_equal=True,
       external_bindings_equal_except_callback_rename=True,self_strict_current=True))
assert previous[1].read_bytes()==objects[1].read_bytes(),'provider object changed'
old_bytes,old_relocs=build.read_object_symbol_bytes(previous[0],CTOR,expected_size=445)
new_bytes,new_relocs=build.read_object_symbol_bytes(objects[0],CTOR,expected_size=445)
assert old_bytes==new_bytes
assert [(a,k,rename(n)) for a,k,n in old_relocs]==new_relocs
old_refs=[(a,k,n) for a,k,n in old_relocs if n==OLD]
assert len(old_refs)==1
at,kind,_=old_refs[0]
assert kind==6
assert struct.unpack_from('<I',old_bytes,at)[0]==0
retail=build.read_target_bytes(0x33B90,445)
assert struct.unpack_from('<I',retail,at)[0]==0x431420
truth=lc.RetailTruth(lc.ledger())
indices={};paired={}
for label,objs in [('before',previous),('after',objects)]:
    index=link_check.load_index()
    link_check.refresh(index,objs,truth)
    indices[label]=index
    paired[label]=[link_check.check_object(o,index,truth,source=s) for o,s in zip(objs,sources)]
for i,report in enumerate(reports):
    before=paired['before'][i];after=paired['after'][i]
    expected=copy.deepcopy(before)
    if i==0: expected['unresolved'].remove(OLD)
    assert expected==after,(before,after)
    vb=link_check.new_variants(previous[i],indices['before'],truth)
    va=link_check.new_variants(objects[i],indices['before'],truth)
    assert all(v in vb for v in va),(vb,va)
    report.update(link_preview=dict(before=before,after=after),variant_findings=dict(before=vb,after=va),
       existing_nonpadding_bytes=link_check.source_bytes({report['source']})[report['source']])
rows=dc.source_rows(sources);row_object=build.row_object
try:
    build.row_object=lambda row: BASE/'before'/row_object(row).name
    before_data=dc.object_facts(rows)
finally:build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
result=dict(index=meta,objects=reports,callback_relocation=dict(constructor_rva='0x00033B90',
    offset=at,retail_operand_rva=hex(0x33B90+at),retail_target='0x00031420',before=OLD,after=NEW),
    unresolved_findings_removed=1,data_bindings_unchanged=True,
    preexisting_data_findings=dc.findings(after_data,dc.dl.load()),
    legacy_predicted_linked_bytes_gain=0,closed_strict_gain_unmeasured=True)
(BASE/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: only callback relocation name changes; unresolved findings -1; provider and data facts unchanged')
print('Callback operand RVA',hex(0x33B90+at),'targets retail RVA 0x00031420')
