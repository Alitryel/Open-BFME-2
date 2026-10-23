"""Paired scoped legacy link comparison; reads but never writes the census.

Run from the repository root. Before objects/receipts are retained under
build/controlbar-border-link-20261015/before; prepare current sources first.
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

OUT = ROOT / 'build/controlbar-border-link-20261015'
SUPPORT = ROOT / 'reverse/attempt_support/controlbar-border-link-20261015'
OLD = '?rva0031ABD9@ControlBar@@QAEXPAVGameWindow@@H@Z'
NEW = '?setCommandBarBorder@ControlBar@@QAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z'
NAMES = {OLD: NEW}

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
        if name.startswith('.debug'):
            continue
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', NAMES.get(s['name'], s['name']))
            else:
                assert s['section'] > 0
                label = ('local', s['section'], raw[s['section'] - 1][0], s['value'])
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
for source in paths:
    obj = build.obj_path((ROOT / source).resolve())
    old = OUT / 'before' / obj.name
    assert lc.object_current((ROOT / source).resolve(), obj, allow_fresh=False), source
    objects['before'].append(old)
    objects['after'].append(obj)
    # Compare every nondebug section and all relocations, normalizing
    # the replaced external callee and local label spelling. Local relocation
    # sections and offsets must stay identical; code/data bytes may not change.
    oldsections, oldraw = sections(old.read_bytes())
    newsections, newraw = sections(obj.read_bytes())
    assert [(r[0], r[1], r[2]) for r in oldraw] == [(r[0], r[1], r[2]) for r in newraw]
    assert oldsections == newsections, source
    def ext(data):
        return collections.Counter((NAMES.get(s['name'], s['name']), s['storage'],
                                    s['section'], s['value'])
                                   for s in lc._coff_symbols(data) if s['storage'] == 2)
    assert ext(old.read_bytes()) == ext(obj.read_bytes()), source
    proof[source] = {'strict_reusable_current_receipt': True,
                     'before_object_sha256': sha(old), 'after_object_sha256': sha(obj),
                     'before_receipt_sha256': sha(old.with_suffix('.deps.json')),
                     'after_receipt_sha256': sha(obj.with_suffix('.deps.json')),
                     'all_nondebug_sections_identical_after_callee_and_local_label_normalization': True}

results, data = {}, {}
original = dc.build.row_object
try:
    for phase in objects:
        localindex = copy.deepcopy(index)
        ck.refresh(localindex, objects[phase], truth)
        results[phase] = {s: ck.check_object(o, localindex, truth, s)
                          for s, o in zip(paths, objects[phase])}
        saved = dict(zip(paths, objects[phase]))
        dc.build.row_object = lambda row: saved.get(row['source'], original(row))
        missing = []
        facts = dc.object_facts(dc.source_rows(paths), missing)
        assert not missing, missing
        data[phase] = dc.findings(facts, dc.dl.load())
finally:
    dc.build.row_object = original
before = copy.deepcopy(results['before'][paths[0]])
assert OLD in before['unresolved']
before['unresolved'].remove(OLD)
assert before == results['after'][paths[0]]
assert len(before['unresolved']) == 1 and 'addHotKey@HotKeyManager' in before['unresolved'][0]
assert results['before'][paths[1]] == results['after'][paths[1]]
assert all(not v for v in results['after'][paths[1]].values())
assert data['before'] == data['after'] == []

row = next(r for r in csv.DictReader((ROOT / 'reverse/functions.csv').open())
           if r['source'] == paths[0] and r['target_rva'].lower() == '0x0031b641')
size, rva = int(row['target_size'], 0), int(row['target_rva'], 16)
a, ar = build.read_object_symbol_bytes(objects['before'][0], build.ledger_object_symbol(row), size)
b, br = build.read_object_symbol_bytes(objects['after'][0], build.ledger_object_symbol(row), size)
assert a == b
assert [(o, k, NAMES.get(n, n)) for o, k, n in ar] == br
calls = [(o, k, n) for o, k, n in br if n == NEW]
assert len(calls) == 1
at, kind, _ = calls[0]
assert kind == 20 and b[at:at + 4] == bytes(4)
retail = build.read_target_bytes(rva, size)
assert rva + at + 4 + struct.unpack_from('<i', retail, at)[0] == 0x31ABD9
result = {'context': ctx, 'object_comparisons': proof,
          'paired_legacy_findings': results, 'data_findings': data,
          'retail_call': {'caller_rva': hex(rva), 'offset': at, 'callee_rva': '0x0031ABD9',
                          'kind': 'REL32', 'object_addend': 0, 'before_name': OLD, 'after_name': NEW},
          'authored_cpp_bytes_added': 0, 'incremental_local_legacy_linked_bytes': 0,
          'unresolved_names_removed': 1, 'closed_strict_gain_claimed': False,
          'actual_link_or_data_back_claimed': False}
(SUPPORT / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
