"""Bounded destructor-provider repair; original objects stay in ignored build/."""
import hashlib
import json
import sys
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, 'tools')
import build
import data_check as dc
import link_census as lc
import link_check as ck

BASE = Path('build/rva00423a4a-link-20261015')
OUT = Path(__file__).parent
SOURCES = (BASE / 'sources.txt').read_text().splitlines()
DTOR = '??1Rva00423A4A@@QAE@XZ'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(ck.INDEX) == meta['sha256']
truth = lc.RetailTruth(lc.ledger())
objects = [build.obj_path(build.ROOT / s) for s in SOURCES]
before = [BASE / 'before' / o.name for o in objects]
rows = dc.source_rows(SOURCES)
reports = []
for i, (source, old, new) in enumerate(zip(SOURCES, before, objects)):
    assert lc.object_current(build.ROOT / source, new, allow_fresh=False)
    a = {n: (d, z) for n, d, z in lc.comdat_bodies(old)}
    b = {n: (d, z) for n, d, z in lc.comdat_bodies(new)}
    assert a.keys() - b.keys() == ({DTOR} if i < 2 else set())
    assert not b.keys() - a.keys()
    changed = sorted(n for n in a.keys() & b.keys() if a[n] != b[n])
    assert len(changed) == (6 if i == 0 else 5 if i == 1 else 0)
    assert all('Rva00423A4A' in n for n in changed)
    af, bf = lc.object_facts(old, truth), lc.object_facts(new, truth)
    assert set(af[1]) == set(bf[1])  # exclusive definitions
    assert set(af[3]) == set(bf[3])  # weak bindings
    assert set(bf[2]) - set(af[2]) == ({DTOR} if i < 2 else set())
    assert not set(af[2]) - set(bf[2])
    matched = []
    for row in rows:
        if row['source'] != source:
            continue
        # These rows have no object-symbol aliases.
        assert 'object-symbol=' not in row['notes']
        size = int(row['target_size'])
        assert build.read_object_symbol_bytes(old, row['name'], expected_size=size) == \
            build.read_object_symbol_bytes(new, row['name'], expected_size=size)
        matched.append(row['name'])
    reports.append({'source': source, 'self_strict_current': True,
        'object_sha256': {'before': sha(old), 'after': sha(new)},
        'receipt_sha256': {'before': sha(old.with_suffix('.deps.json')),
                           'after': sha(new.with_suffix('.deps.json'))},
        'removed_empty_destructor': {DTOR: a[DTOR]} if i < 2 else {},
        'changed_cleanup_comdats': changed,
        'matched_bodies_and_relocations_unchanged': matched,
        'exclusive_definitions_and_weak_bindings_unchanged': True,
        'only_added_undefined_external': DTOR if i < 2 else None})

paired = {}
selections = {}
variants = {}
original_index = ck.load_index()
rank = ck.link_rank(lc.ledger())
previous = {obj.name: {} for obj in objects}
for name, copies in original_index['comdat'].items():
    for position, digest, _ in copies:
        held = previous.get(original_index['objects'][position])
        if held is not None:
            held.setdefault(name, set()).add(digest)
for label, candidates in [('before', before), ('after', objects)]:
    index = ck.load_index()
    ck.refresh(index, candidates, truth)
    paired[label] = [ck.check_object(obj, index, truth, source=s)
                     for s, obj in zip(SOURCES, candidates)]
    # Match CLI admission: staged peers refreshed together, original debt
    # exempted, and real link order considered before charging other units.
    variants[label] = [ck.new_variants(obj, index, truth, previous[obj.name], rank)
                       for obj in candidates]
    copies = sorted(index['comdat'][DTOR])
    losses, rule = lc.keep_rule(copies)
    selections[label] = {'rule': rule,
        'copies': [(index['objects'][p], digest, verdict) for p, digest, verdict in copies],
        'kept': [index['objects'][p] for p, _, _ in copies if not losses[p]]}
assert paired['before'][:2] == paired['after'][:2]
assert paired['before'][2]['comdat'] == [(DTOR, 'first', None)]
assert not any(paired['after'][2].values())
assert selections['after']['kept'] == [objects[2].name]
assert not any(variants['after'])

row_object = build.row_object
with patch.object(build, 'row_object', lambda row: BASE / 'before' / row_object(row).name):
    old_data = dc.object_facts(rows)
new_data = dc.object_facts(rows)
assert old_data == new_data
assert not dc.findings(new_data, dc.dl.load())
eh_before = json.loads((BASE / 'eh-before.json').read_text())
eh_after = json.loads((BASE / 'eh-after.json').read_text())
assert eh_before == eh_after
assert len(eh_after) == 9 and all(v[0] == 'EXACT' for v in eh_after.values())
sizes = ck.source_bytes(set(SOURCES))
linked = {label: sum(sizes[s] for s, finding in zip(SOURCES, checks)
                     if not any(finding.values())) for label, checks in paired.items()}
assert linked == {'before': 0, 'after': 150}
assert sha(ck.INDEX) == meta['sha256']
(OUT / 'proof.json').write_text(json.dumps({
    'base_commit': (BASE / 'base.txt').read_text().strip(), 'index': meta,
    'objects': reports, 'paired_legacy_findings': paired,
    'destructor_provider_selection': selections,
    'paired_legacy_local_linked_nonpadding_bytes': linked,
    'self_strict_sources': 3, 'eh_exact_before_and_after': 9,
    'data_bindings_unchanged': True, 'paired_variant_admission_findings': variants,
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}, indent=2) + '\n')
print('PASS: two empty destructor copies removed; 12 matched bodies/relocations and 9 EH records unchanged; strict-current objects; legacy local LINKED 0 -> 150B; closed-strict gain unmeasured')
