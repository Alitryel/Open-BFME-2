# StatsCollector FileSystem provider binding

BFME 2 base: c3c5c141a9. Discovery: repair_queue.py link and link_rank.py
top/near, then unresolved data names grouped by consumers. Committed status
describes 67e1365aa9; the unchanged local index measures 147cfae2cb at
2026-10-14 07:27. index-meta.json records its SHA256. No census, status,
history, baseline, pin or alias changed.

StatsCollector declared TheFileSystem as Rva003006C4 *, creating a private
decorated name without a provider. It now declares the real FileSystem *
global and casts at the existing directory-worker call. System/FileSystem.cpp
defines that name; data_ledger.csv owns its four-byte datum at RVA 0x00A06A48.
The matched setup body at 0x00437DF8 has a zero-addend DIR32 at offset 29
whose native operand is VA 0x00E06A48. The native datum and existing provider
establish this binding independently of donor names or layouts. Existing
function identities, class layouts, compiler settings and worker ABI remain
the evidence carried by their existing rows.

Acceptance:

- Before/after bounded link_check --prepare-current: both explicit units
  self-strict, with reusable receipts; all 20 matched rows exact. Independent
  ordinary build.sh: 20/20, 44 literals and two empty-string references,
  18 named imports, zero skipped references or baselines.
- All nondebug COFF section bytes, extents, flags and positions agree, as do
  relocation coordinates, types and destinations after the one intended
  global-name substitution. Defined external symbols agree. The provider
  object and receipt are identical. object-proof.json records the native
  operand and object/receipt hashes. Original objects, source and proof script
  remain under build/stats-filesystem-link-20261014/.
- Same-index legacy preview: consumer unresolved names 2 -> 1; its separate
  getMoney COMDAT finding remains. Total consumer findings 3 -> 2; pair LINKED
  bytes stay zero. Provider findings are unchanged. No closed-strict, census
  or link.exe placement gain is claimed. Closed-strict --refresh
  --current-ledger refuses 409 missing provider objects before any full-tree
  compile. No maintainer-only runner was started.
- EH: 5/5 EXACT, no baseline/nonexact/missing objects. Enforced converged
  data: eight addresses, zero second names/unjudged rows. Shadow data: zero
  findings. New-variants admission, class gate, frozen definitions, CSV and
  whitespace checks pass. Placement resweep: zero bodies and zero pins.

Remaining consumer blockers are the unowned stats-path datum g_00DC8AF0 and
Player::getMoney COMDAT selection. Neither was changed or retried. Other
scanned FileSystem consumers already use the real pointer declaration.
Authored C++ growth is zero; this is a verified dependency repair.

Reference review: retained verified BFME 1 gitlink/checkout
23b143233b5a8664a3bdf8572df6d905c310a5a1, verified by BFME 2 commit 9b6bf3e581.
Reviewed donor 0835ab92bef30e3303e729a0ce09cf591368d0cd and its byte/link
evidence: bind the real data owner and retain a private view at use. This
principle is applicable; its Apt source, addresses and layouts are unrelated
and were not imported. The earlier broader dedicated donor review is reused.
Official master was fetched as a7c38d3b2597121f178ab5190b3062478823257d.
The full old/new freshness comparison remains incomplete: the prior attempt
needed 2982 stale TUs and was interrupted with 2806 remaining after about
21 minutes (unicode-comparator-link-20261014/readme.md). The verified pointer
and success stamp were preserved; no freshness success is claimed. Unrelated
untracked reverse/zh_sweep preparation is preserved.
