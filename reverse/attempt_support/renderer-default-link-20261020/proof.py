import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,"tools")
import build, link_check as ck, link_census as lc
renames={}
BASE=Path("build/renderer-default-link")
def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s.get("name") in excluded and s.get("section",0) > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    if obj.resolve() == (BASE/'before.obj').resolve():
        # The empty Matrix4 ctor used to keep one no-op static initializer.
        ctor = next(s for s in symbols if s['name']=='??0Matrix4@@QAE@XZ')
        cs = sections[ctor['section']-1]
        assert data[cs['raw_pointer']:cs['raw_pointer']+cs['raw_size']].hex()=='5668000000006a048bf16a1056e8000000008bc65ec3'
        def refs(section):
            return [(at,kind,symbols[n]['name']) for at,n,kind in
                [struct.unpack_from('<IIH',data,section['reloc_pointer']+10*j) for j in range(section['reloc_count'])]]
        assert refs(cs)==[(2,6,'??0Vector4@@QAE@XZ'),(14,20,'??_H@YGXPAXIHP6EPAX0@Z@Z')]
        vs = sections[next(s['section'] for s in symbols if s['name']=='??0Vector4@@QAE@XZ')-1]
        assert data[vs['raw_pointer']:vs['raw_pointer']+vs['raw_size']]==bytes.fromhex('8bc1c3') and not vs['reloc_count']
        init = [(i,s) for i,s in enumerate(sections,1) if s['name']=='.text$yc']
        crt = [(i,s) for i,s in enumerate(sections,1) if s['name']=='.CRT$XCU']
        assert len(init)==len(crt)==1
        i,si=init[0];c,sc=crt[0]
        assert data[si['raw_pointer']:si['raw_pointer']+si['raw_size']]==bytes.fromhex('b900000000e900000000')
        assert refs(si)==[(1,6,'?BFME2World@@3VMatrix4@@A'),(6,20,'??0Matrix4@@QAE@XZ')]
        assert data[sc['raw_pointer']:sc['raw_pointer']+sc['raw_size']]==b'\0'*4 and sc['reloc_count']==1
        _,n,kind=struct.unpack_from('<IIH',data,sc['reloc_pointer'])
        assert symbols[n]['section']==i and symbols[n]['value']==0 and kind==6
        omitted.update((i,c))
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

donor=Path('reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix4.h').read_text()
scoped=Path('reference/shims/bfme_matrix4_sse_link/matrix4.h').read_text().split('/*',1)[1]
assert '/*'+scoped==donor.replace('Matrix4(void) {};','__declspec(dllimport) __forceinline Matrix4(void) {};')
paths=['Code/GameEngine/Source/Common/Rva00785FD0RendererReset.cpp']
objects={s:build.obj_path(build.ROOT/s) for s in paths}
old=BASE/'before.obj';new=objects[paths[0]]
index_sha=sha(ck.INDEX.read_bytes())
assert lc.object_current(build.ROOT/paths[0],new,allow_fresh=False)
before={n:(h,z)for n,h,z in lc.comdat_bodies(old)}
after={n:(h,z)for n,h,z in lc.comdat_bodies(new)}
removed=set(before)-set(after)
assert removed=={'??0Matrix4@@QAE@XZ'}
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
assert gains=={'before':0,'after':1195},gains
assert sha(ck.INDEX.read_bytes())==index_sha
report={'index_sha256':index_sha,'measurement':ck.load_index()['meta'],
 'before_object_sha256':sha(old.read_bytes()),'after_object_sha256':sha(new.read_bytes()),
 'removed_comdats':sorted(removed),'removed_noop_BFME2World_initialization':True,'retained_comdats':len(after),
 'retained_nondebug_bytes_flags_definitions_and_relocations_identical':True,
 'self_strict_current':True,'closed_strict_gain_unmeasured':True,
 'legacy_predicted_linked_nonpadding_bytes':gains,'paired_link':paired}
Path('reverse/attempt_support/renderer-default-link-20261020/proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: paired legacy +1195 B; self-strict 6 rows plus data; retained sections identical; no-op world initialization removed')
