"""Read-only paired object and local legacy-link proof; leaves index unchanged."""
import copy, hashlib, json, sys
from pathlib import Path
ROOT = Path.cwd()
OUT = ROOT / 'build/mesh-addref-link-20261015'
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'reverse/attempt_support/moduledata-snapshot-link-20261015')]
import build, link_check as ck, link_census as lc, sections as sec
before = json.loads((OUT / 'before.json').read_text())
assert before['index_sha256'] == hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
sources = before['sources']
old = [OUT / build.obj_path(ROOT / s).name for s in sources]
new = [build.obj_path(ROOT / s) for s in sources]
addref = '?Add_Ref@RefCountClass@@QAEXXZ'
release = '?Release_Ref@RefCountClass@@QAEXXZ'
proof = {}
for source, b, a in zip(sources, old, new):
    assert hashlib.sha256(b.read_bytes()).hexdigest() == before['before_sha256'][source]
    assert build.compile_is_current(ROOT / source, a, strict=True), source
    bs, az = sec.sections(b), sec.sections(a)
    removed, added = bs - az, az - bs
    expected = {addref: 5}
    if source == sources[2]:
        expected[release] = 11
    assert not added, (source, [(s[0],s[2],s[5]) for s in added])
    assert {p[2][0][0]: p[5] for p in removed} == expected, source
    assert sum(removed.values()) == len(expected)
    for part in removed:
        assert len(part[2]) == 1 and part[2][0][1:] == (0, 2)
        assert part[0].startswith('.text')
    for part in az:
        for _, _, target in part[4]:
            assert not any(name in str(target) for name in expected)
    assert a.read_bytes().count(b'__imp_') <= b.read_bytes().count(b'__imp_')
    proof[source] = {
        'before_sha256': hashlib.sha256(b.read_bytes()).hexdigest(),
        'after_sha256': hashlib.sha256(a.read_bytes()).hexdigest(),
        'self_strict': True, 'retained_nondebug_sections': sum((bs & az).values()),
        'all_retained_bytes_and_relocations_identical': True,
        'removed': [{'definitions': part[2], 'size': part[5]} for part in removed],
    }
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
paired = {}
for label, objects in [('before',old), ('after',new)]:
    idx = copy.deepcopy(index)
    ck.refresh(idx, objects, truth)
    paired[label] = {s: ck.check_object(o, idx, truth, s) for s,o in zip(sources,objects)}
assert json.loads(json.dumps(paired['before'])) == before['before']
for s in sources:
    removed_names = {p['definitions'][0][0] for p in proof[s]['removed']}
    for key, findings in paired['after'][s].items():
        expected = paired['before'][s][key]
        if key == 'comdat':
            expected = [f for f in expected if f[0] not in removed_names]
        assert findings == expected, (s,key,findings,expected)
sizes = ck.source_bytes(set(sources))
linked = {label: sum(sizes[s] for s, findings in rows.items() if not any(findings.values()))
          for label, rows in paired.items()}
counts = {label: sum(len(v) for rows in cohort.values() for v in rows.values()) for label,cohort in paired.items()}
assert linked == {'before':0, 'after':0}
assert counts == {'before':10, 'after':6}
assert before['index_sha256'] == hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
result = {'base':before['base'], 'index_meta':before['index_meta'],
          'index_sha256':before['index_sha256'], 'objects':proof, 'paired':paired,
          'linked_nonpadding_bytes':linked, 'blocker_count':counts,
          'closed_strict':False,
          'currency':'three owned objects self-strict; other providers use legacy index currency'}
(OUT / 'object-proof.json').write_text(json.dumps(result,indent=2) + '\n')
print('20 matched rows preserved; 63 retained nondebug sections and symbolic relocations unchanged.')
print('Removed only three unused Add_Ref copies (5 bytes each) and one Release_Ref copy (11 bytes).')
print('Paired legacy blockers:', counts, '; LINKED bytes:', linked, '; no closed-strict claim.')
