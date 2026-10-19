# Native constructor cleanup link repair

Four existing matched units gain **314 authored retail bytes in the legacy
link preview**. No new C++ coverage, pins, aliases or baseline edits.

| Unit (under Code/GameEngine/Source/) | Before | After | Authored bytes |
| --- | --- | --- | ---: |
| Common/Rva00362DBDCtor.cpp | unresolved nonvirtual Rva00362D6C dtor | LINKS | 89 |
| Common/Rva000E59D3Ctor.cpp | unresolved Holder14 dtor | LINKS | 102 |
| Common/Rva003733C8.cpp | unresolved private secondary dtor | LINKS | 73 |
| GameLogic/Object/Update/Rva00253510Ctor.cpp | unresolved DieMuxData dtor | LINKS | 50 |

Paired `python3 tools/link_check.py --paths-from build/link-seat-dtor-paths.txt`
previews use the identical 123-unit scope and census index 1a1c90e405
(2026-10-18 17:31): 70/123 clean, 9,511 B before; 74/123 clean, 9,825 B
after. Earlier repairs already current in this scope are excluded from the gain.
The index and committed census/status are unchanged. Closed-strict linkage and
runtime behavior are not measured by this preview.

## Independent target evidence

* BuffManager 00362DBD constructs nine 44-byte elements at +8, and its exact
  native unwind graph uses the virtual destructor at 00362D6C. That destructor
  and the element constructor 00362D25 are already rowed under Rva00362D6C.
  Give the consumer the same virtual destructor declaration; subtract its
  four-byte vptr from padding to preserve the proven array stride.
* The floor-buffer owner constructor 000E5A47 has a one-word owning handle at
  +14. Its native action 007633F6 selects 0017098D, whose complete body loads
  the pointer, null-tests and tail-calls rowed TextureClass::Release_Ref at
  0061ED10. The already rowed paired destructor 000E59D3 independently supplies
  the same member cleanup. Implement it inline without inventing a dtor pin.
* Constructor 003733C8 has the Snapshot subobject at +0C (BBB554 table) and
  native cleanup through Snapshot::~Snapshot at 0049B47C. Replace its private
  secondary view with the existing shared header. Keep its other base unchanged.
* DestroyDieModuleData constructor 00253510 has native unwind action 00771C42:
  load saved this, tail-jump 0049B47C. This cleans the Snapshot base at +0,
  not the opaque DieMuxData member at +8. Use canonical Snapshot inheritance,
  retaining unused word +4 and 48-byte member +8. Remove the false member
  destructor declaration. Its application identity remains based on the
  previously recorded native factory relationship, not the shared vtable.

`./build.sh` verifies all 8 existing rows in the four units, including two
renumbered funclets. `tools/eh_verify.py` reports EXACT for all four native
parent EH graphs. Frozen-definition checks and `git diff --check` pass.
Bounded `link_check.py --prepare-current` supplies strict reusable receipts
for these explicit providers; this is self-strict compilation, not closed
provider resolution. Normal commit hooks rerun the upstream acceptance gates.

## Donor review and limits

Reviewed official BFME1 master 8619c4c56d73cfeb7beb7d7dd87e4fbde47b01da,
including native destructor ownership repairs af83a425, 06a23066 and 4b285d7b.
Those particular SurfaceClass/UnicodeString changes are not transferred here;
this sweep uses independently verified BFME2 row names and cleanup graphs.
Build inputs remain the last verified BFME1 pointer
64d369b90170b7e9ec917d646f020b11f13eb0d5. Its pending freshness update is
blocked by the already recorded BC6F20/C77BE8/C7A630 DIR32 ownership conflict
in ../bfme1-freshness-20261018/readme.md; no successful-check stamp is written.
