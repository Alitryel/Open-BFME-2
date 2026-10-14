import hashlib,json,shutil,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check
BASE=Path('build/sentence-geometry-link-20261014')
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    def norm_name(name): return name.replace("RenderSentenceGeometryView", "TextureStatisticsStructWide")
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s['name'] in excluded and s['section'] > 0]
    assert {s['name'] for s in removed} == excluded
    omitted = {s['section'] for s in removed}
    leaders = {}
    for s in symbols:
        if s.get('storage') == 2 and s['section'] > 0:
            leaders.setdefault(s['section'], []).append(norm_name(s['name']))
    def body(n):
        s = sections[n - 1]
        p = s['raw_pointer']
        return data[p:p+s['raw_size']] if p else b''
    def referent(i):
        s = symbols[i]
        n = s['section']
        assert n not in omitted, 'removed helper has an incoming non-debug relocation'
        if s['storage'] in (2, 105):
            return (norm_name(s['name']), s['storage'], s['value'])
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
assert all(lc.object_current(build.ROOT/p,o,allow_fresh=False) for p,o in zip(paths,objects))
before=BASE/'before'/objects[0].name; after=objects[0]
raw=link_check.INDEX.read_bytes(); meta=json.loads((BASE/'index-meta.json').read_text());assert sha(raw)==meta['sha256']
old={n:(d,z) for n,d,z in lc.comdat_bodies(before)};new={n:(d,z) for n,d,z in lc.comdat_bodies(after)}
renamed={'??'+str(i)+'TextureStatisticsStructWide@@QAE@XZ':'??'+str(i)+'RenderSentenceGeometryView@@QAE@XZ' for i in (0,1)}
assert set(old)-set(new)==set(renamed) and set(new)-set(old)==set(renamed.values())
assert all(old[n]==new[renamed.get(n,n)] for n in old)
b,_=normalized(before,set());a,_=normalized(after,set());assert b==a,('normalized sections changed',b-a,a-b)
truth=lc.RetailTruth(lc.ledger());bf=lc.object_facts(before,truth);af=lc.object_facts(after,truth)
assert all(set(bf[i])==set(af[i]) for i in (1,2,3))
for o in objects[1:]:assert o.read_bytes()==(BASE/'before'/o.name).read_bytes()
paired={}
for label in ('before','after'):
 idx=link_check.load_index();objs=[BASE/'before'/o.name for o in objects] if label=='before' else objects
 link_check.refresh(idx,objs,truth);paired[label]={p:link_check.check_object(o,idx,truth,p) for p,o in zip(paths,objs)}
assert json.loads(json.dumps(paired['before']))==json.loads((BASE/'paired-before.json').read_text())
assert all(not v for v in paired['after'][paths[0]].values())
for p in paths[1:]:assert paired['before'][p]==paired['after'][p]
report={'base_commit':(BASE/'base.txt').read_text().strip(),'index_meta':meta,'sources':paths,'renamed_helpers':renamed,
 'object_before_sha256':sha(before.read_bytes()),'object_after_sha256':sha(after.read_bytes()),
 'strict_current_receipts':True,'all_nondebug_sections_and_normalized_relocations_equal':True,
 'retained_comdats':{n:old[n] for n in old if n not in renamed},'renamed_helper_digests':{n:old[n] for n in renamed},
 'strong_undefined_weak_sets_unchanged':True,'three_witness_objects_unchanged':True,'paired_findings':paired,
 'legacy_existing_linked_bytes_before':0,'legacy_existing_linked_bytes_after':256,'new_authored_cpp_bytes':0,
 'closed_strict_gain_claimed':False}
shutil.copy2(after,BASE/'object-after.obj');shutil.copy2(after.with_suffix('.deps.json'),BASE/'receipt-after.json')
(BASE/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: constructor/destructor renamed; all nondebug sections and relocations unchanged; paired LEGACY closure +256 existing bytes')
