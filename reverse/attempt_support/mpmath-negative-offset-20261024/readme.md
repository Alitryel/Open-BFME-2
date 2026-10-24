# XMP negative table displacement, 2026-10-24

model=gpt-6 lane=R budget=30m. Current BFME2 f155433f1cb439e7fbf80493cf096ea7a84f48cd; current donor32774ab03393709a7f14331ba8d98d281a55ffd9. Reviewed the donor numerical source and earlier numerical-render-dependency-cleanup-20261020 evidence. The donor link_cycle has no dual-datum repair to inherit.

The unchanged mpmath.cpp control passes61/61 complete functions, its prime-table data row and five imports; frozen-definition check passes. Native XMP_Prepare_Modulus at61D1E0 is359 bytes. Its fourth scratch-modulus operand at+98 has a signed DIR32 addend -8, encoding retail A097E8 rather than the symbol's A097F0 base. The other three scratch references carry addend0. This is the reference expression &_scratch_modulus[sub_precision-2].

The authoritative5c98b266ee graph marks the complete256-byte scratch array atA097F0 and its adjacent520-byte double-staging buffer atA095E8 correct, but rejects this one operand as data-unmapped. The predecessor ends exactly atA097F0; the encoded address is inside its final eight bytes. Existing tests deliberately reject all before-symbol displacements until both the indexed datum and preceding bytes are checked. This is a valid missing-proof path, never permission to ignore the predecessor.

A proposed tooling repair must judge both complete adjacent named datums, preserve their individual pins and one-to-one address mappings, follow every pointer, include both in shifted-base closure, and continue refusing a bad predecessor, bad named array, an out-of-section displacement or an unsupported COMMON case. No C++ source, data layout, pin or baseline change is proposed. The current conditional3558-byte gain is diagnostic only.

## Separate verifier repair

The follow-up change accepts only a negative DIR32 displacement into the immediately preceding named datum in the selected defining object's same concrete section. It adds ordinary zero-addend references to both complete origins. Both origins retain pins, forward/back one-to-one checks, pointer discovery, full content verification and shifted-base closure. COMMON, before-section and skipped-predecessor cases remain rejected. The C++ source, ledger, data names, pins and baselines remain unchanged.

Regression command: python3 -m pytest tools/tests/test_link_cycle.py tools/tests/test_gate_exploits.py -q -rs. Actual exit0:126 passed; one optional exploit-fixture parameter has no fixture and is skipped. Controls reject a bad predecessor or named array, either bad pin or origin mapping, a bad pointer target reached from either object, and a shifted mismatch in either object.

The read-only replay uses the original immutable5c98b266eefeb20ef18e4fee427d671c4c320ec8 images and objects. It first reproduces1,668,941 unique credited bytes exactly with the original verifier, then produces a diagnostic1,672,493 with the candidate: ten gained rows /3558 bytes, one lost row /6 bytes, net3552. XMP_Prepare_Modulus has no failures and closes. The lost Rva0011C460Get row now fails data-fwd:CurrentAdapterIdentifier, exposing an inconsistent address map through the additional origins. This refusal is preserved. The original receipt is byte-for-byte unchanged; replay-results.json is diagnostic evidence, not an authoritative new measurement.

Tooling work and review completed within the30-minute source-work budget; the separately authorized full immutable link-cycle measurement follows. No source recovery or new matched coverage is claimed.
