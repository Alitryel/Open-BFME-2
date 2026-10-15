# Frame-rate consumer ownership repair

Base: `a9ac41bf81455297dca5c8ca4b7073848ced7ead`.
Local index receipt: `19a2565407`, 2026-10-15 09:33; underlying census:
`5986a99448`, 2026-10-15 04:52. Index SHA-256 and strict before/after source,
object and dependency-receipt hashes are in `proof.json`. The committed
link-status snapshot is a discovery lead only. No per-row data-back artifact
was available or used. Census, index, status and baselines remain unchanged.

Five consumers now declare and reference the existing sole four-byte owner
`BfmeLogicFramesPerSecond`, replacing `g_00DBA4E4`/`g_Va00DBA4E4`:

| Consumer | Row RVA | Retail extent | Corrected DIR32 references |
| --- | --- | --- | --- |
| Rva001E4DB0Ctor | 0x001E4ABE | 754 | 3 |
| RTS3DSceneRenderOneObject | 0x0006FB59 | 2550 | 1 |
| ScriptEngineRva0020A586 | 0x0020A586 | 121 | 1 |
| HordeMeleeSwarmFindMeleeAttackPosition | 0x00583D54 | 1443 | 2 |
| DynamicPortalBehaviourCreateWaypoints | 0x00460F90 | 711 | 1 |

The renderer has two C++ reads but one emitted relocation. No body is added
or extended. All nondebug sections, relocation offsets/types/addends, link
directives and external bindings are identical after normalizing only these
two old names to the owner. Ten address-named hatch occurrences disappear.
The provider's object is entirely unchanged, including debug information.

## Identity and provenance

For every changed row, retail operands and compiled relocation addends
independently identify RVA `0x009BA4E4` (VA `0x00DBA4E4`). The existing
data ledger and verified data row assign exactly this address to
`?BfmeLogicFramesPerSecond@@3HA` in ColdGlobalDwordGetters.cpp. Its initializer
is integer five, not the later runtime frame rate. The data gate verifies its
whole allocation and initializer. Existing ownership evidence is in
`../frame-rate-owner-link-20261014/readme.md`. The descriptive global name is
not claimed as an original debug symbol. No pin, alias, layout, body identity
or second datum is introduced.

Reviewed BFME 1 repair `92a8d854746f059994f8ab370c133f3ba71eec24`:
bind consumers to an existing data_rows owner instead of inventing a global.
This ownership principle applies; its debug-cell address and layout are not
BFME 2 evidence. No donor inputs are imported. The clean reference checkout
and committed gitlink remain `a7c38d3b2597121f178ab5190b3062478823257d`.
Official fetch found `1c4d808dd6a0f2bd514f607f40e9e422db3ab91b`; reference
scope is claimed by another worker. Comparative old/new full verification,
layout reconciliation and pointer publication remain that scope's blocker.
No successful freshness stamp is written.

## Acceptance and measured improvement

`link_check.py --prepare-current` over the five consumers and unchanged
provider passes before and after: 43/43 function rows, one data row, one
string literal plus one empty-string reference, 26 float literals and zero
named imports. All six objects have strict reusable receipts. These are
normal byte/source/data gates and self-currency evidence; they do not prove
self-strict placement or closed-strict link closure.

`proof.py` compares saved before objects against current after objects and
refreshes the same three measurable objects into independent copies of the
same index. The constructor changes from one unresolved global to no finding:
752 nonpadding retail bytes newly pass this local legacy preview. The
unchanged provider remains clean at 511 bytes; paired total is 511 -> 1263.
The renderer loses exactly its frame-rate unresolved name (eight findings
become seven); it remains blocked on FogEnable, W3DShroud rva0006F1FE, four
COMDAT choices and selected Set_Output_Ambient. See paired findings for names.

The other three consumers are absent from this index. Normal `link_check`
correctly refuses to give them a preview; no link order is manufactured.
Their byte-exact code and corrected binding/ownership are covered by the same COFF
comparison and target-derived data facts. No linked-byte gain is claimed for
them. `link_check.py --new-variants` passes all five edited consumers.

Converged-data enforcement passes all six sources: eight protected addresses,
zero second names, zero unjudged rows. EH verification passes both relevant
rows EXACT. Frozen-file, class gate, CSV integrity and diff checks pass.
Placement rescan of all five edited units returns zero bodies and zero pins.

The optional broader `data_check --enforce` remains nonzero: findings decrease
17 -> 12 and outside-baseline findings decrease nine -> four. Saved before
objects prove all four remaining findings predate this repair: FogEnable and
LODTextureReduction in the renderer, and g_Va00DBD0F0 plus
g_currentAptOnlineCustomMatch in the unchanged provider. There are no new data
findings and no baseline is edited. This is existing shadow debt, not an
acceptance waiver.

New authored C++ coverage is zero. No closed-strict gain, real link.exe
placement or data-back improvement is asserted. No full link cycle, census
build/measure/history, nightly, boot or scheduler operation was started.
BannerUIUpdate still has a frame-rate address binding, but another worker
holds its body claim; it is left for that scope.

## Reproduction

Scratch snapshots are in `build/locomotor-frame-global-link-20261015`.
`context.json` lists the six complete source paths; `before-N.cpp/.obj/
.deps.json` were copied only after strict normal verification. Reproduce the
before phase from the base tree with the same compiler inputs; preserve the
index named above and copy the strict objects and receipts before editing.
Run `python3 reverse/attempt_support/locomotor-frame-global-link-20261015/proof.py`
after `python3 tools/link_check.py --prepare-current <six sources>`.
The proof reads saved objects directly for the paired data check and never
replaces a live compiler cache or represents saved objects as current source.
Acceptance transcripts are retained here beside the structured proof.
