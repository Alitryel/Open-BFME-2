# XMP negative table displacement, 2026-10-24

model=gpt-6 lane=R budget=30m. Current BFME2 f155433f1cb439e7fbf80493cf096ea7a84f48cd; current donor32774ab03393709a7f14331ba8d98d281a55ffd9. Reviewed the donor numerical source and earlier numerical-render-dependency-cleanup-20261020 evidence. The donor link_cycle has no dual-datum repair to inherit.

The unchanged mpmath.cpp control passes61/61 complete functions, its prime-table data row and five imports; frozen-definition check passes. Native XMP_Prepare_Modulus at61D1E0 is359 bytes. Its fourth scratch-modulus operand at+98 has a signed DIR32 addend -8, encoding retail A097E8 rather than the symbol's A097F0 base. The other three scratch references carry addend0. This is the reference expression &_scratch_modulus[sub_precision-2].

The authoritative5c98b266ee graph marks the complete256-byte scratch array atA097F0 and its adjacent520-byte double-staging buffer atA095E8 correct, but rejects this one operand as data-unmapped. The predecessor ends exactly atA097F0; the encoded address is inside its final eight bytes. Existing tests deliberately reject all before-symbol displacements until both the indexed datum and preceding bytes are checked. This is a valid missing-proof path, never permission to ignore the predecessor.

A proposed tooling repair must judge both complete adjacent named datums, preserve their individual pins and one-to-one address mappings, follow every pointer, include both in shifted-base closure, and continue refusing a bad predecessor, bad named array, an out-of-section displacement or an unsupported COMMON case. No C++ source, data layout, pin or baseline change is proposed. The current conditional3558-byte gain is diagnostic only.
