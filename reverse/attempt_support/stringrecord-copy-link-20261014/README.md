# String-record forward-copy link repair

Base checkout: ededc90661. Local preview census: cb660e4d97, 2026-10-13
04:02; index SHA256 is recorded in comdat-diff.json. The committed discovery
queue describes 67e1365aa9 and is not this preview baseline.

The erase unit declared STLport __copy with two template parameters instead
of InputIter, OutputIter, Distance. Its wrapper therefore referenced an
undefined name instead of the existing verified three-parameter provider at
0x005DD714. Correct the declaration and pass a local empty iterator tag,
rather than value-initializing its storage. The empty tag carries no state;
retail likewise takes its address without writing it.

Independent target evidence: the native erase call at 0x00381B33 reaches
0x0038151E. That complete 29-byte wrapper calls 0x005DD714 at +20 (REL32),
whose 47-byte loop advances both pointers in eight-byte steps and invokes
the verified record assignment at 0x005DD6B6. The wrapper's complete bytes
and actual relocation now agree; its former 36-byte implementation saved EDI
and zeroed empty-tag storage. No record application identity or donor-derived
layout is promoted to a target fact.

BFME1 linking review fetched upstream ef090c9ed943ce407c69e0c202be172d24eb1916
and inspected repairs d4ab8b980fe916fe70e137b2c2d2d04bceda8c9a and
39928bad445d45d73d25efc24ade970820326b5f. Their WWVegas allocation-provider
repairs concern a different cause and are inapplicable here. The clean
committed donor pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85;
its existing comparative full-gate blocker is retained in
build/reference-update-blocker.txt. No pointer or freshness-success stamp
was advanced, and no donor inputs were silently substituted.

Acceptance:

- Bounded link_check.py --prepare-current verifies 15/15 existing rows in
  erase and its actual forward-copy provider TU with strict reusable receipts,
  including the ordinary byte/string/float/import gates. The initial ordinary
  ./build.sh also preserved the erase row before the tag correction.
- COMDAT comparison: only __copy_ptrs changes, 36 bytes / wrong to 29 bytes /
  retail. Two other COMDAT byte-and-normalized-relocation hashes stay equal;
  no COMDAT is added or removed. Its only changed external is the corrected
  three-template-parameter __copy name. wrapper.json records full extent,
  masked equality and the exact callee binding.
- Same-index legacy preview of erase, allocate-copy and the older opaque
  wrapper: total findings 12 -> 9; erase findings 3 -> 0 and LINKS 0 -> 51
  existing authored retail bytes. The six allocate-copy and three opaque-unit
  findings are unchanged. This is local legacy credit, not a new census or
  closed-strict measurement. New authored C++ bytes: zero.
- Frozen-definition, class and whitespace checks pass. Converged-data check:
  eight addresses, zero second names, zero unjudged rows. An early concurrent
  data probe saw the old receipt while strict preparation was running; the
  final sequential probe in data-after.log passes.

Remaining work: allocate-copy still has UnicodeString/record cleanup and
insertion COMDAT selection conflicts. The old StlSweepW5Rva0038151E.cpp
claims a backward wrapper over an opaque nine-byte element and retains an
unresolved assignment plus wrong backward-copy selection. Its pinned callee
is a forward eight-byte copy in retail, so its identity/layout needs a separate
repair; this change does not rename that owner or add a competing row/pin.
Chat-history storage g_00E022F8 has declarations but no verified definition.
Broader census/closed-strict and updated-donor verification remain outstanding.
No full census, link cycle, nightly, boot or scheduler runner was invoked.
