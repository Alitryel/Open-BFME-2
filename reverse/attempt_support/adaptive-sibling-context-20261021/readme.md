# Adaptive four-channel decompressor: real sibling context controls

The target is AdaptiveDeltaMotionChannelClass::decompress<4>, native
0018F9C0..0018FA9E (222 bytes, RET16). The existing bank, full GetFrame4
home, prior attempt log and 0x0018f9c0-w1-20261019.md handoff were reviewed.
The established donor operation and target layouts are unchanged: Data+18,
NumFrames+C, Scale+14; sixteen-byte header and nine-byte per-channel packet.
The real bfme2AdaptiveDeltaFilterTable owns DB67D8. This pass adds no identity,
layout or provenance claim.

The recently established ArmyDefinition compiler-state finding suggested a
new control: change which real scalar/four-component getframe/decompress
instances precede the target. Seven distinct orders all emit the same
223-byte mismatch, first differing at +B. Native keeps the source-frame index
in EBP and output in ECX; the existing bank exchanges these roles and adds
an entry move. These results rule out these particular sibling orders, not
every possible compiler-state explanation.

A separate lifetime/type hypothesis groups the existing source pointer and
source-frame index into an ordinary two-field decoding state. Constructor,
copy-constructor and inline factory forms emit 233, 233 and 239 bytes. They
do not improve the entry shape. No volatile access, dummy effect, artificial
preceding function or manual register constraint was introduced.

All ten completed diagnostics have zero unresolved references. Actual full
COFF extents and source hashes are retained in verification.json; an
explain_mismatch exit of zero is diagnostic completion, not byte-match proof.
Replay context before state, using the normal tools/explain_mismatch.py path
and distinct ignored build objects. The retained prior bank is the immutable
input. Control and structured-state disassemblies preserve the differences.

No production code, header, pin or matched ledger row changed. The existing
partial bank is preserved byte for byte because none of these candidates is
better. Earlier independent control-flow, lifetime, compiler and declaration
experiments remain relevant; do not repeat them without new evidence. The
remaining prerequisite is a supported explanation for the entry allocation,
not a missing callee. Claim released after recording this result.

Inputs: BFME2 e1add842097; BFME1 a80da2e3be84. Existing bank settings
Ob2/G7/SSE/DNDEBUG/MD/EHsc. About 12 minutes, model gpt-6.1-sol.
