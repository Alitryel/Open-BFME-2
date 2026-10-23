"""Reproduce the bounded literal/link proof from preserved build/ snapshots."""
import hashlib
import json
import shutil
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check
import link_debt

BASE = Path('build/buff-color-link-20261015')
SOURCE = 'Code/GameEngine/Source/GameClient/BuffNuggetFXNuggetCtor.cpp'
CTOR = '??0BuffNuggetFXNugget@@QAE@XZ'
LITERALS = [(219, 0x00BC4DD8, '__real@3e4ccccd', 'cdcc4c3e'),
            (235, 0x00BCAE8C, '__real@3ecccccd', 'cdcccc3e'),
            (251, 0x00BBB8D8, '__real@3f800000', '0000803f')]


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


obj = build.obj_path(build.ROOT / SOURCE)
before = BASE / 'before' / obj.name
assert lc.object_current(build.ROOT / SOURCE, obj, allow_fresh=False)
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256']
old_body, old_relocs = build.read_object_symbol_bytes(before, CTOR, 295)
new_body, new_relocs = build.read_object_symbol_bytes(obj, CTOR, 295)
expected = bytearray(old_body)
added = []
for offset, address, name, bits in LITERALS:
    assert old_body[offset:offset+4] == struct.pack('<I', address)
    assert build.read_target_bytes(address - 0x400000, 4).hex() == bits
    literal, relocs = build.read_object_symbol_bytes(obj, name, 4)
    assert literal.hex() == bits and not relocs
    expected[offset:offset+4] = bytes(4)
    added.append((offset, 6, name))
assert bytes(expected) == new_body
assert sorted(old_relocs + added) == sorted(new_relocs)
old_comdats = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new_comdats = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert set(new_comdats) - set(old_comdats) == {'__real@3e4ccccd', '__real@3ecccccd'}
assert not set(old_comdats) - set(new_comdats)
assert all(old_comdats[n] == new_comdats[n] for n in old_comdats if n != CTOR)
# Local EH labels are compiler-renumbered; compare their section, offset and
# payload rather than their spelling, including every nondebug data section.
assert normalized(before, {CTOR}) == normalized(obj, {CTOR, '__real@3e4ccccd', '__real@3ecccccd'})
truth = lc.RetailTruth(lc.ledger())
index = link_check.load_index()
assert link_check.in_census(index, obj.name)
assert not link_check.new_variants(obj, index, truth)
literal_families = {}
for _, _, name, _ in LITERALS:
    family = index['comdat'].get(name, [])
    assert family and {digest for _, digest, _ in family} == {new_comdats[name][0]}
    literal_families[name] = {'indexed_copies': len(family), 'digest_size': new_comdats[name]}
paired = {}
for label, candidate, source in [('before', before, BASE/'before'/Path(SOURCE).name),
                                 ('after', obj, build.ROOT/SOURCE)]:
    index = link_check.load_index()
    link_check.refresh(index, [candidate], truth)
    finding = link_check.check_object(candidate, index, truth)
    finding['addresses'] = link_debt.addresses(source.read_text())
    paired[label] = finding
assert len(paired['before']['addresses']) == 3
assert all(not v for k, v in paired['before'].items() if k != 'addresses')
assert not any(paired['after'].values())
report = {
    'base_commit': (BASE/'base.txt').read_text().strip(), 'index': meta,
    'source': SOURCE, 'strict_current_receipt': True,
    'object_before_sha256': sha(before.read_bytes()), 'object_after_sha256': sha(obj.read_bytes()),
    'constructor_operand_substitutions': LITERALS, 'all_other_code_and_relocations_equal': True,
    'unchanged_other_comdat_bodies': len(old_comdats)-1, 'compiler_literal_families': literal_families,
    'new_harmful_comdat_variants': [], 'paired_findings': paired,
    'legacy_existing_linked_bytes_before': 0,
    'legacy_existing_linked_bytes_after': link_check.source_bytes({SOURCE})[SOURCE],
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
shutil.copy2(obj, BASE/'object-after.obj')
shutil.copy2(obj.with_suffix('.deps.json'), BASE/'receipt-after.json')
(BASE/'object-proof.json').write_text(json.dumps(report, indent=2)+'\n')
print('PASS: three literal address operands replaced, all other code/relocations equal; LEGACY +%d linked bytes'
      % report['legacy_existing_linked_bytes_after'])
