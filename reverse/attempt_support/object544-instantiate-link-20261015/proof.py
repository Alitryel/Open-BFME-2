"""Bounded paired link/object proof; baseline snapshots stay in ignored build/."""
import hashlib, json, shutil, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, eh_verify, link_census as lc, link_check
BASE=Path('build/object544-instantiate-link-20261015')
SOURCE='Code/Libraries/Source/WWVegas/WWLib/StlportObject544Vector.cpp'
def sha(data):
    return hashlib.sha256(data).hexdigest()


def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    eh = eh_verify.Obj(obj)
    while True:
        expanded = omitted | {s["index"] for s in eh.sections if s["assoc"] in omitted}
        if expanded == omitted:
            break
        omitted = expanded
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
                        for j in range(0, len(raw), 4)
                        if symbols[struct.unpack_from("<I", raw, j)[0]]["section"] not in omitted]).encode()
        if section["name"] == ".sxdata" and raw == b"[]":
            continue
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], len(raw),
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


obj=build.obj_path(build.ROOT/SOURCE)
before=BASE/'before'/obj.name
old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
removed=set(old)-set(new)
print('retained',len(new),'removed',len(removed),'added',set(new)-set(old))
assert not set(new)-set(old)
assert all(new[n]==old[n] for n in new)
a=normalized(before,removed);b=normalized(obj,set())
assert len(new)==21 and len(removed)==68
assert a==b
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
assert lc.object_current(build.ROOT/SOURCE,obj,allow_fresh=False)
truth=lc.RetailTruth(lc.ledger());paired={};indices={};peer_findings={}
PROVIDER='Code/Libraries/Source/WWVegas/WWLib/StlportVectorDtorFamily.cpp'
provider=build.obj_path(build.ROOT/PROVIDER)
assert lc.object_current(build.ROOT/PROVIDER,provider,allow_fresh=False)
for label,o in [('before',before),('after',obj)]:
    index=link_check.load_index();link_check.refresh(index,[o,provider],truth)
    peer_findings[label]=link_check.check_object(provider,index,truth,PROVIDER)
    paired[label]=link_check.check_object(o,index,truth,SOURCE);indices[label]=index
assert len(paired['before']['comdat'])==1 and sum(map(len,paired['before'].values()))==1,paired
assert not any(paired['after'].values()),paired
assert peer_findings['before']==peer_findings['after']
assert not link_check.new_variants(obj,indices['before'],truth)
selection={};sole=[]
for n in sorted(removed):
    a=sorted(indices['before']['comdat'].get(n,()));z=sorted(indices['after']['comdat'].get(n,()))
    if not z:
        sole.append(n);continue
    old_losers,old_rule=lc.keep_rule(a);new_losers,new_rule=lc.keep_rule(z)
    assert all(not loses or old_losers[i] for i,loses in new_losers.items()),n
    assert a[0][1]==z[0][1],n
    selection[n]={'before':a,'after':z,'rule':new_rule}
(BASE/'sole-symbols.json').write_text(json.dumps(sole,indent=2)+'\n')
print('sole removed',len(sole),'shared',len(selection))
scan=json.loads((BASE/'consumer-scan.json').read_text());assert not scan['external_consumers']
import data_check as dc
from unittest.mock import patch
rows=dc.source_rows([SOURCE]);row_object=build.row_object
with patch.object(build,'row_object',lambda row: BASE/'before'/row_object(row).name):
    data_before=dc.object_facts(rows)
data_after=dc.object_facts(rows);assert data_before==data_after
assert not dc.findings(data_after,dc.dl.load())
report={'base_commit':(BASE/'base.txt').read_text().strip(),'index':meta,'source':SOURCE,
'object_before_sha256':sha(before.read_bytes()),'object_after_sha256':sha(obj.read_bytes()),
'removed_comdats':{n:old[n] for n in sorted(removed)},'retained_comdats':new,
'all_retained_nondebug_sections_bytes_and_symbolic_relocations_equal':True,
'removed_comdats_have_no_incoming_relocations_from_retained_sections':True,
'shared_family_selection_unchanged':selection,'paired_findings':paired,
'consumer_scan':scan,'data_bindings_unchanged':True,'provider':{'source':PROVIDER,'sha256':sha(provider.read_bytes()),'receipt_sha256':sha(provider.with_suffix('.deps.json').read_bytes()),'paired_findings':peer_findings},'strict_current_receipt':True,'legacy_existing_linked_bytes_before':0,
'legacy_existing_linked_bytes_after':link_check.source_bytes({SOURCE})[SOURCE],
'new_authored_cpp_bytes':0,'closed_strict_gain_claimed':False}
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: retained sections and shared selections unchanged; LEGACY local +473 existing linked bytes')
