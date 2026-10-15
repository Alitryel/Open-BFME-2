"""Paired audio float-store binding proof; saved baseline is in ignored build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check as ck, data_check as dc
BASE = Path('build/audio-float-binding-20261015')
OLD = '?_bfme_ro_set_98@RenderObjClass@@UAEXM@Z'
NEW = '?set@Rva00210C91FloatField@@QAEXM@Z'
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded=(), aliases=None):
    aliases = aliases or {}
    excluded = set(excluded)
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
            return aliases.get(symbol["name"], symbol["name"]), symbol["storage"], symbol["value"]
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
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
sources = context['sources']
objects = [build.obj_path(build.ROOT / source) for source in sources]
before = [BASE / 'before' / obj.name for obj in objects]
assert all(lc.object_current(build.ROOT / s, o, allow_fresh=False) for s, o in zip(sources, objects))
assert normalized(before[0]) == normalized(objects[0], excluded={NEW})
for i in (1, 2):
    assert normalized(before[i], aliases={OLD: NEW}) == normalized(objects[i])
assert normalized(before[3]) == normalized(objects[3])
parent_names = ['?rva00433498@Rva00433498@@QAEXM@Z', '?xferNoName@DynamicAudioEventInfo@@QAEXPAVXfer@@@Z']
changed_relocations = []
for i, name in zip((1, 2), parent_names):
    old_raw, old_refs = build.read_object_symbol_bytes(before[i], name)
    new_raw, new_refs = build.read_object_symbol_bytes(objects[i], name)
    assert old_raw == new_raw
    assert new_refs == [(at, kind, NEW if name == OLD else name) for at, kind, name in old_refs]
    changed = [(at, kind) for at, kind, name in old_refs if name == OLD]
    assert len(changed) == 1 and changed[0][1] == 20
    changed_relocations.append(dict(source=sources[i], symbol=name, offset=changed[0][0], bytes=len(new_raw)))
old_comdats = {n:(d,z) for n,d,z in lc.comdat_bodies(before[0])}
new_comdats = {n:(d,z) for n,d,z in lc.comdat_bodies(objects[0])}
assert new_comdats.keys() - old_comdats.keys() == {NEW}
assert not old_comdats.keys() - new_comdats.keys()
assert all(old_comdats[n] == new_comdats[n] for n in old_comdats)
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase, cohort in [('before', before), ('after', objects)]:
    index = ck.load_index()
    assert all(ck.in_census(index, o.name) for o in cohort)
    ck.refresh(index, cohort, truth)
    paired[phase] = {s:ck.check_object(o,index,truth,source=s) for s,o in zip(sources,cohort)}
assert json.loads(json.dumps(paired['before'])) == context['before_link']
assert sum(len(v) for f in paired['before'].values() for v in f.values()) == 5
assert not any(any(f.values()) for f in paired['after'].values())
for old_obj, obj in zip(before, objects):
    previous = {n:{d} for n,d,z in lc.comdat_bodies(old_obj)}
    assert not ck.new_variants(obj, index, truth, previous=previous)
rows = dc.source_rows(sources)
row_object = build.row_object
try:
    build.row_object = lambda row: BASE / 'before' / row_object(row).name
    before_data = dc.object_facts(rows)
finally:
    build.row_object = row_object
after_data = dc.object_facts(rows)
assert before_data == after_data
import eh_verify as eh
image = eh.Image()
assert image.bytes[0x210c91:0x210ca2].hex() == 'f30f10442404f30f118198000000c20400'
assert image.bytes[0xe43e7:0xe43f4].hex() == '8b442404898198000000c20400'
assert build.read_object_symbol_bytes(objects[0], NEW) == (image.bytes[0x210c91:0x210ca2], [])
for obj, name in zip(objects[:3], [NEW] + parent_names):
    copies, _, _, _ = lc.object_facts(obj, truth)
    assert [verdict for symbol, _, _, verdict in copies if symbol == name] == ['retail']
for i,rva in zip((1,2), (0x433498,0x4331c6)):
    site = rva + changed_relocations[i-1]['offset']
    assert site + 4 + eh._signed(image.dword(site)) == 0x210c91
    changed_relocations[i-1]['retail_call_operand'] = hex(site)
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
report = dict(context=context, before_sha256=[sha(o.read_bytes()) for o in before],
    after_sha256=[sha(o.read_bytes()) for o in objects], self_strict_current=True,
    all_retained_nondebug_sections_identical_modulo_two_external_name_changes=True,
    added_helper_bytes=17, retained_provider_comdats=len(old_comdats),
    changed_relocations=changed_relocations, data_bindings_unchanged=True,
    data_findings=dc.findings(after_data,dc.dl.load()), paired_link=paired,
    findings_before=5, findings_after=0, clean_units_before=1, clean_units_after=4,
    existing_nonpadding_bytes_unblocked=sum(ck.source_bytes(set(sources[1:])).values()),
    unblocked_source_bytes=ck.source_bytes(set(sources[1:])),
    closed_strict_gain_unmeasured=True)
(BASE / 'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('Paired local legacy findings: 5 -> 0; clean units: 1/4 -> 4/4')
print('Existing nonpadding bytes unblocked:',report['existing_nonpadding_bytes_unblocked'])
print('Self-strict current objects; retained nondebug sections unchanged modulo two helper referents')
print('Data bindings unchanged; findings:',report['data_findings'])
