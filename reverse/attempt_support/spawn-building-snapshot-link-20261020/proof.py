"""Paired local link prediction; baseline objects are retained in build/."""
import hashlib, json, struct, sys
from pathlib import Path
sys.path.insert(0, "tools")
import build, link_check as ck, link_census as lc
BASE=Path("build/spawn-snapshot-link-20261020")
context=json.loads((BASE/"context.json").read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==context["index_sha256"]
paths=context["paths"];objects={s:build.obj_path(build.ROOT/s) for s in paths}
truth=lc.RetailTruth(lc.ledger());paired={}
for phase in ("before","after"):
 objs={s:BASE/"before"/o.name if phase=="before" else o for s,o in objects.items()}
 index=ck.load_index();ck.refresh(index,list(objs.values()),truth)
 paired[phase]={s:ck.check_object(o,index,truth,source=s) for s,o in objs.items()}
core=("unresolved","duplicates","comdat","addresses","selected")
assert paired["before"][paths[0]]["comdat"]==[("??_7Rva004E179A@@6B@","first",None)]
assert all(not paired["before"][s][k] for s in paths[1:] for k in core)
assert all(not paired["after"][s][k] for s in paths for k in core)
names=["??_ERva004E179A@@UAEPAXI@Z","?LoadPostProcess@Rva004E179A@@UAEXXZ","?GetSnapshotName@Rva004E179A@@UAEPBDXZ","?DoXfer@Rva004E179A@@UAEXAAVXfer@@@Z"]
retail=build.read_target_bytes(0x861B78,16)
assert struct.unpack("<4I",retail)==(0x8E1CFA,0x4B3FD0,0x8E1794,0x8E1398)
tables={}
for source in paths[:2]:
 body,relocs=build.read_object_symbol_bytes(objects[source],"??_7Rva004E179A@@6B@",16)
 assert len(body)==16 and [n for at,kind,n in relocs]==names
 assert [(at,kind) for at,kind,n in relocs]==[(i*4,6) for i in range(4)]
 assert body==bytes(16)
 assert (names[0],"??_GRva004E179A@@UAEPAXI@Z") in lc._weak_externals(objects[source].read_bytes())
 tables[source]=dict(raw=body.hex(),relocations=relocs,retail=retail.hex())
sizes=ck.source_bytes(set(paths));gain=sizes[paths[0]];assert gain==129
result=dict(context=context,paired=paired,tables=tables,legacy_newly_linked_unique_bytes=gain,self_strict=True,closed_strict=False,source_bytes=sizes)
Path(__file__).with_name("proof.json").write_text(json.dumps(result,indent=2)+"\n")
print("PASS: four native vtable slots; all four units link; +129 unique legacy linked bytes; self-strict, closure unmeasured")
