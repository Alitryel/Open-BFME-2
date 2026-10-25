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


## Transition handler, EyeTower, MetaEvent and animation trials

GameWindowTransitions dry-run accepts four files / seven rows; EyeTower accepts Aim + PushBack / two rows. Both would delete a source with the sole MS-header audit item at that path (critical-section imports and atan2 respectively), so neither was applied. These are consumer blockers in addition to remaining private-view/baseline failures. Refining the empty-header probe with build.compiler_environment's WINEPATH changes the failure to cl D2021 for the raw POSIX temporary filename, proving the owning tool also needs Wine argument handling. No tool, queue or shared environment was changed.

MetaEvent dry-run accepts no merge: the composed MetaMap needs record declarations before getFirstMetaMapRec, and the deleting donor lacks its member declaration. ProcessAnimateWindow accepts no merge: duplicate ICoord2D and missing finished member. Its grandfathered present-unmatched definitions and hatch register were untouched. Frozen checks report existing bodies as matched; no source changes or new claims were made for either trial. Do not repeat these unchanged trials without their declaration/header prerequisites.

## WindowLayout merge and expanded audit

The supported merge writes WindowLayout.cpp from BfmeQuickMatchScreenBaseSlot4.cpp and Rva00538B2FFind.cpp: two matched rows preserved, one net source removed. The differently named window_layout.cpp remains protected and separate; mixed sources are unchanged. Rva00538ADCFinish fails incompatible private BfmeQuickMatchScreenBase members and remains separate. Current in-memory routing approves both moves despite unresolved/stale planner hints; the planner itself does not approve them.

Fetched and reviewed origin/master..HEAD (five locally outgoing commits 3e23ecd519..34ec8d11f7) plus staged WindowLayout moves, with cumulative own changes from 91fe970939. Extended the same combined consumer audit to all sixteen absorbed paths. The two new old paths have no live consumers except the source ledgers the merge repoints. No protected register, header queue or name-basis key is changed. Historical census, attempts, original EA evidence and provenance comments are retained. The new destination needs the fresh byte/frozen checks and normal hooks before commit. Claims for accepted merges remain held until confirmed publication; rejected donors are released.


## Publication and remaining small trials

The six-commit batch landed through 4e835ab16a. The push hook verified 50/50 rows across six sources, four exact EH rows, ten converged data addresses, strings and floats. All twenty-one accepted file claims were released after confirmed publication; release --landed found no remaining queued RVA claims. Five retail TUs preserve 23 moved/retained rows and remove fourteen net source files. The RadiusDecal prerequisite separately preserves six original rows. This is consolidation progress, not newly recovered C++ bytes or a census linking claim.

Further dry runs (no new claims or applied moves): GameWindowGlobal fails canonical BFME2 versus ZH AsciiString redefinitions; HeaderTemplate's lookup donor has no baseline match under the destination verifier; RandomSoundSelector and SwayClientUpdate fail forward-declaration ordering before BfmeXfer; Shell accepts only its audio predicate, with isAnimFinished and m_60 missing in composition. RandomSoundSelector and LoadScreen each initially accept only one donor, giving zero net file reduction. RayEffect was stopped at preflight because its donor carries three active inferred parameter-name basis records, requiring the same shared source-history support as GameWindow. Evidence and row boundaries are recorded in re_attempts.log. None is a coverage regression.

LoadScreen has a local prerequisite: expanded its existing 85 BFME_VSLOT invocations into the exact virtual declarations the macro generated, removing the definition/undef. This preserves slot names, order, types and flags while letting the merge engine hoist declarations without depending on donor-body macro placement. The original two rows freshly verify byte for byte; frozen checks and normal hooks remain required. Before this prerequisite's publication call, fetched origin/master=ae10f71a0a and reviewed the outgoing range and staged paths: no unpublished source moves remain, no new path consumer is introduced, and protected registers are unchanged. The next merge must regenerate its planner snapshot because this source changed.


## Final LoadScreen result and handoff

Prerequisite 2b72483017 passed the original two-row byte build, frozen check, data checks and normal commit hook. The refreshed planner passed --check. The new dry-run now accepts LoadScreenUpdates, confirming the macro fix, but rejects Rva00356413Method because the merged GameWindowManager declaration follows TheWindowManager's extern. Further composition also needs the existing NetworkInterface/window-manager virtual views reconciled (different member names and coverage). No merge was applied and zero files were removed for this prerequisite. Do not retry the unchanged composition. The source remains byte-exact, with no added hatch or flags change.

Final scoped queue was inspected with tu_skeleton --queue --under Code/GameEngine/Source/GameClient/ --limit 20. Its remaining entries are the previously recorded compile, canonical-header/consumer, protected-register or mixed-donor prerequisites; the Shell tail entry was also tested separately. No independent linking, naming or reference lane was taken. All blocked dry-runs were unclaimed; rejected claims from applied merges were released. The five landed TUs are RadiusDecal, GameWindowTransitionsStyles, Display, VideoPlayer and WindowLayout (14 net files removed; 23 rows preserved).

Final progress.py origin/master: BYTE-MATCHED 7,978,500 (100.00%); authored C++ 7,249,368 (90.86%); LINKING 7,343,016 (97.74%); LINKED 7,598,950 (95.24%). All deltas versus fetched origin/master are zero. Linking values are the 2026-10-25 09:42 census at d2636bb381, not a prediction or a fresh census. No ownership receipt was produced.

The publisher deferred 2b72483017 below its batch threshold. The final handoff commit calls it again as required. Pending batch audit is origin/master..HEAD plus this staged documentation/log update: only the LoadScreen prerequisite changes source, without moving a path; there is no pending source-path consumer update. The earlier sixteen absorbed-path audit landed with the six-commit batch. Initial untracked generated assembly and reverse/zh_sweep are preserved.

If the final publisher again holds this batch, the runner must publish it. Retained claims until confirmed publication: file:Code/GameEngine/Source/GameClient/GUI/LoadScreenUpdates.cpp, 0x00355FF9 and 0x00356082. After landing, release the file claim and settle/release those two prerequisite RVAs. No other session claims remain. Remaining work is ABI/header and shared path-consumer reconciliation described above, not a continuation of an unfinished merge.
