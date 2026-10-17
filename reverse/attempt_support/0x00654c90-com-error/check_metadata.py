from pathlib import Path
import sys,json
sys.path.insert(0,'tools');import build,eh_verify
source=sys.argv[1] if len(sys.argv)>1 else 'Code/Libraries/Source/COM/ComRaise.cpp'
native=eh_verify.Obj(build.obj_path('vendor/comsupp/comsupp.lib','Release\\comraise.obj'))
mine=eh_verify.Obj(build.obj_path(source))
def section_signature(obj,sym):
 s=obj.sections[sym['section']-1]
 return s['data'],[(o,t,obj.symbols[n]['name']) for o,n,t in s['relocs']]
results=[]
for name,sym in native.by_name.items():
 if sym['section']<=0 or sym.get('storage')!=2:continue
 sec=native.sections[sym['section']-1]
 if sec['name'].startswith('.text'):continue
 assert name in mine.by_name,name
 left=section_signature(native,sym);right=section_signature(mine,mine.by_name[name])
 print(name,sec['name'],len(left[0]),'native-object metadata exact',left==right)
 if left!=right:print('native',left,'compiled',right)
 assert left==right,name
 results.append({'name':name,'section':sec['name'],'bytes':left[0].hex(),'relocations':left[1]})
import struct
image=eh_verify.Image()
functions=[('??0_com_error@@QAE@JPAUIErrorInfo@@_N@Z',0x654c90,54),('?_com_raise_error@@YGXJPAUIErrorInfo@@@Z',0x654cd0,51),('??0_com_error@@QAE@ABV0@@Z',0x654d10,50),('??1_com_error@@UAE@XZ',0x654d50,38),('??_G_com_error@@UAEPAXI@Z',0x654d80,58)]
placements={};external={};todo=[];seen=set();symbol_map=build.load_symbol_map()
def place(index,base):
 if index in placements:assert placements[index]==base,(index,placements[index],base)
 else:placements[index]=base;todo.append(index)
for name,rva,size in functions:
 symbol=mine.by_name[name];place(symbol['section'],rva-symbol['value'])
 row=dict(name=name,source=source,target_rva=hex(rva),target_size=str(size),notes='')
 patch=build.compile_function(row,symbol_map,build.obj_path(source))
 assert patch['bytes']==patch['target'],name
 assert not build.body_extent_problems(row,patch,symbol_map,build.obj_path(source),[f[1] for f in functions]+[0x654dc0]),name
def references(index):
 section=mine.sections[index-1];base=placements[index]
 for offset,symindex,rtype in section['relocs']:
  assert rtype in (6,20),(index,offset,rtype)
  sym=mine.symbols[symindex]
  raw=struct.unpack_from('<I',section['data'],offset)[0]
  value=image.dword(base+offset)
  if rtype==20:
   value=(base+offset+4+struct.unpack('<i',struct.pack('<I',value))[0])&0xffffffff
   addend=struct.unpack('<i',struct.pack('<I',raw))[0]
  else:value-=image.base;addend=raw
  if sym['section']>0:place(sym['section'],value-sym['value']-addend)
  else:external.setdefault(sym['name'],set()).add(value-addend)
while todo:
 index=todo.pop()
 if index in seen:continue
 seen.add(index);references(index)
retail=[]
for entry in results:
 symbol=mine.by_name[entry['name']];index=symbol['section'];section=mine.sections[index-1]
 assert index in placements,entry['name']
 base=placements[index];masked=set()
 for offset,_,_ in section['relocs']:masked.update(range(offset,offset+4))
 target=image.bytes[base:base+len(section['data'])]
 assert len(target)==len(section['data'])
 assert all(a==b for offset,(a,b) in enumerate(zip(section['data'],target)) if offset not in masked),entry['name']
 entry['retail_section_rva']=hex(base);entry['retail_exact']=True
 retail.append(entry)
 print('retail metadata exact',entry['name'],hex(base),len(target))
for name,rva,_ in functions:
 result=eh_verify.verify_row(image,mine,name,rva);print('EH',name,result)
 assert result in (None,('EXACT',''))
Path('build/resume-eh-local/turn41-comraise-metadata.json').write_text(json.dumps({'source':source,'metadata':retail,'external_targets':{n:[hex(v) for v in sorted(values)] for n,values in external.items()}},indent=2))
