import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/locomotor-frame-global-link-20261015'

RENAMES = {'?g_00DBA4E4@@3HA': '?BfmeLogicFramesPerSecond@@3HA',
           '?g_Va00DBA4E4@@3HA': '?BfmeLogicFramesPerSecond@@3HA'}

def canonical(name):
    return RENAMES.get(name, name)

def sections(data):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    raw = []
    for i in range(count):
        h = 20 + optional + 40 * i
        name = data[h:h + 8].rstrip(b'\0').decode('latin1')
        size, pointer, reloc = struct.unpack_from('<III', data, h + 16)
        nr = struct.unpack_from('<H', data, h + 32)[0]
        flags = struct.unpack_from('<I', data, h + 36)[0]
        body = data[pointer:pointer + size] if pointer else None
        raw.append((name, flags, size, body, reloc, nr))
    result = collections.Counter()
    for name, flags, size, body, reloc, nr in raw:
        if name.startswith('.debug'):
            continue
        if name == '.sxdata':
            # COFF symbol indices change when the unused wrapper disappears.
            body = tuple(symbols[t[0]]['name'] for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', canonical(s['name']))
            else:
                # Compare the actual local target section and offset, rather
                # than MSVC's automatically renumbered $L/$T label.
                assert s['section'] > 0
                target_name, target_flags, target_size, target_body, _, _ = raw[s['section'] - 1]
                label = ('local', target_name, target_flags, target_size,
                         target_body.hex() if target_body is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

import copy
import shutil
import link_check as ck
import hatch_counters
import data_check
from unittest.mock import patch

ctx = json.loads((OUT / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
paths = ctx['sources']
objects = [build.obj_path(ROOT / s) for s in paths]
report = {'context': ctx, 'objects': {}, 'paired_results': {}}
for i, (source, obj) in enumerate(zip(paths, objects)):
    assert build.compile_is_current(ROOT / source, obj, strict=True)
    before = (OUT / f'before-{i}.obj').read_bytes()
    after = obj.read_bytes()
    assert sections(before) == sections(after)
    def bindings(data):
        return {(canonical(s['name']), s['storage'], s['section'] > 0,
                 s['value'] if s['section'] <= 0 else 0)
                for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
    assert bindings(before) == bindings(after)
    def renamed_refs(data):
        syms = {s['index']: s for s in lc._coff_symbols(data)}
        refs = []
        for j in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * j
            name = data[h:h + 8].rstrip(b'\0').decode('latin1')
            if name.startswith('.debug'):
                continue
            at = struct.unpack_from('<I', data, h + 24)[0]
            nr = struct.unpack_from('<H', data, h + 32)[0]
            for k in range(at, at + nr * 10, 10):
                offset, target, kind = struct.unpack_from('<IIH', data, k)
                if syms[target]['name'] in RENAMES:
                    assert kind == 6
                    refs.append({'section': j + 1, 'offset': offset,
                                 'kind': kind, 'old_target': syms[target]['name']})
        return refs
    refs = renamed_refs(before)
    assert len(refs) == [3, 1, 1, 2, 1, 0][i]
    assert not renamed_refs(after)
    if i == 5:
        assert before == after
    old_hatches = hatch_counters.scan(source, (OUT / f'before-{i}.cpp').read_text())
    new_hatches = hatch_counters.scan(source, (ROOT / source).read_text())
    assert not new_hatches - old_hatches
    report['objects'][source] = {
        'all_nondebug_sections_and_normalized_bindings_identical': True,
        'changed_dir32_targets': refs, 'strict_receipt_current': True,
        'hatches_removed': sum((old_hatches - new_hatches).values())}
    for name, old, new in [('object', before, after),
                           ('receipt', (OUT / f'before-{i}.deps.json').read_bytes(),
                            obj.with_suffix('.deps.json').read_bytes()),
                           ('source', (OUT / f'before-{i}.cpp').read_bytes(),
                            (ROOT / source).read_bytes())]:
        report['objects'][source]['before_' + name + '_sha256'] = hashlib.sha256(old).hexdigest()
        report['objects'][source]['after_' + name + '_sha256'] = hashlib.sha256(new).hexdigest()

index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
# Only these objects exist in the index. Do not invent link order for others.
measurable = [0, 1, 5]
report['not_in_index'] = [paths[i] for i in [2, 3, 4]]
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    current = []
    for i in measurable:
        if phase == 'before':
            d = OUT / 'saved-before'
            d.mkdir(exist_ok=True)
            obj = d / objects[i].name
            shutil.copy2(OUT / f'before-{i}.obj', obj)
        else:
            obj = objects[i]
        current.append(obj)
    ck.refresh(local, current, truth)
    report['paired_results'][phase] = {
        paths[i]: ck.check_object(obj, local, truth, paths[i])
        for i, obj in zip(measurable, current)}
for i in measurable:
    old, new = (report['paired_results'][p][paths[i]] for p in ('before', 'after'))
    expected = copy.deepcopy(old)
    expected['unresolved'] = [n for n in old['unresolved'] if n not in RENAMES]
    assert expected == new
assert not any(report['paired_results']['after'][paths[0]].values())
totals = {}
sizes = ck.source_bytes({paths[i] for i in measurable})
for phase in ('before', 'after'):
    totals[phase] = sum(sizes[s] for s, findings in report['paired_results'][phase].items()
                        if not any(findings.values()))
assert totals == {'before': 511, 'after': 1263}
report['local_legacy_linked_bytes'] = totals
report['new_authored_cpp_bytes'] = 0
rows = data_check.source_rows(paths)
old_objects = {s: OUT / f'before-{i}.obj' for i, s in enumerate(paths)}
# Read the saved, previously byte-verified object snapshots without replacing
# any live cache object or pretending they have current-source receipts.
with patch.object(build, 'row_object', lambda row: old_objects[row['source']]):
    unread = []
    old_facts = data_check.object_facts(rows, unread)
    assert not unread
unread = []
new_facts = data_check.object_facts(rows, unread)
assert not unread
ledger = data_check.dl.load()
old_findings = set(data_check.findings(old_facts, ledger))
new_findings = set(data_check.findings(new_facts, ledger))
removed = old_findings - new_findings
assert not new_findings - old_findings
assert len(removed) == 5
assert all(r[1] == 'wrong-name' and r[2] in RENAMES and r[3] == '0x009BA4E4'
           for r in removed)
assert all(('?BfmeLogicFramesPerSecond@@3HA', 0x009BA4E4) in new_facts[s][0]
           for s in paths[:-1])
baseline = data_check.read_baseline()
assert new_findings - baseline <= old_findings - baseline
report['data_check'] = {
    'before_findings': len(old_findings), 'after_findings': len(new_findings),
    'removed': sorted(removed),
    'before_outside_baseline': sorted(old_findings - baseline),
    'remaining_preexisting_outside_baseline': sorted(new_findings - baseline),
    'canonical_binding_to_target_rva_verified_for_all_five_consumers': True}
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Five consumers: eight DIR32 bindings corrected; all other nondebug bytes/relocations identical.')
print('Paired local legacy linked bytes:', totals)
print('Address-named hatch occurrences removed:', sum(r['hatches_removed'] for r in report['objects'].values()))
