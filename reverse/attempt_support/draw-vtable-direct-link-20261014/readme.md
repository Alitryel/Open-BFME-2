# Draw-constructor vtable alias repair

BFME2 source base: 8b339678e4 (the full hash is in object-proof.json).
Replace ten vtable aliases in four existing constructors with direct
`__identifier` references to the exact same decorated names the old
`/alternatename` directives selected. The aliases are no longer declared,
referenced or emitted as linker directives; their ten keyed hatch-baseline
entries are deleted. No other baseline entry changes.

Consumers:

- W3DSailModelDrawCtor.cpp, RVA 0x000D078F, 60 bytes: two aliases removed.
- W3DHordeModelDrawCtor.cpp, RVA 0x00078A82, 68 bytes: two aliases removed.
- W3DQuadrupedDrawCtor.cpp, RVA 0x000CA0A4, 42 bytes: three aliases removed.
- W3DSupplyDrawCtor.cpp, RVA 0x000CAE43, 56 bytes: three aliases removed.

These are unchanged vtable dependencies, not new class or folded-table
identity claims. The provider name Rva000CA119 and its layout remain opaque.
Rva000C79C9Derived.cpp defines the five Rva000CA119/Rva000CAEC6 vtables;
W3DTankDrawConstructor.cpp defines the DrawInterfaceA table used by Sail
and Horde. Both provider sources and objects are unchanged. The direct
references retain the old aliases' selection, including any existing
provider incompleteness. No headers, compiler flags, function extents,
function/data rows, pins or implementation behavior change.

Acceptance:

- Before and after bounded `link_check.py --prepare-current` pass 10/10
  matched rows across these six units with strict reusable receipts. The
  independent normal byte gate also passes 10/10; zero string/import
  references are skipped or baselined, and the one float literal verifies.
- Object proof compares every non-debug/non-directive section's raw bytes,
  flags, size and relocations, plus every external definition and canonical
  undefined reference. They are identical after replacing each old alias
  name with precisely its original target. Ten DIR32 referents change names,
  with no changed instruction/data bytes or other referents. Provider
  objects are byte-for-byte unchanged and define all six distinct targets.
  Strict receipts are current for all six units.
- EH verification: EXACT 1; zero non-exact, baseline or missing objects.
  Data checking: zero findings. Converged checking: eight addresses, zero
  second names or unjudged rows. Class and declared-definition checks pass;
  placement rescan finds zero additional bodies or pins.
- The supplied index is measured at cb660e4d97, 2026-10-13 04:02 UTC, with
  SHA256 4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e.
  The committed status at 67e1365aa9 serves discovery only. Both local
  previews use the same supplied index and refresh these six objects in
  memory. Before and after: Sail LINKS with 60 own bytes; Quadruped LINKS
  with 42; Supply LINKS with 56; Horde and both providers remain blocked.
  The current cohort total is **158 -> 158 legacy preview linked bytes**.
  The printed census-relative 98 -> 158 is an earlier repair, not a gain
  from this change. New authored matched C++ bytes: zero.
- Verified improvement: **ten fewer alias hatches**, with byte identity and
  unchanged local link behavior. Strict receipts prove current bodies,
  not self-strict LINK closure or closed-strict gains. No such gains are
  claimed, and no full link/census/nightly/smoke runner was started. Census,
  committed status and history are unchanged.

Remaining legacy blockers: Horde's g_00BC68F0 primary-table definition;
Rva000C79C9Derived's base destructor and two f2 methods; W3DTankDraw's
W3DScriptedModelDraw destructor and its a/b methods. These pre-existing
dependencies were not reconstructed or retried. The global hatch updater
also refuses 1335 pre-existing growth keys outside this cohort; only this
repair's ten existing keyed entries were removed, without admitting any
growth or changing the verifier.

Donor review: retained clean verified BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master fetched to
c6faaa15c8fdbaf27e91e1b4902d0fc065034f75. Reviewed that revision's
game/Libraries/Source/WWVegas/WW3D2/MaterialInfoDtor.cpp, whose direct
decorated VectorClass vtable reference supplies the applicable technique.
Also reviewed donor linking repairs 92a8d854 (canonical debug global) and
3978ec8e (duplicate progress-bar body); neither changes these dependencies.
No donor body, layout or target address is imported. BFME2 provider and
object evidence above is independent. The overdue same-revision old/new
full-byte BFME1 freshness comparison remains outstanding after the prior
5882-stale-TU/shared-compiler blocker. This repair retains verified inputs,
does not advance the pointer, and does not write a freshness success stamp.

Discovery: repair_queue.py link; link_rank.py help, --top 15, --kind A and
--kind D; current sources and prior attempt evidence. name_globals.py
--dry-run on RebuildHole/RunOffMap/ArrowStorm/BoatWake finds zero supported
rewrites, without treating the wider lane as exhausted. All four consumers
were claimed before edits. Their aliases form one compatible dependency
repair; all their matched bodies are retained and verified. Normal commit
hooks enforce the remaining acceptance checks. Reproducible scratch proof
and snapshots are retained in build/draw-vtable-direct-link-20261014.
