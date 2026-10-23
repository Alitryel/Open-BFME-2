"""Bounded COFF and legacy-link comparison; snapshots remain under build/."""
import collections, copy, hashlib, json, shutil, struct, sys
from pathlib import Path
ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build, link_check as ck, link_census as lc
OUT = ROOT / 'build/font-cache-owner-link-20261015'
OLD = '?g_Va00DE2084@@3IA'
NEW = '?BfmeFontCharsCache@@3V?$SimpleDynVecClass@PAVFontCharsClass@@@@A'
def rename(name):
    return NEW if name == OLD else name

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
        if name.startswith('.debug') or name == '.drectve':
            continue
        if name == '.sxdata':
            # COFF symbol indices change when the unused wrapper disappears.
            body = tuple(rename(symbols[t[0]]['name']) for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', rename(s['name']))
            else:
                # Compare the actual local target section and offset, rather
                # than MSVC's automatically renumbered $L/$T label.
                assert s['section'] > 0
                target_name, target_flags, target_size, target_body, _, _ = raw[s['section'] - 1]
                label = ('local', target_name, target_flags, target_size,
                         target_body.hex() if target_body is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

def bindings(data):
    return {(rename(s['name']),s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}

def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            n,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+n])
    return result

paths = json.loads((OUT/'sources.json').read_text())
ctx = json.loads((OUT/'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
rank = ck.link_rank(lc.ledger())
objects, proof = {}, {}
for source in paths:
    obj = build.obj_path(ROOT/source)
    before = OUT/'before'/obj.name
    assert lc.object_current(ROOT/source, obj, allow_fresh=False), source
    a, b = before.read_bytes(), obj.read_bytes()
    assert sections(a) == sections(b), source
    assert bindings(a) == bindings(b), source
    assert directives(a) == directives(b), source
    syma, symb = list(lc._coff_symbols(a)), list(lc._coff_symbols(b))
    old_present = any(s['name']==OLD for s in syma)
    assert old_present == (source != paths[-1])
    assert not any(s['name']==OLD for s in symb)
    assert any(s['name']==NEW for s in symb)
    previous = {}
    for name, digest, _, verdict in lc.object_facts(before, truth)[0]:
        previous.setdefault(name, set()).add(digest)
    assert not ck.new_variants(obj,index,truth,previous,rank), source
    proof[source] = {'strict_receipt_current':True,
        'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),
        'object_before_sha256':hashlib.sha256(a).hexdigest(),
        'object_after_sha256':hashlib.sha256(b).hexdigest(),
        'nondebug_sections_and_bindings_equal_after_owner_rename':True,
        'directives_unchanged':True,'owner_rename':old_present}
    objects[source] = (before,obj)
    after = OUT/'after';after.mkdir(exist_ok=True)
    shutil.copy2(obj,after/obj.name)
    shutil.copy2(obj.with_suffix('.deps.json'),after/obj.with_suffix('.deps.json').name)
results = {}
for phase,n in [('before',0),('after',1)]:
    local=copy.deepcopy(index)
    ck.refresh(local,[objects[s][n] for s in paths],truth)
    results[phase]={s:ck.check_object(objects[s][n],local,truth,s) for s in paths}
for source in paths:
    before,after=results['before'][source],results['after'][source]
    expected=copy.deepcopy(before)
    if source != paths[-1]:
        assert OLD in expected['unresolved'],(source,before)
        expected['unresolved'].remove(OLD)
    assert expected==after,(source,before,after)
    print(source, sum(map(len,before.values())), '->',sum(map(len,after.values())), 'findings')
assert not any(results['after'][paths[-1]].values())
report={'context':ctx,'index_meta':index['meta'],'objects':proof,'paired_results':results,
        'removed_unresolved_findings':3,'legacy_linked_bytes_gain':0,
        'new_authored_cpp_bytes':0,'closed_strict_gain_claimed':False,
        'existing_bytes_affected':ck.source_bytes(set(paths))}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: three undefined scalar bindings removed; all other nondebug content identical after owner rename')
