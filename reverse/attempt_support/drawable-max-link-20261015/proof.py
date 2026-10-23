import collections,copy,hashlib,json,struct,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'tools/link_check.py').is_file());sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/drawable-max-link-20261015'
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


import data_check as dc

context = json.loads((OUT/'context.json').read_text())
index = ck.load_index()
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == context['index_sha256']
truth = lc.RetailTruth(lc.ledger())
source, provider = context['paths']
obj, pobj = [build.obj_path(ROOT/path) for path in context['paths']]
bobj, bpobj = [OUT/'saved-before'/o.name for o in [obj,pobj]]
assert all(build.compile_is_current(ROOT/path,o,strict=True)
           for path,o in zip(context['paths'],[obj,pobj]))
before,after = bobj.read_bytes(),obj.read_bytes()
assert bpobj.read_bytes() == pobj.read_bytes(), 'provider changed'
name = '??$max@I@_STL@@YAABIABI0@Z'
old = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(before)}
new = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(after)}
assert old.keys()-new.keys() == {name} and not new.keys()-old.keys()
assert all((old[n][0],old[n][2:]) == (new[n][0],new[n][2:]) for n in new)
os,ns = sections(before),sections(after)
removed = list((os-ns).elements())
assert len(removed) == 1 and not ns-os
assert removed[0][3] == old[name][0].hex()
assert directives(before) == directives(after)
assert bindings(before)-bindings(after) == {(name,2,True,0)}
assert not bindings(after)-bindings(before)
assert_unreferenced(before,{name})
# The removed external body differs from the canonical native provider.
canonical = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(pobj.read_bytes())}
assert canonical[name][3] == 17 and old[name][2] != canonical[name][2]
results = {}
for phase,objects in [('before',[bobj,bpobj]),('after',[obj,pobj])]:
    local = copy.deepcopy(index)
    ck.refresh(local,objects,truth)
    results[phase] = {path:ck.check_object(o,local,truth,path)
                      for path,o in zip(context['paths'],objects)}
b,a = results['before'][source],results['after'][source]
assert sum(map(len,b.values())) == 1 and len(b['comdat']) == 1 and b['comdat'][0][0] == name
assert not any(a.values())
assert results['before'][provider] == results['after'][provider]
lookup = build.row_object
data_results = {}
try:
    for phase,objects in [('before',[bobj,bpobj]),('after',[obj,pobj])]:
        by_source = dict(zip(context['paths'],objects))
        build.row_object = lambda row: by_source[row['source']] if row['source'] in by_source else lookup(row)
        unread = []
        facts = dc.object_facts(dc.source_rows(context['paths']),unread)
        assert not unread
        data_results[phase] = dc.findings(facts,dc.dl.load())
finally:
    build.row_object = lookup
assert data_results['before'] == data_results['after'] == []
byte_count = ck.source_bytes(set(context['paths']))[source]
assert byte_count == 506
proof = {
    'context':context,'strict_current_objects':context['paths'],
    'consumer':{'source':source,'before_sha256':hashlib.sha256(before).hexdigest(),
        'after_sha256':hashlib.sha256(after).hexdigest(),'retained_comdats_identical':len(new),
        'all_other_nondebug_sections_and_relocations_identical':True,
        'external_bindings_and_directives_identical_except_removed_name':True,
        'removed':{'name':name,'bytes':old[name][0].hex(),'relocations':old[name][1],
            'digest':old[name][2],'size':old[name][3]},'no_nondebug_relocations_to_removed_body':True},
    'provider':{'source':provider,'whole_object_identical':True,
        'sha256':hashlib.sha256(pobj.read_bytes()).hexdigest(),'native_rva':'0x00013740',
        'body':canonical[name][0].hex(),'digest':canonical[name][2],'size':canonical[name][3]},
    'results':results,'data_findings':data_results,
    'local_legacy_linked_bytes_before':0,'local_legacy_linked_bytes_after':byte_count,
    'authored_cpp_byte_gain':0,'closed_strict_claim':False}
(OUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print(f'{len(new)} retained COMDATs and every other nondebug section/relocation unchanged; sole unused max copy removed; paired legacy consumer LINKS 0 -> {byte_count}B; provider unchanged')
