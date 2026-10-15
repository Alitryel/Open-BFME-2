"""Compare owned before/current objects and paired local link predictions."""
import copy
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path.cwd()
OUT = ROOT / 'build/icoord-adapter-link-20261015'
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'reverse/attempt_support/moduledata-snapshot-link-20261015')]
import build
import link_check as ck
import link_census as lc
import sections

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

context = json.loads((OUT / 'before.json').read_text())
assert sha(ck.INDEX) == context['index_sha256']
name = '?asBase@@YAAAUICoord2DBase@@AAUICoord2D@@@Z'
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
objects = {source: build.obj_path(ROOT / source) for source in context['sources']}
before_objects = {source: OUT / 'before' / obj.name for source, obj in objects.items()}
paired = {}
for label, paths in [('before', before_objects), ('after', objects)]:
    preview = copy.deepcopy(index)
    ck.refresh(preview, list(paths.values()), truth)
    paired[label] = {source: ck.check_object(obj, preview, truth, source)
                     for source, obj in paths.items()}

reports = {}
for source, obj in objects.items():
    before = before_objects[source]
    saved_source = OUT / 'before' / Path(source).name
    before_receipt = before.with_suffix('.deps.json')
    receipt = json.loads(before_receipt.read_text())
    assert receipt['version'] == 2 and receipt['path'] == source
    assert receipt['source'] == hashlib.md5(saved_source.read_bytes()).hexdigest()
    assert receipt['object'] == hashlib.md5(before.read_bytes()).hexdigest()
    assert build.compile_is_current(ROOT / source, obj, strict=True)
    old, new = sections.sections(before), sections.sections(obj)
    removed = old - new
    assert not new - old
    assert sum(removed.values()) == 1
    part = next(iter(removed))
    assert part[0].startswith('.text') and part[2] == ((name, 0, 2),)
    assert part[3] == bytes.fromhex('8b442404c3')
    for retained in new:
        for _, _, target in retained[4]:
            assert name not in str(target)
    assert obj.read_bytes().count(b'__imp_') == before.read_bytes().count(b'__imp_')
    assert json.loads(json.dumps(paired['before'][source])) == context['sources'][source]
    assert paired['before'][source]['comdat'] == [(name, 'first', None)]
    assert sum(map(len, paired['before'][source].values())) == 1
    assert not any(paired['after'][source].values())
    reports[source] = {
        'before_source_sha256': sha(saved_source), 'after_source_sha256': sha(ROOT / source),
        'before_object_sha256': sha(before), 'after_object_sha256': sha(obj),
        'before_receipt_sha256': sha(before_receipt),
        'after_receipt_sha256': sha(obj.with_suffix('.deps.json')),
        'self_strict_current': True,
        'retained_nondebug_sections': sum(new.values()),
        'retained_bytes_flags_definitions_and_symbolic_relocations_identical': True,
        'removed_unused_adapter': {'name': name, 'bytes': part[3].hex(), 'size': part[5]},
    }

byte_counts = ck.source_bytes(set(objects))
report = {
    **context, 'objects': reports, 'paired': paired,
    'indexed_adapter_peers': [
        {'object': index['objects'][i], 'digest': digest, 'verdict': verdict}
        for i, digest, verdict in index['comdat'].get(name, ())],
    'legacy_predicted_linked_nonpadding_bytes': {'before': 0, 'after': sum(byte_counts.values()),
                                               'after_by_source': byte_counts},
    'authored_cpp_byte_growth': 0, 'closed_strict_gain_measured': False,
}
assert sha(ck.INDEX) == context['index_sha256']
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print(f'PASS: {len(reports)} objects preserve every retained section; two unused 5B adapters removed; '
      f'legacy findings 2 -> 0, predicted linked 0 -> {sum(byte_counts.values())}B; no closed-strict claim.')
