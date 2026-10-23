"""Same-index provider binding proof; saved baseline stays in ignored build/."""
import hashlib
import json
import struct
import sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check as ck
import data_check as dc
from unittest.mock import patch
BASE = Path('build/scripted-opacity-binding-link-20261015')
SOURCE = 'Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DScriptedProcessAnimationsRva000BFDFE.cpp'
PEER = 'Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawDistanceOpacity.cpp'
OLD = '?rva000B5A72@Rva000B5A72@@QAEXPAX@Z'
NEW = '?rva000B5A72@Rva000B5C41@@QAEXPAUArg000B5A72@@@Z'
PARENT = '?processAnimations@W3DScriptedModelDraw@@QAEXXZ'

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

obj = build.obj_path(build.ROOT / SOURCE)
peer = build.obj_path(build.ROOT / PEER)
before = BASE / 'before' / obj.name
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(ck.INDEX.read_bytes()) == meta['sha256']
assert all(lc.object_current(build.ROOT / s, o, allow_fresh=False)
           for s, o in [(SOURCE, obj), (PEER, peer)])
assert normalized(before, aliases={OLD: NEW}) == normalized(obj)
old_bodies = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new_bodies = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert old_bodies.keys() == new_bodies.keys()
assert {n for n in old_bodies if old_bodies[n] != new_bodies[n]} == {PARENT}
raw_before, refs_before = build.read_object_symbol_bytes(before, PARENT)
raw_after, refs_after = build.read_object_symbol_bytes(obj, PARENT)
assert raw_before == raw_after
assert len(raw_after) == 1416
assert refs_after == [(at, kind, NEW if name == OLD else name)
                       for at, kind, name in refs_before]
assert sum(name == OLD for at, kind, name in refs_before) == 1
truth = lc.RetailTruth(lc.ledger())
paired, peers = {}, {}
for label, candidate in [('before', before), ('after', obj)]:
    index = ck.load_index()
    ck.refresh(index, [candidate, peer], truth)
    paired[label] = ck.check_object(candidate, index, truth, source=SOURCE)
    peers[label] = ck.check_object(peer, index, truth, source=PEER)
assert peers['before'] == peers['after']
assert not any(peers['after'].values())
assert OLD in paired['before']['unresolved']
assert paired['after']['unresolved'] == [n for n in paired['before']['unresolved'] if n != OLD]
assert len(paired['before']['unresolved']) == 2
assert len(paired['after']['unresolved']) == 1
assert all(paired['before'][k] == paired['after'][k] for k in paired['before'] if k != 'unresolved')
assert not ck.new_variants(obj, index, truth)
data_rows = dc.source_rows([SOURCE, PEER])
row_object = build.row_object
before_row_object = lambda row: before if row['source'] == SOURCE else row_object(row)
with patch.object(build, 'row_object', before_row_object):
    data_before = dc.findings(dc.object_facts(data_rows), dc.dl.load())
data_after = dc.findings(dc.object_facts(data_rows), dc.dl.load())
assert data_before == data_after
assert data_after == [(SOURCE, 'wrong-name', '?g_bfmeDisplayAnimationSyncClock@@3HA', '0x009E1B40')]
report = {
 'base_commit': (BASE / 'base.txt').read_text().strip(), 'index': meta,
 'source': SOURCE, 'provider': PEER,
 'strict_current_receipts': [SOURCE, PEER],
 'before_object_sha256': sha(before.read_bytes()), 'after_object_sha256': sha(obj.read_bytes()),
 'provider_object_sha256': sha(peer.read_bytes()),
 'consumer_bytes': len(raw_after), 'consumer_bytes_sha256': sha(raw_after),
 'old_relocation': [r for r in refs_before if r[2] == OLD],
 'new_relocation': [r for r in refs_after if r[2] == NEW],
 'all_nondebug_sections_identical_after_only_callee_name_substitution': True,
 'retained_comdats': len(new_bodies), 'paired_findings': paired,
 'provider_findings': peers,
 'preexisting_shadow_data_findings_unchanged': data_after,
 'legacy_linked_bytes_before': 0, 'legacy_linked_bytes_after': 0,
 'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
Path('reverse/attempt_support/scripted-opacity-binding-link-20261015/proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS: identical bytes and sections modulo one callee spelling; unresolved 2 -> 1; provider unchanged and clean; no linked-byte gain')
