# 0x006C4730 GeneralAllocatorDebug realloc: the trailer alone picks the allocation (2026-10-20, claude r56)

The bank `reverse/attempts/0x006c4730.cpp` is unchanged: 798 B, 18 differing
bytes, all in the backup trailer at +0x9b..+0xb3. Earlier rounds are in
`allocator-trailer-materialize-20261020.md`, `allocator-trailer-copyprop-20261020.md`
and `allocator-header-lifetime-20261020.md`. This round tested whether
something outside the trailer can pull the exact trailer (named `n`, the
"c1" form) back onto the bank's allocation. It cannot. About 700 compiles.

## Model: the trailer's tree alone picks one of five attractors

`nd` below counts differing bytes of the 798 B target.

| Trailer form inside `mallocBackup` | nd | Allocation |
| --- | ---: | --- |
| Bank: pointer phi `end = c ? p+m+4 : p+m; *(end-10)=0` (also memset or memcpy on `end-10`) | 18 | retail's |
| Per-arm pointer, constant folded (`p+(h&M)+4-10`, every reassociation spelling, two pointer statements) | 213 | retail's (lea -6, 1 B longer) |
| Per-arm pointer with an `(unsigned short)` cast barrier on `(h&M)+4` | 218 | retail's, plus an extra movzx |
| Named integer `n` used in the address (c1: arm1 or both arms; any type except `__int64`/`ushort`; `p-10+n`, `[n-10]`, `-5` forms) | 665 | the 814 B layout |
| Size phi (`usable` if/else or `?:`, chunk base, named pointer or not) | 605 | the 784 B layout |

A dead named `n` (assigned but unused) stays at 213, so the flip needs the
named integer's value to reach the address. The forms `n = h&M; p+n+4-10`
(638), `char *n = p+(h&M)` (578) and `unsigned n = (unsigned)p+...` (640) are
further attractors.

## Inert in every world (bank, c1, size phi)

Each factor below leaves every world at the nd it already had:

- **Function shape (g48, 360 compiles):**
  - `extra` and `backupLength` unified into one variable, as in WB;
  - the flag `|= 4` inside the loop with `break`, as in WB;
  - `if (backup) memmove`;
  - `do`/`for(;;)`/`while(true)`;
  - `mallocBackup(extra+2)` versus a `flags` parameter with `size += 2` inside.
- **WB-faithful retry loops (g55):**
  - `if (m_next != &head) purge(); else return 0;` for the backup loop;
  - `for(;;){ result=...; if (result) {...; break;} ... }` in three spellings for the realloc loop.
- **goto-formed retry loops (g60):** for either loop.
- **Inline signature (g50, g56):**
  - `if (p)`, `if (p != 0)` or an early return (612 for c1);
  - `0`, `(unsigned short)0` or `0u`;
  - plain, `inline` or `__forceinline`;
  - `void *`, `void *const` or `char *p`;
  - the param as `const unsigned &`, `int`, `unsigned long` or `const`;
  - an explicitly hoisted `request = extra + 2`.
- **Store through a helper (g58):** `setLength(p, 0)`, member or static, with a `ushort`, `uint` or `const ushort &` length param. Each world keeps its nd.
- **Inlinee written by hand into the loop (g57):** with locals at block scope or function scope.
- **Meters (g49, g53):** 0-65 dead `int` locals at function top, 0-39 inside the inline, 1-39 `void *q = 0` locals. c1 stays 665 throughout, so this is no symbol-count phase effect.

## WB evidence (target facts from worldbuilder.exe)

- WB 0x70c940 (vtable slot 34, +0x88) is the debug `MallocInternal(size, flags)`.
  - `local_8 = flags & 0x80000000` is a dword, not a bool; when it is set, size += 2.
  - It calls 0x704410 (the base MallocInternal).
  - The trailer is `pChunk = p-8`, `nSize = [pChunk+4] & M`, `pLen = pChunk+nSize-2`, `*pLen = 0`, with three named locals.
  - WB has no mmapped (bit 2) branch: it is an older or other-config PPMalloc. Retail adds the `+4` arm.
- WB 0x70be40 (realloc) has one length variable (no separate `extra`).
  - The `|= 4` happens inside the loop on `pChunk = backup-8`.
  - `if (backup) memmove`.
  - A hook callback block (+0x4b0) that retail lacks.

- **Static inline accessors (g61):** `chunkSizeOf`, `chunkIsMapped` (spelled `!= 0`) and `usableSizeOf`, used for a pointer phi, a size phi and an end phi.
  - The per-arm pointer forms give 225: the bool helper costs a `shr`/`test dl,1` and folds -6.
  - The size and end phis give 615-633.
  - `usableSizeOf2` with `n += 4` gives 459.
  - None keeps both the exact trailer and the allocation.

## Untried

- An accessor set that returns `h & 2` as an int, not a bool, so the `test cl,2` stays.
- c2 source-level weighting: the flip needs a named integer in the address. A different statement boundary that stops the `+4` folding without a user symbol is the remaining kind of lever. Neither the ushort cast nor `__int64` keeps the bytes.
