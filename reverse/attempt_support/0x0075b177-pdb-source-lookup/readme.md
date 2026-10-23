# Banked whole pdblkup.obj reconstruction

The complete independently authored three-body C++ draft is banked at
`reverse/attempts/0x0075b177.cpp` by re_log (actual filename is tool-owned).
GetImageInfo849B and GetPdbDll312B are strict full-byte matches. The847-byte
_RTC_GetSrcLine has native size, frame, branch layout and all but four bytes;
two independent three-byte argument loads are commuted. Do not publish this
partial whole member or claim its unused private helpers as completed recovery.
No production Code source or ledger row was changed and coverage gain is zero.

Retail instructions, original COFF identity/relocations and native CodeView
provide the layout and ABI. ImageInfo is32B with fields sig0,BaseAddress4,
BaseSize8,hndl12,img16,sectHdr20,imgName24,next28. Native local source-module
header and start/end structs are4/8B. Native PDB interfaces are cdecl, Win32
lookup interfaces stdcall; unused PDB validation outputs are four-byte unsigned
longs, not inferred GUIDs. Public SDK declarations are used through actual
headers; psapi function declarations are temporarily renamed on include to
permit original private function-pointer names. No Microsoft implementation
source was read. Native cache misses, partial-init paths, inclusive image range,
strict section start test, cleanup/leak behavior and unsigned line-distance
selection are preserved without safety fallbacks.

The native compiler version is13.10.3077, matching the local compiler. Shared
G5/G6/GB,O2/Os,Ob2,Oy-,Op and intrinsic profiles did not resolve the last loads;
G7 changes alloca alignment and breaks a sibling, Og-/Oa diverge broadly.
Changing simple zero-store order/return declaration, register/const hints and
conditional spelling did not resolve it. Do not replay these unchanged trials.
Named parser-table views and the lifetime of the WORD DBI output were the
successful shared shape discoveries; the bank contains that final form.

Upstream pointer64d369b9 still keeps all three bodies prebuilt. The old clean
a0e8f345 checkout was advanced only to the committed pointer after verifying
cleanliness and ancestry; toolchain/reference inputs are unchanged between them.
The latest fetched BFME1 master was ahead of that verified pointer and was not
substituted. Claims are released when banking. Revisit with a new hypothesis
for the final parameter-load ordering; inspect native-types.txt and the exact
mismatch offsets in verification.json first. Evidence alone is not progress.
