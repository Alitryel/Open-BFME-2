# Short-path reference discovery, 2026-10-24

BFME2 baseline5c7cb7f78b; verified pinned BFME1 donor32774ab03393709a7f14331ba8d98d281a55ffd9.
WorkerD:/b2/w04, independent caches; native pinned MSVC7.1, ordinary donor compile flags.
No source/pin/ledger/verifier changes were made by this discovery pass.

Fresh BFME1 scan:38,788 donors,5,525 exact placements all claimed,5,516 independent
boundary controls,617 near comparisons. Ranked and near queues each serve0 free
bodies. The named lift lane completed with its full--limit1000 listing.

A fresh normal ZH compile under the short worker root built919 of987 TUs and failed68.
This replaces the earlier long-root311-object population for this worker and resolves
the previous WindowsMAX_PATH _prolog.h failure class. The68 remaining failed TUs are
listed in failed-tus.txt; diagnostics show genuine obsolete symbols, unavailable API
or SDK declarations and source/platform incompatibilities, not the old path-length
failure. No failed object from an older input population was retained.

Fresh matching examined27,008 functions from919 objects:1,112 exact-unique claimed,
798 exact-multi,4,749 near,4,738 no-needle and15,611 no-placement. Packets produced0
bodies/0bytes;242 addresses were already ledger-owned. An empty placement queue
exhausts this search under these pinned inputs, not all source-based reconstruction.

The required explicit nonrecursive official donor fetch found origin/master at
27429e78c24577effa2f34df3e37e591876310f5, ahead of32774ab033. The delta spans230
files, including source/header/tooling changes and a cross-repository reference.
The pinned checkout was preserved clean. No nested references were initialized,
no pointer was silently advanced, and no successful freshness marker was written.
A donor-pointer update remains pending paired full-byte verification against the
previous inputs and review of applicable changes, under AGENTS.md. These sweep
results certify the old verified pin only; they do not certify the newer donor.

Machine-local reproducible logs and objects remain under w04/build/reference-*
and w04/build/spike_zh. The published link index fetched for actual recovery work
is2026-10-24 16:05 at7e43384268, with347 objects added to the private object store.

Separate actual source recoveries from this seat are the195B Apt array cleanup and
four110B Apt XML predicates, each in its own normal-hook commit. They remove inline
assembly from already-counted C++ units and add zero aggregate C++ coverage bytes.

## Targeted audit of the newer donor's eleven remaining CRT helpers

Read-only comparison of32774ab033 and official27429e78, without advancing the checkout.
Unlike the generic donor queue, this inspected already-claimed ASM/lib providers directly.
The corresponding donor rows at27429e78 are unchanged from32774ab033:

| Helper | BFME1 RVA | Bytes | Actual provider at27429e78 |
| --- | --- | ---: | --- |
| __allmul | 009F7210 |52| libc.lib llmul.obj |
| __aulldiv |009F7BC0|104| libc.lib ulldiv.obj |
| __alldiv |009F70E0|170| libc.lib lldiv.obj |
| __aulldvrm |009F7C30|149| libc.lib ulldvrm.obj |
| __allshl |009F7CE0|31| libc.lib llshl.obj |
| __aullshr |009F7D00|31| libc.lib ullshr.obj |
| __ftol2 |009F6E38|117| msvcrt.lib ftol2.obj |
| __SEH_prolog |009F7E88|59| libc.lib sehprolg.obj |
| __SEH_epilog |009F7EC3|17| libc.lib sehprolg.obj |
| __chkstk |009F6C60|61| StackProbeBodyThunk.cpp: naked __asm/_emit placeholder |
| __EH_prolog |00B028A4|31| ?d_00b028a4@@YAXXZ in game/gen_asm/d_00aa0d0d.asm |

These extents total822B, the BFME2 prebuilt-helper population under investigation.
The chkstk file's legacy notes say C++ ICF alias, but inspection shows a naked
raw-byte emitter; it is not eligible authored C++ under BFME2's anti-lift policy.
Its added donor log entry70c87eaa records a two-label __chkstk/__alloca_probe
verifier-admission issue when replacing that placeholder with the prebuilt member,
not a C++ code-generation solution.

New donor commit9d741c60 likewise removes the naked ArrayNewHelperBodyThunk.cpp
emitter and binds the vector-constructor iterator and two unwind funclets to
libc.lib members. It supplies no authored C++ helper or new compiler recipe.
The nearby11B startup-initializer recoveries are ordinary data publishers, not
implementations of any of the eleven helpers listed above.

Targeted log/diff searches for those helper names, d1Binl, shrink-wrap and intrinsic
recipes found no new applicable codegen recipe in32774ab033..27429e78. The checked
build/flag/toolchain inputs have no delta. In particular the archive Git blob IDs
are identical in both revisions: libc.lib1ee4c7cf8dca8312e00881b755ea1c4ecf0322b1;
msvcrt.lib9b60aa9f2eff1d1d8cbafa0f8d09d273ff4b2d73.

Conclusion limited to this audited revision range and helper population: no new
authored C++ provider or compiler recipe unlocks BFME2's remaining822 prebuilt
bytes. The independent locally banked compiler/ABI prerequisites still apply.
No decoder implementation source, new pointer, gate or baseline was used/changed.
