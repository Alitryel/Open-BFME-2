import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,"tools")
import build,link_census as lc,link_check as ck
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    leaders = {}
    for symbol in symbols:
        if symbol.get("storage") == 2 and symbol["section"] > 0:
            leaders.setdefault(symbol["section"], []).append(symbol["name"])

    def body(n):
        section = sections[n - 1]
        pointer = section["raw_pointer"]
        return data[pointer:pointer + section["raw_size"]] if pointer else b""

    def referent(i):
        symbol = symbols[i]
        n = symbol["section"]
        assert n not in omitted, "removed helper has an incoming nondebug relocation"
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or n in omitted:
            continue
        raw = body(n)
        if section["name"] == ".sxdata":
            # The linker sorts SafeSEH handlers by RVA; input order is immaterial.
            raw = repr(sorted(repr(referent(struct.unpack_from("<I", raw, j)[0]))
                              for j in range(0, len(raw), 4))).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


base=Path('build/ai-scale-link-20261015')
ctx=json.loads((base/'context.json').read_text())
assert sha(ck.INDEX.read_bytes())==ctx['index_sha256']
excluded={'?scale@Coord3D@@QAEXM@Z'}
truth=lc.RetailTruth(lc.ledger())
provider='Code/Libraries/Source/WWVegas/WWMath/region.cpp'
po=build.obj_path(Path(provider).resolve())
assert build.compile_is_current(Path(provider).resolve(),po,strict=True)
provider_fact=next(row for row in lc.object_facts(po,truth)[0] if row[0] in excluded)
assert provider_fact[3]=='retail'
report={**ctx,'objects':{},'paired_findings':{},'provider_fact':provider_fact,'new_authored_cpp_bytes':0,'closed_strict_gain_measured':False,'self_strict_placement_gain_measured':False}
olds=[];news=[]
for name in ctx['sources']:
 p=Path(name);obj=build.obj_path(p.resolve());old=base/'before'/obj.name
 oldsource=base/('source-before.cpp' if name==ctx['source'] else p.stem+'-before.cpp')
 a={n:(d,z) for n,d,z in lc.comdat_bodies(old)};b={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 assert a.keys()-b.keys()==excluded and not b.keys()-a.keys(),name
 assert all(a[n]==b[n] for n in b),name
 assert normalized(old,excluded)==normalized(obj,set()),name
 af,bf=lc.object_facts(old,truth),lc.object_facts(obj,truth)
 assert all(set(af[j])==set(bf[j]) for j in (1,2,3)),name
 receipts=[json.loads(q.read_text()) for q in (old.with_suffix('.deps.json'),obj.with_suffix('.deps.json'))]
 for r,o,src in zip(receipts,(old,obj),(oldsource,p)):
  assert r['version']==2 and r['source']==hashlib.md5(src.read_bytes()).hexdigest() and r['object']==hashlib.md5(o.read_bytes()).hexdigest()
 for k in ('cmd','inventory','retry_dirs','search_roots','deps','path'):
  assert receipts[0][k]==receipts[1][k],(name,k)
 assert build.compile_is_current(p.resolve(),obj,strict=True),name
 report['objects'][name]={'retained_comdats':len(b),'nondebug_sections_and_relocations_unchanged':True,'strong_undefined_and_weak_bindings_unchanged':True,'no_incoming_relocation_to_removed_helper':True,'removed_comdat':{s['name']:{'bytes':body.hex(),'digest':digest,'size':size} for s,body,rel,digest,size in lc._comdat_sections(old.read_bytes()) if s['name'] in excluded},'hashes':{str(q):sha(q.read_bytes()) for q in [old,obj,old.with_suffix('.deps.json'),obj.with_suffix('.deps.json'),oldsource,p]},'strict_current_before_after_receipts_bound':True,'unchanged_dependency_inventory':True}
 olds.append(old);news.append(obj)
for phase,objs in [('before',olds),('after',news)]:
 ix=ck.load_index();ck.refresh(ix,objs+[po],truth)
 report['paired_findings'][phase]={name:ck.check_object(o,ix,truth,name) for name,o in zip(ctx['sources'],objs)}
 report['paired_findings'][phase][provider]=ck.check_object(po,ix,truth,provider)
assert report['paired_findings']['before'][provider]==report['paired_findings']['after'][provider]
for name in ctx['sources']:
 before=report['paired_findings']['before'][name];after=report['paired_findings']['after'][name]
 expect={k:list(v) for k,v in before.items()};expect['comdat']=[r for r in expect['comdat'] if r[0] not in excluded]
 assert expect==after,name
 assert sum(map(len,before.values()))-sum(map(len,after.values()))==1,name
 print(name+': '+str(sum(map(len,before.values())))+' -> '+str(sum(map(len,after.values())))+' findings; retained COMDATs '+str(report['objects'][name]['retained_comdats']))
report['provider_hashes']={str(q):sha(q.read_bytes()) for q in [po,po.with_suffix('.deps.json'),Path(provider)]}
report['index_family']=[{'object':ck.load_index()['objects'][a],'digest':d,'verdict':v} for a,d,v in ck.load_index()['comdat']['?scale@Coord3D@@QAEXM@Z']]
assert sha(ck.INDEX.read_bytes())==ctx['index_sha256']
Path('reverse/attempt_support/ai-scale-link-20261015/proof.json').write_text(json.dumps(report,indent=2)+'\n')
