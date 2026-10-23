from pathlib import Path
import sys,struct,json
repo=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(repo/'tools'))
import build
root=repo/'build/runtime-dispatch-validation'
root.mkdir(parents=True,exist_ok=True)
map_={'_RuntimeDispatchCore_00007AF3':0x7af3,'_RuntimeDispatchCore_00007C63':0x7c63,'_RuntimeDispatchEntry_00007ED9':0x7ed9,'_RuntimeDispatchEntry_00008449':0x8449}
records=[]
for f in ('cores','entries'):
 obj=root/(f+'.obj')
 source=repo/'Code/Libraries/Source/CRT'/('RuntimeRelativeDispatchCores.asm' if f=='cores' else 'RuntimeRelativeDispatchEntries.asm')
 ok,out,code=build.try_compile_source(source,obj)
 assert ok,(out,code)
 names=sorted((s for s in build.read_object_symbols(obj.read_bytes()) if s['section']>0 and s['name'] in map_),key=lambda s:s['value'])
 assert len(names)==2
 for i,symbol in enumerate(names):
  size=13 if f=='cores' else 7
  raw,relocs=build.read_object_symbol_bytes(obj,symbol['name'])
  extent=names[i+1]['value']-symbol['value'] if i+1<len(names) else len(raw)
  assert extent==size
  raw=bytearray(raw[:size]);relocs=[r for r in relocs if r[0]<size]
  rva=map_[symbol['name']]
  for off,kind,name in relocs:
   assert kind==20
   addend=struct.unpack_from('<i',raw,off)[0]
   struct.pack_into('<i',raw,off,map_[name]-(rva+off+4)+addend)
  target=build.read_target_bytes(rva,size)
  assert bytes(raw)==target,(symbol['name'],raw.hex(),target.hex())
  row={'name':symbol['name'],'rva':rva,'size':size,'resolved_hex':raw.hex(),'relocations':relocs}
  records.append(row);print(row,flush=True)
(root/'byte-proof.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
