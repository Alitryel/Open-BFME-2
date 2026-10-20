# Teleport vector max binding

Against published index b73720bed9 (2026-10-20 05:34), the current compiled
TeleportToCasterSpecialPower.cpp has one losing COMDAT: unsigned `_STL::max`.
The rowed owner is stlport_basic_ios_init.cpp at RVA 0x00013740. Apply the
established TU-local overload before vector headers; no new pin or alias.
The donor review at BFME1 a2c8039e supports avoiding incidental STL owners;
the local recipe and proof are in unsigned-max-cohort-link-20261014.

Paired previews against the same index change this unit from 0 to 1,136 linked
non-padding retail bytes. proof.json records both findings, object hashes and
the index hash. All 67 retained COMDATs have identical bytes and relocations;
only the conflicting unsigned max definition disappears. Other max consumers
still have independent blockers, so this commit does not claim gains for them.

Acceptance: ./build.sh passes all 5 rows, one string and three floats;
link_check --prepare-current passes before and after, with a current strict
self receipt; EH verification is 2/2 exact; declared-unmatched and converged
data checks pass; place_bodies finds no additional bodies or pins. The linked
increase is the legacy published-index preview, not closed-strict evidence.

Existing shadow data warning: the compiler's static-init guard at 0x00A043B0
is named differently from provisional g_Va00E043B0 in data_ledger.csv.
`data_check --enforce` reports wrong-name; retained relocation identity proves
this edit does not change it. No closed-strict or data ownership repair claimed.

Independent seat verification also passed all 26 consumer/provider rows with
`link_check.py --prepare-current`. Upstream ba6e5758d3 landed the same max
binding before this seat rebased; its 1,136 bytes are not a new gain from this
follow-up. The unchanged provider retains independent blockers.
