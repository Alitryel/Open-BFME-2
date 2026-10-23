# Rva0014F699 deleting-destructor ownership repair

Base: 52dc2f818f82e2ab946068ee8381be8f2f1d7f1f. The discovery census
reverse/link_status.csv measures 4b7e7091c4. Acceptance uses a frozen published
index updated at a2839ea429, 2026-10-15 13:35, based on census 5986a99448.
proof.json records its SHA256 and paired results. No index, status or history
was changed.

FamilyDeletingDtors_Rva0014F699.cpp emitted a 58-byte inline destructor at a
name whose matched native owner in Rva0014F699Assign.cpp is 52 bytes. The
extra six bytes write the derived vtable, absent from the native body. The
owner uses novtable and therefore does not emit the separately rowed scalar
deleting thunk. Reuse the declaration-only vtable-emission pattern already in
neighboring FamilyDeletingDtors_Rva00150558.cpp and Rva0015058E.cpp: declare
the virtual destructor and define the unused tag constructor to request the
vtable and scalar thunk. Remove the incorrect destructor, its unused anchor,
and now-unneeded private member/base cleanup views. Two present-unmatched
annotations and an absent-from-retail anchor annotation become one honest
absent-from-retail constructor annotation. No baseline was edited.

The limited view claims only the observed virtual cleanup slot; it is not a
complete object layout or recovered original class identity. Target identity
and ABI are unchanged: retail 0x0014DC3F calls the rowed destructor at
0x0014D1E3 and rowed delete at 0x0002FD60 under flag bit 0. The vtable and
28-byte deleting thunk retain every original byte and relocation. The tag
constructor is synthetic support, not a recovered retail body.

Acceptance:
- Normal byte gate passes the deleting thunk, 1/1. Bounded prepare-current
  verifies emitter and native owner before and after, all 4/4 rows, with strict
  reusable compiler receipts and no string/float/import discrepancies.
- Paired objects preserve the deleting thunk and vtable exactly, including
  relocation referents and weak-external aliases. The only added callable is
  the 11-byte synthetic constructor, whose sole relocation writes the same
  vtable. All four nondebug after sections are accounted for, including the
  unchanged runtime directives. The native owner object is byte-identical.
- Paired previews of the same index, replacing only the two verified objects,
  remove exactly one COMDAT-loser finding. The emitter changes from blocked to
  LINKS (0 -> 28 existing bytes); the owner stays LINKS at 189 existing bytes.
  The ordinary local link check agrees: 1/2 -> 2/2 clean, 189 -> 217 bytes.
  The apparent census-relative 0 -> 217 total includes the previously completed
  owner repair; this session's paired gain is only 28.
- No new COMDAT variants. Class and frozen-definition checks pass. Data and
  enforced converged-data checks find zero issues. EH verification: EXACT 1,
  zero missing objects or nonexact rows. CSV and whitespace checks pass.
  The affected-unit placement resweep finds zero new bodies and zero pins.

These are local legacy link predictions with strict-current object receipts.
Authored C++ grows by zero bytes. Self-strict executable placement, closed-strict
closure, a new census and runtime checks are unmeasured. No maintainer-only
runner was started. proof.py can replay the checks using the ignored before
snapshots in build/rva0014f699-deleter-link-20261015.

The indexed ownership sweep finds exactly two copies of the native destructor:
the correct owner and the conflicting emitter removed here. The two neighboring
deleting-thunk emitters already link cleanly and need no repair. The insert
unit's separate allocator/copy-constructor findings remain outside this fix;
no unchanged deferred codegen attempt was repeated.

BFME 1 donor review: fetched official upstream master e082760734795655f086939df77b393f4b728375
and reviewed c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and 53d32d6b4b377317a3397971629ca3ad20b870e9.
Their ownership principle applies, while inline-import suppression is
inapplicable here: the complete native destructor is already provided
elsewhere and the separate deleting thunk must stay emitted. The existing
BFME 2 sibling emitters supply the proven local mechanism. No donor layout,
flags, source or new identity was imported. Preserve verified checkout/gitlink
a7c38d3b2597121f178ab5190b3062478823257d: another worker holds
file:reference/open-bfme-1 and the prior comparative full-baseline freshness
blocker remains. No pointer advance or freshness-success stamp is claimed.

Model: gpt-6.1-sol.
