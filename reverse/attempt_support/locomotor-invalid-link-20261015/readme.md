# Locomotor invalid-position setter emitter repair

AIStatesSmallUpdates.cpp stops emitting an unused external
`?setAllowInvalidPosition@Locomotor@@QAEX_N@Z` COMDAT. Its existing inline
set/clear semantics, member +0x44, bit 1 and callers are unchanged. The imported
forceinline spelling follows current AIEnterStateOnEnter, AIEnterStateOnExit,
AIStatesDerivedOnExit and AIMoveAndDeleteStateUpdate siblings. No new import,
undefined name, pin, alias, header, compiler flag or ledger row is introduced.

The paired local preview removes exactly one COMDAT conflict and adds no
findings. State::slot01 and State::slot02 remain unresolved; this unit still
holds 619 existing nonpadding bytes outside the legacy linked count. Newly
linked bytes and new authored C++ bytes are both zero. No closed-strict or
placed self-strict gain is claimed. Strict reusable compilation receipts are
current before and after; these establish the scoped body gate, not closure.

## Evidence

Base: 9c39f887a6848d0fb58269b1180daa8e89f06292.
The unchanged runner index measures commit 28269d8e8d, 2026-10-15 09:31 UTC.
measurement.json contains its SHA256; proof.json contains original/current
source, object and receipt hashes and complete paired link findings.

The only removed section is the unused 20-byte setter. All 20 retained COMDATs
have identical bytes, extents and relocation digests. All other nondebug COFF
sections and their symbolic relocation destinations are identical; SafeSEH
symbol-index changes are normalized by name. Link directives and every other
external definition/reference are unchanged. There is no new import reference.
The paired comparison refreshes both objects independently into copies of the
same index; no shared index or status artifact is changed. The scratch proof
and original source/object/receipt remain in build/locomotor-invalid-link-20261015.

Target facts: full retail onEnter at 0x0034F01B (312 bytes) and onExit at
0x0034A121 (70 bytes) verify the existing receiver flag operations and ABI.
The unchanged field names/purpose derive from the prior ZH-guided recovery;
this repair establishes no extra class layout or standalone setter address.

Donor review: retained clean BFME 1 gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d. Upstream repair
66b19a8e95a4add525ef808fcea088e306798e2b (reviewed patch and verification
message) uses precisely imported forceinline to remove unused allocator
copies without new imports. Its emitter technique is applicable; Apt identities,
addresses and layout are inapplicable. Local AI siblings supply the same setter
precedent. BFME 1 master fetched during initial pull is 86d49b09; the reference
pointer remains foreign claimed (codex-6bc6-20261008), so it was not advanced
and no freshness success stamp was written. Its full comparative update is
outstanding.

## Acceptance

- Before bounded prepare-current: both candidate units pass 33/33 rows; only
  AIStatesSmallUpdates is owned and edited. AIStatesBfmeOnExit is foreign claimed.
- ./build.sh AIStatesSmallUpdates.cpp: 7/7 exact, one string and one float
  literal verified, no named imports.
- After link_check.py --prepare-current: seven rows exact and one current strict
  reusable receipt; census/index/status unchanged.
- Ordinary link_check.py: remaining two unresolved slots, 0 -> 0 linked bytes.
  Paired check_object proof: three findings -> two, removed setter only.
- eh_verify.py: zero EH-bearing rows, zero missing objects or nonexact rows.
- data_check.py --enforce: one unchanged baselined finding, zero outside baseline.
  Whole retained object/data/relocation comparison proves it unchanged.
- data_check.py --converged: eight addresses, zero second names/unjudged rows.
- class_gate.py, find_declared_unmatched.py --fail and
  link_check.py --new-variants pass. Existing present-unmatched destructor marker
  is untouched; frozen-file check exits zero.
- place_bodies.py: zero additional bodies or pins.
- check_csv.py and git diff --check pass.

No census build/measure/history, link cycle, nightly, boot or scheduler was run.
Remaining slot identities require separate target/vtable investigation. The
other same-cause emitter in AIStatesBfmeOnExit belongs to another live seat.
