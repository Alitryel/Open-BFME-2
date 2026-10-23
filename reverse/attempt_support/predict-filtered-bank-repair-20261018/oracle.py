"""Compare this bank's observable prediction dispatch with the whole retail body.

Clean room: specs/001c5e30.md, retail, and this repository only. Pixel-producing
callees are stubbed; this checks dispatch/arguments and cdecl preserved state,
not the separate pixel algorithms. No compiler or gate is invoked here.
"""
import hashlib
import json
from pathlib import Path
import random
import struct
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import build
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *

SYMBOL = '?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z'
RVA = 0x1C5E30
ENTRY = 0x400000 + RVA
INSTANCE, LAST, GOLD, LOOP, OUTPUT, STACK, STOP = (
    0x100000, 0x200000, 0x300000, 0x400000, 0x600000, 0x700000, 0x900000)
BUILDER, VARIANCE, FILTER, UNPACK = 0x5D8DD0, 0x5D8A30, 0x800000, 0x800010
ADDRESSES = {
    '?g_bfmeVp6SelectorMap@@3PAEA': 0xBD8D00,
    '?g_bfmeSlotB54@@3PAXA': 0xE22D1C,
    '?g_bfmeSlotB50@@3PAXA': 0xE22D18,
    '_VP6_PredictFiltered': BUILDER,
    '_Var16Point': VARIANCE,
}

def compiled(source):
    raw, relocations = build.read_object_symbol_bytes(build.obj_path(source), SYMBOL)
    result = bytearray(raw)
    for offset, kind, name in relocations:
        dest = ADDRESSES[name]
        addend = struct.unpack_from('<I', result, offset)[0]
        if kind == 20:
            value = dest + addend - (ENTRY + offset + 4)
        elif kind == 6:
            value = dest + addend
        else:
            raise AssertionError((kind, name))
        struct.pack_into('<I', result, offset, value & 0xFFFFFFFF)
    return bytes(result)

def run(code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    for start, size in [(INSTANCE,0x6000),(LAST,0x10000),(GOLD,0x10000),
                        (LOOP,0x1000),(OUTPUT,0x1000),(STACK,0x10000),
                        (ENTRY & ~0xFFF,0x2000),(0x5D8000,0x1000),
                        (FILTER,0x1000),(STOP,0x1000),(0xBD8000,0x1000),
                        (0xE22000,0x1000)]:
        uc.mem_map(start,size)
    def put(address, value):
        uc.mem_write(address,struct.pack('<I',value & 0xFFFFFFFF))
    put(INSTANCE+8,case['mode'])
    put(INSTANCE+0x70,0x1000)
    put(INSTANCE+0x74,64)
    put(INSTANCE+0x7C,case['shift'])
    put(INSTANCE+0x80,(1 << case['shift'])-1)
    put(INSTANCE+0x88,64)
    put(INSTANCE+0x24C,GOLD)
    put(INSTANCE+0x254,LAST)
    put(INSTANCE+0x290,LOOP)
    uc.mem_write(INSTANCE+0x19D,bytes([case['profile']]))
    uc.mem_write(INSTANCE+0x4534,bytes([case['loop']]))
    uc.mem_write(INSTANCE+0x692,bytes([case['filter'],case['size']]))
    put(INSTANCE+0x694,case['threshold'])
    vector = INSTANCE+0x24+4*case['block']
    uc.mem_write(vector,struct.pack('<hh',case['x'],case['y']))
    uc.mem_write(0xBD8D00,build.read_target_bytes(0x7D8D00,40))
    put(0xE22D1C,FILTER)
    put(0xE22D18,UNPACK)
    uc.mem_write(ENTRY,code)
    for address in [BUILDER,VARIANCE,FILTER,UNPACK,STOP]:
        uc.mem_write(address,b'\xC3')
    esp = STACK+0x8000
    uc.mem_write(esp,struct.pack('<IIII',STOP,INSTANCE,OUTPUT,case['block']))
    uc.reg_write(UC_X86_REG_ESP,esp)
    saved = {UC_X86_REG_EBX:0x11223344,UC_X86_REG_ESI:0x22334455,
             UC_X86_REG_EDI:0x33445566,UC_X86_REG_EBP:0x44556677}
    for register,value in saved.items():
        uc.reg_write(register,value)
    trace = []
    def hook(emu,address,size,user):
        if address == STOP:
            emu.emu_stop()
            return
        counts = {BUILDER:4,VARIANCE:2,FILTER:7,UNPACK:3}
        if address not in counts:
            return
        stack = emu.reg_read(UC_X86_REG_ESP)
        args = struct.unpack('<'+'I'*counts[address],emu.mem_read(stack+4,4*counts[address]))
        trace.append([address,*args])
        if address == BUILDER and case['mutate']:
            emu.mem_write(vector,struct.pack('<hh',case['x']+1,case['y']-1))
        if address == VARIANCE:
            emu.reg_write(UC_X86_REG_EAX,case['variance'])
    uc.hook_add(UC_HOOK_CODE,hook)
    uc.emu_start(ENTRY,STOP+1,count=10000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP
    assert uc.reg_read(UC_X86_REG_ESP) == esp+4
    assert all(uc.reg_read(reg)==value for reg,value in saved.items())
    return trace,bytes(uc.mem_read(INSTANCE,0x6000))

def main():
    source = Path(sys.argv[1] if len(sys.argv)>1 else 'reverse/attempts/0x001c5e30.cpp')
    own = compiled(source)
    retail = build.read_target_bytes(RVA,768)
    rng = random.Random(0x1C5E30)
    cases = []
    for block in range(6):
        for x,y in [(0,0),(1,0),(0,1),(1,1),(-1,-1),(-7,9),(12,-16)]:
            for profile,loop in [(0,0),(1,0),(1,1)]:
                cases.append(dict(block=block,x=x,y=y,profile=profile,loop=loop,
                                  mode=2,shift=2,filter=2,size=0,threshold=0,
                                  variance=0,mutate=0))
    for _ in range(600):
        threshold = rng.choice([0,1,16,100,1000])
        cases.append(dict(block=rng.randrange(6),x=rng.randint(-128,128),
                          y=rng.randint(-128,128),profile=rng.randrange(3),
                          loop=rng.randrange(3),mode=rng.randrange(10),
                          shift=rng.randrange(4),filter=rng.randrange(4),
                          size=rng.choice([0,1,2,3,4,8]),threshold=threshold,
                          variance=rng.choice([0,threshold,max(0,threshold-1),threshold+1]),
                          mutate=rng.randrange(2)))
    # The native shift takes its low five count bits. Exercise every value
    # of the unsigned threshold byte, including the shift-count wrap edges.
    for threshold in range(256):
        for loop in range(2):
            cases.append(dict(block=0,x=-65,y=63,profile=1,loop=loop,mode=2,
                              shift=2,filter=2,size=threshold,threshold=0,
                              variance=0,mutate=0))
    failures = []
    for index,case in enumerate(cases):
        expected = run(retail,case)
        actual = run(own,case)
        if actual != expected:
            failures.append(dict(index=index,case=case,retail=expected[0],compiled=actual[0]))
    report = dict(source=str(source),cases=len(cases),failures=len(failures),
                  source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                  retail_sha256=hashlib.sha256(retail).hexdigest(),
                  compiled_sha256=hashlib.sha256(own).hexdigest(),
                  examples=failures[:8])
    print(json.dumps(report,indent=2))
    return int(bool(failures))

if __name__ == '__main__':
    raise SystemExit(main())
