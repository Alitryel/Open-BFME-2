"""Bounded interface-table proof; snapshots remain in ignored build/."""
import hashlib, json, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check as ck, data_check as dc
from unittest.mock import patch
BASE = Path('build/army-summary-tables-link-20261015')
EVIDENCE = Path('reverse/attempt_support/army-summary-tables-link-20261015')
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
        if symbol["storage"] in (2, 105):
            return aliases.get(symbol["name"], symbol["name"]), symbol["storage"], symbol["value"]
        assert n not in omitted, "unexpected local reference to a new table"
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

sources = json.loads((BASE / 'sources.json').read_text())
tables = [
    '?ArmySummaryTemplateVisitorTable@@3QBQ8Rva00220D1E@@AEHPBVThingTemplate@@@ZB',
    '?ArmySummaryObjectVisitorTable@@3QBQ8Rva002206F9@@AE_NPAVRva0037DCA5@@@ZB',
]
aliases = dict(zip(['?g_00BE6A64@@3QBQBXB', '?g_00BE6A68@@3QBQBXB'], tables))
objects = [build.obj_path(build.ROOT / source) for source in sources]
before = [BASE / 'before' / obj.name for obj in objects]
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(ck.INDEX.read_bytes()) == meta['sha256']
reports = []
for source, old, new, table in zip(sources, before, objects, tables):
    assert lc.object_current(build.ROOT / source, new, allow_fresh=False), source
    # Every retained section, byte, external definition and normalized relocation
    # is equal. Only the two constructor references change their external names;
    # each newly added four-byte table occupies a separate .rdata section.
    assert normalized(old, aliases=aliases) == normalized(new, excluded=[table]), source
    reports.append({'source': source, 'self_strict_current': True,
                    'all_retained_nondebug_sections_equal': True,
                    'object_sha256': {'before': sha(old.read_bytes()), 'after': sha(new.read_bytes())},
                    'receipt_sha256': {'before': sha(old.with_suffix('.deps.json').read_bytes()),
                                       'after': sha(new.with_suffix('.deps.json').read_bytes())}})
truth = lc.RetailTruth(lc.ledger())
paired = {}
for label, candidates in [('before', before), ('after', objects)]:
    index = ck.load_index()
    ck.refresh(index, candidates, truth)
    paired[label] = [ck.check_object(obj, index, truth, source=source)
                     for source, obj in zip(sources, candidates)]
assert paired['before'][0]['unresolved'] == sorted(aliases)
assert all(not value for result in paired['after'] for value in result.values()), paired['after']
assert all(not value for value in paired['before'][1].values()), paired['before'][1]
result = {'index': meta, 'objects': reports, 'same_index_local_findings': paired,
          'local_linked_bytes': {'before': 82, 'after': 1145, 'gain': 1063},
          'new_verified_data_bytes': 8, 'new_authored_cpp_bytes': 0,
          'closed_strict_gain': 'unmeasured; dependency closure not prepared'}
(EVIDENCE / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
