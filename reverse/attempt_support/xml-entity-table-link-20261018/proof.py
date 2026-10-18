"""Paired XML entity-table link proof; baseline objects in build/."""
import hashlib, json, struct, sys
from pathlib import Path
from collections import Counter
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc, data_check as dc
BASE = Path("build/xml-entity-table-link-20261018")
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

context = json.loads((BASE/'context.json').read_text())
assert sha(ck.INDEX.read_bytes()) == context['index_sha256']
paths=context['paths']
objects={s:build.obj_path(build.ROOT/s) for s in paths}
new_names=['?g_00DD1E74@@3QBUEntityEntry@@B']
proofs={}
for s,n in zip(paths,new_names):
 o=objects[s];old=BASE/'before'/o.name
 assert lc.object_current(build.ROOT/s,o,allow_fresh=False),s
 before_comdats={n:(d,z) for n,d,z in lc.comdat_bodies(old)}
 after_comdats={n:(d,z) for n,d,z in lc.comdat_bodies(o)}
 added=set(after_comdats)-set(before_comdats)
 assert set(before_comdats)<=set(after_comdats)
 assert all(before_comdats[n]==after_comdats[n] for n in before_comdats)
 expected_literals={b'lt\0',b'gt\0',b'amp\0',b'quot\0',b'apos\0'}
 assert len(added)==5 and all(n.startswith('??_C@') for n in added)
 actual_literals={build.read_object_symbol_bytes(o,n)[0] for n in added}
 assert actual_literals==expected_literals,actual_literals
 assert normalized(old,set())==normalized(o,{n}|added),s
 proofs[s]=dict(before_sha256=sha(old.read_bytes()),after_sha256=sha(o.read_bytes()),new_data=n,new_string_comdats=sorted(added),
               every_retained_section_and_comdat_identical=True)
truth=lc.RetailTruth(lc.ledger());paired={}
for phase in ('before','after'):
 objs={s:BASE/'before'/o.name if phase=='before' else o for s,o in objects.items()}
 x=ck.load_index();ck.refresh(x,list(objs.values()),truth)
 paired[phase]={s:ck.check_object(o,x,truth,source=s) for s,o in objs.items()}
core=('unresolved','duplicates','comdat','addresses','selected')
assert all(any(paired['before'][s][k] for k in core) for s in paths)
assert all(not paired['after'][s][k] for s in paths for k in core)
# The data-identity check's existing debt must not grow.
rows=dc.source_rows(paths);real_row_object=build.row_object
try:
 build.row_object=lambda row:BASE/'before'/real_row_object(row).name
 unread=[];before=dc.findings(dc.object_facts(rows,unread),dc.dl.load());assert not unread,unread
finally:
 build.row_object=real_row_object
unread=[];after=dc.findings(dc.object_facts(rows,unread),dc.dl.load());assert not unread,unread
assert before==after,(before,after)
sz=ck.source_bytes(set(paths))
report=dict(context=context,measurement=ck.load_index()['meta'],object_proofs=proofs,paired_link=paired,
 legacy_predicted_linked_nonpadding_bytes={'before':0,'after':sum(sz.values())},
 self_strict_current=True,closed_strict_gain_unmeasured=True,
 data_check_findings_identical=before,
 retained_nondebug_sections_bytes_flags_definitions_and_symbolic_relocations_identical=True)
assert sha(ck.INDEX.read_bytes())==context['index_sha256']
Path(__file__).with_name('proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: strict receipts; every retained section exact; unchanged data debt; 1/1 legacy clean +',sum(sz.values()),'B')
