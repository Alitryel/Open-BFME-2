"""Strong-filter bank check: retail, compiled C++, and the published clean spec.

No external VP6 source is used. Native and candidate run in separate emulators.
"""
import hashlib
import json
from pathlib import Path
import random
import struct
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "AGENTS.md").is_file())
sys.path.insert(0, str(ROOT / "tools"))
import build
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import *

ENTRY, BUF, SCALE, STACK, STOP = 0x5C1AD0,0x300000,0x200000,0x700000,0x60000000
ORIGIN = 0x1000
SHARPEN = struct.unpack('<64i',build.read_target_bytes(0x9B7A28,256))
SAVED = {UC_X86_REG_EBX:0x11223344,UC_X86_REG_EBP:0x22334455,
         UC_X86_REG_ESI:0x33445566,UC_X86_REG_EDI:0x44556677}

def run(code,data,pitch,qindex,quality,destination):
    u=Uc(UC_ARCH_X86,UC_MODE_32)
    for start,size in [(ENTRY & ~0xFFF,0x3000),(BUF,0x10000),(SCALE,0x1000),
                       (STACK,0x10000),(STOP,0x1000),(0xDB7000,0x1000)]:
        u.mem_map(start,size)
    u.mem_write(ENTRY,code)
    u.mem_write(BUF,data)
    u.mem_write(SCALE,struct.pack('<64i',*([quality]*64)))
    u.mem_write(0xDB7A28,struct.pack('<64i',*SHARPEN))
    esp=STACK+0xF000
    u.mem_write(esp,struct.pack('<7I',STOP,0,BUF+ORIGIN,BUF+destination,pitch,qindex,SCALE))
    u.reg_write(UC_X86_REG_ESP,esp)
    for reg,value in SAVED.items():u.reg_write(reg,value)
    u.emu_start(ENTRY,STOP,count=1000000)
    assert u.reg_read(UC_X86_REG_ESP)==esp+4
    assert all(u.reg_read(reg)==value for reg,value in SAVED.items())
    assert bytes(u.mem_read(SCALE,256))==struct.pack('<64i',*([quality]*64))
    return bytes(u.mem_read(BUF,len(data)))

def model(data,pitch,qindex,quality,destination):
    result=bytearray(data)
    cap=min(3*quality,32)
    def weight(a,b):
        value=quality-abs(a-b)+32
        return SHARPEN[qindex] if value < -64 else min(max(value,0),cap)
    vertical=[[weight(data[ORIGIN+(r-1)*pitch+c],data[ORIGIN+r*pitch+c])
               for c in range(8)] for r in range(9)]
    horizontal=[[weight(data[ORIGIN+r*pitch+c-1],data[ORIGIN+r*pitch+c])
                 for c in range(9)] for r in range(8)]
    for r in range(8):
        row=[]
        for c in range(8):
            p=ORIGIN+r*pitch+c
            up,down,left,right=vertical[r][c],vertical[r+1][c],horizontal[r][c],horizontal[r][c+1]
            value=((128-up-down-left-right)*result[p]+up*result[p-pitch]+
                   down*result[p+pitch]+left*result[p-1]+right*result[p+1]+64)>>7
            row.append(max(0,min(255,value)))
        result[destination+r*pitch:destination+r*pitch+8]=bytes(row)
    return bytes(result)

def main():
    source=Path(sys.argv[1] if len(sys.argv)>1 else 'reverse/attempts/0x001c1ad0.cpp')
    raw,relocations=build.read_object_symbol_bytes(build.obj_path(source),'_DeringBlockStrong_C',code_only=True)
    candidate=bytearray(raw)
    for offset,kind,name in relocations:
        assert (kind,name)==(6,'_Vp6FilterEdgeTagTable'),(kind,name)
        addend=struct.unpack_from('<I',candidate,offset)[0]
        struct.pack_into('<I',candidate,offset,(0xDB7A28+addend)&0xFFFFFFFF)
    candidate=bytes(candidate)
    retail=build.read_target_bytes(0x1C1AD0,2030)
    rng=random.Random(0x1C1AD0)
    count=0
    for qindex in range(64):
        for pattern in range(4):
            pitch=10+((qindex*5+pattern)%23)
            quality=[0,1,2,7,15,31,64,128][(qindex+pattern)%8]
            if pattern==0:data=bytes([qindex*4])*0x6000
            elif pattern==1:data=bytes((255 if (i+i//pitch)%2 else 0) for i in range(0x6000))
            elif pattern==2:data=bytes((i*3+i//pitch)%256 for i in range(0x6000))
            else:data=rng.randbytes(0x6000)
            for destination in [0x3000,ORIGIN,ORIGIN+1,ORIGIN-1,ORIGIN+pitch-3]:
                native=run(retail,data,pitch,qindex,quality,destination)
                actual=run(candidate,data,pitch,qindex,quality,destination)
                expected=model(data,pitch,qindex,quality,destination)
                assert native==expected,(qindex,pattern,destination,'native/spec')
                assert actual==expected,(qindex,pattern,destination,'compiled/spec')
                count+=1
    print(json.dumps(dict(source=str(source),cases=count,failures=0,size=len(candidate),
                          source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                          retail_sha256=hashlib.sha256(retail).hexdigest(),
                          compiled_sha256=hashlib.sha256(candidate).hexdigest(),
                          checks=['full buffer including canaries','disjoint/inplace/partial overlap',
                                  'all64sharpen indices','native/candidate/published-spec',
                                  'cdecl stack/nonvolatile registers','unchanged scale table']),indent=2))

if __name__=='__main__':main()
