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

OUT = ROOT / 'build/lua-debug-state-link-20261015'

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



def bindings(data):
    return {(s['name'],s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}

def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            n,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+n])
    return result

import copy
import link_check as ck
import data_check as dg
ctx=json.loads((OUT/'context.json').read_text());paths=ctx['sources']
oldname='?g_00E01DC0@@3PAXA'
newname='?g_activeObj12F0610@@3PAXA'
rename=lambda x: tuple(rename(v) for v in x) if isinstance(x,tuple) else (newname if x==oldname else x)
index=ck.load_index();assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
truth=lc.RetailTruth(lc.ledger());proof={};objects={'before':[],'after':[]}
for i,s in enumerate(paths):
    obj=build.obj_path((ROOT/s).resolve());old=OUT/'before'/obj.name
    assert lc.object_current((ROOT/s).resolve(),obj,allow_fresh=False)
    before=old.read_bytes();after=obj.read_bytes()
    objects['before'].append(old);objects['after'].append(obj)
    os,ns=sections(before),sections(after)
    assert collections.Counter({rename(k):v for k,v in os.items()})==ns
    assert {rename(k) for k in bindings(before)}==bindings(after)
    assert directives(before)==directives(after)
    if i==2:
        a,b=bytearray(before),bytearray(after);a[4:8]=b[4:8]=b'\0'*4;assert a==b
    refs=sum(n*sum(label==('external',oldname) for _,_,label in sec[4]) for sec,n in os.items())
    assert refs==(4 if i<2 else 0),refs
    proof[s]={'self_strict_current':True,'before_object_sha256':hashlib.sha256(before).hexdigest(),'after_object_sha256':hashlib.sha256(after).hexdigest(),'before_receipt_sha256':hashlib.sha256((OUT/'before'/obj.with_suffix('.deps.json').name).read_bytes()).hexdigest(),'after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),'all_nondebug_sections_and_relocations_identical_after_global_rename':True,'whole_coff_identical_except_timestamp':i==2,'retargeted_dir32_relocations':refs}
results={};data={};original=dg.build.row_object
for phase in objects:
    local=copy.deepcopy(index);ck.refresh(local,objects[phase],truth)
    results[phase]={s:ck.check_object(o,local,truth,s) for s,o in zip(paths,objects[phase])}
    saved=dict(zip(paths,objects[phase]));dg.build.row_object=lambda row:saved.get(row['source'],original(row))
    missing=[];facts=dg.object_facts(dg.source_rows(paths),missing);assert not missing,missing
    data[phase]={'facts':{s:[sorted(b),sorted(d)] for s,(b,d) in facts.items()},'findings':dg.findings(facts,dg.dl.load())}
dg.build.row_object=original
for i,s in enumerate(paths):
    expected={'unresolved':[oldname] if i<2 else [],'duplicates':[],'comdat':[],'addresses':[],'selected':[]}
    assert results['before'][s]==expected,results['before'][s]
    assert all(not v for v in results['after'][s].values()),results['after'][s]
assert data['before']['findings']==[(s,'wrong-name',oldname,'0x00A01DC0') for s in paths[:2]],data['before']['findings']
assert not data['after']['findings']
for s in paths:
    oldfacts=data['before']['facts'][s];newfacts=data['after']['facts'][s]
    assert sorted((newname if n==oldname else n,a) for n,a in oldfacts[0])==sorted(map(tuple,newfacts[0]))
    assert oldfacts[1]==newfacts[1]
result={'context':ctx,'objects':proof,'paired_legacy_findings':results,'data':data,'new_authored_unique_bytes':0,'incremental_legacy_linked_bytes':1027,'closed_strict_gain_claimed':False,'data_wrong_name_findings_before':2,'data_wrong_name_findings_after':0}
Path('reverse/attempt_support/lua-debug-state-link-20261015/proof.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'legacy_findings':results,'data_findings_before':data['before']['findings'],'data_findings_after':data['after']['findings']},indent=2))
