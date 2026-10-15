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

OUT = ROOT / 'build/online-login-tree-link-20261015'

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

context=json.loads((OUT/'context.json').read_text());results={}
for i,source in enumerate(context['paths']):
    before=(OUT/str(i)/'before.obj').read_bytes()
    obj=build.obj_path((ROOT/source).resolve());after=obj.read_bytes()
    (OUT/str(i)/'after.obj').write_bytes(after)
    old={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(before)}
    new={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(after)}
    removed=old.keys()-new.keys();retained=old.keys()&new.keys()
    assert removed==set(context['removed_names']),removed
    assert not new.keys()-old.keys(),new.keys()-old.keys()
    assert all(old[n]==new[n] for n in retained),[n for n in retained if old[n]!=new[n]]
    os,ns=sections(before),sections(after)
    removed_sections=list((os-ns).elements());added_sections=list((ns-os).elements())
    assert len(removed_sections)==len(added_sections)==1
    assert removed_sections[0][3]==old[next(iter(removed))][0].hex()
    assert added_sections[0][3]=='8b0033c93b020f95c18ac1c3' and not added_sections[0][4]
    previous_helpers={s['name'] for s in lc._coff_symbols(before) if s['storage']==3 and s['section']>0 and s['name'].startswith('??$?9')}
    helpers=[s for s in lc._coff_symbols(after) if s['storage']==3 and s['section']>0 and s['name'].startswith('??$?9') and s['name'] not in previous_helpers]
    assert len(helpers)==1,helpers
    assert_unreferenced(before,removed);assert_unreferenced(after,[h['name'] for h in helpers])
    ob,nb=bindings(before),bindings(after)
    assert ob-nb=={(n,2,True,0) for n in removed},ob-nb
    assert not nb-ob,nb-ob
    assert directives(before)==directives(after)
    assert build.compile_is_current((ROOT/source).resolve(),obj,strict=True),source
    results[source]={'retained_comdats_identical':sorted(retained),'removed':{n:{'bytes':old[n][0].hex(),'relocation_digest':old[n][1],'size':old[n][2]} for n in removed},'removed_sections':removed_sections,'added_sections':added_sections,'private_helpers':[h['name'] for h in helpers],'nondebug_caller_relocations':0,'bindings_removed':sorted(ob-nb),'bindings_added':sorted(nb-ob),'other_sections_and_directives_identical':True,'strict_receipt_current':True,'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),'sha256_before':hashlib.sha256(before).hexdigest(),'sha256_after':hashlib.sha256(after).hexdigest()}
    print(source,len(retained),'retained COMDATs identical; only unreferenced comparison replaced')
assert hashlib.sha256((ROOT/'build/link_census/link_index.pkl').read_bytes()).hexdigest()==context['index_sha256']
(OUT/'object-proof.json').write_text(json.dumps({'context':context,'proof':results},indent=2)+'\n')
