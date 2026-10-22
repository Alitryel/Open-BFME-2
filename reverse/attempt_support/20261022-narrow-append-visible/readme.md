Narrow append provider handoff
=============================

The formerly claimed 0x179B0 provider unit became available, reopening the
20261020 visible-body hypothesis in stlport_narrow_string.cpp. Inputs:
BFME2 cfb8dbcc0a, BFME1 retained at 37c3022de1, published census 08160bc2c9;
MSVC 7.1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC.

An explicit inline member specialization requires `template<> template<>`.
MSVC rejects the single-template spelling with C2768. The visible definition
avoids the earlier declaration-only C1001, and all 19 existing ledger rows
remain exact. However, the emitted PBD append is 243 bytes versus retail's
254, and the legacy consumer cohort remains at zero linked bytes.

The remaining ABI and visibility differences are concrete. Retail calls the
static _STL::allocator<char>::allocate(unsigned, const void*) at 0x307F0;
the actual header exposes const-member allocate through undefined
__malloc_alloc<0>. Retail also inlines deallocation before calling free at
0x30830, whereas this earlier unit must declare _String_base's
_M_deallocate_block external for its other matched rows (call to 0x142D70).
The later exact owner uses its own static allocator view and visible
deallocation. Copying its control flow does not reconcile those shared ABI
and inline summaries. No alias, pin or second private owner was added.

The retained patch is diagnostic, not a matched 254-byte body; no partial
bank is claimed. The source was restored and passed its original 19/19 gate.
All 20 file/RVA claims were released. No linking gain is credited.

Do not repeat unchanged declaration-only, extern-template or visible-body
transplant trials. Resume when a canonical static allocator/provider ABI
and scoped deallocation visibility can preserve the 19 existing rows.

Local diagnostics: build/link-seat-20261022e/append-visible.diff,
append-visible-after.log, append-visible-gate.log and append-visible-gate2.log.
The patch retained beside this note is sufficient to resume. Time: 8 minutes.
