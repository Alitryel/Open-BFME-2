"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/terrain-inline-link-20261015')
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

context = json.loads((BASE / 'context.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == context['index_sha256']
source = context['source']
getters = {'?getHeight@WorldHeightMap@@QAEGHH@Z', '?setFlipState@WorldHeightMap@@QAEXHH_N@Z'}
obj = build.obj_path(build.ROOT / source)
before = BASE / 'before' / obj.name
assert lc.object_current(build.ROOT / source, obj, allow_fresh=False)
old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert set(old) - set(new) == getters
assert not set(new) - set(old)
assert all(old[n] == new[n] for n in new)
assert normalized(before, getters) == normalized(obj, set())
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase, candidate in [('before', before), ('after', obj)]:
    index = link_check.load_index()
    link_check.refresh(index, [candidate], truth)
    paired[phase] = link_check.check_object(candidate, index, truth, source=source)
assert paired['before']['duplicates'] == ['?setFlipState@WorldHeightMap@@QAEXHH_N@Z']
assert {x[0] for x in paired['before']['comdat']} == getters
assert sum(map(len, paired['before'].values())) == 3
assert not any(paired['after'].values())
previous = {name: {digest} for name, digest, size in lc.comdat_bodies(before)}
assert not link_check.new_variants(obj, index, truth, previous=previous)
rows = dc.source_rows([source])
row_object = build.row_object
try:
    build.row_object = lambda row: BASE / 'before' / row_object(row).name
    before_data = dc.object_facts(rows)
finally:
    build.row_object = row_object
after_data = dc.object_facts(rows)
assert before_data == after_data
assert sha(link_check.INDEX.read_bytes()) == context['index_sha256']
report = dict(context=context, source=source, self_strict_current=True,
    before_sha256=sha(before.read_bytes()), after_sha256=sha(obj.read_bytes()),
    removed_comdats={name:old[name] for name in sorted(getters)}, retained_comdats=len(new),
    all_retained_nondebug_sections_bytes_flags_definitions_relocations_unchanged=True,
    no_incoming_nondebug_relocations_to_removed_helpers=True,
    paired_link=paired, findings_before=sum(map(len, paired['before'].values())),
    findings_after=sum(map(len, paired['after'].values())),
    affected_existing_nonpadding_bytes=link_check.source_bytes({source})[source],
    data_bindings_unchanged=True, data_findings=dc.findings(after_data, dc.dl.load()),
    legacy_linked_before=False, legacy_linked_after=True,
    closed_strict_gain_unmeasured=True)
(BASE / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Retained COMDATs unchanged:', len(new))
print('Paired findings:', report['findings_before'], '->', report['findings_after'])
print('Data bindings unchanged; findings:', report['data_findings'])
