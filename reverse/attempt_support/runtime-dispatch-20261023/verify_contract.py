from pathlib import Path
import sys,struct,json,random
repo=Path(__file__).resolve().parents[3]
root=repo/'build/runtime-dispatch-validation'
sys.path.insert(0,str(root/'deps'))
sys.path.insert(0,str(repo/'tools'))
import build
from unicorn import Uc,UcError,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
BASE,STACK,DEST=0x400000,0x200000,0x500000
SP=STACK+0xf000
CALLER=0x12345678
REGS={'eax':UC_X86_REG_EAX,'ecx':UC_X86_REG_ECX,'edx':UC_X86_REG_EDX,'ebx':UC_X86_REG_EBX,'ebp':UC_X86_REG_EBP,'esi':UC_X86_REG_ESI,'edi':UC_X86_REG_EDI}
proof=json.loads((root/'byte-proof.json').read_text())
images={name:{r['rva']:(build.read_target_bytes(r['rva'],r['size']) if name=='retail' else bytes.fromhex(r['resolved_hex'])) for r in proof} for name in ('retail','candidate')}
PATHS=[(0x7ed9,0x7af3,0x712b,-3509),(0x8449,0x7c63,0x735b,-4341)]
def execute(which,path,mode,values,flags,destination,expect_fault=False):
 entry,core,slot,bias=path
 ret=BASE+entry+7
 assert ret+bias==BASE+slot
 u=Uc(UC_ARCH_X86,UC_MODE_32)
 u.mem_map(BASE,0x10000);u.mem_map(STACK,0x10000);u.mem_map(DEST,0x1000)
 for rva,body in images[which].items():u.mem_write(BASE+rva,body)
 u.mem_write(BASE+0x712b,b'\0'*4);u.mem_write(BASE+0x735b,struct.pack('<I',0x66825ab4))
 u.mem_write(BASE+slot,struct.pack('<I',destination))
 u.mem_write(SP-32,b'\xa5'*96)
 if mode=='entry':
  frame=struct.pack('<I',CALLER);start=BASE+entry;final_sp=SP-8
 else:
  frame=struct.pack('<4I',ret,values['eax'],values['ecx'],CALLER);start=BASE+core;final_sp=SP+4
 u.mem_write(SP,frame)
 expected_stack=bytearray(u.mem_read(SP-32,96))
 if mode=='entry':struct.pack_into('<3I',expected_stack,20,ret,values['eax'],values['ecx'])
 for name,value in values.items():u.reg_write(REGS[name],value)
 u.reg_write(UC_X86_REG_ESP,SP);u.reg_write(UC_X86_REG_EFLAGS,flags)
 fault=None
 try:u.emu_start(start,destination if not expect_fault else DEST, count=32)
 except UcError as e:fault=e.errno
 assert (fault is not None)==expect_fault,(which,mode,fault)
 actual={name:u.reg_read(reg) for name,reg in REGS.items()}
 assert actual['eax']==destination and actual['ecx']==ret
 assert all(actual[name]==values[name] for name in ('edx','ebx','ebp','esi','edi'))
 assert u.reg_read(UC_X86_REG_EFLAGS)==flags
 assert u.reg_read(UC_X86_REG_ESP)==final_sp
 assert u.reg_read(UC_X86_REG_EIP)==destination
 assert bytes(u.mem_read(SP-32,96))==bytes(expected_stack)
 assert struct.unpack('<3I',bytes(u.mem_read(final_sp,12)))==(values['eax'],values['ecx'],CALLER)
 assert struct.unpack('<I',bytes(u.mem_read(BASE+slot,4)))[0]==destination
 other=0x735b if slot==0x712b else 0x712b
 assert struct.unpack('<I',bytes(u.mem_read(BASE+other,4)))[0]==(0x66825ab4 if other==0x735b else 0)
 return actual,u.reg_read(UC_X86_REG_ESP),u.reg_read(UC_X86_REG_EIP),u.reg_read(UC_X86_REG_EFLAGS),fault
rng=random.Random(0x7af37c63)
cases=[]
for n in range(136):
 values={name:(rng.getrandbits(32) if n>=8 else [0,1,0xffffffff,0x80000000,0x7fffffff,0xaaaaaaaa,0x55555555,0x12345678][n]) for name in REGS}
 flags=0x202|(rng.getrandbits(12)&0x8d5)
 cases.append((values,flags))
count=0
fault_count=0
for test_base in (0x400000,0x1000000):
 BASE=test_base
 for path in PATHS:
  for mode in ('entry','core'):
   for index,(values,flags) in enumerate(cases):
    dest=DEST+0x100+4*(index%64)
    assert execute('retail',path,mode,values,flags,dest)==execute('candidate',path,mode,values,flags,dest)
    count+=1
 for path,initial in zip(PATHS,(0,0x66825ab4)):
  values,flags=cases[3]
  assert execute('retail',path,'entry',values,flags,initial,True)==execute('candidate',path,'entry',values,flags,initial,True)
  fault_count+=1
# Negative control: ADD computes the same address but clobbers native flags.
original=images['candidate'][0x7af3]
assert original[6:9]==bytes.fromhex('8d0408')
images['candidate'][0x7af3]=original[:6]+bytes.fromhex('01c8')+original[9:]
rejected=False
try:
 execute('candidate',PATHS[0],'entry',cases[0][0],0x202,DEST+0x100)
except AssertionError:
 rejected=True
finally:
 images['candidate'][0x7af3]=original
assert rejected, 'flag-clobbering ADD mutant escaped contract checks'
report={'valid_destination_differential_pairs':count,'initial_value_unmapped_fault_pairs':fault_count,'vectors':len(cases),'image_bases':2,'paths':2,'modes':['entry','core'],'checks':['full register state','all selected arithmetic flags including unchanged CF','synthetic stack frame and return chain','stack canaries','cell preservation','destination EIP','same unmapped fetch failure for initial file values'],'add_for_lea_negative_control_rejected':rejected,'scope':'Per-stub ABI equivalence with controlled mutable-cell inputs; not discovery of runtime writer or actual resolver target; not a boot or link test.'}
(root/'contract-proof.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
