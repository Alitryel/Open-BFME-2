"""Compare the PlayerList getter emission repair against saved strict objects."""
import hashlib,json,struct,sys
from collections import Counter
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as lc,link_check
BASE=Path("build/logicdispatch-playerlist-link-20261015")
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



ctx=json.loads((BASE/"context.json").read_text())
assert sha(link_check.INDEX.read_bytes())==ctx["index_sha256"]
excluded={"?getLocalPlayer@PlayerList@@QAEPAVPlayer@@XZ","?getPlayerCount@PlayerList@@QAEHXZ"}
p=ctx["sources"][0]
obj=build.obj_path(Path.cwd()/p)
old=BASE/"before"/obj.name
assert build.compile_is_current(Path.cwd()/p,obj,strict=True)
a={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
b={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
assert a.keys()-b.keys()==excluded and not b.keys()-a.keys()
assert all(a[n]==b[n] for n in b)
assert normalized(old,excluded)==normalized(obj,set())
truth=lc.RetailTruth(lc.ledger())
af,bf=lc.object_facts(old,truth),lc.object_facts(obj,truth)
assert all(set(af[j])==set(bf[j]) for j in (1,2,3))
removed={sym["name"]:body.hex() for sym,body,rel,digest,size in lc._comdat_sections(old.read_bytes()) if sym["name"] in excluded}
assert removed=={"?getLocalPlayer@PlayerList@@QAEPAVPlayer@@XZ":"8b4110c3","?getPlayerCount@PlayerList@@QAEHXZ":"8b4114c3"}
oldreceipt=json.loads(old.with_suffix(".deps.json").read_text())
newreceipt=json.loads(obj.with_suffix(".deps.json").read_text())
assert oldreceipt["version"]==newreceipt["version"]==2
assert oldreceipt["source"]==newreceipt["source"]==hashlib.md5(Path(p).read_bytes()).hexdigest()
assert oldreceipt["object"]==hashlib.md5(old.read_bytes()).hexdigest()
assert newreceipt["object"]==hashlib.md5(obj.read_bytes()).hexdigest()
for k in ("cmd","inventory","retry_dirs","search_roots","path"):
 assert oldreceipt[k]==newreceipt[k],k
assert oldreceipt["deps"].keys()==newreceipt["deps"].keys()
changed={k for k in oldreceipt["deps"] if oldreceipt["deps"][k]!=newreceipt["deps"][k]}
assert changed=={ctx["header"]},changed
assert oldreceipt["deps"][ctx["header"]]==hashlib.md5((BASE/"header-before.h").read_bytes()).hexdigest()
assert newreceipt["deps"][ctx["header"]]==hashlib.md5(Path(ctx["header"]).read_bytes()).hexdigest()
paired={}
for phase,o in (("before",old),("after",obj)):
 index=link_check.load_index();link_check.refresh(index,[o],truth)
 paired[phase]=link_check.check_object(o,index,truth,p)
expected={k:list(v) for k,v in paired["before"].items()}
expected["comdat"]=[r for r in expected["comdat"] if r[0] not in excluded]
assert len(paired["before"]["comdat"])-len(expected["comdat"])==2
assert expected==paired["after"]
report={**ctx,"paired_findings":paired,"removed_comdats":removed,"retained_comdats":len(b),
 "all_retained_nondebug_sections_bytes_flags_definitions_and_relocations_unchanged":True,
 "strong_undefined_weak_names_unchanged":True,"strict_current_before_after_receipts_bound":True,
 "before_object_sha256":sha(old.read_bytes()),"after_object_sha256":sha(obj.read_bytes()),
 "before_receipt_sha256":sha(old.with_suffix(".deps.json").read_bytes()),
 "after_receipt_sha256":sha(obj.with_suffix(".deps.json").read_bytes()),
 "before_header_sha256":sha((BASE/"header-before.h").read_bytes()),"after_header_sha256":sha(Path(ctx["header"]).read_bytes()),
 "new_authored_cpp_bytes":0,"legacy_linked_bytes_before":0,"legacy_linked_bytes_after":0,
 "self_strict_placement_gain_measured":False,"closed_strict_gain_measured":False}
assert sha(link_check.INDEX.read_bytes())==ctx["index_sha256"]
Path("reverse/attempt_support/logicdispatch-playerlist-link-20261015/proof.json").write_text(json.dumps(report,indent=2)+"\n")
print(p+": "+str(sum(map(len,paired["before"].values())))+" -> "+str(sum(map(len,paired["after"].values())))+" findings; "+str(len(b))+" retained COMDATs unchanged")
