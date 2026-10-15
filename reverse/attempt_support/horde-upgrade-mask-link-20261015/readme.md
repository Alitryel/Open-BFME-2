# Horde upgrade-mask iterator link repair

Base BFME 2 checkout: `2f90b52cc0fc89ab2039483c1c68e202784b3dbb`.
The retained runner index is refreshed at `19a2565407`, 2026-10-15 09:33,
from census `5986a99448`, 2026-10-15 04:52. `context.json` records its hash.
Both preview phases deep-copy that same index and refresh only the explicitly
prepared current `HordeContainApplyUpgradeMask.cpp` object in memory.
No census, status, ledger, shared header, pin, baseline or data owner changes.

The unit's list and set loops now resolve to local typed `operator!=`
overloads that compare the same node pointers. This removes two incidental
external iterator-base COMDATs. The list-base copy was judged nonretail;
the tree-base copy differed from the first selected copy (no retail address).
Target evidence is the existing whole 401-byte horde interface worker at
RVA `0x00472444`, its verified call relocations and exact EH graph. Its
address-derived identity and existing layout evidence remain unchanged.
No name or layout is inferred from these helper bytes.

## Controlled result and checks

- Ordinary `./build.sh Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp`:
  3/3 existing rows exact, complete folded body verified, string/float/import
  checks pass without baselines or skipped references.
- Before and after bounded `link_check.py --prepare-current`: same 3/3 rows
  verified and strict reusable self receipts. Source/object hashes and receipt
  hashes are recorded in `proof.json`; before inputs remain under the ignored
  scratch directory `build/horde-upgrade-iterator-link-20261015`.
- All 49 retained external COMDATs have identical raw bytes, sizes and
  relocation digests. All other nondebug sections and link directives are
  identical, normalizing local label targets and EH symbol indices. Only the
  two unwanted external bindings disappear. Each replacement is a static
  12-byte comparison helper; neither original nor replacement has a nondebug
  caller relocation. No import, undefined name or weak alias is added.
- Paired bounded local legacy previews: findings **2 -> 0**, LINKS **0 -> 411
  existing unique authored bytes** (401-byte worker and 10-byte EH handler).
  The 34-byte generated erase twin is not counted as authored growth.
  Prescribed ordinary `link_check.py SOURCE` independently reports LINKS.
- EH verifier: 1/1 EXACT, zero baseline or missing-object rows.
- Data enforcement: zero findings; converged-data check: eight addresses,
  zero second names and zero unjudged rows. Declared definitions, class gate,
  new-variant admission, case-collision, CSV and whitespace checks pass.
- Placement resweep: zero new bodies or pins.

The normal pre-commit identity shadow check still reports four findings:
upgrade-template vector `push_back` binds to a different identity at
`0x004DFCB0`, and the Object-list iterator constructor, `begin` and `end`
definitions diverge. The retained-object proof shows these bodies and their
references are unchanged by this repair. They remain separate identity debt;
the shadow gate is not an executable-placement acceptance result.

New authored executable C++ bytes: zero. Strict receipts establish object
currency. This local legacy preview does not measure self-strict executable
placement or closed-strict dependency closure. No full census, full link cycle,
nightly, boot test or other maintainer-only runner was started. Broader linked
image verification remains outstanding.

`proof.py`, run from the repository root, reproduces the object and paired
preview assertions using the saved scratch objects and the identical index.

## Reference review and remaining blocker

The donor checkout and verified gitlink remain clean at
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`351a5f56997636351b22fa3e9349428c612f36d5`. The overdue comparative full-gate
pointer update is foreign-claimed (`file:reference/open-bfme-1`,
`codex-6bc6-20261008`); retain verified inputs and the overdue success stamp.
No successful freshness update is claimed.

Reused and inspected donor repairs `d3f9000fe08615a100e844adfff57fa4a39cd615`
(TileData constructor suppression) and
`de59a7e9f891b3ed2d4221d151ca881f4b75a583` (Apt predicate reconciliation).
Their principle of removing or reconciling incidental competing helpers while
preserving retail callers applies; their classes and data layouts do not.
No donor implementation or ABI is imported. Typed comparisons follow the
already-verified BFME 2 tree-iterator and audio-completion repairs. This unit's
own object comparison, byte gate and EH check establish preservation.

`link_check.py --fetch-index` successfully retained the identical current local
index and populated the matching published object store. No measurement was
manufactured from unavailable per-row artifacts.
