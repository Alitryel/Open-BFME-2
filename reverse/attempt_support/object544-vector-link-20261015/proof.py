"""Paired video-lock object proof; baseline snapshots live in ignored build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, 'tools')
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path('build/object544-vector-link-20261015')
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s.get("name") in excluded and s.get("section",0) > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    table = struct.unpack_from("<I", data, 8)[0]
    associations = {}
    for i, symbol in enumerate(symbols):
        if symbol.get("aux") and symbol.get("storage") == 3 and symbol.get("section", 0) > 0:
            aux = data[table + 18 * (i + 1):table + 18 * (i + 2)]
            parent, selection = struct.unpack_from("<hB", aux, 12)
            if selection == 5:
                associations[symbol["section"]] = parent
    while True:
        more = {n for n, parent in associations.items() if parent in omitted} - omitted
        if not more: break
        omitted.update(more)
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
        assert n not in omitted, "removed helper has an incoming local relocation"
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
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], len(raw) if section["name"] == ".sxdata" else section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


context=json.loads((BASE/'context.json').read_text())
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
assert ck.load_index()['meta']==context['measurement']
sources=context['sources'];objects={s:build.obj_path(build.ROOT/s) for s in sources}
name='??1?$vector@UBfmeObject544@@V?$allocator@UBfmeObject544@@@_STL@@@_STL@@QAE@XZ'
truth=lc.RetailTruth(lc.ledger());proofs={}
for source,obj in objects.items():
    old=BASE/'before'/obj.name
    assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
    before={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
    after={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
    excluded={name} if source==sources[0] else set()
    assert before.keys()-after.keys()==excluded
    assert not after.keys()-before.keys()
    assert all(before[n]==after[n] for n in after)
    assert normalized(old,excluded)==normalized(obj,set())
    def undefined(path):
        st=path.stat();_,_,symbols=build._object_layout(str(path),st.st_mtime_ns,st.st_size)
        return {(v['name'],v['storage'],v['value'],v['type']) for v in symbols if v.get('storage') in (2,105) and v.get('section')==0}
    old_u,new_u=undefined(old),undefined(obj)
    assert not old_u-new_u
    assert new_u-old_u==({(name,2,0,32)} if excluded else set())
    proofs[source]=dict(removed_only_body_and_associative_eh=bool(excluded),undefined_added=sorted(new_u-old_u),before_sha256=sha(old.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(after),removed_comdats={n:before[n] for n in excluded})
paired={}
for phase in ('before','after'):
    objs={s:BASE/'before'/obj.name if phase=='before' else obj for s,obj in objects.items()}
    ind=ck.load_index();ck.refresh(ind,list(objs.values()),truth)
    paired[phase]={s:ck.check_object(o,ind,truth,source=s) for s,o in objs.items()}
assert json.loads(json.dumps(paired['before']))==context['before_link']
assert sum(len(v) for v in paired['before'][sources[0]].values())==1
assert not any(paired['after'][sources[0]].values())
assert paired['before'][sources[1]]==paired['after'][sources[1]]
for source,obj in objects.items():
    previous={n:{d} for n,d,z in lc.comdat_bodies(BASE/'before'/obj.name)}
    assert not ck.new_variants(obj,ind,truth,previous=previous)
rows=dc.source_rows([sources[0]]); row_object=build.row_object
try:
    build.row_object=lambda row: BASE/'before'/objects[sources[0]].name
    old_data=dc.object_facts(rows)
finally:
    build.row_object=row_object
new_data=dc.object_facts(rows);assert old_data==new_data
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
sizes=ck.source_bytes(set(sources));linked={side:sum(sizes[s] for s,v in findings.items() if not any(v.values())) for side,findings in paired.items()}
report=dict(context=context,object_proofs=proofs,paired_link=paired,retained_nondebug_sections_bytes_flags_definitions_and_symbolic_relocations_identical=True,only_removed_safeseh_entry_belongs_to_removed_destructor=True,incoming_call_preserves_external_name_and_native_owner=True,data_bindings_unchanged=True,data_findings=dc.findings(new_data,dc.dl.load()),self_strict_current=True,closed_strict_gain_unmeasured=True,legacy_predicted_linked_nonpadding_bytes=linked)
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: retained sections identical; strict current receipts; one 59-byte competing destructor removed; owner findings unchanged; legacy predicted linked bytes',linked)
