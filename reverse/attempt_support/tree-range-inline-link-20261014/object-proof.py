import hashlib, json, pickle, shutil, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc

BASE = Path('build/tree-range-link-20261014')
SOURCE = sys.argv[1] if len(sys.argv) > 1 else 'Code/Libraries/Source/WWVegas/WWLib/Rva0043B35DErase.cpp'
OUT = BASE/Path(SOURCE).stem if len(sys.argv) > 1 else BASE

def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s['name'] in excluded and s['section'] > 0]
    assert {s['name'] for s in removed} == excluded
    omitted = {s['section'] for s in removed}
    leaders = {}
    for s in symbols:
        if s.get('storage') == 2 and s['section'] > 0:
            leaders.setdefault(s['section'], []).append(s['name'])
    def body(n):
        s = sections[n - 1]
        p = s['raw_pointer']
        return data[p:p+s['raw_size']] if p else b''
    def referent(i):
        s = symbols[i]
        n = s['section']
        assert n not in omitted, 'removed helper has an incoming non-debug relocation'
        if s['storage'] in (2, 105):
            return (s['name'], s['storage'], s['value'])
        return ('local', s['value'], s['storage'], s['type'],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)
    found = []
    for n, s in enumerate(sections, 1):
        if s['name'].startswith('.debug') or n in omitted:
            continue
        raw = body(n)
        if s['name'] == '.sxdata':
            raw = repr([referent(struct.unpack_from('<I', raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        rel = []
        for j in range(s['reloc_count']):
            at, sym, kind = struct.unpack_from('<IIH', data, s['reloc_pointer']+10*j)
            rel.append((at, kind, referent(sym)))
        found.append(repr((s['name'], s['characteristics'], s['raw_size'], sha(raw), rel,
                           sorted(leaders.get(n, ())))))
    helpers = []
    for s in removed:
        section = sections[s['section']-1]
        helpers.append({'name': s['name'], 'size': section['raw_size'],
                        'bytes': body(s['section']).hex(), 'relocations': section['reloc_count']})
    return Counter(found), helpers

before = OUT/'object-before.obj'
after = build.obj_path(build.ROOT/SOURCE)
assert lc.object_current(build.ROOT/SOURCE, after, allow_fresh=False)
index = Path('build/link_census/link_index.pkl').read_bytes()
assert sha(index) == json.loads((BASE/'index-meta.json').read_text())['sha256']
old = {n: (d, s) for n, d, s in lc.comdat_bodies(before)}
new = {n: (d, s) for n, d, s in lc.comdat_bodies(after)}
removed = set(old)-set(new)
assert len(removed) == 2 and not(set(new)-set(old))
assert sum(n.startswith('??0?$_Rb_tree_iterator@U?$pair@$$CBHH@') for n in removed) == 1
assert sum(n.startswith('?upper_bound@?$_Rb_tree@HU?$pair@$$CBHH@') for n in removed) == 1
assert all(old[n] == new[n] for n in new), 'retained COMDAT changed'
b, helpers = normalized(before, removed)
a, _ = normalized(after, set())
assert b == a, ('changed retained sections', list((b-a).items())[:3], list((a-b).items())[:3])
truth = lc.RetailTruth(lc.ledger())
bf = lc.object_facts(before, truth)
af = lc.object_facts(after, truth)
assert bf[1:] == af[1:], 'strong/undefined/weak bindings changed'
shutil.copy2(after, OUT/'object-after.obj')
shutil.copy2(after.with_suffix('.deps.json'), OUT/'receipt-after.json')
report = {
    'source': SOURCE, 'base': (BASE/'base.txt').read_text().strip(),
    'index_meta': pickle.loads(index)['meta'], 'index_sha256': sha(index),
    'object_before_sha256': sha(before.read_bytes()), 'object_after_sha256': sha(after.read_bytes()),
    'strict_current_receipt': True, 'removed_helpers': helpers,
    'retained_external_comdats': len(new),
    'all_retained_external_comdat_bytes_extents_relocations_equal': True,
    'all_other_nondebug_sections_and_relocations_equal': True,
    'strong_undefined_weak_bindings_equal': True,
    'removed_helpers_nondebug_incoming_relocations': 0,
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
(OUT/'object-proof.json').write_text(json.dumps(report, indent=2)+'\n')
print('PASS: two unreferenced helpers removed;', len(new), 'retained COMDATs and all other nondebug sections unchanged')
