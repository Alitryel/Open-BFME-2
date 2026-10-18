# Coord3D allocation forwarding: eight-unit link repair

At fa0a9efb6e, the published census (c2c5ac8c27, 2026-10-18 11:36)
selects a different referenced Coord3D allocation proxy. All eight units
lose that COMDAT; each has no other blocker in a paired refreshed preview.
Their matched source-byte total is 2,387 (17 rows).

Declare allocator<Coord3D>::allocate out of line and retain the header's exact
inline allocation-proxy forwarding expression, using the existing sibling
forceinline/dllimport suppression convention. The declaration prevents MSVC
from inlining the allocator into this forwarding layer. No pin, layout,
compiler flag, runtime import or ledger change is needed. Existing typed
allocator pin 0x00395928 is backed by the retail call at 0x002CDFB9 and the
rowed BfmeE12 28-byte allocator at the same entry.

Checks:

- Before and after: link_check.py --prepare-current on the eight explicit
  owned units; all 17 rows byte-exact with strict reusable compiler receipts.
- Paired same-index preview, refreshing the eight actual before/after objects
  in memory: eight blocked -> eight clean, 0 -> 2,387 source bytes linked.
  See paired-proof.json for per-unit blockers, removed helper names and hashes.
- Every retained code body and relocation is unchanged after normalizing
  compiler-generated $T/$L local labels. Only redundant allocation/rebind
  helpers disappear. No named function is added.
- eh_verify.py before and after: 2 EXACT, 0 missing, 0 baselined. The label
  changes in EH handlers refer to identical retail-exact unwind data.
- find_declared_unmatched.py: all definitions matched; git diff --check clean.
- The canonical BfmeE12 allocator's own byte gate also passes.

This is a self-strict, legacy-index paired gain, not a closed-strict gain or a
new census measurement. --refresh --current-ledger refuses 46 missing objects
(first InGameUIRva002A4A68); no whole-tree compile or maintainer-only runner was
started to manufacture that evidence. Census, index and link_status unchanged.

BFME1 linking guidance reviewed at committed donor 64d369b90170: existing
Coord3D source supplies the same allocator semantics; BFME2's already verified
allocation/deallocation sibling repairs supply the suppression convention.
No donor layout or identity is newly asserted. Upstream BFME1 d348fca17814 is
newer; reference/open-bfme-1 is claimed by another seat, so this seat retains
the committed verified pointer and leaves freshness completion to that owner.
