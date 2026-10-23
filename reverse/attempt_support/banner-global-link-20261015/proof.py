import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/banner-global-link-20261015'

def sections(data):
    symbols = {s['index']: dict(s, name=s['name'].replace('?g_00DFE32C@@3PAVRva00217194BannerUI@@A', '?TheBannerUI@@3PAVBannerUI@@A').replace('?g_00DFE32C@@3PAVBannerUI@@A', '?TheBannerUI@@3PAVBannerUI@@A')) for s in lc._coff_symbols(data)}
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
import link_check as ck
ctx=json.loads((OUT/'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
proof={'context':ctx,'objects':{}}
for source in ctx['paths']:
 obj=build.obj_path(ROOT/source); before=(OUT/'before'/obj.name).read_bytes(); after=obj.read_bytes()
 old,new=sections(before),sections(after)
 removed=list((old-new).elements()); added=list((new-old).elements())
 assert not removed, (source,removed)
 expected=[('.bss',3224371328,4,None,())] if source.endswith('/BannerUI.cpp') else []
 assert added==expected, (source,added)
 print(source,'all existing sections and normalized relocation targets identical')
 assert build.compile_is_current(ROOT/source,obj,strict=True)
 proof['objects'][source]={'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),'before_sha256':hashlib.sha256(before).hexdigest(),'after_sha256':hashlib.sha256(after).hexdigest(),'strict_receipt_current':True,'after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),'removed':removed,'added':added}
idx=ck.load_index(); truth=lc.RetailTruth(lc.ledger()); results={}
for phase in ['before','after']:
 local=copy.deepcopy(idx)
 objects=[OUT/'before'/build.obj_path(ROOT/s).name if phase=='before' else build.obj_path(ROOT/s) for s in ctx['paths']]
 ck.refresh(local,objects,truth)
 results[phase]={s:ck.check_object(o,local,truth,s) for s,o in zip(ctx['paths'],objects)}
for s in ctx['paths']:
 print(s, 'findings',sum(map(len,results['before'][s].values())),'->',sum(map(len,results['after'][s].values())))
 expected=copy.deepcopy(results['before'][s])
 name='?g_00DFE32C@@3PAV'+('Rva00217194BannerUI' if s.endswith('/BannerUI.cpp') else 'BannerUI')+'@@A'
 expected['unresolved'].remove(name)
 assert expected==results['after'][s], s
proof['legacy_local_link_findings']=results
bytecounts=ck.source_bytes(set(ctx['paths']))
proof['legacy_local_linked_bytes']={p:sum(bytecounts.get(s,0) for s,findings in rows.items() if not any(findings.values())) for p,rows in results.items()}
proof['closed_strict_gain']='unmeasured'
import data_check as dc
import data_ledger as dl
rows=dc.source_rows(ctx['paths']); original=build.row_object
try:
 build.row_object=lambda row: OUT/'before'/original(row).name
 unread=[]; before_facts=dc.object_facts(rows,unread); assert not unread,unread
finally:
 build.row_object=original
unread=[]; after_facts=dc.object_facts(rows,unread); assert not unread,unread
before_findings=dc.findings(before_facts,dl.load(OUT/'data-ledger-before.csv'))
after_findings=dc.findings(after_facts,dl.load())
expected=before_findings.copy()
expected.remove(('Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp','wrong-name','?g_00DFE32C@@3PAVRva00217194BannerUI@@A','0x009FE32C'))
assert expected==after_findings, (before_findings,after_findings)
assert len(after_findings)==4
proof['shadow_data_findings']={'before':before_findings,'after':after_findings}
print('shadow data check: 5 -> 4 findings; no added finding')
image=build.exe_image(); assert build.read_pe_bytes(image[0],image[1],0x009FE32C,4)==bytes(4)
proof['target_storage']={'rva':'0x009FE32C','size':4,'retail_bytes':'00000000','canonical_symbol':'?TheBannerUI@@3PAVBannerUI@@A'}
canonical=proof['target_storage']['canonical_symbol']; definitions=[]
for source in ctx['paths']:
 data=build.obj_path(ROOT/source).read_bytes()
 for sym in lc._coff_symbols(data):
  assert 'g_00DFE32C' not in sym['name']
  if sym['name']==canonical and sym['section']>0:
   assert sym['storage']==2 and sym['value']==0
   definitions.append(source)
assert definitions==['Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp']
proof['canonical_definitions']=definitions

assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
(OUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print('legacy LINKED bytes',proof['legacy_local_linked_bytes'])
