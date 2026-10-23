# 0x0000B3C0 ~_String_base<char> COMDAT-copy handoff (link lane K)

Symbol: `??1?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAE@XZ`, retail 63 bytes at 0x0000B3C0,
rowed in `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_base_dtor.cpp` (census verdict
"unknown", digest f8a890dd84b6). On census 2026-10-19 13:17 (8eecc93d07), 72 other units emit a
different copy, which loses: 55 emit the 14-byte frameless body (digest 07644a8ba00d), the rest bind
private free spellings or emit a `jmp _M_deallocate_block` thunk.

## Target facts

- Retail body: an /O2 inline SEH frame (`push -1 / push handler / mov eax,fs:0`) with one unwind
  state (0) stored at [esp+0x0C] and never lowered. The funclet destroys the allocator proxy at
  this+8. The straight-line path is `if (_M_start) free(_M_start)`.
- In the loser units, every matched caller inlines the destructor as the 13-byte sequence. The
  out-of-line copy is referenced only through .debug$F and other emitted COMDATs. No matched row
  calls it out of line.

## Effective flags of the 72 losers

Taken from `build.compiler_command`, which adds directory-profile flags not on the `// cl:` line:
64 units are /O1 (/EHs, /EHsc or /GX), 8 are /O2 /EHsc. None are /O2 /EHs.

## Trials (scratch probes plus one real unit)

1. Flag and header sweep with stock STLport headers: /EHs, /EHsc, /EHa, /O1, /Ob0, /Ob1,
   bfmealloc on or off, _STLP_USE_MALLOC. It always gives the frameless 14- or 15-byte body
   (or a 5-byte jmp under /Ob0).
2. A decl-only specialization of the destructor stops the emission, but callers then call it out
   of line (Rva0055C9A0Write.cpp, WideCharStringToMultiByte.cpp): byte gate FAIL.
3. A `template<> __declspec(dllimport) __forceinline` destructor specialization, also tried
   together with ~basic_string: the copy is gone, but ~basic_string stops inlining in matched
   callers (FAIL, or C2908). Plain `__forceinline` keeps the bytes but still emits 07644a.
4. **Opaque proxy destructor** (new hypothesis): a TU-scoped full specialization of
   `_STLP_alloc_proxy<char*, char, allocator<char> >` whose destructor is
   `if (0) ::free(_M_data);`, as in the owner unit.
   - /O2 /EHs probe: the copy is byte-identical to the owner's f8a890dd84b6, so the hypothesis
     reproduces retail's body.
   - /O1 probe (the 64-unit majority): the frame becomes the 43-byte `__EH_prolog` form, not
     retail's.
   - /O2 /EHsc probe: still frameless, because under /EHsc extern "C" free is nothrow.
     Redeclaring free `throw(...)` after <stdlib.h> does not change that.
   - Real unit stlport_money_put_long_double.cpp (/O2 /EHsc with its own `throw(...)` free):
     the copy becomes f8a890dd84b6. But the inlined destructor in the matched
     `money_put<char>::do_put` now has an extra unwind state for the proxy member (state store
     `c6 44 24 5c 02` against retail's `00`), so the row FAILs. Reverted.

## Verdict

The trials refute a TU-scoped source fix. One definition cannot give both a framed out-of-line
copy and inlined callers with no proxy unwind state, and retail's matched callers prove the
latter. Retail's framed copy came from a TU whose own callers did not inline the destructor (the
owner unit's shape). The losing copies are therefore retail-plausible per-TU variants that the
retail link discarded, the same class as RefCountClass and `??_H`.

Next steps:
- Tooling lane: excuse a copy when an identical-to-owner copy precedes it in link order.
- Or move these units' string-using bodies so the destructor becomes out-of-line there.
