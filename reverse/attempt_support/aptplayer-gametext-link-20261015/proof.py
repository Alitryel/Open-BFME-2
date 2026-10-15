"""Reproduce the bounded GameText binding proof; see readme.md for prerequisites."""
import copy, hashlib, json, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check, data_check as dc
BASE = Path('build/aptplayer-gametext-link-20261015')
EVIDENCE = Path('reverse/attempt_support/aptplayer-gametext-link-20261015')
OLD = '?TheGameText@@3PAVGameText@@A'
NEW = '?TheGameText@@3PAVGameTextInterface@@A'
BODY = '?rva002238E6@Rva00224CDC@@QAEXVAsciiString@@@Z'
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


sources = (EVIDENCE/'sources.txt').read_text().splitlines()
objects = [build.obj_path(build.ROOT/s) for s in sources]
previous = [BASE/'before'/o.name for o in objects]
meta = json.loads((EVIDENCE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256'], 'measurement index changed'
reports=[]
for source, old, new in zip(sources,previous,objects):
    assert lc.object_current(build.ROOT/source,new,allow_fresh=False),source
    assert normalized(old)==normalized(new),source+' nondebug sections differ beyond global rename'
    reports.append(dict(source=source,before_sha256=sha(old.read_bytes()),after_sha256=sha(new.read_bytes()),
       before_receipt_sha256=sha(old.with_suffix('.deps.json').read_bytes()),
       after_receipt_sha256=sha(new.with_suffix('.deps.json').read_bytes()),
       all_nondebug_section_bytes_flags_definitions_and_normalized_relocations_equal=True,
       self_strict_current=True))
assert previous[1].read_bytes()==objects[1].read_bytes(),'provider object changed'
old_bytes,old_relocs=build.read_object_symbol_bytes(previous[0],BODY,expected_size=199)
new_bytes,new_relocs=build.read_object_symbol_bytes(objects[0],BODY,expected_size=199)
assert old_bytes==new_bytes
assert [(a,k,rename(n)) for a,k,n in old_relocs]==new_relocs
old_refs=[(a,k,n) for a,k,n in old_relocs if n==OLD]
assert len(old_refs)==1
at,kind,_=old_refs[0]
assert kind==6
assert struct.unpack_from('<I',old_bytes,at)[0]==0
retail=build.read_target_bytes(0x2238E6,199)
assert struct.unpack_from('<I',retail,at)[0]==0xDFF0BC
# The unchanged provider defines the exact data-ledger name as zero-filled data.
stat=objects[1].stat()
_,sections,symbols=build._object_layout(str(objects[1]),stat.st_mtime_ns,stat.st_size)
providers=[s for s in symbols if s['name']==NEW and s['storage']==2 and s['section']>0]
assert len(providers)==1
provider=providers[0];section=sections[provider['section']-1]
assert section['name']=='.bss' and provider['value']==0
ledger=dc.dl.load()
assert ledger[0x9FF0BC]['name']==NEW
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
    assert not any(after.values()),after
    vb=link_check.new_variants(previous[i],indices['before'],truth)
    va=link_check.new_variants(objects[i],indices['before'],truth)
    assert all(v in vb for v in va),(vb,va)
    report.update(link_preview=dict(before=before,after=after),variant_findings=dict(before=vb,after=va),
       existing_nonpadding_bytes=link_check.source_bytes({report['source']})[report['source']])
rows=dc.source_rows(sources);row_object=build.row_object
unread=[]
try:
    build.row_object=lambda row: BASE/'before'/row_object(row).name
    before_data=dc.object_facts(rows,unread)
finally:build.row_object=row_object
after_data=dc.object_facts(rows,unread)
assert not unread,unread
normalized_before={source:({(rename(n),a) for n,a in binds},{rename(n) for n in defined})
                   for source,(binds,defined) in before_data.items()}
assert normalized_before==after_data,'data bindings changed beyond the singleton name'
assert not dc.findings(after_data,ledger)
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
sizes=link_check.source_bytes(set(sources))
summary={label:dict(clean=sum(not any(v.values()) for v in findings),
    linked_bytes=sum(sizes[s] for s,v in zip(sources,findings) if not any(v.values())))
    for label,findings in paired.items()}
assert summary['after']['linked_bytes']-summary['before']['linked_bytes']==sizes[sources[0]]
result=dict(index=meta,objects=reports,global_relocation=dict(caller_rva='0x002238E6',
    offset=at,retail_operand_rva=hex(0x2238E6+at),retail_target_va='0x00DFF0BC',before=OLD,after=NEW),
    sole_unresolved_finding_removed=True,data_findings=dict(before=sorted(dc.findings(before_data,ledger)),after=[]),
    paired_legacy_preview=summary,new_authored_bytes=0,closed_strict_gain_unmeasured=True)
(EVIDENCE/'proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: complete nondebug sections equal modulo one DIR32 global name; provider unchanged.')
print(json.dumps(summary,indent=2))
