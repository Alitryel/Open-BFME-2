# LAN and skirmish iterator emission repair

BFME2 base: `ee6340d93f59392b937351f68a7cf72d68f1242f`.
Consumers: ChatWindowsLan.cpp and SkirmishAIManager.cpp, at the paths in
context.json. A TU-local typed tree-iterator inequality preserves their node
comparison and suppresses each unused conflicting external base comparison.
No compiler flags, shared headers, pins, ledger rows, data owners or class
layouts change. Existing identities and provenance remain unchanged.

## Paired evidence

The frozen runner index receipt is `825b86983f`, 2026-10-15 12:37; its underlying
census is `5986a99448`, 04:52. Index SHA256:
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
Discovery status was measured at `4b7e7091c4`; it is not used as the before
measurement. Both saved-before and current objects were refreshed into independent
in-memory copies of the same index. No census, index or link status was rewritten.

Current-object local findings decrease **4 to 3** for LAN and **21 to 20** for
skirmish. The paired proof asserts exactly the base-comparison finding disappears
from each and every other finding remains unchanged. Their 83 and 80 retained
COMDAT bodies, extents and relocation digests are identical. In each object, the
only section change replaces an unreferenced 18-byte external base comparison
with an unreferenced private 12-byte typed comparison. All other normalized
nondebug sections, external bindings, linker directives and data facts match.
EH/local symbol renumbering is normalized by actual targets.

Existing nonpadding authored bytes are 733 and 649. New authored C++ bytes: **0**.
Legacy predicted LINKED stays **0 to 0** in both. Strict current compilation and
byte receipts do not establish self-strict or closed-strict placement gains.
No full census, link cycle, nightly, boot or scheduler runner was invoked.

## Acceptance

- Bounded strict preparation passes all 4 LAN and 5 skirmish rows; normal
  `./build.sh` passes each whole file. One LAN string reference is verified;
  no unverified strings, float or import discrepancies. Existing parent EH
  data resolves the renumbered unwind labels without changing ledger pins.
- `eh_verify.py`: 4 EXACT, zero baseline exceptions or missing objects.
- `data_check.py --enforce`: zero findings; converged: 8 addresses, zero second
  names or unjudged rows. Paired data facts remain equal.
- Default local link check exits 1 with the documented remaining blockers.
  New-variant/staged-peer checks pass; normal commit hooks also gate landing.
- Class gate, declared-definition check, check_csv and whitespace checks pass.
  Affected-unit placement rescan finds zero bodies and zero pins.

LAN still needs its record constructor, fill provider and integer less helper.
Skirmish still needs addNewAIForPlayer, iterator/pair/allocator/vector providers,
and three wrong-selected providers. Exact names are in local-link-after.txt and
link-proof.json. The unchanged shared providers and their consumers need separate
supported repairs; this patch adds no provider variants.

## Donor review and scope

Reviewed BFME1 linking repairs `53d32d6b4b377317a3397971629ca3ad20b870e9`
(Apt string-constructor suppression) and `66b19a8e95a4add525ef808fcea088e306798e2b`
(Apt allocation-copy suppression). Their emission-only repair principle is
applicable, but this uses the already established BFME2 typed-iterator pattern;
no donor layout, address or source was imported. Retail verification establishes
the affected callers' invariance independently.

Official donor master was fetched at `6974867b784ad2e651a2e167853246afcb18e3b5`.
The clean verified checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Another worker owns the reference
scope. The last-success stamp is overdue and was not advanced. The earlier
old-input full-gate comparison remains incomplete with thousands of stale TUs;
that unchanged blocker and the live claim prevent a verified pointer update.
This repair retains the last verified inputs.

Discovery used repair_queue.py link and link_rank.py (rank, near and per-file).
Known unchanged blocked trials were not retried. CreateAHero was inspected but
released without edits because its body claims belong to another worker.
Both edited file claims are released after the commit.

Proof scripts are saved attempt evidence, not production tooling. Run from the
repository root in object/link/data order while the scratch saved objects in
build/chat-tree-link-20261015 and the frozen index remain available. JSON/logs
preserve the results; object binaries are not committed.
