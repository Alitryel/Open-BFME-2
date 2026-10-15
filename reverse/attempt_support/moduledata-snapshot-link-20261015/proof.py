"""Paired local preview; never mutates the census/index/status."""
import copy
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path.cwd()
OUT = ROOT / 'build/moduledata-snapshot-link-20261015'
sys.path[:0] = [str(Path(__file__).resolve().parent), str(ROOT / 'tools')]
import build
import link_check as ck
import link_census as lc
import sections as sec

sources = (OUT / 'sources.txt').read_text().splitlines()
before = json.loads((OUT / 'before.json').read_text())
assert before['index_sha256'] == hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
old = [OUT / build.obj_path(ROOT / s).name for s in sources]
new = [build.obj_path(ROOT / s) for s in sources]
provider = sec.sections(new[-1])
sec.normalized = lambda s: '??_7Snapshot@@6B@' if s == '_vtbl_00BBB554' else s
proof = {}
for source, b, a in zip(sources, old, new):
    assert hashlib.sha256(b.read_bytes()).hexdigest() == before['before_object_sha256'][source]
    assert build.compile_is_current(ROOT / source, a, strict=True), source
    bs, az = sec.sections(b), sec.sections(a)
    removed, added = bs - az, az - bs
    if source == sources[-1]:
        assert not removed and not added
    else:
        # Only remove the obsolete linker alias directive. All code, EH,
        # and other sections retain bytes and relocations after rebinding
        # the same retail vtable to its canonical provider name.
        directives = [p for p in removed if p[0] == '.drectve']
        assert len(directives) == 1
        directive = directives[0]
        assert removed[directive] == 1 and len(removed) == 1, (source, removed)
        replacement = directive[3].replace(
            b'/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@ ', b'')
        expected = (directive[0], directive[1], directive[2], replacement,
                    directive[4], len(replacement))
        assert added[expected] == 1, (source, replacement, added)
        del added[expected]
        assert sum(added.values()) == 2, (source, added)
        names = {p[2][0][0] for p in added}
        assert names == {'??_7Snapshot@@6B@', '??_GSnapshot@@UAEPAXI@Z'}
        assert not added - provider, (source, added - provider)
    proof[source] = {
        'before_sha256': hashlib.sha256(b.read_bytes()).hexdigest(),
        'after_sha256': hashlib.sha256(a.read_bytes()).hexdigest(),
        'self_strict': True,
        'retained_nondebug_sections': sum((bs & az).values()),
        'all_retained_bytes_and_relocations_identical_after_vtable_rebinding': True,
        'new_snapshot_sections_equal_current_provider': source != sources[-1],
    }

paired = {}
for label, objects in [('before', old), ('after', new)]:
    idx = copy.deepcopy(index)
    ck.refresh(idx, objects, truth)
    paired[label] = {s: ck.check_object(o, idx, truth, s)
                     for s, o in zip(sources, objects)}
assert json.loads(json.dumps(paired['before'])) == before['before']
for source in sources:
    assert not any(paired['after'][source].values()), paired['after'][source]
    b = paired['before'][source]
    if source != sources[-1]:
        assert b['comdat'] == [('??1Snapshot@@UAE@XZ', 'retail', 'unknown')]
        assert not any(value for key, value in b.items() if key != 'comdat')
sizes = ck.source_bytes(set(sources))
linked = {label: sum(sizes[s] for s, findings in rows.items()
                     if not any(findings.values())) for label, rows in paired.items()}
assert linked == {'before': 32, 'after': 335}, linked
report = {
    'base': before['base'], 'index_meta': index['meta'],
    'index_sha256': before['index_sha256'], 'objects': proof, 'paired': paired,
    'linked_nonpadding_bytes': linked, 'closed_strict': False,
    'currency': 'owned sources self-strict; other providers retain legacy index currency',
}
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('All retained code/EH sections preserved; canonical new sections equal provider.')
print('Paired legacy preview:', linked, '; closed-strict gain not measured.')
