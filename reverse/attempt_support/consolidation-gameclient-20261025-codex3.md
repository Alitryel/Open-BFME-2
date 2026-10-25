# GameClient consolidation, 2026-10-25, codex3

Scope: `Code/GameEngine/Source/GameClient/`. Current planner and in-memory TU routing were used; no routing decisions were regenerated into the committed map.

## RadiusDecal

Reconciled the constructor view in a separate verified prerequisite: the retail constructor initializes the float at +0x0C; the shadow pointer now has the same declaration as the destination. Both original files verified (6/6 rows).

The supported merge accepts RadiusDecal.cpp and RadiusDecal_ctor.cpp: six rows preserved, one source removed. `./build.sh Code/GameEngine/Source/GameClient/RadiusDecal.cpp` verifies 6/6 with three float literals, and find_declared_unmatched reports all bodies matched. Other donors remain rejected: parse-template lacks its static member declaration; clear and setOpacity need private-view reconciliation; two GameLogic donors fail baseline verification at the destination. Mixed donors were not split.

## Blocked trials

* Drawable.cpp: dry-run examined 118 clean donors / 260 approved rows, exhausted flag sets and orders, and found no verified merge retaining the existing destination seed. MaxFrame 0x00271B03 and Frame 0x00271C1C had no baseline match at the destination. No source was changed. This is existing-placeholder cleanup, not a coverage regression. Do not repeat the broad trial without a new seed/compile-environment explanation. Local log: build/drawable-merge-dry-run.txt.
* Snow.cpp: WeatherSetting assignment 0x00201412 fails C2600 in the composed class. Seed and donor expose different bases and field ranges; both standalone files are frozen-check clean. The two-base donor and Overridable seed require ABI reconciliation, not a guessed declaration. No source changed. Local log: build/snow-merge-dry-run.txt.
* GlobalLanguage.cpp: only an STL cleanup donor is accepted (two rows); this would remove zero net files. AdjustFontSize fails composition around its existing inline x87 helper. No merge applied.

## Path audit

Audited prerequisite 3e23ecd519 plus the staged RadiusDecal move from the session base 91fe970939, including the complete locally outgoing commit range after fetching. The only absorbed path at this stage is RadiusDecal_ctor.cpp -> RadiusDecal.cpp. Searched full path, basename and stem in tools, hooks, workflows, Code, docs, reverse and build inputs. The remaining old mentions are historical census data and source provenance comments. Active function and TU-map source columns are repointed by tu_skeleton; the map diff contains only that source-column change. No affected hard-coded build consumer or protected register was found. Fresh build receipts verify the destination.

Preflight review also covered transition styles, GameWindow and WOLLogin candidates. Styles has redundant MS-header queue entries (the destination already has the same macro findings). WOLLogin has an old-source-only queue item; GameWindow has append-only parameter-name basis history. These need classification or consumer support before publication. The MS-header owning tool currently fails its empty-header preprocessing probe under this Linux/Wine seat (false return, empty stdout/stderr); no queue or gate was changed. These preflight findings do not claim those merges landed.
