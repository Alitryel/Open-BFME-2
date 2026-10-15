"""Paired bounded LAN prompt binding proof; see readme.md for prerequisites."""
import copy, hashlib, json, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check, data_check as dc
BASE = Path('build/lan-prompt-provider-link-20261015')
EVIDENCE = Path('reverse/attempt_support/lan-prompt-provider-link-20261015')
OLD = '?method@Rva0054D3D9Target@@QAEXHABVUnicodeString@@0@Z'
NEW = '?configure@Rva0054D3E1Prompt@@QAE_NHABVUnicodeString@@0@Z'
BODY = '?Rva00437EAC@@YAXHABVUnicodeString@@0@Z'
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
    assert normalized(old)==normalized(new),source+' nondebug sections differ beyond callee rename'
    reports.append(dict(source=source,before_sha256=sha(old.read_bytes()),after_sha256=sha(new.read_bytes()),
       before_receipt_sha256=sha(old.with_suffix('.deps.json').read_bytes()),
       after_receipt_sha256=sha(new.with_suffix('.deps.json').read_bytes()),
       all_nondebug_section_bytes_flags_definitions_and_normalized_relocations_equal=True,
       self_strict_current=True))
assert previous[1].read_bytes()==objects[1].read_bytes(),'provider object changed'
old_bytes,old_relocs=build.read_object_symbol_bytes(previous[0],BODY,expected_size=24)
new_bytes,new_relocs=build.read_object_symbol_bytes(objects[0],BODY,expected_size=24)
assert old_bytes==new_bytes
assert [(a,k,rename(n)) for a,k,n in old_relocs]==new_relocs
old_refs=[(a,k,n) for a,k,n in old_relocs if n==OLD]
assert len(old_refs)==1
at,kind,_=old_refs[0]
assert kind==20 and old_bytes[at-1]==0xe8
retail=build.read_target_bytes(0x437EAC,24)
assert 0x437EAC+at+4+struct.unpack_from('<i',retail,at)[0]==0x54D3D9
provider_bytes,provider_relocs=build.read_object_symbol_bytes(objects[1],NEW,expected_size=8)
assert provider_bytes[:4]==bytes.fromhex('8b4904e9')
assert provider_relocs==[(4,20,'?configure@Rva0054D222Prompt@@AAE_NHABVUnicodeString@@0@Z')]
retail_provider=build.read_target_bytes(0x54D3D9,8)
assert 0x54D3D9+8+struct.unpack_from('<i',retail_provider,4)[0]==0x54D12A
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
assert before_data==after_data,'data bindings changed'
assert not dc.findings(after_data,dc.dl.load())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
sizes=link_check.source_bytes(set(sources))
summary={label:dict(clean=sum(not any(v.values()) for v in findings),
    linked_bytes=sum(sizes[s] for s,v in zip(sources,findings) if not any(v.values())))
    for label,findings in paired.items()}
assert summary['after']['linked_bytes']-summary['before']['linked_bytes']==sizes[sources[0]]
result=dict(index=meta,objects=reports,call_relocation=dict(caller_rva='0x00437EAC',
    offset=at,retail_target_rva='0x0054D3D9',before=OLD,after=NEW),
    sole_unresolved_finding_removed=True,data_bindings_unchanged=True,
    paired_legacy_preview=summary,new_authored_bytes=0,closed_strict_gain_unmeasured=True)
(EVIDENCE/'proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: complete nondebug sections equal modulo one REL32 callee name; provider unchanged.')
print(json.dumps(summary,indent=2))

# Compare shadow findings with the saved-before object without changing caches.
import allowed_symbols as allowed, code_identity_gate as identity
row_object = allowed.row_object
identity_results = {}
for label in ('before', 'after'):
    allowed.row_object = lambda row: (BASE/'before'/row_object(row).name
        if label == 'before' and row['source'] in sources else row_object(row))
    try:
        problems, mode, _, count, _ = identity.check([sources[0]], [])
        identity_results[label] = dict(problems=problems, mode=mode, rows=count)
    finally:
        allowed.row_object = row_object
assert identity_results['before'] == identity_results['after']
(EVIDENCE/'identity.json').write_text(json.dumps(identity_results, indent=2)+'\n')
print('PASS: both pre-existing code-identity shadow findings unchanged.')
