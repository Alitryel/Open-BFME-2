"""Compare the scoped repair against saved strict-current objects; no census writes."""
import copy
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path.cwd()
OUT = ROOT / 'build/obbox-transform-link-20261015'
sys.path[:0] = [str(ROOT / 'tools'),
               str(ROOT / 'reverse/attempt_support/moduledata-snapshot-link-20261015')]
import build
import link_check as ck
import link_census as lc
import sections

before = json.loads((OUT / 'before.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == before['index_sha256']
sources = before['sources']
objects = [build.obj_path(ROOT / s) for s in sources]
old_object = OUT / objects[0].name
assert hashlib.sha256(old_object.read_bytes()).hexdigest() == before['object_sha256']
assert all(build.compile_is_current(ROOT / s, o, strict=True)
           for s, o in zip(sources, objects))
old, new = sections.sections(old_object), sections.sections(objects[0])
removed, added = old - new, new - old
assert not added
assert len(removed) == 1 and sum(removed.values()) == 1
part = next(iter(removed))
name = '?Transform@OBBoxClass@@SAXABVMatrix3D@@ABV1@PAV1@@Z'
assert part[0] == '.text' and part[2] == ((name, 0, 2),) and part[-1] == 165

index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
paired = {}
for label, objs in [('before', [old_object] + objects[1:]), ('after', objects)]:
    idx = copy.deepcopy(index)
    ck.refresh(idx, objs, truth)
    paired[label] = {s: ck.check_object(o, idx, truth, s)
                     for s, o in zip(sources, objs)}
assert json.loads(json.dumps(paired['before'])) == before['before']
b = paired['before'][sources[0]]
a = paired['after'][sources[0]]
assert set(b['unresolved']) - set(a['unresolved']) == {
    '?Multiply@Matrix3x3@@SAXABVMatrix3D@@ABV1@PAV1@@Z'}
assert len(b['comdat']) == len(a['comdat']) + 1
assert (name, 'retail', 'wrong') in b['comdat']
assert not any(row[0] == name for row in a['comdat'])
assert a['selected'] == b['selected']
assert all(paired['before'][s] == paired['after'][s] for s in sources[1:])
sizes = ck.source_bytes(set(sources))
linked = {label: sum(sizes[s] for s, findings in rows.items()
                     if not any(findings.values())) for label, rows in paired.items()}
assert linked == {'before': 0, 'after': 0}
report = {
    'base': before['base'], 'index_meta': index['meta'],
    'index_sha256': before['index_sha256'], 'paired': paired,
    'linked_nonpadding_bytes': linked, 'closed_strict': False,
    'removed_section': {'name': name, 'size': part[-1]},
    'retained_nondebug_sections': sum((old & new).values()),
    'all_retained_bytes_and_relocations_identical': True,
    'objects': {s: {'sha256': hashlib.sha256(o.read_bytes()).hexdigest(),
                    'self_strict': True} for s, o in zip(sources, objects)},
}
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Removed only the 165-byte competing Transform; all retained sections identical.')
print('Local legacy findings: one unresolved and one wrong COMDAT removed; LINKED +0.')
