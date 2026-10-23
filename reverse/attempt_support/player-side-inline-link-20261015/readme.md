# Player side getter emission repair

Six private Player views emitted a standalone getSide() COMDAT that conflicts
with the census-selected copy. Their matched callers already inline the field
read. Read the established AsciiString member at +0x58 directly and remove the
unused accessor definitions. ScriptActions replaces four padding bytes with
that same field; two small views expose their existing field. Compiler flags,
other members, row identities, sizes and pins stay unchanged.

The original getter has no incoming relocation from retained nondebug sections
in any of these six objects. Comparing saved, strictly verified original objects
with current objects proves that each removes only
`?getSide@Player@@QBEABVAsciiString@@XZ`. All 313 retained COMDATs keep their
complete bytes, sizes and relocation bindings. All retained nondebug sections,
external bindings and weak externals also compare exactly. Local relocation
targets are compared by section contents, extent, flags and offset; SafeSEH
symbol indices are normalized to their bindings. Debug sections are excluded.
The comparison and original snapshots remain under ignored
build/player-side-inline-link-20261015; hashes and current self-strict receipt
results are in object-proof.json.

## Measurement and limits

Base checkout: 4b7e7091c4dd659f6f123ec7f25cb75a1a178344.
Census index: 28269d8e8d, 2026-10-15 09:31; SHA-256
6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
Both previews use this unchanged index, refreshing the explicitly checked
objects in memory. Census, link_status.csv and measurement history are untouched.
Before includes a seventh trial consumer, StatsCollector, which was restored;
only the following six are changed and counted.

| Consumer | Before | After | Existing bytes passing legacy local preview |
| --- | --- | --- | --- |
| PlayerDoFindCommandCenter.cpp | getSide conflict | Clean | 0 -> 94 |
| ControlBarScheme_setControlBarSchemeByPlayerTemplate.cpp | getSide conflict | Clean | 0 -> 817 |
| CastleBehaviorGetCampDiameter.cpp | getSide conflict | Clean | 0 -> 154 |
| ScriptConditions_evaluateSkirmishPlayerIsFaction.cpp | getSide conflict | Clean | 0 -> 78 |
| ScriptActions.cpp | unresolved Object command + getSide conflict | Object command still unresolved | 0 -> 0 |
| AIPlayerTeamBuild.cpp | getSide and other findings | Other findings unchanged | 0 -> 0 |

This removes six COMDAT findings and gives a **legacy local preview gain of
1,143 existing matched bytes** across four consumers. All six current objects
have **self-strict reusable receipts**. New authored retail bytes: **0**.
Closed-strict closure, a full link cycle and a new census have not been measured.
No claim about the retail identity or canonical layout of the remaining getter
copies follows from removing unused definitions.

ScriptActions still needs
`Object::doCommandButtonAtPosition(const CommandButton*, const Coord3D*, int, int)`.
AIPlayerTeamBuild retains eight unresolved names and its existing STLport,
ThingTemplate, BuildListInfo and AIUpdateInterface COMDAT/selected findings;
link-after.txt lists every one. Those require separate supported repairs.

## Acceptance

- Bounded link_check.py --prepare-current: six current strict receipts.
- ./build.sh on all six sources: 73/73 matched rows, 48 string literals plus
  four empty-string references and 21 float literals pass; no named imports.
- EH verification: 25/25 EXACT, no baseline debt or missing objects. The
  ScriptActions funclet at 0x007830C8 is verified through its unchanged parent
  EH data after a local label renumbering.
- COFF comparison: only the six unused getter definitions disappear.
- Local link_check.py: four of six clean; expected exit 1 for the two units
  retaining independent findings. --new-variants passes.
- find_declared_unmatched.py and class_gate.py pass.
- data_check.py --converged: eight addresses, zero second names or unjudged
  rows; shadow data check: zero findings.
- place_bodies.py rescan: zero bodies, zero pins.
- check_csv.py and git diff --check pass.

## Target and reference evidence

The existing BFME 2 source/ledger and byte-exact caller accesses establish the
+0x58 field and reference use for these particular views. No target identity or
layout is imported from BFME 1. Its retained verified pointer is
`a7c38d3b2597121f178ab5190b3062478823257d`. The ZH Player header at
inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
provides the semantic side-field accessor lead, but returns AsciiString by value;
it does not establish the BFME 2 return ABI or offset. Reviewed upstream linking
repair b4db1bfad3e4738c7762049fffbbddbb1405bab0 concerns AIPlayer::queueUnits,
a different dependency, and is inapplicable here.

The BFME 1 freshness update is outstanding: upstream was fetched, but the
submodule file is under a live foreign claim (codex-6bc6-20261008). Its clean
checkout and committed pointer were preserved and no successful-check stamp was
written. Complete comparative full verification before advancing that pointer.

StatsCollector was tried once with the direct field expression. The existing
105-byte collectUnitCountStats row at 0x00437B4D grew to 107 bytes: LEA became
MOV/ADD and a string literal PUSH moved. Its original source was restored and
its claim released; the blocker is recorded through re_log.py with model and
duration. No nonmatching reconstruction is left in Code/.

No full census, link cycle, nightly or boot runner was started.
