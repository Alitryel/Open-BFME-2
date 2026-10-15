import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/shader-copy-link-20261015'

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
                # Compare the actual local target section and offset, rather
                # than MSVC's automatically renumbered $L/$T label.
                assert s['section'] > 0
                target_name, target_flags, target_size, target_body, _, _ = raw[s['section'] - 1]
                label = ('local', target_name, target_flags, target_size,
                         target_body.hex() if target_body is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

import copy
import shutil
import link_check as ck
ctx = json.loads((OUT/'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
source = ctx['paths'][0]
obj = build.obj_path(ROOT/source)
assert build.compile_is_current(ROOT/source, obj, strict=True)
before = (OUT/'before.obj').read_bytes()
after = obj.read_bytes()
(OUT/'after.obj').write_bytes(after)
removed = '??4ShaderClass@@QAEAAV0@ABV0@@Z'
def comdats(data):
    return {s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(data)}
a,b = comdats(before),comdats(after)
assert a.keys()-b.keys() == {removed}
assert not b.keys()-a.keys()
assert all(a[n] == b[n] for n in b)
os,ns = sections(before),sections(after)
old = list((os-ns).elements())
assert len(old) == 1 and not list((ns-os).elements())
assert old[0][3] == a[removed][0].hex()
def bindings(data):
    return {(s['name'],s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0) for s in lc._coff_symbols(data) if s['storage'] in (2,105)}
ab,bb = bindings(before),bindings(after)
assert ab-bb == {(removed,2,True,0)}
assert not bb-ab
for data in [before,after]:
    symbols = {s['index']:s for s in lc._coff_symbols(data)}
    target_sections = {s['section'] for s in symbols.values() if s['name']==removed}
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0').startswith(b'.debug'):continue
        at=struct.unpack_from('<I',data,h+24)[0]; nr=struct.unpack_from('<H',data,h+32)[0]
        for j in range(at,at+nr*10,10):
            _,target,_=struct.unpack_from('<IIH',data,j); sym=symbols[target]
            assert sym['name'] != removed and sym['section'] not in target_sections
def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            size,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+size])
    return result
assert directives(before)==directives(after)
index=ck.load_index(); truth=lc.RetailTruth(lc.ledger());results={}
for phase in ['before','after']:
    local=copy.deepcopy(index)
    if phase=='before':
        d=OUT/'saved-before';d.mkdir(exist_ok=True)
        current=d/obj.name;shutil.copy2(OUT/'before.obj',current)
    else: current=obj
    ck.refresh(local,[current],truth)
    results[phase]=ck.check_object(current,local,truth,source)
assert [tuple(row) for row in results['before']['comdat']]==[(removed,'first',None)],results
assert sum(map(len,results['before'].values()))==1
assert not any(results['after'].values())
report={'context':ctx,'results':results,'retained_comdats_identical':len(b),
        'removed_comdat':{'name':removed,'bytes':a[removed][0].hex(),'relocation_digest':a[removed][1],'size':a[removed][2]},
        'all_other_nondebug_sections_and_directives_identical':True,
        'nondebug_relocations_to_removed_helper':0,'only_external_binding_removed':removed,
        'strict_receipt_current':True,'after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),
        'object_sha256':{'before':hashlib.sha256(before).hexdigest(),'after':hashlib.sha256(after).hexdigest()},
        'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),
        'legacy_linked_bytes_before':0,'legacy_linked_bytes_after':ck.source_bytes({source})[source],
        'new_authored_bytes':0,'closed_strict_gain_claimed':False}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('Retained COMDATs identical:',len(b),'findings 1 -> 0; local legacy linked bytes 0 ->',report['legacy_linked_bytes_after'])
