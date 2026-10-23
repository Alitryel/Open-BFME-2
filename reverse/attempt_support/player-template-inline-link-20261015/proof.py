"""Compare strict objects and a paired legacy preview without writing the index."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check,data_check as dc
BASE=Path('build/player-template-inline-link-20261015')
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
            raw = repr([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


context=json.loads((BASE/'context.json').read_text())
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
getter='?getPlayerTemplate@Player@@QBEPBVPlayerTemplate@@XZ'
truth=lc.RetailTruth(lc.ledger())
paths=context['sources']
objects=[build.obj_path(build.ROOT/s) for s in paths]
originals=[BASE/'before'/o.name for o in objects]
report={'context':context,'sources':{},'self_strict':True,'closed_strict_gain_unmeasured':True}
for s,o,b in zip(paths,objects,originals):
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False)
 old={n:(d,z) for n,d,z in lc.comdat_bodies(b)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(o)}
 assert set(old)-set(new)=={getter},(s,set(old)-set(new))
 assert not set(new)-set(old),(s,set(new)-set(old))
 assert all(old[n]==new[n] for n in new),s
 assert normalized(b,{getter})==normalized(o,set()),s
 previous={n:{d} for n,d,z in lc.comdat_bodies(b)}
 assert not link_check.new_variants(o,link_check.load_index(),truth,previous=previous)
 report['sources'][s]={'before_sha256':sha(b.read_bytes()),'after_sha256':sha(o.read_bytes()),'removed_comdat':old[getter],'retained_comdats':len(new),'all_retained_nondebug_sections_bytes_flags_definitions_relocations_unchanged':True,'no_incoming_nondebug_relocations_to_getter':True}
paired={}
for phase,cohort in [('before',originals),('after',objects)]:
 index=link_check.load_index()
 link_check.refresh(index,cohort,truth)
 paired[phase]={s:link_check.check_object(o,index,truth,source=s) for s,o in zip(paths,cohort)}
for s in paths:
 b,a=paired['before'][s],paired['after'][s]
 assert len([v for v in b['comdat'] if v[0]==getter])==1
 assert a=={**b,'comdat':[v for v in b['comdat'] if v[0]!=getter]},(s,b,a)
 report['sources'][s]['findings_before']=sum(map(len,b.values()))
 report['sources'][s]['findings_after']=sum(map(len,a.values()))
rows=dc.source_rows(paths)
row_object=build.row_object
try:
 build.row_object=lambda r:BASE/'before'/row_object(r).name
 before_data=dc.object_facts(rows)
finally:build.row_object=row_object
after_data=dc.object_facts(rows)
assert before_data==after_data
assert sha(link_check.INDEX.read_bytes())==context['index_sha256']
report.update(paired_link=paired,data_bindings_unchanged=True,data_findings=dc.findings(after_data,dc.dl.load()),legacy_linked_before=False,legacy_linked_after=False,authored_byte_growth=0)
Path('reverse/attempt_support/player-template-inline-link-20261015/object-proof.json').write_text(json.dumps(report,indent=2)+'\n')
for s,e in report['sources'].items():print(s,': findings',e['findings_before'],'->',e['findings_after'],'; retained COMDATs',e['retained_comdats'])
print('Retained nondebug sections and data bindings unchanged. Data findings:',report['data_findings'])
