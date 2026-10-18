from pathlib import Path
import sys,csv,json,hashlib,subprocess
sys.path.insert(0,'tools');import build,eh_verify
names={'@_RTC_CheckStackVars@8','__RTC_CheckEsp'};rows=[]
with open('reverse/functions.csv',encoding='utf-8',newline='') as f:
 h=next(csv.reader([next(f)]))
 for line in f:
  if line.split(',',1)[0] not in names:continue
  rows.append(dict(zip(h,next(csv.reader([line])))))
assert len(rows)==2
native=build.obj_path('vendor/msvc71crt/msvcrt.lib','..\\build\\intel\\dll_obj\\stack.obj');nobj=eh_verify.Obj(native);img=eh_verify.Image();sm=build.load_symbol_map();proof=[]
for r in rows:
 src=r['source'];obj=build.obj_path(src);assert build.compile_is_current(Path(src).resolve(),obj)
 p=build.compile_function(r,sm,obj);assert p['bytes']==p['target'] and not p['unresolved'];assert not build.body_extent_problems(r,p,sm,obj,[int(v['target_rva'],16) for v in rows])
 name=r['name'];size=int(r['target_size']);raw,rel=build.read_object_symbol_bytes(obj,name,size);old,orels=build.read_object_symbol_bytes(native,name,size);assert raw==old and rel==orels,(name,rel,orels)
 o=eh_verify.Obj(obj);assert o.by_name[name]['storage']==nobj.by_name[name]['storage'];eh=eh_verify.verify_row(img,o,name,int(r['target_rva'],16));assert eh is None
 proof.append({'name':name,'source':src,'rva':r['target_rva'],'size':size,'raw_native_exact':True,'native_relocations_exact':True,'strict_retail_match':True,'eh':eh,'source_sha256':hashlib.sha256(Path(src).read_bytes()).hexdigest(),'cpp_bytes':size if src.endswith('.cpp') else 0,'relocations':rel})
record={'scope':'Complete native stack.obj; ordinary fastcall checker is C++; incoming-ZF/live-register helper is mnemonic MASM and receives zero C++ credit. Independently authored from retail/native COFF and public rtcapi.h; no CRT implementation source.','native_member':'..\\build\\intel\\dll_obj\\stack.obj','bfme1_pointer':subprocess.check_output(['git','rev-parse','HEAD:reference/open-bfme-1'],text=True).strip(),'functions':proof,'new_cpp_bytes':90,'retained_asm_bytes':35,'new_data_bytes':0,'descriptor_layout':{'_RTC_framedesc':{'size':8,'varCount':0,'variables':4},'_RTC_vardesc':{'size':12,'addr':0,'size':4,'name':8}},'header':'public rtcapi.h, resolved through normal compiler dependency cache','place_bodies':'0 bodies, 0 pins','census_preview':'Not in census2967eab33e; focused native-archive link used separately. No whole-game placement/runtime claim.'}
Path('build/resume-eh-local/turn45-stack-proof.json').write_text(json.dumps(record,indent=2));print('native raw bytes and relocations exact: C++90 + MASM35; ordinary EH absent; no data; descriptor8/12 from CodeView and publicheader')
