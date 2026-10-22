# Farm-library data bindings, 2026-10-22

BFME2 input 21387ea4c9; published census ae3b3e68e2 (11:05 UTC).
Rva004EA420Init.cpp originally references undefined g_00E04490 and g_00E04494.
The target accesses the string word at VA E04490 and the vector words at
E04494/E04498/E0449C. Existing data owners are g_Va00E04490 (4-byte storage,
constructed as AsciiString in Rva007AB85CAtexitInits.cpp) and
AIEconomyBuilder::m_farmList (AIEconomyBuilderFarmLibrary.h, storage defined
in Rva007B6880Thunks.cpp). The initializer now uses those same owners and
casts the existing storage to its established local views. The shared header
records independent target and WorldBuilder evidence for the farm list.
No additional data, pin, private class or alternate name is introduced.

Same-index current-object legacy preview: 0 -> 206 authored nonpadding bytes,
1/1 unit links. Normal byte gate: 3/3 rows exact, zero skipped string/import
references. Strict reusable byte receipt passes; closure was not checked.
EH graph EXACT; class gate, undeclared-definition check, data checks and
converged-data check pass (10 converged addresses, no second names). These
are self-strict byte checks plus a legacy link preview, not closed-strict or
actual placement gains. Scratch logs: build/link-seat-farm-{before,after,
byte,strict}.txt. Cause sweep found the other farm consumers already use the
canonical owners; only this initializer retained the two undefined aliases.

## Reverted trials

Rva0026E7C8Xfer.cpp (388 authored B): the temporary derived record's destructor
COMDAT differs from the flat +8 member view in Rva003328EDRva003328ED.cpp.
A dllimport/forceinline empty destructor preserves 4/4 rows but emits an
unresolved imported destructor in cleanup; plain forceinline preserves bytes
but retains the conflict. Reconcile the class contract before another trial.

stlport_wide_ios_imbue.cpp (238 B): declaring the rowed char-string assignment
specialization removes the inline self-check/range call (-15 B); importing
a forceinline equivalent materializes a dispatch-tag store (+5 B) and swaps
locale homes. Requires template/compiler-summary reconciliation, not merely
binding a declaration. Both candidates reverted; both blocked verdicts are in
the attempt log and their claims were released.

## Reference freshness and inherited work

Verified BFME1 pointer remains 37c3022de1ab944c7ffe536440d637dc8199091c;
official master fetched at 42bba2ddbd5cb895d99293583891d3b7315fa49e. The
old-pointer full byte baseline waited on the host compiler lock without
compiling for about twelve minutes; only this seat's waiting build was
terminated. No pointer update or success receipt was written. Freshness is
still due. Changed donor sources were inspected; no moved headers/inputs were
silently substituted. The prior layout migration remains applicable.

Current-object probing found 89,022 B already link from other contributors'
repairs; these are not session gains. ControlBar destructor also links when
its already-repaired opaque provider is refreshed. The published census is
older than those sources. rehome_rows cannot run without its census.log input;
no census or maintainer-only runner was started to recreate it.
