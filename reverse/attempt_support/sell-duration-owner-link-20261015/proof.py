"""Compare saved parent objects with current scoped objects against one index.

The ignored snapshots are in build/sell-duration-owner-link-20261015/before.
Run from the repository root after preparing the two sources in context.json.
This reads the census; it never writes an index or a census measurement.
"""
import collections
import copy
import csv
import hashlib
import json
from pathlib import Path
import struct
import sys

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc
import link_check as ck
import data_check as dc

OUT = ROOT / 'build/sell-duration-owner-link-20261015'
SUPPORT = ROOT / 'reverse/attempt_support/sell-duration-owner-link-20261015'
NAME = '?g_00E027C4@@3MA'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def sections(data):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    raw = []
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
        name = data[h:h + 8].rstrip(b'\0').decode('latin1')
        size, pointer, reloc = struct.unpack_from('<III', data, h + 16)
        nr = struct.unpack_from('<H', data, h + 32)[0]
        flags = struct.unpack_from('<I', data, h + 36)[0]
        raw.append((name, flags, size, data[pointer:pointer + size] if pointer else None, reloc, nr))
    result = collections.Counter()
    for name, flags, size, body, reloc, nr in raw:
        if name.startswith('.debug') or name == '.bss':
            continue
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', s['name'])
            else:
                assert s['section'] > 0
                label = ('local', raw[s['section'] - 1][0], s['name'], s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body.hex() if body is not None else None, tuple(refs))] += 1
    return result, raw


ctx = json.loads((OUT / 'context.json').read_text())
paths = ctx['sources']
assert sha(ck.INDEX) == ctx['index_sha256']
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
objects = {'before': [], 'after': []}
proof = {}
for i, source in enumerate(paths):
    obj = build.obj_path((ROOT / source).resolve())
    old = OUT / 'before' / obj.name
    assert lc.object_current((ROOT / source).resolve(), obj, allow_fresh=False), source
    objects['before'].append(old)
    objects['after'].append(obj)
    before, after = old.read_bytes(), obj.read_bytes()
    os, oldsec = sections(before)
    ns, newsec = sections(after)
    assert os == ns, source
    oldsyms, newsyms = lc._coff_symbols(before), lc._coff_symbols(after)
    if i == 0:
        # There is exactly one new four-byte allocation, after the unchanged
        # private float. No earlier local object's offset or extent changes.
        obss = [s for s in oldsec if s[0] == '.bss']
        nbss = [s for s in newsec if s[0] == '.bss']
        assert len(obss) == len(nbss) == 1
        assert obss[0][2:4] == (4, None) and nbss[0][2:4] == (8, None)
        assert obss[0][1] == nbss[0][1] and nbss[0][5] == 0
        oldg = [s for s in oldsyms if s['name'] == NAME]
        newg = [s for s in newsyms if s['name'] == NAME]
        assert len(oldg) == len(newg) == 1
        assert oldg[0]['storage'] == newg[0]['storage'] == 2
        assert oldg[0]['section'] == oldg[0]['value'] == 0
        assert newg[0]['section'] > 0 and newg[0]['value'] == 4
        assert newsec[newg[0]['section'] - 1][0] == '.bss'
        retained = lambda syms, secs: {(s['name'], s['storage'], s['value'], secs[s['section'] - 1][0] if s['section'] > 0 else s['section']) for s in syms if s['name'] != NAME and s['storage'] == 2}
        assert retained(oldsyms, oldsec) == retained(newsyms, newsec)
        local = lambda syms, secs: {(s['name'], s['value']) for s in syms if s['storage'] == 3 and s['section'] > 0 and secs[s['section'] - 1][0] == '.bss' and s['name'] != '.bss'}
        assert local(oldsyms, oldsec) == local(newsyms, newsec)
    else:
        a, b = bytearray(before), bytearray(after)
        a[4:8] = b[4:8] = b'\0' * 4
        assert a == b
    proof[source] = {'strict_reusable_current_receipt': True,
                     'before_object_sha256': sha(old), 'after_object_sha256': sha(obj),
                     'before_receipt_sha256': sha(old.with_suffix('.deps.json')),
                     'after_receipt_sha256': sha(obj.with_suffix('.deps.json')),
                     'all_nondebug_nonbss_sections_and_relocations_identical': True,
                     'consumer_whole_coff_identical_except_timestamp': i == 1,
                     'added_zero_filled_data_bytes': 4 if i == 0 else 0}

results = {}
data = {}
original = dc.build.row_object
try:
    for phase in objects:
        localindex = copy.deepcopy(index)
        ck.refresh(localindex, objects[phase], truth)
        results[phase] = {s: ck.check_object(o, localindex, truth, s) for s, o in zip(paths, objects[phase])}
        saved = dict(zip(paths, objects[phase]))
        dc.build.row_object = lambda row: saved.get(row['source'], original(row))
        missing = []
        facts = dc.object_facts(dc.source_rows(paths), missing)
        assert not missing, missing
        data[phase] = dc.findings(facts, dc.dl.load())
finally:
    dc.build.row_object = original
for source in paths:
    old = copy.deepcopy(results['before'][source])
    assert old['unresolved'] == [NAME], old
    old['unresolved'] = []
    assert old == results['after'][source], source
assert all(not findings for findings in results['after'][paths[0]].values())
assert data['before'] == data['after'] == [], data

# Independently preserve retail operand evidence and the initial mapped bytes.
operands = []
for row in csv.DictReader((ROOT / 'reverse/functions.csv').open()):
    if row['source'] not in paths or row['status'] != 'matched':
        continue
    source, size = row['source'], int(row['target_size'], 0)
    obj = objects['after'][paths.index(source)]
    try:
        body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
    except ValueError:
        # Only the five known renumbered EH labels may be absent. Their
        # containing object is unchanged, and eh_verify checks their parents.
        assert build.ledger_object_symbol(row) in {
            '$L14356', '$L14848', '$L14888', '$L14943', '$L16470'}
        continue
    for off, kind, symbol in relocs:
        if symbol != NAME:
            continue
        assert kind == 6 and body[off:off + 4] == bytes(4)
        retail = build.read_target_bytes(int(row['target_rva'], 16), size)
        assert struct.unpack_from('<I', retail, off)[0] == 0xE027C4
        operands.append({'source': source, 'rva': row['target_rva'], 'size': size,
                         'operand_offset': off, 'retail_va': '0x00E027C4',
                         'retail_operand_rva': hex(int(row['target_rva'], 16) + off),
                         'object_addend': 0, 'relocation_kind': 'DIR32'})
assert len(operands) == 2, operands
assert build.read_target_bytes(0xA027C4, 4) == bytes(4)
result = {'context': ctx, 'object_comparisons': proof, 'paired_legacy_findings': results,
          'data_findings': data, 'retail_operands': operands, 'retail_initial_bytes': '00000000',
          'authored_cpp_bytes_added': 0, 'verified_data_bytes_added': 4,
          'incremental_local_legacy_linked_bytes': 50,
          'closed_strict_gain_claimed': False, 'actual_link_or_data_back_claimed': False}
(SUPPORT / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({'paired_legacy_findings': results, 'data_findings': data, 'retail_operands': operands}, indent=2))
