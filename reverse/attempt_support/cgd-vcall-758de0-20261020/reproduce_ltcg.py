from pathlib import Path
import subprocess,sys,json,shutil,os,hashlib
root=Path.cwd();sys.path.insert(0,str(root/'tools'));import build,pefile,capstone
out=root/'build/cgd758de0-ltcg-repro';out.mkdir(parents=True,exist_ok=True);base=Path(__file__).with_name('baseline.cpp.txt').read_text();vendor=root/'vendor/vc71-sp1/bin';rtm=build.DEFAULT_VC71_ROOT/'Vc7/bin'
for mode in ['rtm_with_sp1_object_runtime','sp1_linktime']:
 folder=out/mode;folder.mkdir(parents=True,exist_ok=True);bindir=folder/'bin';bindir.mkdir(exist_ok=True)
 for name in ['cl.exe','c1.dll','c1xx.dll','c2.dll','msobj71.dll','mspdb71.dll','msvcp71.dll','msvcr71.dll']:
  shutil.copy2(vendor/name,bindir/name)
 if mode.startswith('rtm'):
  for name in ['cl.exe','c1.dll','c1xx.dll','c2.dll']:shutil.copy2(rtm/name,bindir/name)
 shutil.copy2(rtm/'link.exe',bindir/'link.exe')
 source=folder/'candidate.cpp';source.write_text(base.replace('// cl: /O2 /MD /EHsc /I.','// cl: /O2 /MD /EHsc /I. /GL'))
 obj=folder/'candidate.obj';command,env=build.compiler_command(source,obj);command[0]=str(bindir/'cl.exe');env['PATH']=str(bindir)+os.pathsep+env.get('PATH','')
 result=subprocess.run(command,cwd=root,env=env,capture_output=True,text=True);(folder/'compile.log').write_text(result.stdout+result.stderr)
 print(mode,'compile',result.returncode,flush=True)
 if result.returncode:print((result.stdout+result.stderr)[-1000:],flush=True);continue
 name='?bfmeTwoCGD@BfmeThingCGD@@QAEXXZ';image=folder/'candidate.dll'
 link=[str(bindir/'link.exe'),'/NOLOGO','/DLL','/NOENTRY','/LTCG','/INCREMENTAL:NO','/OPT:NOREF','/OPT:NOICF','/EXPORT:'+name,'/OUT:'+str(image),'/MAP:'+str(folder/'candidate.map'),str(obj)]
 result=subprocess.run(link,cwd=root,env=env,capture_output=True,text=True);(folder/'link.log').write_text(result.stdout+result.stderr)
 print(mode,'link',result.returncode,flush=True)
 if result.returncode:print((result.stdout+result.stderr)[-1400:],flush=True);continue
 pe=pefile.PE(str(image));entry=next(e.address for e in pe.DIRECTORY_ENTRY_EXPORT.symbols if e.name and e.name.decode()==name);ours=pe.get_data(entry,1024);target=build.read_target_bytes(0x758de0,333)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ins=list(md.disasm(ours,0));ret=next((i.address+i.size for i in ins if i.mnemonic.startswith('ret')),None)
 metrics={'mode':mode,'return_end':ret,'prefix_byte_differences':sum(a!=b for a,b in zip(ours[:333],target)),'exact333':ours[:333]==target,'compiler_sha256':hashlib.sha256((bindir/'cl.exe').read_bytes()).hexdigest(),'backend_sha256':hashlib.sha256((bindir/'c2.dll').read_bytes()).hexdigest()}
 (folder/'metrics.json').write_text(json.dumps(metrics,indent=2));print(json.dumps(metrics),flush=True)
 (folder/'candidate.asm').write_text('\n'.join(f'{i.address:04x} {i.mnemonic} {i.op_str}' for i in ins if ret is None or i.address<ret))
