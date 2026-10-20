# Selection kind-test ownership

Inputs: BFME2 19fcaef83e; unchanged retail-truth-2 index 5366c4f808,
2026-10-20 12:21. The earlier attempt at 70129 in re_attempts.log rejected
renaming the shared integer-returning owner into a Boolean helper: converting
the result in the owner changes its 21-byte body. That owner stays unchanged.

InGameUISelection.cpp instead declares the existing rowed
ThingTemplate::rva000456AC(int) const and calls it through Drawable's local
adapter. The selection callers test AL in retail. An unsigned-char projection
of the integer result preserves this test without changing the shared helper's
signature or generating a Boolean conversion in it. This is a caller-side ABI
binding, not promotion of the address-derived helper into a new semantic name.
The existing helper's +0x108 bit-array access and Team::countKind caller support
the ThingTemplate receiver and index identity independently of matching bytes.
No shared header, owner, pin, or existing alternate-name pin changes.

Same-index current-object LEGACY pair preview:
- selection unit: 0 -> 171 linked bytes;
- unchanged ThingTemplateRva000456AC provider: 29 -> 29 bytes.
Both units link in that preview. All 5 rows pass the ordinary byte gate and
self-strict prepare-current receipts. No closed-strict or full-link claim.
No authored C++ byte growth. The two 49-byte kind queries and existing
73-byte deselect body remain exact. Only this indexed unit was sole-blocked
by the alternate semantic name; other consumers need separate repairs.

Diagnostics: build/seat-selection-before.txt, seat-selection-after.txt,
seat-selection-gate.txt and seat-selection-strict.txt.
