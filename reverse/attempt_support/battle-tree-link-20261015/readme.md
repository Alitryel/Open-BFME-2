# LivingWorldAutoResolveBattle tree comparison link repair

Base measurement: `e0b779b4f6`. The battle TU emits an unused external
STLport base-iterator inequality that disagrees with the selected copy.
Use the established TU-local typed node comparison instead. Game bodies,
layouts, headers, compiler flags, pins, globals and ledger rows are unchanged.

## Controlled evidence

The frozen runner index measures `19a2565407` (2026-10-15 09:33), based on
census `5986a99448` (04:52); context.json records its exact hash. The committed
status queue instead measures `28269d8e8d` (09:31). Published-index fetch kept
the newer local index and fetched current available objects. No census,
per-row data-back ranking or index/status rewrite was performed.

Before and after `link_check.py --prepare-current` each verify **33/33** rows
and establish strict current receipts for this explicitly owned source.
Paired local refreshes of only this consumer against independent copies of
the frozen index show **12 -> 11 findings**. Exactly the tree-base comparison
conflict disappears; every other finding is identical. Legacy local LINKED
remains **0 -> 0**, with **2,412** existing nonpadding authored bytes in the
unit. No self-strict placement or closed-strict gain is claimed.

All **201 retained COMDATs** have identical bytes, extents and relocation
digests. Normalized nondebug sections change only by replacing an unused
18-byte external comparison with an unused 12-byte static typed comparison.
Neither has a nondebug caller relocation. Other normalized sections,
relocations, external bindings and directives are identical. The comparison
provider is unchanged. Local compiler labels are compared by destination;
all **7/7 EH graphs are EXACT**, and the byte gate resolves renumbered funclet
labels from verified parent EH data.

## Acceptance and handoff

- `./build.sh`: **33/33**, one string and two float literals verified.
- `link_check.py --new-variants`, class gate and declared-definition check pass.
- Enforced data checks: zero findings; eight converged addresses, zero aliases.
  Paired data facts/findings are identical. Identity shadow findings remain
  **18 -> 18**, zero new findings; existing findings are preserved verbatim.
- Ordinary local link check exits 1 for the eleven remaining findings,
  consistent with paired proof: vector copy/destroy/range-insert/overflow
  conflicts and selected copies, plus less<int>.
- `place_bodies.py`: zero bodies/pins. Ledger and diff checks pass.

Full placement and closed-strict verification remain outside this seat's
permission. No broader linked-byte improvement is asserted.

## Reference review and blocked independent attempt

BFME1 `de59a7e9f891b3ed2d4221d151ca881f4b75a583` supports consistent incidental
predicate ownership; BFME2's established typed comparison and target object
proof support this adaptation. New upstream `66b19a8e9` allocation suppression
was reviewed and is unrelated. Donor checkout remains clean at verified
`a7c38d3b2597121f178ab5190b3062478823257d`; official master was fetched, but
reference scope is foreign claimed and the previously documented full-gate
input blocker is unresolved. No pointer update or freshness-success stamp.

An earlier attempt in Rva000A7E9E reproduced its recorded unparented funclet
label false reject (9/10 byte rows despite 3/3 exact EH and 94 unchanged
retained COMDATs). The attempt was recorded, source restored, original 10/10
verification recovered, and its file claim released. No workaround was landed.

Scripts run from the repository root. Before objects and source backups stay
in ignored build/battle-tree-link-20261015; binaries are not committed.
