# Team-vector copy: linked provider ownership

Move the existing 68-byte `vector<BfmeThingUBB>` copy constructor at
0x0032BE3C from SidesListTeamsInfoRecVectorCopy.cpp to
SidesListTeamsInfoRecCopy.cpp. The latter already emits the complete identical
named body and uses it to copy the native TeamsInfoRec member at +0x0C.
Its existing target-derived layout has 16-byte records, an index iterator at
+8 and a Dict at +0xC. No new class identity, symbol pin, ABI, flags or authored
function bytes are claimed.

Before: the standalone instantiation does not link because its emitted
`_Construct<BfmeThingUBB>` copy is not retail's. The actual TeamsInfoRec copy
unit links 180 bytes. After: that unit links 248 bytes, **+68 bytes of current
scoped linked availability**. These before/after figures use the same published
retail-truth-4 index, 11b3872700 (2026-10-23 23:06 UTC). This is a scoped preview,
not a new census, full-image link or runtime result.

The retired file contains only provisional record declarations and the one
explicit template instantiation. The receiving source already contains the
more precise target-derived record and actual caller; no independent recovered
implementation is discarded. Git retains the original source and its evidence.

`add_match.py --replace-existing` verifies 9/9 receiving-unit rows, with zero
unresolved relocations reported by the ordinary gate; literal/float/import
checks pass. `eh_verify.py` reports EXACT 1, zero not exact. `link_check.py`
reports LINKS, 180 -> 248. The original collector's other blockers and all
unrelated units are unchanged. The complete row identity is retained.

The donor review is inherited from the f5140c1c reference/provider survey in
link-seat-provider-audit-20261024.md. No new donor code is imported here;
native caller/layout evidence and the existing verified instantiation establish
the transfer. No census or full verification runner was started.
