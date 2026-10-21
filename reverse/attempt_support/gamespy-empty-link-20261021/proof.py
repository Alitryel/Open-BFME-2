"""Read-only paired preview; baseline object must retain its original filename."""
import hashlib,json,struct,sys
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
source='Code/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoomSlotInit_LaunchGame_StartGame.cpp'
provider='Code/Libraries/Source/WWVegas/WWLib/string_base.cpp'
new=build.obj_path(build.ROOT/source)
old=Path('build/empty-string-link/before')/new.name
owner=build.obj_path(build.ROOT/provider)
sha=lambda b:hashlib.sha256(b).hexdigest()
index_sha=sha(ck.INDEX.read_bytes())
assert all(lc.object_current(build.ROOT/p,build.obj_path(build.ROOT/p),allow_fresh=False)for p in [source,provider])
def body(path):
 st=path.stat();data,sections,symbols=build._object_layout(str(path),st.st_mtime_ns,st.st_size)
 symbol=next(s for s in symbols if s['name']=='?startGame@GameSpyStagingRoom@@UAEXH@Z')
 section=sections[symbol['section']-1]
 raw=bytearray(data[section['raw_pointer']:section['raw_pointer']+section['raw_size']])
 refs=[]
 for j in range(section['reloc_count']):
  offset,index,kind=struct.unpack_from('<IIH',data,section['reloc_pointer']+10*j)
  refs.append((offset,kind,symbols[index]['name']))
  raw[offset:offset+4]=bytes(4)
 return bytes(raw),refs
old_body,old_refs=body(old);new_body,new_refs=body(new)
assert old_body==new_body and len(old_body)==360
assert [(a,b)for a,b,c in old_refs]==[(a,b)for a,b,c in new_refs]
changed=[(a[0],a[2],b[2])for a,b in zip(old_refs,new_refs)if a!=b]
assert changed==[(108,'??_C@_00CNPNBAHC@?$AA@','?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB'),(172,'?g_bfmeEmptyF9@@3PADA','??_C@_00CNPNBAHC@?$AA@')]
truth=lc.RetailTruth(lc.ledger());core=('unresolved','duplicates','comdat','addresses','selected')
paired={}
for phase,obj in [('before',old),('after',new)]:
 index=ck.load_index();ck.refresh(index,[obj,owner],truth)
 paired[phase]={}
 for p,o in [(source,obj),(provider,owner)]:
  result=ck.check_object(o,index,truth,source=p)
  paired[phase][p]={k:result[k]for k in core}
sizes=ck.source_bytes({source,provider})
linked={phase:sum(sizes[p]for p,r in group.items()if not any(r.values()))for phase,group in paired.items()}
assert linked['after']-linked['before']==355
assert sha(ck.INDEX.read_bytes())==index_sha
report={'index_sha256':index_sha,'measurement':ck.load_index()['meta'],
 'before_object_sha256':sha(old.read_bytes()),'after_object_sha256':sha(new.read_bytes()),
 'complete_parent_bytes_equal_except_relocation_fields':True,'parent_size':360,
 'changed_relocations':changed,'paired_preview':paired,'legacy_predicted_linked_nonpadding_bytes':linked,
 'self_strict_consumer_and_provider':True,'closed_strict_gain_unmeasured':True}
Path('build/empty-string-link/proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: complete 360B parent unchanged except two constant references; paired legacy +355 B')
