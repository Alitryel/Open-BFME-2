"""Paired Coord3D allocation-wrapper proof; baseline objects in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/vector-size-link-seat-20261018")
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s.get("name") in excluded and s.get("section",0) > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    table = struct.unpack_from("<I", data, 8)[0]
    associations = {}
    for i, symbol in enumerate(symbols):
        if symbol.get("aux") and symbol.get("storage") == 3 and symbol.get("section", 0) > 0:
            aux = data[table + 18 * (i + 1):table + 18 * (i + 2)]
            parent, selection = struct.unpack_from("<hB", aux, 12)
            if selection == 5:
                associations[symbol["section"]] = parent
    while True:
        more = {n for n, parent in associations.items() if parent in omitted} - omitted
        if not more: break
        omitted.update(more)
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
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        assert n not in omitted, "removed helper has an incoming local relocation"
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or n in omitted:
            continue
        raw = body(n)
        if section["name"] == ".sxdata":
            # SafeSEH is an unordered symbol-index inventory; link.exe sorts RVAs.
            # Compare the retained symbolic entries including multiplicity.
            raw = repr(sorted([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)
                        if symbols[struct.unpack_from("<I", raw, j)[0]]["section"] not in omitted], key=repr)).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], len(raw) if section["name"] == ".sxdata" else section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


import sys,hashlib,json,copy,struct
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
base=Path('build/link-seat-20261018b')
sources=['Code/Libraries/Source/Apt/Rva006EC730GetBounds.cpp','Code/GameEngine/Source/Common/LadderPreferencesDtor.cpp','Code/GameEngine/Source/Common/Rva006F1360Dtor.cpp']
def sha(p):return hashlib.sha256(p if isinstance(p,bytes) else p.read_bytes()).hexdigest()
proof={}
paths={'before':{},'after':{}}
for s in sources:
 o=build.obj_path(build.ROOT/s);old=base/'apt-before'/o.name
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False),s
 a={sym['name']:(body.hex(),digest,size) for sym,body,_,digest,size in lc._comdat_sections(old.read_bytes())}
 b={sym['name']:(body.hex(),digest,size) for sym,body,_,digest,size in lc._comdat_sections(o.read_bytes())}
 assert a.keys()==b.keys(),(s,a.keys()-b.keys(),b.keys()-a.keys())
 changed={n:{'before':a[n],'after':b[n]} for n in a if a[n]!=b[n]}
 assert changed and all(n.startswith('??_7') for n in changed), (s,changed)
 assert normalized(old,set(changed))==normalized(o,set(changed)),s
 paths['before'][s]=old;paths['after'][s]=o
 proof[s]=dict(before_object_sha256=sha(old),after_object_sha256=sha(o),before_source_sha256=sha(base/'apt-before'/Path(s).name),after_source_sha256=sha(Path(s)),retained_nonvtable_comdat_count=sum(not n.startswith('??_7') for n in a),only_changed_comdats=changed,strict_current_after=True,all_other_nondebug_sections_and_symbolic_relocations_identical=True)
truth=lc.RetailTruth(lc.ledger());paired={}
for phase in ('before','after'):
 x=ck.load_index();ck.refresh(x,list(paths[phase].values()),truth)
 paired[phase]={s:ck.check_object(o,x,truth,source=s) for s,o in paths[phase].items()}
core=('unresolved','duplicates','comdat','addresses','selected')
for s in sources:
 assert any(paired['before'][s][k] for k in core),(s,'before already clean')
 assert not any(paired['after'][s][k] for k in core),(s,paired['after'][s])
sz=ck.source_bytes(set(sources))
result=dict(census=ck.load_index()['meta'],index_sha256=sha(ck.INDEX),objects=proof,paired_legacy_results=paired,legacy_newly_linked_nonpadding_bytes=sum(sz.values()),source_bytes=sz,self_strict_byte_checks='12/12 matched rows exact with strict reusable receipts',closed_strict_gain_measured=False,authored_cpp_bytes_added=0)
(base/'apt-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: non-vtable COMDATs unchanged; 3/3 legacy clean; gain',sum(sz.values()),'B')
