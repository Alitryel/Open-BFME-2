"""Recheck the bounded PlayerList helper-emission repair."""
import hashlib,json,shutil,struct,sys
from collections import Counter
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_census as lc,link_check
BASE=Path("build/player-update-accessor-link-20261015")
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
name="?getLocalPlayer@PlayerList@@QAEPAVPlayer@@XZ"
excluded={name}
paths=ctx["sources"]
objects=[build.obj_path(Path.cwd()/p) for p in paths]
before=[BASE/"before"/o.name for o in objects]
truth=lc.RetailTruth(lc.ledger())
summary={}
for i,(p,oldobj,newobj) in enumerate(zip(paths,before,objects)):
    assert build.compile_is_current(Path.cwd()/p,newobj,strict=True),p
    old_receipt=json.loads(oldobj.with_suffix(".deps.json").read_text())
    new_receipt=json.loads(newobj.with_suffix(".deps.json").read_text())
    oldsource=BASE/("source-before.cpp" if i==0 else "select-source-before.cpp")
    assert old_receipt["version"]==new_receipt["version"]==2
    assert old_receipt["source"]==hashlib.md5(oldsource.read_bytes()).hexdigest()
    assert old_receipt["object"]==hashlib.md5(oldobj.read_bytes()).hexdigest()
    assert all(old_receipt[k]==new_receipt[k] for k in ("cmd","deps","inventory","retry_dirs","search_roots","path")),p
    a={n:(d,z) for n,d,z in lc.comdat_bodies(oldobj)}
    b={n:(d,z) for n,d,z in lc.comdat_bodies(newobj)}
    assert a.keys()-b.keys()==excluded and not b.keys()-a.keys(),p
    assert all(a[n]==b[n] for n in b),p
    assert normalized(oldobj,excluded)==normalized(newobj,set()),p
    af,bf=lc.object_facts(oldobj,truth),lc.object_facts(newobj,truth)
    assert all(set(af[j])==set(bf[j]) for j in (1,2,3)),p
    removed=[(body.hex(),digest,size) for sym,body,rel,digest,size in lc._comdat_sections(oldobj.read_bytes()) if sym["name"]==name]
    assert len(removed)==1 and removed[0][0]=="8b4110c3",p
    summary[p]={"retained_comdats":len(b),"removed":removed,
        "unchanged_retained_nondebug_sections_flags_bytes_definitions_directives_and_relocations":True,
        "strong_undefined_weak_bindings_unchanged":True,
        "strict_current_after_and_before_receipt_bound_to_saved_inputs":True,
        "before_source_sha256":sha(oldsource.read_bytes()),"after_source_sha256":sha(Path(p).read_bytes()),
        "before_object_sha256":sha(oldobj.read_bytes()),"after_object_sha256":sha(newobj.read_bytes()),
        "before_receipt_sha256":sha(oldobj.with_suffix(".deps.json").read_bytes()),
        "after_receipt_sha256":sha(newobj.with_suffix(".deps.json").read_bytes())}
paired={}
for phase,group in (("before",before),("after",objects)):
    index=link_check.load_index()
    link_check.refresh(index,group,truth)
    paired[phase]={p:link_check.check_object(o,index,truth,p) for p,o in zip(paths,group)}
for p in paths:
    expected={k:list(v) for k,v in paired["before"][p].items()}
    expected["comdat"]=[r for r in expected["comdat"] if r[0]!=name]
    assert len(paired["before"][p]["comdat"])-len(expected["comdat"])==1,p
    assert expected==paired["after"][p],p
index=link_check.load_index()
family=[(index["objects"][j],d,v) for j,d,v in index["comdat"][name]]
report={**ctx,"objects":summary,"indexed_family":family,"paired_findings":paired,
    "new_authored_cpp_bytes":0,"legacy_linked_bytes_before":0,"legacy_linked_bytes_after":0,
    "self_strict_placement_gain_measured":False,"closed_strict_gain_measured":False,
    "provider_currency":"legacy frozen index; first generic provider unchanged, no closure claim"}
assert sha(link_check.INDEX.read_bytes())==ctx["index_sha256"]
Path("reverse/attempt_support/player-update-accessor-link-20261015/proof.json").write_text(json.dumps(report,indent=2)+"\n")
for p in paths:
    print(p+": "+str(sum(map(len,paired["before"][p].values())))+" -> "+str(sum(map(len,paired["after"][p].values())))+" findings; "+str(summary[p]["retained_comdats"])+" retained COMDATs unchanged")
