"""Bounded paired proof for the polygon water-reader link binding."""
import copy, hashlib, json, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, data_check as dc, data_ledger as dl, link_census as lc, link_check
BASE = Path('build/polygon-water-reader-link-20261015')
EVIDENCE = Path('reverse/attempt_support/polygon-water-reader-link-20261015')
OLD = '?Rva00328E96Parse@@YAXAAVDataChunkInput@@HPAX@Z'
NEW = '?rva00328E96@@YAXAAVDataChunkInput@@HPAURva00328E96WaterRecord@@@Z'
BODY = '?parsePolygonTriggersChunkImpl@Impl@OldPolygonTriggerDataChunkParserBase@@QAE_NAAVDataChunkInput@@PBUDataChunkInfo@@@Z'
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
for source,old,new in zip(sources,previous,objects):
    assert lc.object_current(build.ROOT/source,new,allow_fresh=False),source
    assert normalized(old)==normalized(new),source+' changed beyond one callee name'
    reports.append(dict(source=source,before_sha256=sha(old.read_bytes()),after_sha256=sha(new.read_bytes()),
      before_receipt_sha256=sha(old.with_suffix('.deps.json').read_bytes()),
      after_receipt_sha256=sha(new.with_suffix('.deps.json').read_bytes()),
      self_strict_current=True,nondebug_sections_identical_modulo_one_callee=True))
assert previous[1].read_bytes()==objects[1].read_bytes(),'provider changed'
before,br=build.read_object_symbol_bytes(previous[0],BODY,expected_size=222)
after,ar=build.read_object_symbol_bytes(objects[0],BODY,expected_size=222)
assert before==after
assert [(a,k,rename(n)) for a,k,n in br]==ar
sites=[(at,kind) for at,kind,n in br if n==OLD]
assert len(sites)==1
at,kind=sites[0]
assert kind==0x14 and before[at-1]==0xe8
assert struct.unpack_from('<i',before,at)[0]==0
retail=build.read_target_bytes(0x3294D6,222)
target=0x3294D6+at+4+struct.unpack_from('<i',retail,at)[0]
assert target==0x328E96,hex(target)
truth=lc.RetailTruth(lc.ledger())
paired={}
for label,objs in [('before',previous),('after',objects)]:
    index=link_check.load_index()
    link_check.refresh(index,objs,truth)
    paired[label]=[link_check.check_object(o,index,truth,source=s) for o,s in zip(objs,sources)]
expected=copy.deepcopy(paired['before'])
expected[0]['unresolved'].remove(OLD)
assert paired['after']==expected,(paired['before'],paired['after'])
assert paired['after'][0]['unresolved']==['??0Rva00308E63@@QAE@H_N@Z']
assert not any(paired['after'][1].values())
rows = dc.source_rows(sources)
original_row_object = build.row_object
unread = []
try:
    build.row_object = lambda row: BASE/'before'/original_row_object(row).name
    data_before = dc.object_facts(rows, unread)
finally:
    build.row_object = original_row_object
data_after = dc.object_facts(rows, unread)
assert not unread, unread
assert data_before == data_after, 'data bindings changed'
data_findings = dc.findings(data_after, dl.load())
assert data_findings == [(sources[0], 'wrong-name', '?g_Va00DBD0F0@@3HA', '0x009BD0F0')]
sizes=link_check.source_bytes(set(sources))
summary={label:dict(clean=sum(not any(v.values()) for v in values),
 linked_bytes=sum(sizes[s] for s,v in zip(sources,values) if not any(v.values())))
 for label,values in paired.items()}
result=dict(index=meta,objects=reports,callee=dict(caller_rva='0x003294D6',caller_extent=222,
 relocation_offset=at,retail_target_rva=hex(target),before=OLD,after=NEW),
 paired_legacy_findings=paired,paired_legacy_summary=summary,
 unchanged_preexisting_data_findings=data_findings,
 unresolved_findings_removed=1,new_authored_bytes=0,self_strict_placement_unmeasured=True,
 closed_strict_gain_unmeasured=True)
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
(EVIDENCE/'proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: whole nondebug objects identical modulo one REL32 name; provider unchanged.')
print(json.dumps(summary,indent=2))
