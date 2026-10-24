# CRT ehvec* members: native __thiscall callbacks via /d1Binl (2026-10-24)

Resolves the blocker recorded for `__ArrayUnwind` 0x006290B2, `??_M` 0x00629110,
`??_L` 0x00629512 and `??__C` 0x006299C4 (see `array-unwind-clang23-20261023/`
and `family-compiler-prerequisites-20261024/reference-and-arrays.md`).

Target fact: the archive names mangle each callback as `P6E`, a free `__thiscall`
function pointer. Pinned VC7.1 c1xx rejects that type with C4234. Suppressing
the warning demotes the type to cdecl (`P6A`).

Compiler fact, tested in isolation with `build.compiler_command` plus extra flags
on `typedef void (__thiscall *Dtor)(void*); void __stdcall F(void*, Dtor)`:

| flag          | result                                          |
|---------------|-------------------------------------------------|
| (none) / -W1  | C4234 error                                     |
| `/d1Binl`     | compiles; `?F@@YGXPAXP6EX0@Z@Z` (genuine P6E)   |
| `/d2Binl`     | C4234 error                                     |
| `/d1thiscall` | C1007 unrecognized flag                         |

With `/O1 /G6 /MD /EHsc /d1Binl`, the plain `__try/__finally` iterators with a
`success` flag compile to retail's legacy `__SEH_prolog`/`__SEH_epilog` frames.

- `??_M`, `??_L` and `??__C` matched on the first trial.
- `__ArrayUnwind` first came out 88 B against retail's 94 B, with a frame of
  0x10 against 0x14. The inlined filter needs a named record local
  (`EXCEPTION_RECORD *record = exception->ExceptionRecord; switch (record->ExceptionCode)`)
  before it matches. The same filter also stays exact standalone (18 B, 0x006290A0).

Sources: `Code/Libraries/Source/CRT/VS2003/ehvecdtr.cpp` (renamed from
`array_unwind_filter.cpp`; its emission anchor is no longer needed), `ehvecctr.cpp`
and `ehvccctr.cpp`.
