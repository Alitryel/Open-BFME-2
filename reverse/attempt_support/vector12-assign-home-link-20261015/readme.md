# Vector assignment ownership repair

Source base: 1a9bceaf9cb5584e001bd457e53beef266cb84c2.
Local index: 19a2565407, 2026-10-15 09:33; original census
5986a99448, 2026-10-15 04:52. Index SHA256:
a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3.
The committed link_status.csv is discovery evidence, not this measurement.
No census, index, status/history, baseline, pin, flags or shared header changed.

Rva0035149F.cpp owned the 209-byte vector assignment at 0x0035149F.
AIGroupMoveFormation.cpp already emitted a retail-equal inline definition,
needed visibly by its matched formation caller. Rehome the row using
add_match --replace-existing and delete the redundant strong definition and
its unused allocator/helper declarations. Keep the eight-byte forwarding
wrapper and its original linker pragma. The formation source is unchanged.
No emitter, alias, pin, annotation or other escape hatch is added.

Target facts: native 35149F..351570, RET4; size and capacity calculations
use 12-byte elements; allocator 0x000E016A, copy 0x000B6569, uninitialized
copy 0x00346C2D and free wrapper 0x00030830. Call sites include 0x00351606,
0x003530B0, 0x00353198 and 0x0036EE46. Existing Rva and BfmeE12 names remain
address-derived/stand-in identities. No semantic class identity or full-layout
claim is introduced. Both old emitted copies independently pass retail byte
and relocation verdicts. Their free relocations use the two existing ledger
spellings at 0x00030830; all other relocation names agree. No donor source
or layout is imported.

Acceptance:

- Before and after link_check.py --prepare-current for the two claimed units
  passes all three rows with strict reusable receipts. The baseline source
  was also freshly recompiled through this command. Normal ./build.sh passes
  3/3 rows and all four float literals; no string or import references skipped.
  add_match independently verifies the two formation-owned rows.
- Scratch snapshot.py refreshes the same index in memory with both before
  objects, then both after objects. object-proof.json records the source,
  object, receipt and index hashes. The asserting proof verifies that exactly
  one redundant 209-byte code section disappears. The wrapper bytes and
  relocations remain identical; all 82 formation COMDATs and 95 nondebug
  sections are unchanged, including EH symbol references and directives.
- The removed function's two compiler-generated alternatename directives
  disappear from the wrapper object. A fresh baseline build confirmed their
  origin; both exact directives remain in the unchanged formation object.
  The existing explicit pragma and default-library directives are unchanged.
  No binding is lost from the paired cohort. All other retained nondebug
  sections and external bindings are unchanged.
- Both assignment duplicate findings disappear, with no added finding.
  The standalone local link CLI agrees: 0/2 -> 1/2 clean; legacy LINKED
  0 -> 8 existing nonpadding retail bytes. Wrapper ownership changes from
  217 to 8 bytes, formation ownership from 2410 to 2619. Total matched and
  authored C++ bytes do not grow.
- The explicit two-unit cohort is self-strict current. This is a legacy
  local prediction against unchanged external providers. Closed-strict
  closure, link.exe placement and a fresh census gain were not measured.
- EH: one row EXACT, no missing objects. Frozen definitions, canonical classes,
  new COMDAT variants, converged data (eight addresses), shadow data, CSV
  and whitespace checks pass. Placement sweep: zero bodies and zero pins.

Formation still has unresolved Pathfinder::adjustDestination; duplicate
_Construct<Coord3D>, AIGroup::getCenter and AIGroup::rotateOffset; and eight
independent COMDAT findings enumerated in object-proof.json. These are
identical before and after. No gain is attributed to that unit.

Reference review: retained clean verified BFME 1 gitlink/checkout
 a7c38d3b2597121f178ab5190b3062478823257d. Inspected repair
4966496c5ae401ec877a044e1ae6dd04f9d9f65c directly: suppression of surplus
emission while retaining matched callers is applicable as an ownership
principle; its AsciiString code is not imported. Earlier shared-library
review is recorded in adjacent S5/debug-hash repair evidence. Official master
was fetched to fd65b3542571f27ce895f85c62cf82d2107d82ee. Updating remains
blocked by another worker's reference/open-bfme-1 file claim and the outstanding
full old/new byte-gate comparison documented in
../unicode-comparator-link-20261014/readme.md. Verified inputs and the old
freshness stamp are preserved; no successful freshness update is claimed.

Selection used repair_queue.py link and link_rank.py help/top/near and D/S
queries. Current TreeInsert and Rva00216BF5Dtor units already link; remaining
GameEngineControl, Rva00557CCCDtor and sort-entry units have independent
duplicates. Rva00358076AudioComplete remains foreign-claimed; its existing
blocked attempt was not repeated. No per-row data-back artifact was used,
and no ranking was manufactured. No census build/measure/history, full link
cycle, nightly, boot or shadow publisher ran. Scratch sources, objects,
receipts, snapshots and asserting proof remain in
build/vector12-assign-home-link-20261015.
