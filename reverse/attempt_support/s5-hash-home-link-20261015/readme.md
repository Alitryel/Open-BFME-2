# S5 comparison ownership repair

Source base: 698bbbf0d07f56f187577757d22b069694c3fe27.
Local index: 19a2565407, 2026-10-15 09:33; original census
5986a99448, 2026-10-15 04:52. Index SHA256:
a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3.
The committed link_status.csv is a discovery artifact, not this measurement.
No census, index, status/history, baseline, pin, flags or shared header changed.

S5HandleHashCompares.cpp owned the 34-byte comparison at 0x00435B4F.
AptSaveLoad.cpp already emitted an identical inline copy, used by its matched
constructor. The common unit's strong definition competed with that copy.
Rehome the existing row with add_match --replace-existing and remove the
redundant definition, its unused private class and helper declaration/constant.
AptSaveLoad.cpp itself is unchanged. This reduces one private class view and
adds no emitter, alias, pin, annotation or other escape hatch.

Target evidence remains the 34-byte body, reads from other+4 then this+4,
call through ILT 0x00010AFA to the rowed hash helper at 0x0043538F,
comparison against 0x993BA311 and byte result. Both object copies pass the
retail bytes and relocation verdict independently. The constructor's call
establishes the consumer relationship. The original BFME 1 donor provenance
is retained in the row; class names remain address-derived, with no new
semantic identity or full-layout claim. No donor code was imported.

Acceptance:

- Before and after `link_check.py --prepare-current` for the two claimed
  units passes all 12 matched rows, with strict reusable dependency receipts.
  Normal whole-byte gates reuse those objects. Nine string references pass;
  no literals or imports were skipped or baselined. add_match independently
  verifies both rows now owned by AptSaveLoad.cpp.
- Scratch snapshot.py refreshes the same index in memory with both before
  objects, then both after objects. object-proof.json records the index,
  source, object and receipt hashes. The asserting proof verifies that both
  old comparison copies have identical bytes/relocations and retail verdicts;
  exactly one 34-byte section disappears from the common unit. Its eleven
  remaining COMDATs and twelve nondebug sections are unchanged. All fifty
  AptSaveLoad COMDATs and fifty-five nondebug sections are unchanged, including
  relocations, external bindings, extents, EH symbol references and directives.
- Both duplicate findings disappear and no finding is added. The standalone
  local link CLI agrees with the paired proof: 0/2 -> 1/2 clean; legacy LINKED
  0 -> 332 existing nonpadding retail bytes. Common ownership changes from
  366 to 332 bytes and AptSaveLoad from 1161 to 1195. Total matched and
  authored C++ bytes do not grow.
- The explicit cohort is self-strict current. This is a legacy local link
  prediction against unchanged external providers. Closed-strict closure,
  link.exe placement and a fresh census gain were not measured.
- EH: one EH-bearing row EXACT, no missing objects. Frozen definitions,
  canonical classes, new COMDAT variants, converged data (eight addresses),
  shadow data, CSV and whitespace checks pass. The placement sweep returns
  zero bodies and zero pins.

AptSaveLoad retains unresolved destructor and Save providers and its four
independent TreeHintOpaque0043671B STLport COMDAT findings (allocate, _Destroy,
clear and the list-base constructor). These findings are identical before
and after this repair; no gain is attributed to that unit.

Reference review: retained clean verified gitlink/checkout
 a7c38d3b2597121f178ab5190b3062478823257d. BFME 1 repair
4966496c5ae401ec877a044e1ae6dd04f9d9f65c was inspected directly: suppressing
surplus COMDAT emission while retaining matched callers is applicable as an
ownership principle; its AsciiString implementation is not imported. Earlier
review of de59a7e9 and 92a8d854 remains recorded in the adjacent debug-hash
repair evidence. Official master fetched to
7a8811f5d62de60f920d817a0017c88170f69410. Updating remains blocked by another
worker's reference/open-bfme-1 file claim and the outstanding full old/new byte
gate comparison documented in ../unicode-comparator-link-20261014/readme.md.
Verified inputs are preserved; no freshness success or pointer update claimed.

Selection used repair_queue.py link and link_rank.py help/top/near and D/S/A
queries. ModuleFactoryInit and StatsCollector already link in current source;
recent GameInfo, PlayerList and allocator duplicate attempts were not repeated.
No per-row data-back artifact was available or ranking fabricated. No census
build/measure/history, full link cycle, nightly, boot or shadow publisher ran.
Scratch before sources/objects/receipts and snapshot.py/proof.py remain in
build/s5-hash-home-link-20261015.
