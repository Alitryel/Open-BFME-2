# Hash pair provider reconciliation, 2026-10-21

Parent: 22d2deb0df. Published census e20daa4e78, 2026-10-21 21:42.
BFME1 linking revision reviewed earlier: a80da2e3. This change uses BFME2
retail edges and existing rowed STLport providers, without new naming claims.

The 112-byte insert_unique_noresize at 002E037F was blocked by the opaque
72-byte element copy constructor. Its native node helper 002E0273 is 37 bytes:
allocate 80 bytes through 000307F0, initialize its link, and call the existing
pair placement worker at 002E00CC. Forward the opaque pair's _Construct to
that rowed provider. Extracted emitted helper: all 37 bytes masked-equal,
REL32 at +6 -> 000307F0 and +24 -> 002E00CC. The element application identity
and field meanings remain unknown; BfmePod72 is the existing structural view.

The census selected an earlier trivial _Construct<BfmePod72 pair> from
stlport_pod_hash_bodies.cpp instead of StlportPairConstructFamily.cpp. Declare
the pair copy and placement specializations in that unit, retaining the rowed
non-trivial provider. Declaration-only construction initially introduced an
EH cleanup into the rowed node helper (15/16 rows passed). The native helper
has no such cleanup. Applying the no-exceptions STL setting already used by
the exact sibling StlSweepW5Rva002E037F preserves all 16 rowed bodies and removes
that unwanted exceptional path. No throw() promise or assembly was added.

Acceptance:
- Before: both touched units blocked, 0 linked bytes.
- After: 002E037F unit LINKS, **+112 B legacy preview**. The 616-byte hash
  provider remains blocked on other COMDAT and selected-provider conflicts;
  it earns no bytes and is a verified prerequisite of this 112-byte repair.
- ./build.sh and link_check.py --prepare-current: 17/17 exact rows, literal
  and import checks pass, two strict reusable source receipts.
- find_declared_unmatched.py passes. link_check.py --new-variants
  --staged-peers --shadow reports no new competing variants.
- Closed-strict closure is unmeasured; the current-ledger universe has missing
  objects. No maintainer-only verification runner was started.
