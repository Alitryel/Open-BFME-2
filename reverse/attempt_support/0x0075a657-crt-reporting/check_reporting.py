from pathlib import Path
import csv,sys,struct,json,hashlib
sys.path.insert(0,'tools');import build,eh_verify,data_rows
source='Code/Libraries/Source/CRT/RtcError.cpp';obj=eh_verify.Obj(build.obj_path(source));native=build.obj_path('vendor/msvc71crt/msvcrt.lib','..\\build\\intel\\dll_obj\\error.obj');old=eh_verify.Obj(native);img=eh_verify.Image();sm=build.load_symbol_map();names=['?IntToString@@YAPADH@Z','?Initialize@@YAHXZ','?failwithmessage@@YAXPAXHHPBD@Z','?_RTC_Failure@@YAXPAXH@Z','?_RTC_MemFailure@@YAXPAXHPBX@Z','?_RTC_StackFailure@@YAXPAXPBD@Z','__RTC_UninitUse','?WinGetDebugContext@@YAPAXXZ','?Win95IsDebuggerPresent@@YGHXZ','?_IsDebuggerPresent@@YAHXZ','?DebuggerProbe@@YAHK@Z','?DebuggerRuntime@@YAHKHPAXPB_W@Z'];rows=[]
with open('reverse/functions.csv',encoding='utf-8',newline='') as f:
 h=next(csv.reader([next(f)]))
 for line in f:
  if not any(n+',' in line for n in names):continue
  row=dict(zip(h,next(csv.reader([line]))))
  if row['name'] in names:rows.append(row)
assert len(rows)==12
assert build.compile_is_current(Path(source).resolve(),build.obj_path(source))
functions=[];scopes=[];bindings={};literal_refs=[]
for original in rows:
 row=dict(original,source=source,notes='');name=row['name'];rva=int(row['target_rva'],16);size=int(row['target_size']);p=build.compile_function(row,sm,build.obj_path(source));assert p['bytes']==p['target'] and not p['unresolved'],name;assert not build.body_extent_problems(row,p,sm,build.obj_path(source),sorted({int(r['target_rva'],16) for r in rows})),name
 raw,rel=build.read_object_symbol_bytes(build.obj_path(source),name,size);nraw,nrel=build.read_object_symbol_bytes(native,name,size);assert raw==nraw,(name,'raw code')
 def normalize(rs):return [(o,t,'<scope-table>' if name in ['?DebuggerProbe@@YAHK@Z','?DebuggerRuntime@@YAHKHPAXPB_W@Z'] and o==3 and t==6 else n) for o,t,n in rs]
 assert normalize(rel)==normalize(nrel),(name,'native relocations',rel,nrel)
 assert obj.by_name[name]['storage']==old.by_name[name]['storage'],name
 for off,typ,symname in rel:
  if typ!=6 or symname.startswith('$') or symname.startswith('__imp_'):continue
  s=obj.by_name.get(symname)
  if s is None:continue
  sec=obj.sections[s['section']-1]
  if sec['name'].startswith('.text'):continue
  base=img.dword(rva+off)-img.base-struct.unpack_from('<I',raw,off)[0]
  if symname in bindings:assert bindings[symname]==base,(name,symname,base,bindings[symname])
  bindings[symname]=base
  if symname.startswith('??_C@'):
   literal=sec['data'][s['value']:];literal=literal[:literal.index(b'\0')+1];assert literal==img.bytes[base:base+len(literal)];literal_refs.append({'name':symname,'rva':hex(base),'bytes':len(literal),'value':literal[:-1].decode('ascii')})
 if name in ['?DebuggerProbe@@YAHK@Z','?DebuggerRuntime@@YAHKHPAXPB_W@Z']:
  sym=obj.by_name[name];code=obj.sections[sym['section']-1];found=[(o,i,t) for o,i,t in code['relocs'] if o==sym['value']+3];assert len(found)==1;off,index,typ=found[0];assert typ==6;ts=obj.symbols[index];table=obj.sections[ts['section']-1];assert len(table['data'])==12
  trva=img.dword(rva+3)-img.base-ts['value']-struct.unpack_from('<I',code['data'],off)[0];expected=bytearray(table['data']);targets=[]
  for o,i,t in table['relocs']:
   assert t==6;dest=obj.symbols[i];assert dest['section']==sym['section'];add=struct.unpack_from('<I',expected,o)[0];delta=dest['value']-sym['value']+add;va=img.base+rva+delta;struct.pack_into('<I',expected,o,va);targets.append({'scope_offset':o,'body_offset':delta,'target_va':hex(va)})
  assert bytes(expected)==img.bytes[trva:trva+12];scopes.append({'name':name,'rva':hex(trva),'bytes':expected.hex(),'targets':targets,'exact':True,'ordinary_eh_result':eh_verify.verify_row(img,obj,name,rva)})
 functions.append({'name':name,'rva':hex(rva),'size':size,'private':obj.by_name[name]['storage']==3,'raw_native_code_and_relocations_exact':True,'ledger_now_authored':original['source']==source})
