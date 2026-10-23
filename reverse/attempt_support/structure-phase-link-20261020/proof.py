"""Paired legacy prediction; refresh only the owned object in a frozen index."""
import hashlib,json,struct,sys
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
source='Code/GameEngine/Source/GameLogic/Object/Update/StructurePhaseListParsers.cpp'
new=build.obj_path(build.ROOT/source)
old=Path('build/phase-table-link/before')/new.name
assert lc.object_current(build.ROOT/source,new,allow_fresh=False)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
index_sha=sha(ck.INDEX)
truth=lc.RetailTruth(lc.ledger());core=('unresolved','duplicates','comdat','addresses','selected')
paired={}
for phase,obj in [('before',old),('after',new)]:
 index=ck.load_index();ck.refresh(index,[obj],truth)
 result=ck.check_object(obj,index,truth,source=source)
 paired[phase]={k:result[k] for k in core}
size=ck.source_bytes({source})[source]
gains={p:0 if any(r.values()) else size for p,r in paired.items()}
assert gains=={'before':0,'after':570},gains
assert sha(ck.INDEX)==index_sha
native={}
for va,words in [(0xDCBC8C,['INITIAL','DELAY','BURST','ALMOST_FINAL','FINAL']),
                 (0xDCBCE0,['INITIAL','DELAY','BURST','FINAL']),
                 (0xDCBD30,['INITIAL','DELAY','FINAL'])]:
 pointers=struct.unpack('<'+'I'*(len(words)+1),build.read_target_bytes(va-0x400000,4*(len(words)+1)))
 assert pointers[-1]==0
 for p,word in zip(pointers,words):
  assert build.read_target_bytes(p-0x400000,len(word)+1)==word.encode()+b'\0'
 native[hex(va)]={'pointers':[hex(p) for p in pointers],'strings':words}
report={'source':source,'index_sha256':index_sha,'measurement':ck.load_index()['meta'],
        'before_object_sha256':sha(old),'after_object_sha256':sha(new),
        'self_strict_current':True,'closed_strict_gain_unmeasured':True,
        'legacy_predicted_linked_nonpadding_bytes':gains,'paired_link':paired,'retail_tables':native}
Path('reverse/attempt_support/structure-phase-link-20261020/proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: paired legacy +570 B; self-strict object; three native pointer tables')
