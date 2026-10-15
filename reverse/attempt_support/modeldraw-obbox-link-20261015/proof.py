"""Compare the scoped repair against saved strict-current objects; no census writes."""
import copy
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path.cwd()
OUT = ROOT / 'build/modeldraw-obbox-link-20261015'
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
name = '?Transform@OBBoxClass@@SAXABVMatrix3D@@ABV1@PAV1@@Z'
vector = '?Transform_Vector@Matrix3D@@SAXABV1@ABVVector3@@PAV2@@Z'
expected = {name: 237, vector: 196}
assert len(removed) == 2 and sum(removed.values()) == 2
for part in removed:
    assert part[0] == '.text' and len(part[2]) == 1
    symbol, offset, storage = part[2][0]
    assert offset == 0 and storage == 2 and expected[symbol] == part[-1]

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
assert len(b['comdat']) == len(a['comdat']) + 2
assert (name, 'retail', 'wrong') in b['comdat']
assert (vector, 'retail', 'wrong') in b['comdat']
assert not any(row[0] in expected for row in a['comdat'])
assert set(b['selected']) - set(a['selected']) == {name}
assert set(a['selected']) - set(b['selected']) == set()
for source in sources[1:]:
    old_findings, new_findings = paired['before'][source], paired['after'][source]
    assert set(old_findings['selected']) - set(new_findings['selected']) == {name}
    assert not new_findings['selected']
    assert all(old_findings[k] == new_findings[k]
               for k in old_findings if k != 'selected')
sizes = ck.source_bytes(set(sources))
linked = {label: sum(sizes[s] for s, findings in rows.items()
                     if not any(findings.values())) for label, rows in paired.items()}
assert linked == {'before': 0, 'after': sizes[sources[2]]}
assert linked['after'] == 350
for source, obj in zip(sources[1:], objects[1:]):
    assert obj.read_bytes() == (OUT / obj.name).read_bytes()
report = {
    'base': before['base'], 'index_meta': index['meta'],
    'index_sha256': before['index_sha256'], 'paired': paired,
    'linked_nonpadding_bytes': linked, 'closed_strict': False,
    'removed_sections': expected,
    'retained_nondebug_sections': sum((old & new).values()),
    'all_retained_bytes_and_relocations_identical': True,
    'objects': {s: {'sha256': hashlib.sha256(o.read_bytes()).hexdigest(),
                    'self_strict': True} for s, o in zip(sources, objects)},
}
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Removed only the 237-byte Transform and 196-byte Transform_Vector; all retained sections identical.')
print('Local legacy: caller findings149->145; all three lose wrong-selected Transform.')
print('Existing fetch consumer LINKS: +350 nonpadding bytes; no closed-strict gain claimed.')
