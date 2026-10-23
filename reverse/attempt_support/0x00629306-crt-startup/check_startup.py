from pathlib import Path
import csv,sys,struct,json,hashlib
sys.path.insert(0,'tools');import build,eh_verify,data_rows
sources=['Code/Libraries/Source/CRT/'+n+'.cpp' for n in ['XcptFilterImport','AmsgExitImport','InitTermImport','StartupDefaults','WinMainStartup']]
rows=[]
with open('reverse/functions.csv',newline='',encoding='utf-8') as f:
 h=next(csv.reader([next(f)]))
 for line in f:
  if any(','+s+',' in line for s in sources):rows.append(dict(zip(h,next(csv.reader([line])))))
assert len(rows)==7,len(rows)
img=eh_verify.Image();sm=build.load_symbol_map();functions=[]
for source in sources:assert build.compile_is_current(Path(source).resolve(),build.obj_path(source)),source
for row in rows:
 path=build.obj_path(row['source']);proof=build.compile_function(row,sm,path);assert proof['bytes']==proof['target'],row['name']
 assert not proof.get('unresolved'),proof.get('unresolved')
 assert not build.body_extent_problems(row,proof,sm,path,sorted({int(r['target_rva'],16) for r in rows})),row['name']
 functions.append({'name':row['name'],'rva':row['target_rva'],'size':int(row['target_size']),'source':row['source'],'new_unique_cpp':row['name'] in {'_check_managed_app','_WinMainCRTStartup'}})
source=sources[-1];obj=eh_verify.Obj(build.obj_path(source));sym=obj.by_name['_WinMainCRTStartup'];code=obj.sections[sym['section']-1]
rel=[(o,i,t) for o,i,t in code['relocs'] if o==sym['value']+3];assert len(rel)==1
pos,index,typ=rel[0];assert typ==6;table_sym=obj.symbols[index];table=obj.sections[table_sym['section']-1];assert len(table['data'])==12
rva=0x629306;trva=img.dword(rva+3)-img.base-table_sym['value']-struct.unpack_from('<I',code['data'],pos)[0]
expected=bytearray(table['data']);targets=[]
for off,index,typ in table['relocs']:
 assert typ==6;dest=obj.symbols[index];assert dest['section']==sym['section'];add=struct.unpack_from('<I',expected,off)[0];va=img.base+rva+dest['value']-sym['value']+add;struct.pack_into('<I',expected,off,va);targets.append({'table_offset':off,'body_offset':dest['value']-sym['value']+add,'target_va':hex(va)})
assert trva==0x87c758 and bytes(expected)==img.bytes[trva:trva+12]
assert [t['body_offset'] for t in targets]==[0x1c6,0x1da]
static=obj.by_name['_check_managed_app'];assert static['storage']==3
native=build.obj_path('vendor/msvc71crt/msvcrt.lib','build\\intel\\dll_obj\\crtexew.obj')
for row in rows:
 if row['name'] not in {'_check_managed_app','_WinMainCRTStartup'}:continue
 old=eh_verify.Obj(native);s=old.by_name[row['name']];n=int(row['target_size']);original,oreloc=build.read_object_symbol_bytes(native,row['name'],n);authored,areloc=build.read_object_symbol_bytes(build.obj_path(source),row['name'],n)
 normalize=lambda rs:[(o,t,'<startup-scope-table>' if row['name']=='_WinMainCRTStartup' and o==3 and t==6 else name) for o,t,name in rs]
 assert normalize(oreloc)==normalize(areloc),(row['name'],oreloc,areloc)
 assert original==authored,(row['name'],'raw object bytes changed')
default_obj=eh_verify.Obj(build.obj_path(sources[-2]));ds=default_obj.by_name['___defaultmatherr'];sec=default_obj.sections[ds['section']-1];assert ds['storage']==2 and sec['name']=='.data' and len(sec['data'])==4;assert sec['data']==img.bytes[0x9d7f14:0x9d7f18]==b'\1\0\0\0';assert data_rows.compiled_size(sources[-2],'___defaultmatherr')[0]==4
record={'scope':'Whole native crtexew.obj reconstructed as C++; complete retail bodies including SEH filter. All raw object code and external relocation names, types, positions and addends equal native member; scope-table local label is independently graph-resolved. Static helper remains private. Public SDK declarations supply PE/Win32 types; other CRT relationships from original COFF, not implementation source. The startup unit owns no globals; the native merr.obj four-byte flag is moved together with its callback into StartupDefaults.cpp and verified separately.','sources':sources,'bfme1_pointer':build.subprocess.check_output(['git','rev-parse','HEAD:reference/open-bfme-1'],text=True).strip() if hasattr(build,'subprocess') else 'a0e8f345a9b22b4b42088e402962287d7015e3c2','source_sha256':{s:hashlib.sha256(Path(s).read_bytes()).hexdigest() for s in sources},'functions':functions,'new_unique_cpp_bytes':sum(r['size'] for r in functions if r['new_unique_cpp']),'import_provider_bytes_previously_generated_cpp':18,'folded_default_hook_bytes_no_unique_gain':6,'seh_scope':{'rva':hex(trva),'bytes':expected.hex(),'targets':targets,'exact':True,'ordinary_verifier_result':eh_verify.verify_row(img,obj,'_WinMainCRTStartup',rva)},'default_matherr_flag':{'name':'___defaultmatherr','rva':'0x9d7f14','size':4,'value':'01000000','native_member':'build\\intel\\dll_obj\\merr.obj','data_rows_verified':True},'retired_native_member':'build\\intel\\dll_obj\\crtexew.obj'}
assert record['new_unique_cpp_bytes']==597
Path('build/resume-eh-local/turn43-startup-proof.json').write_text(json.dumps(record,indent=2));print('exact functions',len(rows),'new unique C++ bytes',597,'SEH table bytes',12,'native raw code and every relocation identical; native default flag4B exact')

