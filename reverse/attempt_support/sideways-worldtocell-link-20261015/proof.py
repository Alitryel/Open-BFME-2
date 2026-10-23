import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,"tools")
import build,link_census as lc,link_check,data_check as dc
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
        if symbol["name"] in ("_PATHFINDER_CELL_INV", "__real@3dcccccd"):
            assert body(n) == bytes.fromhex("cdcccc3d")
            return ("float-constant-content", "cdcccc3d")
        assert n not in omitted or symbol["storage"] in (2, 105), "unexpected local reference to omitted section"
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
            raw = repr([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)

BASE=Path('build/sideways-worldtocell-link-20261015')
OUT=Path('reverse/attempt_support/sideways-worldtocell-link-20261015')
context=json.loads((BASE/'context.json').read_text())
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
source=context['sources'][0]
obj=build.obj_path(build.ROOT/source)
before=BASE/'before'/obj.name
helper='?Rva002E7875WorldToCell@@YAPAUICoord2D@@PAU1@_NPBUCoord3D@@@Z'
truth=lc.RetailTruth(lc.ledger())
assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
assert set(new)-set(old)=={"__real@3dcccccd"}
assert not set(old)-set(new)
consumer='?rva002F83F5@Pathfinder@@QAEHPAVPathfindCell@@0ABVLocomotorSet@@_N2HPAUICoord2D@@PAVObject@@H@Z'
assert set(n for n in old if old[n]!=new[n])=={helper,consumer}
assert new[helper]==('3f8b7a442248',162)
assert normalized(before,{helper,'_PATHFINDER_CELL_INV'})==normalized(obj,{helper,"__real@3dcccccd","?worldToCellFloor@@YAHM@Z"}), 'nonhelper sections changed'
facts={phase:lc.object_facts(p,truth) for phase,p in [('before',before),('after',obj)]}
assert helper in facts['before'][1] and helper not in facts['after'][1]
assert set(facts['before'][1])-{helper}==set(facts['after'][1])
assert set(facts['before'][2])==set(facts['after'][2])
assert facts['before'][3]==facts['after'][3]
assert [c[3] for c in facts['before'][0] if c[0]==helper]==['wrong']
assert [c[3] for c in facts['after'][0] if c[0]==helper]==['retail']
previous={n:{d} for n,d,z in lc.comdat_bodies(before)}
assert not link_check.new_variants(obj,link_check.load_index(),truth,previous=previous,rank=link_check.link_rank(lc.ledger()))
paired={}
for phase,p in [('before',before),('after',obj)]:
 index=link_check.load_index()
 link_check.refresh(index,[p],truth)
 paired[phase]=link_check.check_object(p,index,truth,source=source)
expected={k:[v for v in values if (v[0] if isinstance(v,(tuple,list)) else v)!=helper] for k,values in paired['before'].items()}
assert paired['after']==expected,(expected,paired['after'])
rows=dc.source_rows([source])
row_object=build.row_object
try:
 build.row_object=lambda r:BASE/'before'/row_object(r).name
 before_data=dc.object_facts(rows)
finally:build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data[source][0]==after_data[source][0]
assert before_data[source][1]-after_data[source][1]=={'_PATHFINDER_CELL_INV'}
assert not after_data[source][1]-before_data[source][1]
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
report={'context':context,'source':source,'before_object_sha256':sha(before.read_bytes()),'after_object_sha256':sha(obj.read_bytes()),'helper':helper,'helper_before':old[helper],'helper_after':new[helper],'helper_retail_truth_before':'wrong','helper_retail_truth_after':'retail','retained_identical_comdats':len(old)-2,'retained_consumer_byte_identical_float_relocations_equivalent':consumer,'all_other_nondebug_sections_bytes_flags_definitions_relocations_unchanged_modulo_identical_float_pooling':True,'only_removed_data_section':'_PATHFINDER_CELL_INV: 4 bytes cdcccc3d, compiler pooling retargets two existing consumer references to identical __real@3dcccccd content','new_tu_local_inline_asm_outline':{'name':'?worldToCellFloor@@YAHM@Z','size':34,'no_incoming_nondebug_relocations':True},'same_undefined_symbols_and_weak_externals':True,'proven_data_bindings_unchanged':True,'unjudged_local_data_reference_removed':'_PATHFINDER_CELL_INV','data_findings':dc.findings(after_data,dc.dl.load()),'self_strict':True,'paired_legacy_prediction':paired,'findings_before':sum(map(len,paired['before'].values())),'findings_after':sum(map(len,paired['after'].values())),'legacy_unit_linked_before':False,'legacy_unit_linked_after':False,'closed_strict_gain_unmeasured':True,'authored_byte_growth':0}
peers=['Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderFootprintAttackRangeQuery.cpp','Code/GameEngine/Source/GameLogic/AI/PathfinderWorldLineWalk.cpp']
peer_objects=[build.obj_path(build.ROOT/s) for s in peers]
assert all(lc.object_current(build.ROOT/s,o,allow_fresh=False) for s,o in zip(peers,peer_objects))
peer_results={}
for phase,p in [('before',before),('after',obj)]:
 index=link_check.load_index()
 link_check.refresh(index,[p]+peer_objects,truth)
 peer_results[phase]={s:link_check.check_object(o,index,truth,source=s) for s,o in zip(peers,peer_objects)}
for src in peers:
 b,a=peer_results['before'][src],peer_results['after'][src]
 assert a=={k:[v for v in values if (v[0] if isinstance(v,(tuple,list)) else v)!=helper] for k,values in b.items()},(src,b,a)
report['legacy_predicted_newly_clean_peer_bytes']=link_check.source_bytes(set(peers))
report['strict_peer_checks']={'sources':peers,'unchanged_objects':{s:sha(o.read_bytes()) for s,o in zip(peers,peer_objects)},'paired_legacy_findings':peer_results}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('Strict object: helper now retail; retained nondebug sections unchanged modulo equivalent float pooling and unused local floor outline.')
print('Paired legacy findings:',report['findings_before'],'->',report['findings_after'],'; no whole-unit linkage gain claimed.')
