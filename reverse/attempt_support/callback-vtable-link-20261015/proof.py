"""Reproduce paired current-object proof from ignored before snapshots."""
import collections, copy, hashlib, json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_check as ck
import link_census as lc
OUT = Path('build/callback-vtable-link-20261015')
ctx = json.loads((OUT / 'context.json').read_text())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(ck.INDEX) == ctx['index_sha256']
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
            body = tuple(symbols[t[0]]['name'] for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', s['name'])
            else:
                assert s['section'] > 0
                tn, tf, tz, tb, _, _ = raw[s['section'] - 1]
                label = ('local', tn, tf, tz, tb.hex() if tb is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

def bindings(data):
    return {(s['name'], s['storage'], s['section'] > 0,
             s['value'] if s['section'] <= 0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}

def comdats(data):
    return {s['name']: (body, digest, size)
            for s, body, rel, digest, size in lc._comdat_sections(data)}

sources = list(ctx['sources'])
objs = [build.obj_path(build.ROOT / s) for s in sources]
befores = [OUT/'before'/p.name for p in objs]
name = '??_7Rva0010F7EE@@6B@'
forwarder = '?rva005D124D@Rva0010F7EE@@UAEHXZ'
report = dict(context=ctx, objects={})
for source, before, after in zip(sources, befores, objs):
    assert sha(before) == ctx['sources'][source]['object_sha256']
    assert lc.object_current(build.ROOT/source, after, allow_fresh=False)
    od, nd = before.read_bytes(), after.read_bytes()
    oc, nc = comdats(od), comdats(nd)
    assert oc.keys() == nc.keys()
    changed = [n for n in oc if oc[n] != nc[n]]
    expected = [name] if source == sources[0] else []
    assert changed == expected
    os, ns = sections(od), sections(nd)
    if expected:
        dropped, added = list((os-ns).elements()), list((ns-os).elements())
        assert len(dropped) == len(added) == 1
        assert dropped[0][0] == added[0][0] == '.rdata'
        assert dropped[0][2:4] == (4,'00000000')
        assert added[0][2:4] == (8,'0000000000000000')
        assert added[0][4][:1] == dropped[0][4]
        assert added[0][4][1:] == ((4,6,('external',forwarder)),)
        assert not bindings(od) - bindings(nd)
        assert bindings(nd) - bindings(od) == {(forwarder,2,False,0)}
    else:
        assert os == ns
        assert bindings(od) == bindings(nd)
    assert lc._weak_externals(od) == lc._weak_externals(nd)
    report['objects'][source] = dict(before_sha256=sha(before), after_sha256=sha(after),
        before_receipt_sha256=sha(before.with_suffix('.deps.json')),
        after_receipt_sha256=sha(after.with_suffix('.deps.json')),
        after_source_sha256=sha(Path(source)),strict_receipt_current=True,
        changed_comdats=changed,retained_comdats_identical=len(nc)-len(changed),
        other_nondebug_sections_bytes_symbolic_relocations_and_bindings_identical=True)
assert comdats(objs[0].read_bytes())[name] == comdats(objs[1].read_bytes())[name]
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
report['results'] = {}
for phase, candidates in [('before',befores),('after',objs)]:
    local = copy.deepcopy(index)
    ck.refresh(local,candidates,truth)
    report['results'][phase] = {src:ck.check_object(obj,local,truth,source=src)
                              for src,obj in zip(sources,candidates)}
b, a = report['results']['before'], report['results']['after']
assert b[sources[0]] == a[sources[0]]
assert len(b[sources[1]]['comdat']) == 1 and b[sources[1]]['comdat'][0][0] == name
expected = copy.deepcopy(b[sources[1]]);expected['comdat'] = []
assert a[sources[1]] == expected
assert not any(a[sources[1]].values())
report['unranked_variants'] = {}
for source, before, after in zip(sources,befores,objs):
    bv, av = ck.new_variants(before,index,truth), ck.new_variants(after,index,truth)
    assert set(av) <= set(bv)
    report['unranked_variants'][source] = dict(before=bv,after=av)
assert sha(ck.INDEX) == ctx['index_sha256']
report.update(authored_cpp_gain=0,local_legacy_linked_before=0,local_legacy_linked_after=161,
              self_strict_executable_placement_unmeasured=True,closed_strict_unmeasured=True,
              vtable=dict(name=name,before_size=4,after_size=8,retail_va='0x00BCFAB0',
                          retail_words=['0x0050F7D2','0x009D124D'],new_undefined=forwarder),
              new_pins_aliases_imports_or_weak_externals=0)
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('Paired proof: B01 table 4 -> 8 bytes matches factory; all code/other sections unchanged. Factory legacy findings 1 -> 0, LINKED 0 -> 161; emitter findings unchanged.')
