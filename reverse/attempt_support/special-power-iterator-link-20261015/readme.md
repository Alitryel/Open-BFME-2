# Special-power consumer: local iterator helper repair, 2026-10-15

At BFME2 base `7c6886694783db16a7e567f28077d75eaee677db`, use the existing
BFME2 typed list-iterator comparison pattern in
`InGameUICanSelectedObjectsDoSpecialPower.cpp`. The local overload compares the
same node pointers and leaves both matched definitions unchanged. It removes
an incidental, unused external base-comparison COMDAT which differs from the
selected provider under this unit's compiler settings. No ledger, pin, global,
class declaration, compiler setting or retail extent changes.

## Before/after evidence

Measurement index update: `19a2565407` (2026-10-15 09:33), underlying census
`5986a99448` (04:52). Exact index SHA-256 and base revision are in `context.json`.
Before editing, prepared the original consumer with `link_check.py
--prepare-current` and saved its genuine object and strict dependency receipt.
Prepared the changed consumer the same way. Both pass 2/2 matched rows.

`link-proof.py` refreshes separate in-memory copies of that unchanged index
with respectively the original and changed consumer. The legacy local preview
has **12 findings before, 11 after**: only
`??9_List_iterator_base@_STL@@QBE_NABU01@@Z` disappears. All other finding
collections agree. The unit still does not link; linked-byte gain and newly
authored matched bytes are both zero. This does not establish a self-strict or
closed-strict placement gain. No index, link status, census or executable link
was updated; maintainer-only broader verification remains outstanding.

`final-object-proof.json` establishes that all 45 retained COMDATs have identical
bodies, sizes and relocation digests. Every other normalized nondebug section
and linker directive agrees. The sole removed section is the unused 18-byte
external base comparison; two unreferenced 12-byte local comparisons are emitted
for the mutable and const iterator types. No retained section references the
removed helper or either added helper. Funclet label renumbering is resolved
through its verified parent EH data without any ledger/pin edit.

## Acceptance

- `./build.sh` consumer: 2/2 matched, literal/import checks pass.
- `link_check.py --prepare-current` before and after: strict reusable receipts.
- `link_check.py --new-variants`: passes.
- `eh_verify.py`: 1/1 EXACT.
- `data_check.py --enforce`: zero findings.
- `data_check.py --converged`: eight addresses, no second or unjudged names.
- `find_declared_unmatched.py`, `class_gate.py`, `git diff --check`: pass.
- `place_bodies.py`: zero additional bodies or pins.
- Commit hooks pass. Shadow code identity reports the existing unowned
  ActionManager binding and divergent `CommandButton::getOptions` definition;
  the controlled comparison proves their definitions/references unchanged.

Remaining blockers are the unrowed ActionManager location check at 0x0041D60B
and ten list/allocator COMDAT discrepancies. They require independent provider
or shared dependency work; this change does not claim to solve them. The
original object/receipt and current object remain under
`build/special-power-iterator-link-20261015`; published scripts and JSON preserve
the controlled comparison and method without committing compiled artifacts.

## Donor and instruction context

Reviewed BFME1 helper reuse repair `63e68aaa567add9eb42a79913d23eece6a19ceee`
and Apt predicate repair `de59a7e9f891b3ed2d4221d151ca881f4b75a583` from official
upstream master observed at `62e0a3b2ff8c9d9fbbcc31c58cb5b8baca5c4241`.
The applicable principle is eliminating surplus conflicting inline definitions;
the actual typed comparison is the established BFME2 pattern already verified
in other list consumers. No donor identity, layout or ABI is transferred.

The BFME1 checkout remains clean at verified pointer
`a7c38d3b2597121f178ab5190b3062478823257d`. Its overdue pointer update has a
foreign file claim and the previous full-gate baseline/dependency blocker.
Preserved those inputs, did not mark freshness successful, and did not repeat
that unchanged blocked trial. No decoder source was read.
