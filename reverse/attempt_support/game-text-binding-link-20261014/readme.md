# TheGameText provider binding repair

BFME 2 base: ae5fe09069. Discovery: repair_queue.py link and link_rank.py
(top, near, and saved blocker names). Committed discovery status describes
67e1365aa9; both local previews use the unchanged index at 147cfae2cb,
2026-10-14 07:27. index-meta.json records its SHA256. No index, census,
status, history, baseline, pin or alias was changed.

Two existing consumers declared TheGameText through private view types,
producing names no provider defines. GameTextStringLookUpLess.cpp defines
GameTextInterface *TheGameText; data_ledger.csv owns its four-byte datum
at RVA 0x009FF0BC (VA 0x00DFF0BC). Seven retail DIR32 operands across the
two matched functions independently reach that address. Both consumers
now declare the real pointer and cast at use to their existing views.
The progress-label fetch retains slot15 and its UnicodeString return ABI;
SupplyCenterDockUpdate retains slot17 and its pointer return ABI. No class
layout, vtable, function identity, body extent or compiler flag changed.

Target identities and layouts are carried from each existing row's evidence.
The singleton binding is established by target operands and the existing
provider/data owner, independently of donor names or BFME 1 addresses.

Acceptance:

- Bounded link_check --prepare-current before/after: all three providers and
  consumers self-strict with reusable receipts; 5/5 matched rows exact.
  Independent ./build.sh: 5/5 exact, ten literals and three empty references,
  three float literals and four named imports verified; zero baselined/skipped.
- Every nondebug COFF section, including directives, has identical bytes,
  extents, flags and position. Relocation coordinates, types, target section
  and value are identical. Only the two private global referents change to
  the owner. Compiler-generated $L/$T labels are normalized by their unchanged
  storage, section and offset; external symbols match after owner normalization.
  Provider object is unchanged. object-proof.json records all seven native
  operands, object and receipt hashes; original objects/receipts and the scratch
  comparison script remain in build/game-text-binding-link-20261014/.
- Same-index legacy local preview: progress label LINKS 0 -> 340 existing
  bytes; SupplyCenterDockUpdate unresolved 3 -> 2, LINKED remains zero.
  Provider stays clean at 153 bytes. Cohort 1/3 -> 2/3 clean, 153 -> 493 bytes.
- EH: 2/2 EXACT, zero baseline/missing failures. Enforced converged-data check:
  eight addresses, no second names/unjudged rows. Shadow data: zero findings.
  New-variants admission, frozen definitions, class gate, CSV and whitespace
  checks pass. Placement resweep: zero bodies and zero pins.

This proves self-strict touched objects and a legacy local preview improvement.
Closed-strict --refresh --current-ledger refuses 399 missing provider objects;
closed-after.txt records the refusal. No closed-strict, fresh census or link.exe
placement gain is claimed. Authored C++ byte growth is zero. No maintainer-only
runner was started. The two remaining SupplyCenterDockUpdate providers are
Player::getSupplyBoxValue and ExperienceTracker::rva0039AE04.

Reference review: verified BFME 1 gitlink 23b143233b5a8664a3bdf8572df6d905c310a5a1,
whose BFME 2 verification is recorded by commit 9b6bf3e581. Reviewed donor
92a8d854746f059994f8ab370c133f3ba71eec24: bind a private view through the real
data owner and cast at use. Its repair principle applies; its source, address
and layout were not imported. Direct allocator repair fea964f85 was also
reviewed, but BFME 2's corresponding repairs were already landed. Sole
getMajorRadius/getDrawModules findings were likewise already repaired and
were not retried. name_globals dry-run on Rva000F5B43Get, Rva00803080Set and
RebuildHoleExposeDie yielded zero rewrites.

Fetched official BFME 1 master a7c38d3b2597121f178ab5190b3062478823257d.
The clean verified pointer is preserved: file:reference/open-bfme-1 is held
by yasinschroeder-codex3, which owns the comparative update. No successful
freshness stamp was written. Unrelated untracked reverse/zh_sweep is preserved.
