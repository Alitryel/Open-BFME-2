import collections, copy, csv, hashlib, io, json, shutil, struct, subprocess, sys
from pathlib import Path
sys.path.insert(0,'tools')
import build, link_census as lc, link_check as ck, data_check as dc
out=Path('build/player-key-cache-link-20261015')
c=json.loads((out/'context.json').read_text())
keys=c['keys']
renames={'?TheKey_'+key+'@@3VRva00148F5ECache@@A':'?TheKey_'+key+'@@3VStaticNameKey@@B' for key in keys}
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==c['index_sha256']
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

def norm(v):
    if isinstance(v,str):return renames.get(v,v)
    if isinstance(v,tuple):return tuple(norm(x) for x in v)
    return v
def normalized_sections(data):
    return collections.Counter({norm(k):v for k,v in sections(data).items()})
def bindings(data):
    return {(norm(s['name']),s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}
objects=[Path(p) for p in c['objects']]
truth=lc.RetailTruth(lc.ledger());index=ck.load_index()
results={};integrity={}
for i,(source,obj) in enumerate(zip(c['paths'],objects)):
    assert build.compile_is_current(Path.cwd()/source,obj,strict=True),source
    a=(out/f'before-{i}.obj').read_bytes();b=obj.read_bytes()
    assert normalized_sections(a)==normalized_sections(b),source
    assert bindings(a)==bindings(b),source
    if i==2:assert a==b
    integrity[source]={'before_sha256':hashlib.sha256(a).hexdigest(),'after_sha256':hashlib.sha256(b).hexdigest(),
        'all_nondebug_sections_and_relocations_equal_after_eight_symbol_renames':True,'normalized_external_bindings_equal':True,'strict_receipt_current':True,'before_receipt_sha256':hashlib.sha256((out/f'before-{i}.deps.json').read_bytes()).hexdigest(),'after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest()}
for phase in ('before','after'):
    local=copy.deepcopy(index)
    if phase=='before':
        saved=out/'saved-before';saved.mkdir(exist_ok=True);used=[]
        for i,obj in enumerate(objects):
            old=saved/obj.name;shutil.copy2(out/f'before-{i}.obj',old);used.append(old)
    else:used=objects
    ck.refresh(local,used,truth)
    results[phase]={source:ck.check_object(obj,local,truth,source) for source,obj in zip(c['paths'],used)}
    results[phase]['linked_sources']=[s for s in c['paths'] if not any(results[phase][s].values())]
    results[phase]['linked_bytes']=sum(ck.source_bytes(set(results[phase]['linked_sources'])).values())
for source in c['paths']:
    expected=copy.deepcopy(results['before'][source])
    removed=[]
    for name in renames:
        if name in expected['unresolved']:
            expected['unresolved'].remove(name);removed.append(name)
    assert expected==results['after'][source],source
    if source==c['paths'][0]:assert len(removed)==8,removed
    elif source==c['paths'][1]:assert len(removed)==1,removed
    else:assert not removed
assert results['before']['linked_bytes']==results['after']['linked_bytes']
rows=[]
for source in c['paths']:
    text=subprocess.check_output(['rg','-F',','+source+',','reverse/functions.csv'],text=True)
    rows.extend(csv.DictReader(io.StringIO('name,export_rva,target_rva,target_size,source,status,notes\n'+text)))
native=[];maps=build.load_symbol_map();canon={v:k for k,v in renames.items()}
for row in rows:
    obj=objects[c['paths'].index(row['source'])]
    patch=build.compile_function(row,maps,obj)
    assert patch['bytes']==patch['target'] and not patch['unresolved'],row['name']
    for off,kind,name in patch['relocs']:
        if name not in canon or off+4>len(patch['target']):continue
        short=name.split('TheKey_',1)[1].split('@@',1)[0]
        word=struct.unpack_from('<I',patch['target'],off)[0]
        assert kind==6 and word==keys[short],(row,off,kind,word)
        native.append({'source':row['source'],'name':row['name'],'rva':row['target_rva'],'size':row['target_size'],
            'key':short,'operand_rva':hex(int(row['target_rva'],16)+off),'kind':'DIR32','retail_va':hex(word)})
assert native==c['operands'],(native,c['operands'])
initializers={}
for short,va in keys.items():
    name='?TheKey_'+short+'@@3VStaticNameKey@@B'
    body,rels=build.read_object_symbol_bytes(objects[2],name,8)
    body=body[:8];rels=[r for r in rels if r[0]<8]
    assert body==bytes(8) and len(rels)==1 and rels[0][:2]==(4,6),(body,rels)
    literal,_=build.read_object_symbol_bytes(objects[2],rels[0][2])
    expected=short.encode()+b'\0'
    assert literal[:len(expected)]==expected
    target=build.read_target_bytes(va-0x400000,8)
    assert target[:4]==bytes(4)
    ptr=struct.unpack_from('<I',target,4)[0]
    assert build.read_target_bytes(ptr-0x400000,len(expected))==expected
    providers=index['strong'][name]
    assert len(providers)==1 and index['objects'][providers[0]]==objects[2].name
    initializers[short]={'rva':hex(va-0x400000),'retail_hex':target.hex(),'retail_string_va':hex(ptr),
        'complete_string_hex':expected.hex(),'provider':c['paths'][2],'provider_symbol':name,'unique_index_provider':True,
        'object_initializer_hex':body.hex(),'object_name_relocation':rels}
data_rows=dc.source_rows(c['paths']);row_object=build.row_object;unread=[]
old_by_name={obj.name:out/f'before-{i}.obj' for i,obj in enumerate(objects)}
try:
    build.row_object=lambda row:old_by_name[row_object(row).name]
    before_data=dc.object_facts(data_rows,unread)
finally:build.row_object=row_object
after_data=dc.object_facts(data_rows,unread)
assert not unread,unread
normalized_before={source:({(renames.get(n,n),a) for n,a in binds},defined)
                   for source,(binds,defined) in before_data.items()}
assert normalized_before==after_data
ledger=dc.dl.load()
data_findings={phase:dc.findings(facts,ledger) for phase,facts in [('before',before_data),('after',after_data)]}
removed_findings=set(map(tuple,data_findings['before']))-set(map(tuple,data_findings['after']))
assert not set(map(tuple,data_findings['after']))-set(map(tuple,data_findings['before']))
assert len(removed_findings)==9 and all(f[1]=='wrong-name' and f[2] in renames for f in removed_findings)
old_ledger=copy.deepcopy(ledger)
for change in c['data_index_changes']:
    before=change['before']; after=change['after']; address=int(before['address'],16)
    assert ledger[address]==after
    old_ledger[address]=before
old_findings=dc.findings(before_data,old_ledger)
assert old_findings==data_findings['after']
base_index=subprocess.check_output(['git','show',c['commit']+':reverse/data_ledger.csv'],text=True)
assert hashlib.sha256(base_index.encode()).hexdigest()==c['old_data_index_sha256']
base_path=out/'base-data-ledger.csv';base_path.write_text(base_index)
base_rows=dc.dl.load(base_path)
assert set(base_rows)==set(ledger)
assert [a for a in base_rows if base_rows[a]!=ledger[a]]==sorted(va-0x400000 for va in keys.values())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==c['index_sha256']
report={**c,'index_measurement':index['meta'],'scope':'legacy census projection with strict current self receipts; no closed-strict claim',
    'integrity':integrity,'results':results,'native_key_operands':native,'initializers':initializers,'verified_rows':len(rows),'data_findings':data_findings,'data_bindings_equal_modulo_eight_renames':True,'original_index_before_findings':old_findings,'removed_canonical_data_findings':sorted(removed_findings),'new_authored_bytes':0,'closed_strict_gain_unmeasured':True}
(out/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('rows',len(rows),'native operands',len(native),'linked bytes',results['before']['linked_bytes'],'->',results['after']['linked_bytes'])
for source in c['paths']:
    a=results['before'][source];b=results['after'][source]
    print(source,{k:(len(a[k]),len(b[k])) for k in a if a[k]!=b[k]})
