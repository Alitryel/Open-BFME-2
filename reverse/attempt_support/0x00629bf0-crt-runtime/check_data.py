from pathlib import Path
Path("build/resume-eh-local").mkdir(parents=True,exist_ok=True)
import sys,csv,struct,json,hashlib
sys.path.insert(0,'tools');import build,eh_verify,data_rows,pe_imports
sources=['Code/Libraries/Source/CRT/RtcSections.cpp','Code/Libraries/Source/CRT/DefaultPrecision.cpp','Code/Libraries/Source/CRT/RtcInit.cpp','Code/Libraries/Source/CRT/RtcGetErrorFunc.cpp']
rows=[]
with open('reverse/functions.csv',newline='',encoding='utf-8') as f:
 h=next(csv.reader([next(f)]))
 for line in f:
  if not any(','+s+',' in line for s in sources):continue
  rows.append(dict(zip(h,next(csv.reader([line])))))
assert len(rows)==9
objs={s:eh_verify.Obj(build.obj_path(s)) for s in sources};img=eh_verify.Image();sm=build.load_symbol_map();functions=[]
for source in sources:assert build.compile_is_current(Path(source).resolve(),build.obj_path(source)),source
for r in rows:
 p=build.compile_function(r,sm,build.obj_path(r['source']));assert p['bytes']==p['target'],r['name']
 functions.append({'name':r['name'],'rva':r['target_rva'],'size':int(r['target_size']),'source':r['source'],'new_cpp':r['name']!='?_RTC_GetErrorFunc@@YAP6AHHPBDH00ZZPBX@Z'})
user=sources[-1];obj=objs[user];private=[]
for name,rva,size in [('__RTC_ErrorReportFunc',0xa1f55c,4),('__RTC_errlist',0x9ddff4,16)]:
 sym=obj.by_name[name];assert sym['storage']==3;sec=obj.sections[sym['section']-1];n,how=data_rows.compiled_size(user,name);assert n==size,(name,n,how)
 assert len(sec['data'])==size and sym['value']==0
 if name=='__RTC_ErrorReportFunc':assert sec['data']==img.bytes[rva:rva+size]==bytes(size)
 else:
  assert len(sec['relocs'])==4
  literals=[]
  for off,index,typ in sec['relocs']:
   assert typ==6;symbol=obj.symbols[index];assert symbol['name'].startswith('??_C@_0')
   literal=obj.sections[symbol['section']-1]['data'][symbol['value']:];end=literal.index(b'\0')+1;literal=literal[:end]
   add=struct.unpack_from('<I',sec['data'],off)[0];va=img.dword(rva+off);assert img.bytes[va-img.base:va-img.base+len(literal)-add]==literal[add:]
   literals.append({'offset':off,'target_va':hex(va),'bytes':len(literal),'value':literal[:-1].decode('ascii'),'coff_name':symbol['name']})
  assert sum(x['bytes'] for x in literals)==133
 private.append({'name':name,'rva':hex(rva),'size':size,'size_proof':how,'storage':'TU-local static, preserved','exact':True,**({'literals':literals} if name=='__RTC_errlist' else {})})
init=objs[sources[2]];guard='?init@?1??_RTC_InitBase@@9@4_NA';sym=init.by_name[guard];sec=init.sections[sym['section']-1];assert sym['storage']==3 and sec['data']==img.bytes[0xa1f540:0xa1f541]==b'\0';private.append({'name':guard,'rva':'0xa1f540','size':1,'size_proof':'native and authored COFF one-byte bool sections; native mangled bool and byte accesses agree','exact':True})
imports=pe_imports.read_imports(build.EXE.read_bytes());pins=[]
for name,rva,slot,export in [('__controlfp',0x62991c,0xbba588,'_controlfp'),('__CRT_RTC_INIT',0x75ace8,0xbba75c,'_CRT_RTC_INIT')]:
 body=build.read_target_bytes(rva,6);assert body==b'\xff\x25'+struct.pack('<I',slot);entry=imports[slot];assert entry.dll.lower()=='msvcr71.dll' and entry.name==export;pins.append({'name':name,'rva':hex(rva),'thunk':body.hex(),'iat_slot':hex(slot),'dll':entry.dll,'export':entry.name})
record={'source_sha256':{s:hashlib.sha256(Path(s).read_bytes()).hexdigest() for s in sources},'functions':functions,'new_cpp_bytes':sum(r['size'] for r in functions if r['new_cpp']),'existing_getter_repaired_bytes':6,'private_data':private,'typed_sentinel_data_rows':16,'import_pins':pins,'whole_members_retired':['initsect.obj','fp8.obj','init.obj','userapi.obj']}
assert record['new_cpp_bytes']==283
Path('build/resume-eh-local/turn42-runtime-proof.json').write_text(json.dumps(record,indent=2));print('exact functions',len(functions),'new CPP bytes',record['new_cpp_bytes'],'private data',sum(r['size'] for r in private),'private literal bytes',133,'typed sentinel rows',16)
