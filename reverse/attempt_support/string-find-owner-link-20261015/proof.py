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

OUT = ROOT / 'build/string-find-owner-link-20261015'

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

def assert_unreferenced(data,targets):
    syms={s['index']:s for s in lc._coff_symbols(data)}
    for target in targets:
        symbol=next(s for s in syms.values() if s['name']==target)
        for i in range(struct.unpack_from('<H',data,2)[0]):
            h=20+struct.unpack_from('<H',data,16)[0]+40*i
            if data[h:h+8].rstrip(b'\0').startswith(b'.debug'):continue
            start=struct.unpack_from('<I',data,h+24)[0];count=struct.unpack_from('<H',data,h+32)[0]
            for at in range(start,start+10*count,10):
                _,ref,_=struct.unpack_from('<IIH',data,at)
                assert syms[ref]['name']!=target and syms[ref]['section']!=symbol['section']



import copy
import link_check as ck
import data_check as dc
OUT=ROOT/'build/string-find-owner-link-20261015'
ctx=json.loads((OUT/'context.json').read_text()); paths=ctx['sources']
name='?rva0060CB61@Rva0060CAEA@@QAE?AURva0060CAEAIterator@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z'
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
index=ck.load_index(); assert index['meta']==ctx['measurement']
truth=lc.RetailTruth(lc.ledger());objects={p:build.obj_path(ROOT/p) for p in paths}
proof={};twins=[]
for i,(p,obj) in enumerate(objects.items()):
    assert build.compile_is_current(ROOT/p,obj,strict=True)
    before=(OUT/'before'/obj.name).read_bytes();after=obj.read_bytes()
    (OUT/'after').mkdir(exist_ok=True);(OUT/'after'/obj.name).write_bytes(after)
    old={s['name']:(b,d,z) for s,b,_,d,z in lc._comdat_sections(before)}
    new={s['name']:(b,d,z) for s,b,_,d,z in lc._comdat_sections(after)}
    twins.append(old[name]);removed={name, '??0Rva0060CAEAIterator@@QAE@PAURva0060CAEANode@@PBX@Z'} if i==0 else set()
    assert set(old)-set(new)==removed
    assert not set(new)-set(old)
    assert all(old[n]==new[n] for n in new)
    missing=list((sections(before)-sections(after)).elements())
    assert not sections(after)-sections(before)
    assert len(missing)==len(removed)
    if removed:
        assert {item[3] for item in missing}=={old[n][0].hex() for n in removed}
        assert_unreferenced(before,removed)
    assert directives(before)==directives(after)
    ob,nb=bindings(before),bindings(after)
    assert ob-nb=={(n,2,True,0) for n in removed}
    assert not nb-ob
    proof[p]={'retained_comdats':len(new),'removed':sorted(removed),
              'other_nondebug_sections_relocations_and_bindings_identical':True,
              'strict_reusable_receipt':True,'before_sha256':hashlib.sha256(before).hexdigest(),
              'after_sha256':hashlib.sha256(after).hexdigest()}
assert twins[0]==twins[1]
paired={}
data={};original=build.row_object
for phase in ('before','after'):
    obs={p:OUT/phase/o.name for p,o in objects.items()}
    local=copy.deepcopy(index);ck.refresh(local,list(obs.values()),truth)
    paired[phase]={p:ck.check_object(o,local,truth,source=p) for p,o in obs.items()}
    build.row_object=lambda row:obs.get(row['source'],original(row))
    missing=[];facts=dc.object_facts(dc.source_rows(paths),missing)
    assert not missing
    data[phase]={'facts':{p:[sorted(b),sorted(d)] for p,(b,d) in facts.items()},'findings':dc.findings(facts,dc.dl.load())}
build.row_object=original
assert json.loads(json.dumps(paired['before']))==ctx['before_link']
for p in paths:
    expected=copy.deepcopy(paired['before'][p]);assert expected['duplicates']==[name]
    expected['duplicates']=[]
    assert expected==paired['after'][p]
assert not any(paired['after'][paths[0]].values())
assert data['before']==data['after']
sizes=ck.source_bytes(set(paths))
report={'context':ctx,'objects':proof,'whole_wrapper_twin':{'size':twins[0][2],'bytes':twins[0][0].hex(),'relocation_digest':twins[0][1]},
        'paired_findings':paired,'data':data,'legacy_predicted_linked_nonpadding_bytes':{'before':0,'after':sizes[paths[0]]},
        'new_authored_cpp_bytes':0,'self_strict_placement_gain_unmeasured':True,'closed_strict_gain_unmeasured':True}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: both duplicate findings removed; retained sections/relocations/bindings identical; 3 strict retail rows; legacy local linked +',sizes[paths[0]])
print(json.dumps(proof,indent=2))
