from pathlib import Path
Path("build/resume-eh-local").mkdir(parents=True,exist_ok=True)
import sys,struct,json,hashlib
sys.path.insert(0,'tools');import build,eh_verify
source='Code/Libraries/Source/CRT/RtcSections.cpp';obj=eh_verify.Obj(build.obj_path(source));img=eh_verify.Image();sm=build.load_symbol_map();report=[]
for name,rva in [('__RTC_Initialize',0x629bf0),('__RTC_Terminate',0x629c34)]:
 sym=obj.by_name[name];code=obj.sections[sym['section']-1];row=dict(name=name,source=source,target_rva=hex(rva),target_size='68',notes='')
 patch=build.compile_function(row,sm,build.obj_path(source));assert patch['bytes']==patch['target']
 assert not build.body_extent_problems(row,patch,sm,build.obj_path(source),[0x629bf0,0x629c34,0x629c78])
 rel=[(o,i,t) for o,i,t in code['relocs'] if o==sym['value']+3];assert len(rel)==1
 off,index,typ=rel[0];assert typ==6;ts=obj.symbols[index];table=obj.sections[ts['section']-1];assert len(table['data'])==12
 trva=img.dword(rva+3)-img.base-ts['value']-struct.unpack_from('<I',code['data'],off)[0]
 expected=bytearray(table['data']);targets=[]
 for o,i,t in table['relocs']:
  assert t==6;dest=obj.symbols[i];assert dest['section']==sym['section'];add=struct.unpack_from('<I',expected,o)[0];va=img.base+rva+dest['value']-sym['value']+add;struct.pack_into('<I',expected,o,va);targets.append({'table_offset':o,'code_offset':dest['value']-sym['value']+add,'target_va':hex(va)})
 assert bytes(expected)==img.bytes[trva:trva+12],name
 report.append({'name':name,'rva':hex(rva),'bytes':68,'scope_rva':hex(trva),'scope_bytes':expected.hex(),'scope_targets':targets,'exact':True,'ordinary_eh_result':eh_verify.verify_row(img,obj,name,rva)})
sentinels=[]
for name,rva in [('___rtc_iaa',0x8fd04c),('___rtc_izz',0x8fd054),('___rtc_taa',0x8fd058),('___rtc_tzz',0x8fd060)]:
 sym=obj.by_name[name];sec=obj.sections[sym['section']-1];assert len(sec['data'])==4;assert sec['data']==img.bytes[rva:rva+4]==bytes(4);sentinels.append({'name':name,'rva':hex(rva),'sort_section':sec['name'],'bytes':4})
assert img.dword(0x8fd050)==0xb5a61f;assert img.dword(0x8fd05c)==0xb5a645
record={'source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'functions':report,'sentinels':sentinels,'callback_entries':[{'rva':'0x8fd050','target':'__RTC_InitBase','target_rva':'0x75a61f'},{'rva':'0x8fd05c','target':'__RTC_Shutdown','target_rva':'0x75a645'}]}
Path('build/resume-eh-local/turn42-initsect-proof.json').write_text(json.dumps(record,indent=2));print(json.dumps(record,indent=2))
