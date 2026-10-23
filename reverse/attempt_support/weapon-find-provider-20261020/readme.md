# Existing SparseMatchFinder lookup provider repair

Base: `54a521e4579ee95884d68f40211063e9aa7cec40`.
Reference: BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`, unchanged.
Model: `Codex(runtime-model-not-exposed)`.

## Native evidence and scope

This corrects the established Weapon/BitFlags<17> ledger contract; it does not
establish the original class name or template argument. Native comparator
`0x0033AD5C` (73 bytes) tests 21 bits from low to high, reading a four-byte
flag word. Numeric unsigned ordering is different: flags 1 and 2 compare false
in retail, but true with unsigned `<`.

The existing `_M_find` at `0x0033AF5F` (92 bytes) calls that comparator twice,
reads tree header `[this]`, comparator `[this+8]`, and node key `+0x10`.
Its const-find wrapper at `0x0033B81C` is 20 bytes. Both are existing matches.
The shared slow-finder pin has older type-identity uncertainty; this change
adds no identity, address binding, row, or coverage claim from that pin.

`STLWeaponTemplateSetBitFlagsHintedInsertUnique.cpp` now exposes the verified
bitwise comparator instead of its incorrect numeric comparison. Its visible
read-only noinline body matters to VC7.1's lookup allocation. `ThingTemplate`
uses the same native comparison through the donor's actual unsigned-long
bitset storage, guarded at compile time to four bytes. Both newly emitted
lookup and comparator copies agree with their existing providers in whole
bytes and relocation targets.

## Changed prerequisite and bounded trials

Prior log 65798 already found the visible correct comparator, but creator and
insertion conflicts prevented a link gain. Those provider conflicts were
repaired in the preceding published batch. This retry addresses that changed
prerequisite; it does not repeat the earlier isolated claim of success.

Ordinary declaration-only `_M_find` specialization, explicit public-find
forwarding, noinline specialization declaration, and extern-template variants
all triggered VC7.1 C1001 in the dependent find call. No gate or compiler
workaround was added. Giving the comparator's actual read-only body to the
consumer makes its `_M_find` exactly 92 bytes naturally.

The initial storage-view body emitted a 77-byte comparator: its first 69 bytes
matched, then it redundantly tested the first Boolean before returning true.
Unsigned-long storage alone retained that body. Nested exits emitted 68 bytes;
a final Boolean return emitted 76. Two opposite-bit exits emitted the complete
retail 73 bytes, so that straightforward control flow is retained. A final
already-running direct-view control also emitted 73 bytes; no further trials
were needed. All these source trials preserved ThingTemplate's 26 owned rows.

## Verification and accounting

Normal targeted build: 49/49 matched bodies across the nine-source provider and
caller group. EH verification: 6/6 exact rows, with zero baselined or missing objects.
The affected-source placement scan found zero new bodies and zero new pins.
Frozen-source check passed. There are no ledger, pin, header, build-profile or
baseline changes; stale insertion annotations and incorrect source prose were
removed from the lookup owner.

A paired check at one fixed index (5366c4f808, 2026-10-20 12:21), with all nine
actual current-source objects, changes 7/9 clean units and 1,656 linked bytes
to 8/9 clean units and 1,768 linked bytes: **+112 linked existing bytes**.
The old census's 776-byte figure is not the before measurement. There are
**zero new unique recovered bytes**. Remaining ThingTemplate blockers are
outside this repaired lookup/comparator closure.

Reproduce with the ordinary `build.sh`, `eh_verify.py`, and `link_check.py`
on ThingTemplate, STLWeaponTemplateSetBitFlagsHintedInsertUnique,
SparseMatchFinderWeaponCompare17, SparseMatchFinderWeaponLowerBound17,
Rva002CF86FCreate, stlport_rb_tree_0033c646_insert, StlSweepR3Rva0033CBAD,
SparseMatchFinderWeaponMapIndex17, and AnimationSoundTreeFree. Run
`place_bodies.py` on the two edited sources without `--apply`.

Local immutable before/after COFF objects, source hashes, dependency receipts,
full command logs, and failed diagnostic source variants are preserved in
`build/weapon-find-batch2/`. No failing body remains in Code.
