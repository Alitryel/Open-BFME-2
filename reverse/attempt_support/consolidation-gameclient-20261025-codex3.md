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

## Transition styles merge and expanded path audit

The supported merge accepts seven files into GUI/GameWindowTransitionsStyles.cpp (seven matched rows), removing six fragments. FullFade init and TextOnFrame update/reverse already have identical TRUE/FALSE header-audit findings at the destination. Their old generated queue entries become redundant and are filtered by repair_queue.ms_header_items when their source disappears; the destination remains served. Owning-tool refresh was attempted and failed as described above; no debt or baseline entry was retired. Other rejected donors need Bool declaration ordering, missing ScoreScaleUp fields, or baseline-byte investigation. All protected/mixed files remain unchanged.

Expanded audit: locally outgoing commits from 91fe970939 through 664c1d9fbe plus staged styles merge. Combined old paths/basenames/stems for RadiusDecal_ctor and the six styles fragments were searched across active tools, hooks, workflows, sources/includes, build inputs, docs and registries. No hard-coded active build or include consumer requires updating. Old source mentions in link_status, re_attempts and provenance comments remain historical. Function/TU-map source columns are the only live registry changes. Protected registers are unchanged. Fresh destination byte verification, frozen checks and normal hooks are the acceptance evidence. File/RVA claims for accepted fragments remain held until publication; rejected donors are released.

## Display merge

The supported merge retains Display.cpp and absorbs Rva0025C3AAVideoRect.cpp: two matched rows, one file removed. Other eligible donors fail on private Display views missing DrawStaticImage/m_staticImages, or mismatched Rva0025C6E2Elem members. Mixed and protected donors were left untouched. Routing was rebuilt in memory; the committed map was not regenerated.

Expanded path audit covers local outgoing 3e23ecd519, 664c1d9fbe, f5cd0417d4 plus the staged Display move. Added the video-rectangle old path/basename/stem to the combined search. Its only remaining mentions are historical census/attempt evidence and generated source provenance; no additional active consumer was found. The function ledger is repointed, protected registers unchanged. Destination build and frozen-body checks are required before commit. The styles hook also reports the pre-existing FullFade alternatename as unreferenced in shadow identity mode; it was retained without adding a hatch.


## VideoPlayer merge and cumulative publication audit

The supported merge absorbs six donors into VideoPlayer.cpp (six rows), removing five net source files. The six-row fresh byte build and frozen-body check pass; check_csv remains clean. GameEngineDeletingBaseDerived2 stays separate because the composed SubsystemInterface Bool declaration fails; mixed/protected donors were not changed. Original VideoPlayer origin evidence is ZH/BFME1 EA structure and approved target routing, not a recovered BFME2 literal path. The allocator's existing address-derived name and STLport marker remain intact.

After fetching origin/master=777d0ff0aa, audited the four locally outgoing commits 3e23ecd519..c3fe3cdeea plus staged VideoPlayer moves, together from session base 91fe970939. Combined full-path, basename and stem searches cover all fourteen absorbed paths across active tools, hooks, workflows, source/includes, build inputs and registries. The map diff changes only six source columns. No affected active consumer was found for the VideoPlayer paths. The Bfme5NinetyTwoRandom -> abs_randwc name-basis entry is a different file, and historical donor prose, census and attempt records remain unchanged. Protected registers are unchanged. The complete staged list and outgoing rename status were reviewed; normal hook acceptance remains required.

## Additional consumer blockers

GameWindow dry-run preserves 35 rows from eleven files, but Rva003145B1Dispatch has two inferred parameter name-basis records. Rename landing/check logic resolves those through file-kind history; tu_skeleton's source-column repoint does not supply that history. No merge was applied. Shared repoint/history support needs its own tooling lane.

WOLLoginMenu dry-run accepts two donors / three rows, but Rva005CA53EFinish has a sole ABI MS-header queue item. The owner tool cannot refresh it in this environment (empty preprocessing probe fails). Deleting the donor would hide that item; no merge applied.

GameFont dry-run accepts eighteen files / eighteen rows, but Rva002186EBDtor has the sole Rva0007DF07 header-adoption queue item at that source. Its acceptance command would point to a deleted file. No merge applied; retain canonical-header debt until its owner supports the move or adoption succeeds through its normal path. Logs: build/gamefont-merge-dry-run.txt and build/gamefont-path-audit.txt. The remaining two donors fail a private element member and duplicate STLport declarations.

Blocked Snow and Drawable records above were made on BFME_MODEL=gpt-6.1-sol; their initial log evidence omitted the model suffix. All blocked trials were dry runs without new claims. Accepted merge file/RVA claims remain held while the batch awaits publication.
