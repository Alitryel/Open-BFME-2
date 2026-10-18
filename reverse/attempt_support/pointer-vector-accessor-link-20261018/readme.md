# Pointer-vector accessor link repair

Baseline cc6343331e, frozen census c2c5ac8c27 (2026-10-18 11:36).
Use STLport's own pointer-distance/start/finish expressions as imported
force-inline specializations. They preserve native inline behavior while
external calls bind to the existing rowed pointer-vector owners.
Rva001F8CC2Assign drops const begin/end/size copies; LargeGroupAudio's
removeOverrides drops mutable begin/end copies. No layout, pin, alias,
ledger, flag or shared-header edits. This extends the preceding verified
vector-accessor repair pattern to the supported pointer-vector members.

3/3 ordinary byte rows pass; strict reusable receipts prove self-strict
currency. proof.py compares retained nondebug sections, flags, definitions,
symbolic relocations and all surviving COMDATs byte-for-byte, and checks
that every referenced removed name keeps the same selected provider.
Frozen-index paired legacy prediction improves 0 -> 283 nonpadding B
across two units (192 + 91). Closed-strict closure and a full link cycle
remain unmeasured; authored-byte coverage is unchanged.

Class, declared-unmatched, data --enforce, converged-data, new-variants,
case and diff checks pass. Baseline objects live in ignored scratch under
build/pointer-vector-link-20261018. proof.json records the paired evidence.
BFME1's verified reference revision remains 64d369b90170b7e9ec917d646f020b11f13eb0d5;
updating the pointer remains blocked by another seat's submodule claim.
The source expressions come from the existing STLport header, with target
byte and object evidence establishing this repair's applicability.
