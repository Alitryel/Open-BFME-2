# Portal placement-copy provider binding, 2026-10-21

Baseline 32c0e5de1c; published census 17918792f6 (09:22), retail-truth-2.
BFME1 donor review remains 5987fd1b859e86801d093256eadc6fb63d87785f.
This repair uses the independently verified BFME2 provider and native call edges.

Rva0046152FFinish.cpp owns the 183-byte insertion worker at46152F and
55-byte push_back at46167A. Both matched, but its redundant _Construct
instantiation called undefined DynamicPortalLink's opaque copy constructor.
Retail's complete null-guarded placement-copy operation is the45-byte460F18,
which calls the rowed67-byte scalar-vector copy constructor at2CFAB9. The
existing Rva00460F18Construct provider owns that complete body and native EH
graph. See reverse/attempt_support/placement-copy-stl-family-20261020.md.
The existing template pin at460F18 supplies an address, not a definition.

A TU-local inline overload delegates the placement-copy operation directly to
Rva00460F18Construct before the STL templates are defined. Both native parent
bodies and every relocation remain exact; the redundant unresolved helper
is no longer emitted. This preserves the established12-byte storage view
without claiming DynamicPortalLink's original application identity or layout.
No class rename, pin, alternate-name alias, or new out-of-line body is used.
A declaration-only template specialization passed2/2 bytes but simply moved
the undefined reference to _Construct, so it was superseded by this binding.

Bounded legacy preview: portal0 ->238 linked bytes,0/1 ->1/1 clean.
Paired with the complete placement-copy provider:1763 ->2001 bytes,
2/2 clean afterwards; provider remains1763 bytes and has no source change.
Strict reusable byte receipts78/78; complete EH34/34 EXACT; new-variant
check passes. find_declared_unmatched passes. No closed-strict LINK gain
is claimed, and no full census/link cycle was run.

The shared provider is unchanged, and the repaired overload is TU-local.
Source search found no other users of this exact opaque placement helper;
other native placement-copy owners have distinct targets and are outside
this repair. No previously linked provider or unrelated caller is displaced.