variables=[]
for name,size in [('_FnIsDebuggerPresent',4),('__RTC_NoFalsePositives',20),('__RTC_ErrorMessages',20),('?_RTC_ErrorLevels@@3PAHA',16),('?buf@?1??IntToString@@YAPADH@Z@4PADA',15),('?fInited@?1??_IsDebuggerPresent@@YAHXZ@4HA',4)]:
 sym=obj.by_name[name];ns=old.by_name[name];sec=obj.sections[sym['section']-1];nsec=old.sections[ns['section']-1];assert sym['storage']==ns['storage'];data=sec['data'][sym['value']:sym['value']+size];ndata=nsec['data'][ns['value']:ns['value']+size];assert len(data)==len(ndata)==size;assert data==ndata,(name,'raw data')
 rva=bindings[name];expected=bytearray(data);literals=[]
 for off,index,typ in sec['relocs']:
  if not sym['value']<=off<sym['value']+size:continue
  off-=sym['value'];assert typ==6;dest=obj.symbols[index];assert dest['name'].startswith('??_C@');literal=obj.sections[dest['section']-1]['data'][dest['value']:];literal=literal[:literal.index(b'\0')+1];add=struct.unpack_from('<I',data,off)[0];va=img.dword(rva+off);assert literal[add:]==img.bytes[va-img.base:va-img.base+len(literal)-add];struct.pack_into('<I',expected,off,va);literals.append({'coff_name':dest['name'],'target_va':hex(va),'size':len(literal),'value':literal[:-1].decode('ascii')})
 assert bytes(expected)==img.bytes[rva:rva+size],name
 if '?1??' in name:
  assert len(sec['data'])==size and len(nsec['data'])==size;why='matching complete isolated native/authored COFF section and mangled type plus exact bounded uses'
 else:
  n,why=data_rows.compiled_size(source,name);assert n==size,(name,n,why)
 variables.append({'name':name,'rva':hex(rva),'size':size,'private':sym['storage']==3,'size_proof':why,'exact':True,**({'literals':literals} if literals else {})})
helper='?GetCurrentTib@@YAPAU_TIB@@XZ';raw,rels=build.read_object_symbol_bytes(build.obj_path(source),helper,7);assert raw==build.read_target_bytes(0x75a73d,7)==b'\x64\xa1\x18\x00\x00\x00\xc3' and not rels;assert obj.by_name[helper]['storage']==3
record={'scope':'Complete RTC reporting member: twelve real C++ reporting bodies. Existing seven-byte FS compiler primitive remains ASM-owned and is not counted as new C++; private inline copy only. Independent target/native COFF reconstruction; no implementation source.','source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'bfme1_pointer':'a0e8f345a9b22b4b42088e402962287d7015e3c2','functions':functions,'new_cpp_bytes':sum(r['size'] for r in functions),'native_data':variables,'seh_scope_tables':scopes,'direct_literals':list({r['name']:r for r in literal_refs}.values()),'retained_asm_primitive':{'name':helper,'rva':'0x75a73d','size':7,'source':'Code/masm_dumps/GetCurrentTib.asm','new_cpp_bytes':0}}
assert record['new_cpp_bytes']==1450 and sum(r['size'] for r in variables)==79
Path('build/resume-eh-local/turn44-rtc-proof.json').write_text(json.dumps(record,indent=2));print('whole member12 exact C++ functions1450B; native data79B; SEH scope tables24B; unchanged ASM primitive7B')
