"""Paired bounded object and legacy link preview; never writes the census."""
import hashlib,json,struct,sys
from pathlib import Path
from collections import Counter
sys.path.insert(0,'tools')
import build,link_census as lc,link_check
BASE=Path('build/fvf-iterator-link-20261015')
HELPER='?Next@GenericMultiListIterator@@QAEXXZ'
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

paths=(BASE/'sources.txt').read_text().splitlines()
meta=json.loads((BASE/'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
truth=lc.RetailTruth(lc.ledger())
report=[]
for source in paths:
 obj=build.obj_path(build.ROOT/source); before=BASE/'before'/obj.name
 assert lc.object_current(build.ROOT/source,obj,allow_fresh=False)
 old={n:(d,z) for n,d,z in lc.comdat_bodies(before)}
 new={n:(d,z) for n,d,z in lc.comdat_bodies(obj)}
 added=set(new)-set(old)
 assert set(old)-set(new)=={HELPER}
 assert len(added)==2 and all('TextureCategoryListIterator@?A0x' in n for n in added)
 assert all(old[n]==new[n] for n in old.keys()&new.keys())
 assert normalized(before,{HELPER})==normalized(obj,added),source
 paired={}
 for label,candidate in [('before',before),('after',obj)]:
  index=link_check.load_index()
  link_check.refresh(index,[candidate],truth)
  paired[label]=link_check.check_object(candidate,index,truth,source=source)
 assert paired['before']['comdat']==[(HELPER,'retail','wrong')]
 assert paired['before']['selected']==[HELPER]
 assert not any(v for k,v in paired['before'].items() if k not in ('comdat','selected'))
 assert not any(paired['after'].values())
 assert not link_check.new_variants(obj,index,truth)
 report.append(dict(source=source,self_strict_current=True,before_sha256=sha(before.read_bytes()),after_sha256=sha(obj.read_bytes()),retained_comdats=len(old)-1,removed_unused_external=HELPER,added_unused_internal_helpers=sorted(added),all_other_sections_bytes_flags_definitions_relocations_unchanged=True,link_preview=paired))
assert sha(link_check.INDEX.read_bytes())==meta['sha256']
(BASE/'object-proof.json').write_text(json.dumps(dict(index=meta,objects=report,legacy_predicted_linked_bytes=816,closed_strict_gain_unmeasured=True),indent=2)+'\n')
print('Both objects self-strict; only unused external Next replaced by two unused internal helper bodies; all retained sections unchanged. Legacy preview 0/2 -> 2/2 clean, +816 existing bytes.')
