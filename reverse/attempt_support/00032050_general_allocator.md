# GeneralAllocator::rva00032050 (0x32050, 140 B) allocation wall

Status: banked 0.9; no byte-exact body. Inputs: `Code/GameEngine/Source/Common/System/memory_pool.cpp`
at the f596d6f5ad1 tree (memory_pool.cpp unchanged from 7f76df1ff53); MSVC 13.10.3077,
base flags `-O2 -GR- -EHsc-` (the farm file has no `// cl:` line). The function is a member of
`EA::Allocator::GeneralAllocator`; caller `rva000320E0` (matched, 128 B) passes
`(chunk, flags)`; retail's 0x32050 never reads `flags`.

## Retail evidence

`0x32050..0x320DC`, `RET 8`. Lock idiom: `Lock *lock = m_4E4;` enter/`++m_count`,
later `--`/leave.

Prologue+call+first check (`+0x00..+0x45`):

```
56 57 8b f9 8b b7 e4 04 00 00 85 f6 74 0e 56 ff 15 00 a2 bb 00
8b 46 18 40 89 46 18 53 8b 5c 24 10 8b 43 04 25 f8 ff ff 7f 53 8b cf
89 44 24 14 e8 0b ff ff ff 8b 4c 24 10 8a d1 80 e2 07 f6 da 1b d2
f7 da 03 c2
```

`this=EDI`, `lock=ESI`, `chunk=EBX`, the masked size spilled to `[esp+14h]` (the dead
arg1 slot), result `EAX` then `EDI`. Checks (`+0x38..+0x69`) in retail order:
`(size&7)!=0`, `size<0x10`, `(chunk&7)!=0`, `size<8`, `size>=size+0x10`; all branchless
(`sbb/neg`, last `sbb/inc`).

Fifth term: `mov edx,[esp+14h]; add edx,0x10; cmp ecx,edx; sbb ecx,ecx; inc ecx`.
The spill is the **masked size**, not the flags parameter; the 0.9 bank's
`flags+0x10` is a misread. Epilogue `+0x6A`: `test esi; lea edi,[ecx+eax]; pop ebx; je;
--m_count; push esi; Leave; mov eax,edi; pop edi; pop esi; ret 8`.

## Candidates

- 0.9 bank `reverse/attempts/0x00032050.cpp`: barrier + two-group single expression.
  First 0x46 bytes match retail (prologue, call, first check); first diff `+0x46`
  (chain order). Its fifth term uses `flags+0x10` (wrong operand).
- New 140 B family (2026-10-22): the free
  `static inline int CheckCount(bool ok) { if (ok) return 0; return 1; }`
  (the matched 0x31E60/0x321F0 style) used as

  ```cpp
  result += CheckCount(((unsigned char)size & 7) == 0);
  result += CheckCount(size >= 0x10);
  result += CheckCount(((unsigned char)(unsigned int)chunk & 7) == 0);
  result += CheckCount(size >= 8);
  result += CheckCount(size < size + 0x10);
  ```

  reproduces retail's check order and polarity exactly at 140 B, but compiles
  `this=ESI`, `lock=EDI`, `chunk=EBX`, `size=EAX`, `result=ESI`; first diff `+0x00`.
- Codegen-neutral variants: header local vs inline cast; single
  `result = call + ...` vs `+=`; `self` alias; member vs free `CheckCount`;
  `(void)flags` present/absent.
- H10 (bank barrier + CheckCount order) and H11 (bank single expression + retail
  order + size fifth term) both fall back to the V7 prologue. The bank's prologue is
  tied to its term tree/barrier; `CheckCount` calls give the order but the V7 prologue.
  A shape that keeps the bank's prologue **and** the `CheckCount` order is the open lead.
- Build pitfall: `_ReadWriteBarrier` declared/pragma'd inside `EA::Allocator` does not
  resolve/apply; put
  `extern "C" void _ReadWriteBarrier(void);`
  `#pragma intrinsic(_ReadWriteBarrier)` at global scope before `namespace EA` (the
  standalone bank already did).

## Caller change

The matched `rva000320E0` currently calls through a union `d_00032050` gen symbol.
Replacing that with the direct member call `rva00032050(chunk, flags)` keeps all 48
rows in `memory_pool.cpp` byte-identical and must land with the body; HEAD's union hack
exists only because the member body is unrowed. Verified 2026-10-22.

## Prior evidence

`reverse/re_attempts.log`: 63156 (240 term orders -> 135 B canonical), 80710 (dlmalloc
`CheckRemallocedChunk` identity: `sz&MASK`, `sz<MINSIZE`, `aligned_OK(chunk2mem)`,
`sz<8`, `sz>=s+MINSIZE`; 1500 groupings; no natural source), 61706/61730
(permute/guard), 81471 (barrier kinds), plus the 0.9 bank. The new `CheckCount`
family is not covered by the plain-expression sweeps and is the useful handoff.
