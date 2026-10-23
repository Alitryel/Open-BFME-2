"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/genbase-link-20261015')
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

context = json.loads((BASE / 'context.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == context['index_sha256']
sources = context['sources']
name = '??1GenBase009EB7D0@@UAE@XZ'
objects = [build.obj_path(build.ROOT / source) for source in sources]
old_objects = [BASE / 'before' / obj.name for obj in objects]
assert all(lc.object_current(build.ROOT / src, obj, allow_fresh=False)
           for src, obj in zip(sources, objects))
old = {n: (d, z) for n, d, z in lc.comdat_bodies(old_objects[0])}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(objects[0])}
assert set(old) - set(new) == {name}
assert not set(new) - set(old)
assert all(old[n] == new[n] for n in new)
# External referent spellings/bindings stay identical, including EH calls to
# the destructor. Only its old local ret-only definition is omitted.
assert normalized(old_objects[0], {name}) == normalized(objects[0], set())
assert normalized(old_objects[1], set()) == normalized(objects[1], set())
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase, candidates in [('before', old_objects), ('after', objects)]:
    index = link_check.load_index()
    link_check.refresh(index, candidates, truth)
    paired[phase] = {src: link_check.check_object(obj, index, truth, source=src)
                     for src, obj in zip(sources, candidates)}
assert not any(paired['before'][sources[0]].values())
assert paired['before'][sources[1]]['comdat'] == [(name, 'first', None)]
assert sum(map(len, paired['before'][sources[1]].values())) == 1
assert not any(any(f.values()) for f in paired['after'].values())
for old_obj, obj in zip(old_objects, objects):
    previous = {n: {d} for n, d, z in lc.comdat_bodies(old_obj)}
    assert not link_check.new_variants(obj, index, truth, previous=previous)
rows = dc.source_rows(sources)
row_object = build.row_object
try:
    build.row_object = lambda row: BASE / 'before' / row_object(row).name
    before_data = dc.object_facts(rows)
finally:
    build.row_object = row_object
after_data = dc.object_facts(rows)
assert before_data == after_data
# Target evidence: both mapped associative EH cleanup calls target the same
# existing five-byte reset trampoline; no second pin or owner is introduced.
import eh_verify as eh
image = eh.Image()
parents = [
    ('??0Rva00136794@@QAE@PBD0MPBVRva0013101E@@ABV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@22@Z', 0x136794),
    ('??1Rva00136794@@UAE@XZ', 0x136aa5)]
cleanup = []
for objpath, (parent, rva) in zip(objects, parents):
    obj = eh.Obj(objpath)
    assert eh.verify_row(image, obj, parent, rva) == ('EXACT', '')
    sym = obj.by_name[parent]
    sections = obj.eh_sections(sym['section'])
    places, conflicts = eh.section_placements(image, obj, dict(sym, retail_rva=rva), sections)
    assert not conflicts
    for sec in sections:
        for offset, symbol, kind in sec['relocs']:
            if obj.symbols[symbol]['name'] == name:
                assert kind == eh.REL32
                site = places[sec['index']] + offset
                target = site + 4 + eh._signed(image.dword(site))
                assert target == 0x135e35
                cleanup.append(dict(source=str(objpath), site=hex(site), target=hex(target)))
assert len(cleanup) == 2
assert image.bytes[0x135e35] == 0xe9
assert 0x135e3a + eh._signed(image.dword(0x135e36)) == 0x61ed80
assert sha(link_check.INDEX.read_bytes()) == context['index_sha256']
report = dict(context=context, before_sha256=[sha(p.read_bytes()) for p in old_objects],
    after_sha256=[sha(p.read_bytes()) for p in objects], self_strict_current=True,
    removed_comdats={name:old[name]}, retained_constructor_comdats=len(new),
    all_retained_nondebug_sections_bytes_flags_definitions_relocations_unchanged=True,
    provider_nondebug_sections_unchanged=True, target_cleanup_calls=cleanup,
    paired_link=paired, findings_before=1, findings_after=0,
    existing_nonpadding_bytes=link_check.source_bytes(set(sources)),
    data_bindings_unchanged=True, data_findings=dc.findings(after_data, dc.dl.load()),
    closed_strict_gain_unmeasured=True)
(BASE / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Retained constructor COMDATs unchanged:', len(new))
print('Provider nondebug sections unchanged; retail cleanup targets verified')
print('Paired legacy findings: 1 -> 0')
print('Data bindings unchanged; findings:', report['data_findings'])
