"""Paired local evidence; run at repo root with this session's build snapshots."""
import copy
import csv
import hashlib
import json
import shutil
import struct
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_check as ck
import link_census as lc
OUT = Path('build/relationship-names-link-20261015')
ctx = json.loads((OUT / 'context.json').read_text())
source = ctx['source']
obj = build.obj_path(Path(source).resolve())
assert build.compile_is_current(Path(source).resolve(), obj, strict=True)
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
ctx['index_metadata'] = ck.load_index().get('meta')
a = (OUT / 'before.obj').read_bytes()
b = obj.read_bytes()
def comdats(data):
    return {s['name']: (body.hex() if body is not None else None, digest, size)
            for s, body, _, digest, size in lc._comdat_sections(data)}
old, new = comdats(a), comdats(b)
assert not old.keys() - new.keys()
assert all(old[n] == new[n] for n in old)
added = sorted(new.keys() - old.keys())
assert all(n.startswith('??_C@') for n in added)
name = '?TheRelationshipNames@@3PAPBDA'
def externals(data):
    return {(s['name'], s['section'] > 0, s['storage'])
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
assert externals(a) - externals(b) == {(name, False, 2)}
assert externals(b) - externals(a) == {(name, True, 2)} | {(n, True, 2) for n in added}
def sections(data):
    symbols = lc._coff_symbols(data)
    by_index = {s['index']: s for s in symbols}
    table = 20 + struct.unpack_from('<H', data, 16)[0]
    sections = {}
    identities = {}
    ordinals = {}
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        h = table + 40*i
        label = data[h:h+8].rstrip(b'\0').decode()
        owners = tuple(sorted(s['name'] for s in symbols if s['section'] == i+1 and s['storage'] == 2))
        # The only changed external definition gets its own comparison below.
        base = (label, owners)
        ordinal = ordinals.get(base, 0)
        ordinals[base] = ordinal + 1
        identities[i+1] = base + (ordinal,)
    for i, key in identities.items():
        if key[0].startswith('.debug') or any(n in added for n in key[1]):
            continue
        h = table + 40*(i-1)
        size, at, reloc = struct.unpack_from('<III', data, h+16)
        nr = struct.unpack_from('<H', data, h+32)[0]
        flags = struct.unpack_from('<I', data, h+36)[0]
        def target(s):
            return s['name'] if s['storage'] in (2,105) else (identities.get(s['section']),s['value'])
        body = data[at:at+size].hex() if at else None
        if key[0] == '.sxdata':
            body = [target(by_index[x[0]]) for x in struct.iter_unpack('<I', data[at:at+size])]
        refs = [(where, kind, target(by_index[t])) for where,t,kind in struct.iter_unpack('<IIH',data[reloc:reloc+10*nr])]
        assert key not in sections
        sections[key] = (flags,size,body,refs)
    return sections
x,y=sections(a),sections(b)
assert not x.keys() - y.keys()
assert y.keys() - x.keys() == {('.data', (name,), 0)}
assert all(x[k] == y[k] for k in x), [k for k in x if x[k] != y[k]]
old_data = None
new_data = y[('.data',(name,),0)]
assert new_data[1] == 16 and len(new_data[3]) == 3
assert new_data[2] == '00'*16
assert [r[0] for r in new_data[3]] == [0,4,8]
# Paired preview against one frozen index, replacing only this strictly prepared object.
index=ck.load_index()
truth=lc.RetailTruth(lc.ledger())
results={}
for phase in ('before','after'):
    local=copy.deepcopy(index)
    current=obj
    if phase=='before':
        d=OUT/'saved-before'
        d.mkdir(exist_ok=True)
        current=d/obj.name
        shutil.copy2(OUT/'before.obj',current)
    ck.refresh(local,[current],truth)
    results[phase]=ck.check_object(current,local,truth,source)
assert results['before']==ctx['before']
assert results['before']['unresolved']==[name]
assert not results['after']['unresolved']
assert all(results['before'][k]==results['after'][k] for k in results['before'] if k!='unresolved')
row=next(r for r in csv.DictReader(open('reverse/functions.csv')) if r['name'].startswith('?dumpCommandHistory@RecorderClass'))
native=build.read_target_bytes(int(row['target_rva'],16),int(row['target_size']))
needle=struct.pack('<I',0xDBA4D4)
sites=[i for i in range(len(native)-3) if native[i:i+4]==needle]
assert len(sites)==1
report={'context':ctx,'results':results,'retained_comdats_identical':len(old),'added_string_comdats':added,'all_other_nondebug_sections_and_relocations_identical':True,'data_section_before':old_data,'data_section_after':new_data,'native_consumer':{'row':row,'sha256':hashlib.sha256(native).hexdigest(),'table_operand_rva':hex(int(row['target_rva'],16)+sites[0]),'instruction_window':native[sites[0]-5:sites[0]+9].hex()},'legacy_linked_delta':0,'strict_after_object_sha256':hashlib.sha256(b).hexdigest(),'strict_after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest()}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'retained_comdats':len(old),'added_strings':len(added),'before':results['before'],'after':results['after'],'native_operand_rva':report['native_consumer']['table_operand_rva']},indent=2))
