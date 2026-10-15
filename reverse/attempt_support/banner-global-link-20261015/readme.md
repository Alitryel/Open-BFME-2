# Banner singleton link repair, 2026-10-15

Define `class BannerUI; BannerUI *TheBannerUI = 0;` once in the existing banner
unit and rename nine consumers. The INI parser casts the canonical pointer to
its existing private view; no class layout is changed. No alias or second
address-bound datum is introduced.

Target facts: the existing BFME 2 constructor at RVA 0x00217211 names its
subsystem `TheBannerUI`; matched parse, init, update and destruction consumers
read the singleton at VA 0x00DFE32C. All four native storage bytes are zero.
Donor a7c38d3b2597121f178ab5190b3062478823257d independently defines
`BannerUI *TheBannerUI = 0` in
`game/GameEngine/Source/GameClient/InGameUICreateReplayControlThunk.cpp`.
The donor supplies identity evidence, not the target address or a class layout.
The private parser view remains a structural inference.

## Paired result

Base tree a48a9b5cfb691c334037127cd8723980d9ee671b. The local index is
19a2565407 (2026-10-15 09:33), census 5986a99448 (04:52), SHA256
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
Committed link_status describes another measurement and was discovery only.
Before and after refresh the same nine explicit objects in memory against this
same index. No index, census or status is changed.

- Unresolved findings: 23 -> 14; one old singleton spelling removed per source.
- Other findings unchanged: 15 losing COMDATs, four wrong selections, no
  duplicate definitions or hard-coded-address findings. Total: 42 -> 33.
- Clean units: 0/9 -> 1/9; AptInGameSpellBookInterface becomes linkable.
- Existing authored LINKED bytes in the legacy local preview: 0 -> 2,143
  (padding excluded). No new authored C++ bytes. No closed-strict gain claimed.

Both snapshots have strict-current compiler receipts. The complete object proof
normalizes just the two old singleton spellings to the canonical spelling,
then compares every nondebug section, including directives, bytes, extents and
relocations. All existing sections are identical; the owner adds one four-byte
zero-filled BSS section. There is exactly one canonical definition in the nine
objects and no old spelling. Strict receipts are checked again after the proof.
This is self-strict object evidence plus a legacy local link preview, not a
closed-strict closure or full link measurement.

## Checks

Before and after `link_check.py --prepare-current --paths-from sources.txt`:
147/147 matched rows exact; strings (36 plus 11 empty references), floats (24)
and imports (12) pass. Data ownership verification passes for the new four-byte
row. EH: 29/29 EXACT. Class, frozen-source and new-variants checks pass. Placement
resweep: zero new bodies or pins. CSV and diff checks pass.

The data ledger is generated with `tools/data_ledger.py --out build/...`; only
its 0x009FE32C row is copied back by the included merge script. Generation reports
512 unrelated sources missing objects, so no tree-wide freshness is claimed.
The row remains provisional because the separately claimed reset consumer still
uses the old spelling. No converged-address entry is added prematurely.

Enforced converged check passes across all nine sources (eight protected
addresses). The broader data identity check remains shadow debt: five findings
before -> four after, with no added finding, proved from saved before objects
and their old ledger against current objects and the updated row. The residual
four are g_pRva00224BC9 and existing military-subtitle/update static names;
`data_check.py --enforce` therefore exits 1. No baseline or whitelist changes.
The normal local link check exits 1 for the eight units with residual blockers.
The acceptance outputs and complete findings are included here.

`proof.py` repeats the paired comparison when the saved object snapshots in
`build/banner-global-link-20261015/` and this index remain available. Binary
snapshots are local scratch, not committed artifacts.

## Handoff

`Code/GameEngine/Source/GameClient/InGameUIReset.cpp` was claimed by another
worker and is unchanged. Rename its remaining `g_00DFE32C` reference/declaration
to the canonical class pointer, byte-verify it, then regenerate the data-ledger
row. Do not define the old spelling or introduce an alias. Remaining link
findings for the other eight consumers are in proof.json and link-preview.txt.
A full link cycle and closed-strict closure remain outstanding; no maintainer-only
runner was started.

The official BFME 1 master fetched this session is
6d787ff64618f5c2ab68c2eba99b8472c1c4eae9. The clean last verified checkout/gitlink
remains a7c38d3b2597121f178ab5190b3062478823257d. Updating that reference is held
by another worker and the prior full comparative gate needs thousands of stale
donor objects; no successful freshness stamp or pointer advance is claimed.

Other attempted repairs were restored and their claims released: snow override
getter suppression changes the parent optimizer shape; string-record dllimport
cleanup adds an unresolved EH import; two water comparator suppression forms
change both parents' frame/register shape. Their blocked verdicts and exact
boundaries are recorded in re_attempts.log. Their local scratch directories
contain the failed gates and restored passing gates. Do not repeat unchanged
trials; the original native byte gates pass after restoration.
