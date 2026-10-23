"""Recheck the bounded AreaPolygon helper-emission repair."""
import hashlib,json,shutil,struct,sys
from collections import Counter
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as lc,link_check
BASE=Path("build/area-bounds-copy-link-20261015")
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



p="Code/GameEngine/Source/Common/AreaPolygonUpdateBounds.cpp"
w="Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp"
obj=build.obj_path(build.ROOT/p); provider=build.obj_path(build.ROOT/w)
before=BASE/"before"/obj.name
excluded={"??0MathCoord2D@@QAE@ABV0@@Z"}
meta=json.loads((BASE/"index-meta.json").read_text())
assert sha(link_check.INDEX.read_bytes())==meta["sha256"]
assert all(lc.object_current(build.ROOT/s,o,allow_fresh=False) for s,o in ((p,obj),(w,provider)))
old_receipt=json.loads(before.with_suffix(".deps.json").read_text())
new_receipt=json.loads(obj.with_suffix(".deps.json").read_text())
assert old_receipt["version"]==new_receipt["version"]==2
assert old_receipt["source"]==hashlib.md5((BASE/"source-before.cpp").read_bytes()).hexdigest()
assert old_receipt["object"]==hashlib.md5(before.read_bytes()).hexdigest()
assert all(old_receipt[k]==new_receipt[k] for k in ("cmd","deps","inventory","retry_dirs","search_roots","path"))
old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
assert set(old)-set(new)==excluded and not set(new)-set(old)
assert all(old[n]==new[n] for n in new)
assert normalized(before,excluded)==normalized(obj,set())
truth=lc.RetailTruth(lc.ledger())
bf,af=lc.object_facts(before,truth),lc.object_facts(obj,truth)
assert all(set(bf[j])==set(af[j]) for j in (1,2,3))
paired={}
for label,consumer in (("before",before),("after",obj)):
    index=link_check.load_index()
    link_check.refresh(index,[consumer,provider],truth)
    paired[label]={s:link_check.check_object(o,index,truth,s) for s,o in ((p,consumer),(w,provider))}
assert paired["after"][p]=={k:[] for k in paired["before"][p]}
assert [x[0] for x in paired["before"][p]["comdat"]]==list(excluded)
assert paired["before"][w]==paired["after"][w]
index=link_check.load_index()
family={n:[(index["objects"][j],d,v) for j,d,v in index["comdat"].get(n,[])] for n in excluded}
report={"base_commit":(BASE/"base.txt").read_text().strip(),"index":meta,"consumer":p,"provider":w,
 "consumer_before_sha256":sha(before.read_bytes()),"consumer_after_sha256":sha(obj.read_bytes()),
 "source_before_sha256":sha((BASE/"source-before.cpp").read_bytes()),"source_after_sha256":sha(Path(p).read_bytes()),
 "consumer_before_receipt_sha256":sha(before.with_suffix(".deps.json").read_bytes()),"consumer_after_receipt_sha256":sha(obj.with_suffix(".deps.json").read_bytes()),
 "provider_source_sha256":sha(Path(w).read_bytes()),"provider_object_sha256":sha(provider.read_bytes()),"provider_receipt_sha256":sha(provider.with_suffix(".deps.json").read_bytes()),
 "strict_reusable_receipts":True,"before_receipt_bound_to_original_source_object_and_same_inputs":True,
 "retained_comdats":len(new),"removed_comdat":{n:old[n] for n in excluded},
 "retained_nondebug_sections_flags_bytes_bindings_and_relocations_identical":True,
 "strong_undefined_weak_sets_identical":True,"family":family,"paired_findings":paired,
 "source_bytes":link_check.source_bytes({p,w}),"new_authored_cpp_bytes":0,
 "self_strict_placement_gain_measured":False,"closed_strict_gain_measured":False}
for label,o in (("after",obj),("provider",provider)):
    shutil.copy2(o,BASE/(label+".obj"));shutil.copy2(o.with_suffix(".deps.json"),BASE/(label+"-receipt.json"))
(BASE/"proof.json").write_text(json.dumps(report,indent=2)+"\n")
print(json.dumps(report,indent=2))
