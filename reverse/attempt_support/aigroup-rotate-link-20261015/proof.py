import copy, hashlib, json, sys
from pathlib import Path

R = Path.cwd()
sys.path.insert(0, str(R / 'tools'))
import build, link_check as ck, link_census as lc

O = R / 'build/aigroup-rotate-link-20261015'
ctx = json.loads((O / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
split, home, consumer = ctx['sources']
name = ctx['row']['name']
objects, proofs = {}, {}
for i, source in enumerate(ctx['sources']):
    current = build.obj_path(R / source)
    snap = O / str(i)
    before = snap / current.name
    receipt = json.loads((snap / 'before.deps.json').read_text())
    assert receipt['version'] == 2
    assert hashlib.md5(before.read_bytes()).hexdigest() == receipt['object']
    assert hashlib.md5((snap / 'before.cpp').read_bytes()).hexdigest() == receipt['source']
    assert all(hashlib.md5((R / p).read_bytes()).hexdigest() == digest
               for p, digest in receipt['deps'].items())
    entry = {'before_sha256': hashlib.sha256(before.read_bytes()).hexdigest(),
             'strict_before_receipt': True}
    if source == split:
        assert not (R / source).exists()
        entry['removed_provider'] = True
    else:
        assert build.compile_is_current(R / source, current, strict=True)
        after_receipt = json.loads(current.with_suffix('.deps.json').read_text())
        assert all(receipt[k] == after_receipt[k] for k in
                   ('cmd', 'path', 'version', 'inventory', 'search_roots', 'retry_dirs'))
        assert before.read_bytes() == current.read_bytes()
        assert (snap / 'before.cpp').read_bytes() == (R / source).read_bytes()
        entry.update({'strict_after_receipt': True, 'entire_object_identical': True})
    objects[source] = (before, current)
    proofs[source] = entry

def body(obj):
    return next((b, digest, size) for sym, b, refs, digest, size
                in lc._comdat_sections(obj.read_bytes()) if sym['name'] == name)

assert body(objects[split][0]) == body(objects[home][0])
assert {s['name'] for s in lc._coff_symbols(objects[split][0].read_bytes())
        if s['storage'] == 2 and s['section'] > 0} == {name}
assert body(objects[home][0])[2] == int(ctx['row']['target_size'])
assert not any(r['source'] == split for r in lc.ledger())
row = next(r for r in lc.ledger() if r['name'] == name)
assert row['source'] == home
got = build.compile_function(row, build.load_symbol_map(), objects[home][1])
assert got['bytes'] == got['target'] and not got['unresolved']

results, selections = {}, {}
for phase in (0, 1):
    local = copy.deepcopy(index)
    present = ctx['sources'] if phase == 0 else [home, consumer]
    ck.refresh(local, [objects[s][phase] for s in present], truth)
    if phase:
        ck.forget(local, [objects[split][0].name])
    results[phase] = {s: ck.check_object(objects[s][phase], local, truth, None)
                      for s in present}
    selections[phase] = ck.selection_signature(local, name)

for source in (home, consumer):
    before, after = results[0][source], results[1][source]
    assert all(before[k] == after[k] for k in before if k != 'duplicates')
    assert after['duplicates'] == [n for n in before['duplicates'] if n != name]
assert name in results[0][home]['duplicates']
assert results[0][split]['duplicates'] == [name]
assert not any(v for k, v in results[0][split].items() if k != 'duplicates')
assert not any(e[0] == objects[split][0].name for e in selections[1])
assert any(results[1][home].values())
assert results[0][consumer] == results[1][consumer]
proof = {'context': ctx, 'objects': proofs,
         'retail_exact_twin': {'name': name, 'digest': body(objects[home][0])[1], 'size': 129},
         'paired_link_results': results, 'selection': selections,
         'self_strict_object_evidence': True, 'closed_strict_gain_measured': False,
         'legacy_predicted_linked_byte_gain': 0, 'authored_cpp_byte_gain': 0}
(O / 'proof.json').write_text(json.dumps(proof, indent=2) + '\n')
print('Exact retail twin; retained objects identical; duplicate removed; no linked-byte gain claimed')
for source, result in results[1].items():
    ck.report(source, objects[source][1], result, index, ck.source_bytes({source})[source])
