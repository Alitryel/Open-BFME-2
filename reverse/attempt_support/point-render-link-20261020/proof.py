import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,"tools")
import build, link_check as ck, link_census as lc
renames={}
BASE=Path("build/point-render-link")
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
            return renames.get(symbol["name"], symbol["name"]), symbol["storage"], symbol["value"]
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

paths=['Code/Libraries/Source/WWVegas/WW3D2/Rva00177860Render.cpp']
objects={s:build.obj_path(build.ROOT/s) for s in paths}
old=BASE/'before.obj';new=objects[paths[0]]
index_sha=sha(ck.INDEX.read_bytes())
assert lc.object_current(build.ROOT/paths[0],new,allow_fresh=False)
before={n:(h,z)for n,h,z in lc.comdat_bodies(old)}
after={n:(h,z)for n,h,z in lc.comdat_bodies(new)}
removed=set(before)-set(after)
assert removed=={'??0Vector4@@QAE@MMMM@Z','?Set@Vector4@@QAEXMMMM@Z','?Set_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@ABVMatrix4@@@Z'}
assert after.keys()<=before.keys()
assert all(before[n]==after[n]for n in after)
assert normalized(old,removed)==normalized(new,set())
truth=lc.RetailTruth(lc.ledger());core=('unresolved','duplicates','comdat','addresses','selected')
paired={}
for phase,obj in [('before',old),('after',new)]:
 x=ck.load_index();ck.refresh(x,[obj],truth)
 r=ck.check_object(obj,x,truth,source=paths[0]);paired[phase]={k:r[k]for k in core}
size=ck.source_bytes(set(paths))[paths[0]]
gains={p:0 if any(r[k]for k in core)else size for p,r in paired.items()}
assert gains=={'before':0,'after':3766},gains
assert sha(ck.INDEX.read_bytes())==index_sha
report={'index_sha256':index_sha,'measurement':ck.load_index()['meta'],
 'before_object_sha256':sha(old.read_bytes()),'after_object_sha256':sha(new.read_bytes()),
 'removed_comdats':sorted(removed),'retained_comdats':len(after),
 'retained_nondebug_bytes_flags_definitions_and_relocations_identical':True,
 'self_strict_current':True,'closed_strict_gain_unmeasured':True,
 'legacy_predicted_linked_nonpadding_bytes':gains,'paired_link':paired}
Path('reverse/attempt_support/point-render-link-20261020/proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: paired legacy +3766 B; self-strict 1 row; retained sections identical')
