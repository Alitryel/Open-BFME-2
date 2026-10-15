"""Read-only paired COFF and legacy link preview for the owned particle consumer."""
import copy
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path.cwd()
OUT = ROOT / 'build/particle-matrix-index-link-20261015'
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'reverse/attempt_support/moduledata-snapshot-link-20261015')]
import build
import link_check as ck
import link_census as lc
import sections

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

context = json.loads((OUT / 'before.json').read_text())
source = context['source']
assert sha(ck.INDEX) == context['index_sha256']
obj = build.obj_path(ROOT / source)
before = OUT / 'before' / obj.name
before_receipt = before.with_suffix('.deps.json')
receipt = json.loads(before_receipt.read_text())
assert receipt['version'] == 2
assert receipt['path'] == source
assert receipt['source'] == hashlib.md5((OUT / 'before' / Path(source).name).read_bytes()).hexdigest()
assert receipt['object'] == hashlib.md5(before.read_bytes()).hexdigest()
assert build.compile_is_current(ROOT / source, obj, strict=True)
old, new = sections.sections(before), sections.sections(obj)
removed = old - new
name = '??AMatrix3@@QBEABVVector3@@H@Z'
assert not new - old
assert sum(removed.values()) == 1
part = next(iter(removed))
assert part[0].startswith('.text') and part[2] == ((name, 0, 2),)
assert part[3] == bytes.fromhex('8b4424046bc00c03c1c20400'), part[3].hex()
for retained in new:
    for _, _, target in retained[4]:
        assert name not in str(target)
assert obj.read_bytes().count(b'__imp_') == before.read_bytes().count(b'__imp_')
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
paired = {}
for label, path in [('before', before), ('after', obj)]:
    preview = copy.deepcopy(index)
    ck.refresh(preview, [path], truth)
    paired[label] = ck.check_object(path, preview, truth, source)
assert json.loads(json.dumps(paired['before'])) == context['before']
assert paired['before']['comdat'] == [(name, 'first', None)]
assert not any(paired['after'].values())
assert sum(map(len, paired['before'].values())) == 1
assert sha(ck.INDEX) == context['index_sha256']
peers = [{'object': index['objects'][i], 'digest': digest, 'verdict': verdict}
         for i, digest, verdict in index['comdat'].get(name, ())]
report = {
    **context,
    'before_sha256': sha(before), 'after_sha256': sha(obj),
    'before_receipt_sha256': sha(before_receipt),
    'before_source_sha256': sha(OUT / 'before' / Path(source).name),
    'after_source_sha256': sha(ROOT / source),
    'after_receipt_sha256': sha(obj.with_suffix('.deps.json')),
    'self_strict_current': True,
    'retained_nondebug_sections': sum(new.values()),
    'all_retained_bytes_flags_definitions_and_symbolic_relocations_identical': True,
    'removed_unused_helper': {'name': name, 'bytes': part[3].hex(), 'size': part[5]},
    'paired': paired, 'indexed_indexer_peers': peers,
    'authored_cpp_byte_growth': 0,
    'legacy_predicted_linked_nonpadding_bytes': {'before': 0, 'after': 1816},
    'closed_strict_gain_measured': False,
}
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print(f'PASS: {sum(new.values())} retained sections identical; unused {part[5]}B accessor removed; legacy findings 1 -> 0; consumer self-strict, no closed-strict claim.')
