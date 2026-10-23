"""Paired GPU rendering-stack caller proof; baseline objects in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/link-seat-20261018b")
RENAME = {
    "?Rva001688FF@@YAXPBV?$RefCountPtr@VRenderingMethod@FXShader@@@@H@Z": "?Rva001688FFShift@@YAXPAPAVRva001688FFElement@@H@Z",
    "?Rva00168952@@YAXPBV?$RefCountPtr@VRenderingMethod@FXShader@@@@H@Z": "?Rva00168952Clear@@YAXPAPAVRva001688FFElement@@H@Z",
}
def rename(n): return RENAME.get(n,n)
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
        assert symbol["name"] not in excluded, "retained section references removed helper"
        if symbol["storage"] in (2, 105):
            return rename(symbol["name"]), symbol["storage"], symbol["value"]
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


source = 'Code/GameEngine/Source/GameClient/System/FXParticleSystem/GpuDrawModuleDoParticles.cpp'
obj = build.obj_path(build.ROOT/source)
old = BASE/'gpu-before'/obj.name
excluded = {
 '?Set_Transform@DX8Wrapper@@SAXHABVMatrix3D@@@Z',
 '??AVector4@@QBEABMH@Z', '??4Vector4@@QAEAAV0@ABV0@@Z',
 '??AMatrix3D@@QBEABVVector4@@H@Z', '??4Matrix4@@QAEAAV0@ABV0@@Z',
 '?Transpose@Matrix4@@QBE?AV1@XZ', '??0Matrix4@@QAE@ABVVector4@@000@Z',
 '??0Matrix4@@QAE@ABVMatrix3D@@@Z',
}
assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
assert normalized(old,excluded)==normalized(obj,set()), 'retained sections changed beyond helper binding names'
a={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
b={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
assert a.keys()-b.keys()==excluded and not b.keys()-a.keys()
truth=lc.RetailTruth(lc.ledger())
paired={}
for phase,path in [('before',old),('after',obj)]:
    index=ck.load_index();ck.refresh(index,[path],truth)
    paired[phase]=ck.check_object(path,index,truth,source=source)
core=('unresolved','duplicates','comdat','addresses','selected')
assert any(paired['before'][k] for k in core)
assert not any(paired['after'][k] for k in core),paired['after']
body='?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z'
x,xr=build.read_object_symbol_bytes(old,body,expected_size=779)
y,yr=build.read_object_symbol_bytes(obj,body,expected_size=779)
assert x==y
assert [(a,k,rename(n)) for a,k,n in xr]==yr
assert len([n for _,_,n in xr if n in RENAME])==2
result=dict(census=ck.load_index()['meta'],index_sha256=sha(ck.INDEX.read_bytes()),source=source,
 before_sha256=sha(old.read_bytes()),after_sha256=sha(obj.read_bytes()),
 retained_nondebug_sections_identical_after_two_relocation_renames=True,
 removed_nonretail_comdat=list(excluded),paired_legacy_results=paired,
 legacy_newly_linked_nonpadding_bytes=ck.source_bytes({source})[source],
 self_strict_current=True,closed_strict_gain_measured=False,authored_cpp_bytes_added=0)
Path('reverse/attempt_support/gpu-render-stack-link-20261018/proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: retained sections unchanged beyond two helper bindings; legacy gain',result['legacy_newly_linked_nonpadding_bytes'])
