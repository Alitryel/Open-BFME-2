# Audio-completion timer helper ownership

At BFME 2 `7d35a1a0fabdee9d5431b68ae65b774efca8b7c0`, the two
280-byte audio-completion bodies already require a visible inline/noinline
`Rva00357DF8::rva00357DF8` definition for their established compiler shape.
That unit emits the retail-equal 28-byte callable body as well. The ledger
instead owned the helper in `ScriptEngineRva00357DF8.cpp`, whose strong copy
conflicted with the existing consumer copy. This duplicate was the only local
link finding in either unit. Move the helper row to the consumer and delete the
redundant unit; keep the C++ implementation unchanged.

## Measurement and evidence

`object-proof.json` records the frozen index hash and measurement metadata:
index `825b86983f` (2026-10-15 12:37), census `5986a99448`
(2026-10-15 04:52). Both before objects were prepared with
`link_check.py --prepare-current`, passing 3/3 total byte rows and 2/2 EH EXACT
rows, and saved before any edits. Their two helper copies have equal bytes,
normalized relocations and retail verdicts. After moving the row, the consumer
passes 3/3 byte rows with a strict reusable receipt and 2/2 EH EXACT rows.
All 39 retained non-debug COFF sections (including bytes, normalized
relocations, external bindings and flags) are unchanged.

For the paired local preview, load the same index and retail truth, use
`link_check.refresh` with both saved before objects under their original object
basenames, and call `check_object`: both report only the helper duplicate.
Then `link_check.forget` only the removed provider object in memory, refresh the
strict-current consumer object, and check the consumer: every finding list is
empty. The deleted provider has no remaining ledger rows. No persisted index,
status, census or link order is edited. This is 0 -> 588 locally linkable legacy
bytes, +0 authored C++ bytes; closed-strict closure is **not measured**.

The prescribed ordinary `link_check.py <consumer>` still exits 1 with the same
helper duplicate: its default bounded refresh retains the deleted provider's
old definitions in the saved index. It does not apply `forget` to units removed
from the ledger. This stale-index limitation is reported, not bypassed by an
index rewrite. A runner index refresh or a maintainer-authorized census can
measure the persisted result. No full link cycle was run.

Other acceptance checks: `find_declared_unmatched.py` passes;
`place_bodies.py` finds 0 additional bodies/pins; `check_csv.py`, converged-data
check, new-COMDAT-variant check and `git diff --check` pass. The commit hooks
provide the final staged acceptance checks.

## Other investigated blockers

The DX8 setter ownership attempt was reverted after two failed shapes: VC7.1
rejects out-of-class dllimport member redeclarations (C2761); moving the existing
full dx8wrapper shim before mapper.h changes mapper header precedence and the
Grid clone allocation (0x34 -> 0x30), breaking Parse_Mapping_Args bytes/EH.
Its strict baseline was 98/98 consumer rows, 4/4 native-owner rows and 9 EH EXACT
rows. The original sources, objects and receipts were restored. The blocked
attempt is recorded in re_attempts.log; a scoped setter-only declaration remains
necessary. No false-reject or improvement is claimed for that attempt.

BFME 1 linking donor review: inspected repair
`66b19a8e95a4add525ef808fcea088e306798e2b` in
`game/Libraries/Source/EA/Apt/Rva00893270.cpp` as a linking lead: its
forceinline/dllimport declaration suppresses an unused emitted COMDAT. DX8 use
is blocked by the declaration/header-precedence evidence above; no donor source
is imported by the audio helper rehome. Its basis is the two existing target
objects and verified ledger bodies.

The clean BFME 1 pointer remains `a7c38d3b2597121f178ab5190b3062478823257d`.
Fetched upstream master is `c3c5a59620585b5752df5861abfd7979010f485b`.
The reference path was claimed by another seat, and the preserved prior
freshness handoff reports a full-byte gate with 2,982 stale units (2,806 still
remaining after 21 minutes). This session preserves the verified inputs and
stamp, makes no pointer update, and does not mark freshness successful. That
shared update/verification remains outstanding.
