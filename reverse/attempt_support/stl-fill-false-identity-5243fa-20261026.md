# Retract the false STL fill identity at 0x005243FA

Inspected revision: `a4e418bdf8`, based on master `d0aba6dd78`.
Date: 2026-10-26. Scope: the entire served
`Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005243FA.cpp`.

## Target evidence and the conflicting claim

The 27-byte native wrapper at 0x005243FA calls 0x0052408B at 0x0052440B.
Its bytes are
`558bec518d45ff50ff7510ff750cff7508e87bfcffff83c410c9c3`.
The native callee is 179 bytes, not a fill loop: it searches eight-byte
records and calls the existing 0x00523EFF equality predicate seven times,
at 0x005240A5, 0x005240BA, 0x005240CB, 0x005240DC, 0x00524103,
0x00524114 and 0x00524125. The predicate compares an integer and StringBase.

The served file instantiates `stable_sort` over an invented one-byte
`Rva005243FARecord`. Its rowed `uninitialized_fill_n` wrapper has the same
masked 27-byte shape, but calls an emitted 29-byte `__uninitialized_fill_n`
byte-fill helper. That helper has no relocations and bytes
`8b4c240885c98b4424047e1085c074088b54240c8a128810404975f0c3`.
The helper's pin to 0x0052408B therefore asserts the wrong code identity.
The old byte gate passing this wrapper does not establish that identity.

The correct wrapper already exists as `?Rva005243FA@@YAHHHH@Z` in
`Code/GameEngine/Source/Common/Rva0052A22CForwarders.cpp`. Its relocation
at offset 18 names the existing 179-byte `Rva0052408BFind` provider in
`Code/Libraries/Source/WWVegas/WWLib/stlport_hero_integer_vector_tree.cpp`.
That provider has seven references to the rowed equality predicate in
`Code/Libraries/Source/WWVegas/WWLib/Rva00523EFFEqual.cpp`.
`Rva00524477Dispatch.cpp` consumes the wrapper's EAX result. These current
objects and the native call graph agree. The current TU map already names
the retained owners; no row move or TU-map rewrite is needed.

This establishes a false duplicate claim, not a newly recovered source name.
The original algorithm and record names remain unknown. STLport is donor
evidence for the rejected instantiation, not proof of BFME 2 source identity.

## Scoped repair

- Retract the false `uninitialized_fill_n` row and its now-orphaned source.
  Keep the existing native wrapper, its pin, the find provider and predicate.
- Remove only the false helper's pin at 0x0052408B. No new pin, alias,
  source, name or code body is introduced.
- Record the retraction in `reverse/deleted_rows.csv` so union merges cannot
  silently resurrect it.
- Tighten exactly four entries produced by `hatch_counters.py --update`:
  the removed pin and the file's three pragma-optimization entries.
  Preserve unrelated register entries rather than bundling earlier upstream
  cleanup into this change. No data, identity or header debt key belongs to
  this source.

Independent read-only review scanned all 23,304 cached COFF string tables
without errors: `Rva005243FARecord` appears only in the discarded object.
The historical 47e030bafc index likewise assigns all 55 record-specific
external definitions to that object, with no incoming COMDAT consumers.
Its two generic COMDAT families have other providers (1,229 placement-new
copies and 24 `__gcd<int>` copies); it was not first in either indexed order.
Those are historical provider facts, not a fresh final-image selection claim.

## Verification

Before removal, normal `build.sh` passed 21 rows in five sources. Afterward,
normal `build.sh` passed all 20 retained rows in four sources. No retained
source was edited. Frozen-file checks passed before editing, and the
retained forwarder has no unrowed defined function.

The current-object ordinary link preview against fetched index
`d1f046749a` (2026-10-26 13:18) reports all four retained units LINKS:
forwarders 65 bytes, find/tree unit 1,331, predicate 35 and dispatcher 99;
1,530 -> 1,530 authored nonpadding bytes. This is preservation, not a
new linked-byte gain. The historical failed source is removed because its
identity was false, not repaired into a distinct additional native body.

`check_csv.py`: 98,270 function rows, 15,657 symbols and 2,217 data rows.
`pin_consistency.py --check`: zero new, baselined or stale violations.
The two native addresses retain exactly one matched owner each. The deleted
27-byte duplicate contributes no unique coverage; no native byte is lost.

## Publication cache repair

The preceding publication passed the repaired Windows stdin worker startup
but refused three identity retirements because participating provider objects
were stale. The named stale dependencies included ICoord3D.h after checkout
normalized its line endings. A read-only scan found 337 stale providers.
Two ordinary `build.sh` chunks verified 2,708 rows across all 337 sources,
with 62 data rows; the next scan found zero stale sources among 22,812
compiled C/C++ providers. All three previously refused identity verdicts
then passed, with no removed key still found. No cache receipt was forged,
no checker was weakened, and no running build or gate was relaunched.

The full publication hook remains authoritative for the outgoing batch.
Census and NOT OURS changes are not claimed by this repair.

## Batch path and coverage audit

Immediately before publication, the PR-local audit against d0aba6dd78 covers
all eight deleted sources: seven approved INI donors and the rejected STL
instantiation. The 65 tracked mentions are provenance comments, historical
census/attempt evidence and the updated target/obstacle entries. No active
tool, hook, workflow, include or source-register consumer still requires a
deleted source. The earlier supplementary audit of upstream deletions remains
separate and retains its documented pre-existing queue/map findings.

`python3 tools/progress.py origin/master` after the retraction reports
BYTE-MATCHED 100% and C++ exact 7,984,346 bytes, delta +0. The official
d1f046749a census remains LINKING 7,322,361 / LINKED 7,567,229 bytes.
This is debt/identity cleanup with full unique coverage preserved.
