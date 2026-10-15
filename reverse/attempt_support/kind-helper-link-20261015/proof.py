import collections,copy,hashlib,json,shutil,struct,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/kind-helper-link-20261015'
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
cases = [
    ('script-kind-helpers-link-20261015', {'?isKindOf@ThingTemplate@@QBE_NH@Z', '?clear@?$BitFlags@$0HE@@@QAEXXZ'}, 5, 2),
    ('supply-kind-clear-link-20261015', {'??0?$BitFlags@$0HE@@@QAE@XZ', '?clear@?$BitFlags@$0HE@@@QAEXXZ'}, 3, 0),
]
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
rows = {}
proofs = {}
before_objs, after_objs = [], []
for folder, names, old_count, new_count in cases:
    scratch = ROOT/'build'/folder
    ctx = json.loads((scratch/'context.json').read_text())
    assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
    source = ctx['source']
    obj = build.obj_path(ROOT/source)
    assert build.compile_is_current(ROOT/source, obj, strict=True)
    bobj = scratch/'saved-before'/obj.name
    assert bobj.read_bytes() == (scratch/'before.obj').read_bytes()
    before, after = bobj.read_bytes(), obj.read_bytes()
    old = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(before)}
    new = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(after)}
    assert old.keys()-new.keys() == names
    assert not new.keys()-old.keys()
    assert all((old[n][0],old[n][2],old[n][3]) == (new[n][0],new[n][2],new[n][3]) for n in new)
    os, ns = sections(before), sections(after)
    removed_sections = list((os-ns).elements())
    assert len(removed_sections) == 2 and not ns-os
    assert {s[3] for s in removed_sections} == {old[n][0].hex() for n in names}
    assert directives(before) == directives(after)
    ob, nb = bindings(before), bindings(after)
    assert ob-nb == {(name,2,True,0) for name in names} and not nb-ob
    assert_unreferenced(before, names)
    rows[source] = (bobj, obj, old_count, new_count)
    before_objs.append(bobj)
    after_objs.append(obj)
    proofs[source] = {
        'context': ctx,
        'retained_comdats_identical': len(new),
        'removed': [{'name':n,'size':old[n][3],'bytes':old[n][0].hex(),
                     'relocations':old[n][1],'digest':old[n][2]} for n in sorted(names)],
        'other_sections_bindings_and_directives_identical': True,
        'no_nondebug_caller_relocations_to_removed_body': True,
        'consumer_strict_current': True,
        'before_object_sha256': hashlib.sha256(before).hexdigest(),
        'after_object_sha256': hashlib.sha256(after).hexdigest(),
    }
provider = 'Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp'
pobj = build.obj_path(ROOT/provider)
assert build.compile_is_current(ROOT/provider,pobj,strict=True)
provider_copies = {s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(pobj.read_bytes())}
clear = provider_copies['?clear@?$BitFlags@$0HE@@@QAEXXZ']
assert clear[2] == 'cd02e976ed1c' and clear[3] == 14
results = {}
for phase, objects in [('before',before_objs),('after',after_objs)]:
    local = copy.deepcopy(index)
    ck.refresh(local, objects+[pobj], truth)
    results[phase] = {source: ck.check_object(pair[phase=='after'],local,truth,source)
                      for source,pair in rows.items()}
    results[phase][provider] = ck.check_object(pobj,local,truth,provider)
for source, (_,_,old_count,new_count) in rows.items():
    assert sum(map(len,results['before'][source].values())) == old_count
    assert sum(map(len,results['after'][source].values())) == new_count
    assert results['before'][source]['unresolved'] == results['after'][source]['unresolved']
assert results['before'][provider] == results['after'][provider]
# Judge the original/current data bindings with the existing data-check reader.
# Redirect only its row-object lookup to saved snapshots; never replace cache files.
lookup = build.row_object
data_results = {}
try:
    for phase in ['before','after']:
        def row_object(row):
            if row['source'] in rows:
                return rows[row['source']][phase=='after']
            return lookup(row)
        build.row_object = row_object
        unread = []
        facts = dc.object_facts(dc.source_rows(list(rows)+[provider]),unread)
        assert not unread, unread
        data_results[phase] = dc.findings(facts, dc.dl.load())
finally:
    build.row_object = lookup
assert data_results['before'] == data_results['after']
assert len(data_results['after']) == 2
proof = {'base':'318028c9781ce6b1470d6fda394a599152db2708',
         'index_meta':index['meta'], 'index_sha256':hashlib.sha256(ck.INDEX.read_bytes()).hexdigest(),
         'consumers':proofs, 'results':results,
         'provider':{'source':provider,'strict_current':True,'clear_digest':clear[2],
                     'clear_size':clear[3],'object_sha256':hashlib.sha256(pobj.read_bytes()).hexdigest(),
                     'findings_unchanged':True},
         'data_findings':data_results, 'legacy_linked_bytes_before':0,
         'legacy_linked_bytes_after':439, 'closed_strict_claim':False,
         'authored_cpp_byte_gain':0}
(OUT/'proof.json').write_text(json.dumps(proof,indent=2,default=lambda v:v.hex() if isinstance(v,bytes) else str(v))+'\n')
print('paired consumers: findings 5 -> 2 and 3 -> 0; provider unchanged; data findings unchanged (2); legacy LINKED 0 -> 439 bytes')
