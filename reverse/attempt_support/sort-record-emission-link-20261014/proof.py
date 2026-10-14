import hashlib, json, pickle, shutil, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc

BASE = Path('build/linear-insert-link-20261014')
SOURCE = 'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptLanLobbyRefreshGamesList.cpp'
OUT = BASE

def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s['name'] in excluded and s['section'] > 0]
    assert {s['name'] for s in removed} == excluded
    omitted = {s['section'] for s in removed}
    leaders = {}
    for s in symbols:
        if s.get('storage') == 2 and s['section'] > 0:
            leaders.setdefault(s['section'], []).append(s['name'])
    def body(n):
        s = sections[n - 1]
        p = s['raw_pointer']
        return data[p:p+s['raw_size']] if p else b''
    def referent(i):
        s = symbols[i]
        n = s['section']
        assert n not in omitted, 'removed helper has an incoming non-debug relocation'
        if s['storage'] in (2, 105):
            return (s['name'], s['storage'], s['value'])
        return ('local', s['value'], s['storage'], s['type'],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)
    found = []
    for n, s in enumerate(sections, 1):
        if s['name'].startswith('.debug') or n in omitted:
            continue
        raw = body(n)
        if s['name'] == '.sxdata':
            raw = repr([referent(struct.unpack_from('<I', raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        rel = []
        for j in range(s['reloc_count']):
            at, sym, kind = struct.unpack_from('<IIH', data, s['reloc_pointer']+10*j)
            rel.append((at, kind, referent(sym)))
        found.append(repr((s['name'], s['characteristics'], s['raw_size'], sha(raw), rel,
                           sorted(leaders.get(n, ())))))
    helpers = []
    for s in removed:
        section = sections[s['section']-1]
        helpers.append({'name': s['name'], 'size': section['raw_size'],
                        'bytes': body(s['section']).hex(), 'relocations': section['reloc_count']})
    return Counter(found), helpers


paths=(BASE/'sources.txt').read_text().splitlines()
objects=[build.obj_path(build.ROOT/p) for p in paths]
before=BASE/'before'/objects[0].name
after=objects[0]
assert all(lc.object_current(build.ROOT/p,o,allow_fresh=False) for p,o in zip(paths,objects))
index=Path('build/link_census/link_index.pkl').read_bytes()
assert sha(index)==json.loads((BASE/'index-meta.json').read_text())['sha256']
old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
new={n:(d,z) for n,d,z in lc.comdat_bodies(after)}
removed=set(old)-set(new)
assert removed=={'??1Rva000795C1Record@@QAE@XZ'} and not(set(new)-set(old))
assert all(old[n]==new[n] for n in new)
b,helpers=normalized(before,removed);a,_=normalized(after,set())
assert b==a, ('retained sections differ',list((b-a).items())[:3],list((a-b).items())[:3])
truth=lc.RetailTruth(lc.ledger());bf=lc.object_facts(before,truth);af=lc.object_facts(after,truth)
assert all(set(bf[i])==set(af[i]) for i in (1,2,3))
for p,o in zip(paths[1:],objects[1:]):assert (BASE/'before'/o.name).read_bytes()==o.read_bytes(),p
import link_check
paired={}
for label in ('before','after'):
 idx=link_check.load_index();objs=[BASE/'before'/o.name for o in objects] if label=='before' else objects
 link_check.refresh(idx,objs,truth)
 paired[label]={p:link_check.check_object(o,idx,truth,p) for p,o in zip(paths,objs)}
assert json.loads(json.dumps(paired['before']))==json.loads((BASE/'paired-before.json').read_text())
for p in (paths[0],paths[1],paths[3],paths[4]):assert all(not v for v in paired['after'][p].values()),(p,paired['after'][p])
assert paired['after'][paths[2]]['comdat']==[]
assert paired['after'][paths[2]]['selected']==paired['before'][paths[2]]['selected']
assert sum(len(v) for v in paired['after'][paths[2]].values())==1
sizes=link_check.source_bytes(set(paths))
gain=sum(sizes[p] for p in paths if any(paired['before'][p].values()) and not any(paired['after'][p].values()))
report={'base_commit':(BASE/'base.txt').read_text().strip(),'index_meta':pickle.loads(index)['meta'],'index_sha256':sha(index),
 'sources':paths,'object_before_sha256':sha(before.read_bytes()),'object_after_sha256':sha(after.read_bytes()),
 'removed_helpers':helpers,'retained_external_comdats':len(new),'all_retained_comdat_bytes_extents_relocations_equal':True,
 'all_other_nondebug_sections_and_normalized_relocations_equal':True,'strong_undefined_weak_external_sets_equal':True,
 'removed_helpers_nondebug_incoming_relocations':0,'four_consumers_object_bytes_unchanged':True,'strict_current_receipts':True,
 'paired_findings':paired,'legacy_linked_bytes_before':sum(sizes[p] for p in paths if not any(paired['before'][p].values())),
 'legacy_linked_bytes_after':sum(sizes[p] for p in paths if not any(paired['after'][p].values())),
 'legacy_existing_bytes_gain':gain,'new_authored_cpp_bytes':0,'self_strict_gain_claimed':False,'closed_strict_gain_claimed':False}
shutil.copy2(after,BASE/'object-after.obj');shutil.copy2(after.with_suffix('.deps.json'),BASE/'receipt-after.json')
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: unused destructor removed;',len(new),'retained COMDATs unchanged; paired legacy gain',gain,'existing bytes')
