# Image-map shared tree constructor repair

The unsigned Image-pointer map insert unit now declares the existing tree-base
constructor specialization rather than emitting a conflicting local copy. This
follows the declaration-only pattern already used by this unit's node factory,
tree destructor and node allocator. No constructor implementation, shared
header, compiler flag, layout, pin, ledger row or exception policy changes.

At base 1d6cf0f54f98ed734602fa968176615110c9bf6a, a strict-current object has
one live COMDAT blocker: its `_Rb_tree_base<pair<const unsigned, Image*>, ...>`
constructor differs from the first definition in link order (no retail address).
Paired old/current previews independently refresh that one object's definitions
into copies of the same index: 28269d8e8d, 2026-10-15 09:31 UTC. All findings
clear, predicting 0 -> 681 existing authored retail bytes for this unit. No new
C++ bytes are claimed. This is a local legacy preview; strict compiler receipts
establish current inputs, not self-strict placement or closed-strict closure.
Neither a census nor a full link cycle was run; link_status.csv is unchanged.

The affected six consumers/rows remain exact: `_M_insert` (0x004D9C49, 136B),
`insert_unique` (0x004D795B, 134B), hinted `insert_unique` (0x0020673B, 294B),
map `insert` (0x00358211, 29B), ImageSubscriptMap::operator[] (0x002077D6, 69B),
and `lower_bound` (0x0053BD25, 20B). Their gross extent is 682 bytes, with 681
real authored bytes after padding is excluded. The two incidental tree
constructors retain their original external calls to the shared base ctor.

Object proof compares the preserved strict-current baseline object to the final
strict-current object. All 124 retained COMDATs have identical bytes and
relocation digests. Every other nondebug section, including data and EH, is
identical after resolving renumbered local labels to section contents/offsets;
link directives are identical too. Exactly four text COMDATs disappear: the
base constructor and its now-unused allocator-conversion/proxy helpers. The
base constructor changes from defined to undefined, retaining ordinary direct
calls to the census's provider; one allocator reference used only by removed
code disappears. No new symbol, import indirection or reference is introduced.
The proof records hashes, exact removed bodies and paired findings.

A census-wide same-symbol search finds this sole base-constructor blocker.
MilesAudioManager has a separate tree-base destructor blocker and is untouched.
`place_bodies.py` finds no additional bodies or pins in the repaired unit.

Acceptance: ./build.sh and link_check.py --prepare-current pass 6/6 retail rows;
link_check.py SOURCE reports LINKS 681; --new-variants accepts. EH verification,
class gate, enforced data and converged-data checks, find_declared_unmatched,
check_csv and diff whitespace checks pass. No hatch is added.

Donor review used committed BFME 1 a7c38d3b2597121f178ab5190b3062478823257d
and fetched repair 53d32d6b4b377317a3397971629ca3ad20b870e9 (Apt default ctor
emission). The unused-emitter repair principle applies; forcing inline here
changed incidental callers, so that exploratory variant was discarded in favor
of existing BFME 2 declaration-only precedents (stlport_map_int_ptr_init and
StlportIntMapInsertFamily). Target identity, ABI and layouts remain those already
established by the six ledger rows; no donor addresses or layouts are inferred.
The overdue comparative donor-pointer update remains owned by the live foreign
file:reference/open-bfme-1 claim; checkout and verified gitlink are preserved.
