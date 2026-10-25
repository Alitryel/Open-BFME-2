# GameClient consolidation follow-up, 2026-10-25, codex3

Scope: `Code/GameEngine/Source/GameClient/`. Continued the preserved two-commit
batch from the previous session without discarding its changes or initial
untracked generated assembly and reverse/zh_sweep inputs. Read current AGENTS.md
and consolidation workflow, pulled/rebased, and passed check_csv. The BFME 1
freshness receipt (2026-10-24 04:42 UTC) is under 72 hours old.

## RadiusDecal parser

Prerequisite 93c3230942 supplies the parser fragment's existing static declaration
to the destination class view, with an INI forward declaration. No fields,
compiler flags, hatches or body statements change. All six original rows and
three float literals freshly verify. The supported dry run now accepts the
parser; the prior missing-member composition failure is cleared for this donor.

The claimed merge accepts RadiusDecal.cpp and RadiusDecalParseTemplate.cpp:
seven rows preserved, one source removed. Fresh ./build.sh verifies 7/7;
find_declared_unmatched and check_csv pass. The map diff is a single source-column
repoint, not a map regeneration. Mixed donors remain intact. The GameLogic
update/xfer donors still lack a baseline match at this destination, clear needs
its destructor declaration, and setOpacity needs a compatible shadow view.
Those unchanged blockers were not repaired or relabelled as coverage regressions.

## Publication audit

Fetched origin/master=ce5e16cd06. Reviewed origin/master..HEAD (preserved
LoadScreen prerequisite and handoff plus 93c3230942) together with the staged
RadiusDecal merge. The complete pending path move is
RadiusDecalParseTemplate.cpp -> RadiusDecal.cpp. Searched its full path, basename
and stem across tools, hooks, workflows, Code/includes, docs, reverse registers
and root build/configuration files. Remaining mentions are historical link_status
and generated provenance/placeholder comments. No active hard-coded consumer,
include or protected-register key needs repair. Source ledgers are repointed;
the fresh destination receipt is used. Local audit output:
build/gameclient-session2-path-audit.txt.

Accepted file/RVA claims remain held until confirmed publication. Rejected donor
claims are released separately. Publication runs only with the commit through
/opt/runner/publish; a deferred batch remains the runner's responsibility.


## GameWindowGlobal canonical string context

Prerequisite 2f2ea4eeb3 removes the donor-wide header environment and uses the
registered BFME 2 UnicodeString header, with callable-only declarations for the
two existing GameWindowManager bodies. The rowed names preserve virtual
winMakeColor and nonvirtual winGetTextSize; no complete manager layout or slot
is asserted. Both original rows verify. The old duplicate donor/canonical
AsciiString composition failure is cleared for winFindFont.

The supported merge accepts the existing TU and GameWindowManager_winFindFont:
three matched rows preserved and one fragment removed. The two other approved
addresses remain in mixed Common sources, untouched. Only functions.csv and
current tu_map source columns are repointed; no map regeneration is staged.

Expanded the batch consumer audit to both absorbed paths (RadiusDecal parser
and GameWindowManager_winFindFont), using full paths, basenames and stems across
active tools, hooks, workflows, source/includes, build/configuration files and
registers. Remaining references are historical link_status, retained donor
provenance and generated placeholder comments. No active consumer or protected
register key needs a transfer. Audit output remains in ignored build/ reports;
accepted claims stay held while the runner defers publication.

Fresh destination build verifies 3/3, find_declared_unmatched and check_csv pass.
The pre-commit hook supplies the normal data, identity, ownership, include, EH,
case and byte checks. The fetched upstream may advance independently while the
batch waits; source-path audit concerns the outgoing commits plus staged merge,
not unrelated upstream changes that will be retained by the publisher's rebase.


## RadiusDecal opacity and confirmed publication

The seven-commit batch landed through 70a67784ed via /opt/runner/publish. The
push hook verified 39/39 rows across four sources, five exact EH rows, ten
converged addresses, strings and floats. Landed file claims for LoadScreen,
GameWindowGlobal and the parser fragment were released; release --landed ran.
Rebased prerequisite identities include 3d1fcc4261 (parser), 54265e4418
(GameWindowGlobal), and 70a67784ed (opacity).

The opacity prerequisite uses the real Shadow pointer type for the +0x04
holder and explicit casts for the observed position prefix. Target call identity
is the already rowed Shadow::setOpacity at 0x003308F6. It declares the existing
RadiusDecal::setOpacity without changing fields, flags, pins or hatches. All
seven old rows and three float literals verify. The supported merge then accepts
RadiusDecal_setOpacity.cpp, preserving eight rows and removing one fragment.
Fresh destination build verifies 8/8 and four float literals; frozen-body and
check_csv checks pass. The current-map diff repoints one source column only.

The complete pending batch after the confirmed push contains only this opacity
move. Audited the fetched origin/master..HEAD plus staged move across active
tools, hooks, workflows, source/includes, build inputs and registries. Remaining
old basename references are historical link_status, generated provenance and
comments in Rva0029A469/ScriptActions_Rva003BC37C describing the verified pattern.
No active consumer or protected register key needs changing. Earlier parser/font
moves were audited and published in the preceding batch.

The remaining clear/destructor donor is outside the destination scope and has
a different field vocabulary and virtual release view; a guessed destructor
declaration alone would not reconcile its layout. Other GameLogic donors still
lack baseline matches at this destination. Their source is left intact.


## MetaEvent record reconciliation

Prerequisite 4ec781d6ee reconciles the seed's observed MetaMapRec fields with
the rowed 0x001DB537 allocator: integer key/transition storage, category and two
canonical UnicodeString words make the same 0x24-byte record. A forward
record declaration and the existing protected getMetaMapRec callable let the
merge compose it. The 819-byte translator and its TheMetaMap data row freshly
verify before and after this prerequisite. No global definition changes.

The supported claimed merge absorbs MetaMapGetMetaMapRec.cpp: three rows
preserved, one source removed. Fresh build verifies 3/3 and the existing data
row; find_declared_unmatched and check_csv pass. The map diff only repoints two
source columns. The deleting helper still lacks its callable and virtual layout
in the composed MetaMap; it is outside the donor-preparation scope. Other
sources are mixed or protected and remain intact.

The normal hook reports a shadow wrong-name finding for the unchanged
TheMessageStream reference at RVA 0x00A00950. The cached data_ledger calls that
provisional address TheMessageStream, but data_ledger.load reconciles the
explicit verified owner MessageStreamSubsystem from data_rows. The same
TheMessageStream declaration and calls exist in origin/master's original
MetaEvent source. No alias, data definition, baseline or register was added;
all enforced converged-address checks pass. Reconciliation belongs to the data
owner, outside this consolidation pass.

Before this commit, the complete pending moves are opacity -> RadiusDecal and
MetaMapGetMetaMapRec -> MetaEvent. Audited the fetched outgoing commits plus the
staged merge with their combined full paths, basenames and stems across active
tools, hooks, workflows, source/includes, build inputs, docs and registries.
Only historical census/attempt records, source provenance/placeholder comments
and pattern-reference comments remain. No active consumer or protected-register
transfer is needed. Local audit: build/gameclient-session2-opacity-metaevent-audit.txt.
The prior published parser/font audit is unchanged.


## Styles initializer compile environment

The seed now spells its existing bool fields and callable signatures directly,
so a donor-local unsigned-char Bool alias cannot reinterpret those signatures.
The GameWindow view declares the already-rowed winSetEnabledImage callable
used by MainMenuScaleUpTransition::init. Its donor keeps its original byte
fields and uses literal 0/1 in place of private NULL/FALSE/TRUE macros, avoiding
conditional-definition interactions in the composed translation unit. No layout,
call identity, compiler flags, pin or hatch changes. Fresh builds verify all
eight existing bodies and three float literals; frozen-body checks pass.
The supported dry run now accepts the seed and this donor (eight rows).
Remaining private-base field vocabulary, FullFade coordinate views, mixed and
protected donors are still rejected and untouched.

Before the prerequisite publication call, refreshed the complete pending opacity
and MetaEvent path audit against fetched origin/master. No new path move is in
this prerequisite. Active tools/hooks/workflows, source includes, build inputs
and registries have no stale consumers; remaining mentions are historical or
source provenance/placeholder/pattern comments.


## Styles initializer merge and cumulative audit

The supported merge accepts MainMenuScaleUpTransitionInit.cpp into the retail
styles TU: eight rows preserved, one actual fragment removed. Fresh destination
build verifies 8/8 with its string and three float literals; frozen-body and
ledger checks pass. Only one source column in each function ledger and current
TU map changes; no regenerated map or protected register is staged.

The full pending range now has three moves: RadiusDecal_setOpacity,
MetaMapGetMetaMapRec and MainMenuScaleUpTransitionInit into their respective
retail destinations. Searched full paths/basenames/stems across active tools,
hooks, workflows, source/includes, build/config inputs, docs and registries.
No hard-coded build/include consumer requires repair. Historical census,
attempt logs and source provenance/placeholder/pattern comments remain.
Local combined output: build/gameclient-session2-three-moves-audit.txt.

The old initializer has a generated ms_header_queue entry for NULL/FALSE/TRUE.
NULL and the donor-local macros were already eliminated in prerequisite
75db5f4784, whose standalone byte check passed. FALSE/TRUE are the destination's
existing queue item, unchanged and still served by repair_queue.ms_header_items.
That picker filters nonexistent sources. Thus no unique remaining finding is
hidden by this move, and no header debt or queue retirement is claimed. The
owning tool's read-only scan was retried; its Wine preprocessing probe still
drops standard headers, consistent with the previous handoff. Queue and tools
remain unchanged; this is classification of redundant generated entries.


## TextOnFrame initializer prerequisite and publication retry

Reconciled the initializer's private record with the destination's already
rowed update/reverse view: the +0x10 argument is that view's m_startFrame,
with the existing +0x14 end frame. Removed its unused NULL guard and used
bool literals instead of donor-local TRUE/FALSE definitions. No new name
identity, field offset, callable, flag, pin or hatch is asserted. The complete
62-byte initializer verifies independently and its frozen-body check passes.
The supported dry run accepts it with the destination, preserving nine rows.

The five-commit batch passed pre-push verification: 46/46 bodies over four
sources, four exact EH records, one data row, strings/floats and ten converged
data addresses. GitHub then rejected its pack with a remote temporary-pack
rename/storage failure. A concurrent claim fetch replaced FETCH_HEAD before
the publisher retry, which stopped with Cannot rebase onto multiple branches.
No rebase is left active; the five commits remain queued after its successful
initial rebase. Claim fetches and subsequent publication are now serialized.

The MS-header diagnostic confirmed kitchen sink prefix does not preprocess
with empty diagnostics. It then waited for other index-building threads;
the read-only diagnostic was interrupted once the failure was established.
No queue or gate was edited. The prior three-move consumer audit remains
current for this prerequisite, which introduces no additional path change.


## FullFade coordinate and base view prerequisite

The private donor used four adjacent integers where the destination uses the
canonical eight-byte ICoord2D at +0x18/+0x20. Reconciled it to the existing
destination base, virtual declarations and coordinate fields, and rewrote only
the coordinate accesses. The existing color helper now has the destination's
identical expression. Both private W3DDisplay declarations expose the already
rowed rva0004D6B3 and rva0008EEF0 callables, with an Image forward declaration.
No global, flag, callable target, pin or hatch changes. No external donor
layout/name is claimed as target evidence. Both complete FullFade bodies
(114-byte update, 197-byte draw) and all eight destination rows freshly verify;
frozen-body checks pass. The supported dry run accepts the seed plus FullFade
and TextOnFrame initializer, preserving eleven rows.

Claimed the exact FullFade draw at 0x0035F369; an accidentally requested
0x0035EA05 and its automatically attached Common file claim were released
immediately without editing either source. Before this prerequisite's publish
call, fetched origin and confirmed the prior three pending moves have no new
active path consumers. The prospective five-path audit also finds only the
redundant macro queue rows, historical records and source comments. No further
path is removed in this prerequisite commit.

## FullFade and TextOnFrame merge

Applied the supported three-file merge into GameWindowTransitionsStyles.cpp:
eleven rows retained and two actual fragments removed. Fresh ./build.sh checks
11/11 rows, one string and four floats; find_declared_unmatched and check_csv
pass. The map diff changes only three source cells, preserving routing evidence.
No protected register, shared header, compiler flag or hatch is changed.

Fetched origin and audited all five pending absorbed paths across the outgoing
commits (fork d0c913e6dd through 2753f90c4f) plus this staged merge. Direct
origin/master..HEAD also shows newer upstream Apt changes in reverse; these
are unrelated upstream changes, not outgoing moves. Combined full-path,
basename and stem search covers tools/hooks/workflows, Code includes, root
build/configuration files, docs and registers. Remaining references are the
already classified redundant MS-header macro rows, historical census/attempt
records and source provenance/placeholder/pattern comments. The destination
macro queue finding remains served; no debt retirement is claimed. No active
consumer needs repointing. Local evidence: build/gameclient-session2-five-final-audit.txt.

## Constructor follow-up

Rva0035DB3FTransitionCtor's private base view can be reconciled at the same
observed offsets, and its standalone 71 bytes still verify. The supported
composition then reports bytes rather than the original missing-base-field
compile error. The attempt is reverted, recorded with re_log.py and both file
and RVA claims released; its store-order subobject/barrier is untouched. No
unverified constructor body remains in Code.

TextOnFrameTransitionCtor's existing base and derived views are reconciled with
the destination: the same +0x04/+0x08/+0x09/+0x0a/+0x0c prefix, explicit derived
constructor, and its pre-existing destructor/empty virtuals. All field offsets,
virtual order and native call targets stay fixed. Both views use the destination's
existing names; no new identity claim or external layout is asserted. Removed
redundant donor Bool/macro aliases. Fresh standalone verification passes all
12/12 rows across the two files, four floats and one string; frozen checks pass.
The supported dry run accepts both for twelve rows. This prerequisite introduces
no source-path change; the complete five-move consumer audit remains current.

## TextOnFrame constructor merge

Supported merge accepts the constructor and styles seed: twelve matched rows
preserved, one fragment removed. Fresh destination byte check passes 12/12,
with one string and four floats. Frozen check and check_csv pass. Only one
source cell in functions.csv and tu_map.csv is repointed. Rejected donor file
and RVA claims are released; accepted claims remain until publication.

The combined audit now covers all six pending absorbed paths (the prior five
plus TextOnFrameTransitionCtor) through 9c3022cc6b plus the staged merge, from
fork d0c913e6dd after fetching origin. The constructor's only additional mentions
are historical link_status, provenance/placeholder comments and its redundant
FALSE/TRUE MS-header queue row: those macros were removed in the verified
prerequisite and the destination's existing finding stays served. No unique
debt is hidden or retired. Combined active-tool/hook/workflow/include/build/
registry audit finds no consumer needing repair. Evidence:
build/gameclient-session2-six-audit.txt. Existing upstream-only changes are
excluded from outgoing move inventory; no generated TU map is staged.

## Display virtual/data view prerequisite

New evidence-backed prerequisite for the prior Display composition failures:
combine the already rowed display-mode callable order (width/height slots
0x38/0x3c, getters 0x40/0x44, mode 0x58) with the height/width bodies' observed
+0x0c/+0x10 fields and DrawStaticImage's +0x68 three-element array. These are
BFME 2 facts in the existing rowed sources, not external donor offsets. Kept
the existing 0x18-byte element and direct DrawStaticImage callable, adjusted
padding for the existing vptr, and used the same declaration in all three
files. No body statement, virtual call index, function name, global, flag,
pin or hatch changes. A missing Int typedef in the first height trial was
fixed with the equivalent int spelling before verification.

Fresh ./build.sh verifies 5/5 rows across Display, DisplaySetDisplayMode and
DisplaySetHeight, with eight float literals. All frozen checks pass. Supported
dry-run now accepts all three files/five rows, clearing the old missing
DrawStaticImage/m_staticImages failure for these two donors. Other private
views and protected/mixed donors remain rejected. Local report:
build/display-session2-dry2.txt. This prerequisite moves no path; fetched
origin and the prior complete six-move consumer audit remains current.

## Display merge and last path audit

The supported merge retains five matched rows in Display.cpp and removes
DisplaySetDisplayMode.cpp and DisplaySetHeight.cpp. Fresh destination build
verifies 5/5 with eight floats; frozen check and check_csv pass. The staged
map contains only three source-column repoints, preserving route evidence.
Rejected donor claims and the previously landed seed RVA claims are released.

The preceding eleven-commit batch landed through d9f789c76e. Its push hook
verified 55/55 rows across seven sources, four exact EH records, one data row,
strings/floats and ten converged data addresses. GitHub rejected the initial
pack upload; the publisher's own serialized retry succeeded. No bypass was
used. All accepted file claims for those landed merges have been released.

Fetched origin/master=a57891e839. The only pending source-path changes are the
two Display absorptions; prior six pending moves are now published. Searched
both old full paths, basenames and stems across active tools, hooks, workflows,
Code/includes, root build/configuration files, docs and registries. Remaining
matches are historical link_status, source provenance/placeholder comments,
and different still-live W3DDisplaySetDisplayMode paths matched by substring.
There is no old-source header/name-basis key or active build/include consumer
to repoint. Original EA/history references are preserved. Local audit evidence:
build/display-session2-final-audit.txt. Audit scope is d9f789c76e..HEAD plus the
staged merge; no other locally outgoing move remains.

## Session result and handoff

Five retail TUs consolidated: RadiusDecal, GUI/GameWindowGlobal,
MessageStream/MetaEvent, GUI/GameWindowTransitionsStyles, and Display. Ten
actual fragments removed; thirteen body rows moved, with 31 distinct original
and moved rows preserved across the verified destination snapshots (upstream
later added unrelated GameWindowGlobal rows). Nine prerequisite commits were
verified separately. This is file consolidation, +0 newly authored C++ bytes,
not a fresh linking or image-ownership measurement.

Final progress.py origin/master reports BYTE-MATCHED 7,978,500 (100.00%),
authored C++ 7,249,368 (90.86%), LINKING 7,343,016 (97.74%), LINKED 7,598,950
(95.24%), all deltas zero. Link figures remain the 2026-10-25 09:42 census at
d2636bb381. No maintainer-only runner or ownership recorder was started.

Scoped queue was refreshed with tu_skeleton --queue --under
Code/GameEngine/Source/GameClient/ --limit 20. Previously recorded private-view,
mixed/protected-register and header-owner/Wine probe blockers remain. The
Rva0035DB3F constructor composition attempt was reverted and logged; standalone
71-byte equivalence does not establish a safe composed merge. New queue entries
from upstream routing, including Keyboard and ControlBarResizer, were not
investigated this pass and are eligible for a fresh next session. No assertion
that all scoped work is blocked is made. Read the prior handoff before repeating
unchanged Drawable/Snow/header-consumer or naming-history trials.

If this final merge is deferred by the shared push slot, the runner publishes
it. Keep exactly the Display destination and two removed donor file claims
until that publication is confirmed, then release them and settle/release
0x0025C262, 0x0025C378, 0x0025C391, 0x0025C3AA and 0x0025D33B. Earlier accepted
claims and all rejected/abandoned work are released. Initial untracked gen_asm
and reverse/zh_sweep files are preserved. No unfinished source edit remains.

## Keyboard merge and follow-up blockers

Fetched origin/master before work; the scoped planner snapshot passed
`name_lane.py consolidate --check`, then the in-memory TU map queue surfaced a
fresh Keyboard entry. The approved merge accepted `KeyboardKeyAccessors.cpp`
and `KeyboardResetKeys.cpp`, preserving 12 rows in `Keyboard.cpp`. Fresh
`./build.sh Code/GameEngine/Source/GameClient/Input/Keyboard.cpp` verifies 12/12;
`find_declared_unmatched.py` reports no unmatched definitions. The tool
repointed three function rows and three TU-map rows. This is mechanical
consolidation, with no new matched bytes.

Leave the other Keyboard donors for a Sol prerequisite pass. Dry run rejected
`KeyboardCheckKeyRepeat.cpp` with duplicate `_STL::allocator` and
`KEY_STATE_DOWN` definitions; `KeyboardRva00232A42.cpp` because `getPrintableKey`
is absent from `Keyboard` and `KEY_NAMES_COUNT` is undeclared;
`KeyboardRva00232AE8.cpp` and `rva00232B7BRva00232B7BFarm.cpp` with duplicate
`_STL::allocator` / `_STL::_Vector_base` template definitions. The plan also
refuses `KeyboardInitKeyNames.cpp` and `KeyboardInitUpdate.cpp` because they are
keyed in protected path-keyed registers. No prerequisite was edited here.

Combined pending path audit covers the prior Display merge and this Keyboard
merge. Searched old source names and stems across active tools, hooks, workflows,
Code/includes, root configuration, docs and registries. Remaining hits are
source-provenance comments, historical ledger records, or still-live files; no
active consumer required a manual repair. Audit range is origin/master..HEAD
plus the staged Keyboard move. Historical EA paths remain intact.

## ControlBarResizer merge

The fresh queue also offered ControlBarResizer. Its current plan had seven
approved rows; dry run accepted all three donors unchanged, moving eight rows
including the TU's already-local row set. `./build.sh` verifies 8/8, including
four float literals, and `find_declared_unmatched.py` reports all definitions
matched. The merge repointed six function rows and four TU-map rows. The mixed
FontLibraryInit donor remains untouched.

Updated combined tooling compatibility audit covers origin/master..HEAD and
the staged ControlBarResizer move, including the earlier Display and Keyboard
absorptions. Search of active tools, hooks, workflows and Code/includes found no
path consumers needing a manual repair; remaining hits are source comments,
provenance and still-live references. Historical EA paths remain intact.

## GlobalLanguage accepted donor and blockers

The scoped GlobalLanguage dry run accepted only GlobalLanguageInitBFME2.cpp (two
rows). `GlobalLanguageAdjustFontSize.cpp` failed composition at generated line
136 with `C2144: syntax error: 'void' should be preceded by ';'` and
`C1004: unexpected end of file found`; the STL list clear donor failed the
byte check. The accepted donor's fresh build verifies 2/2 rows, five literals,
one empty-string reference, and twelve named imports; the frozen check reports
all definitions matched. Other mixed files and rejected donors were untouched.

After fetching and rebasing onto origin/master, all four moved TUs were rebuilt
successfully and frozen checks passed. The final compatibility audit covers the
rebased origin/master..HEAD range plus the staged GlobalLanguage move. Search
across active tools, hooks, workflows and Code/includes found only merge
provenance or still-live source comments for absorbed paths, with no consumer
requiring repair. Historical EA paths are preserved.

## RadiusDecal dry-run blocker

RadiusDecal's current plan had four pull donors and three mixed files, but the
merge dry run accepted none. `GameLogic/Object/Update/RadiusDecal.cpp` and
`RadiusDecal_rva00330F7D.cpp` each failed with `no baseline match`;
`RadiusDecal_clear.cpp` failed compilation because the seed view does not declare
`RadiusDecal::~RadiusDecal` (`C2600: cannot define a compiler-generated special
member function (must be declared in the class first)`). No files were changed
or claimed; this needs a Sol prerequisite/reconstruction review before retry.

## WOLLoginMenu accepted donors

The WOLLoginMenu plan had 42 approved rows. Dry run accepted three donors
unchanged: Rva005CA53EFinish.cpp and the STL list tree erase/cleanup sources,
for six rows total. `stlport_string_list_pair_cleanup.cpp` failed the byte
check and remains untouched. The applied merge repointed six function rows and
five TU-map rows; fresh build verifies 6/6, one string literal, and the frozen
check finds no unmatched definition.

The final combined path audit covers the five local TU merges after rebase plus
the staged WOLLoginMenu move. Searched old donor names across active tools,
hooks, workflows and Code/includes. Remaining hits are merge-provenance comments
or historical/still-live references; no consumer needs a manual update. Full
range: origin/master..HEAD plus staged WOLLoginMenu files.

## GameWindowGlobal dry-run blocker

GameWindowGlobal's plan had five approved rows and two donors. The merge dry run
accepted none; `GameWindowManager_winFindImage.cpp` failed compilation with
`C2039: 'winMakeColor' is not a member of 'GameWindowManager'` in the composed
TU. No files were changed or claimed. Reconcile the declarations/header view in
Sol's prerequisite lane before retrying; the other donor was not applied.

## Additional dry-run blockers from this seat

- `SwayClientUpdate_xfer.cpp` was rejected in the composed TU: `BfmeXfer.h`
  reports `C2061: syntax error: identifier 'Snapshot'`. No donor was accepted;
  its constructor and pool-key files remain refused by protected registers.
- `Rva001DB66ADelete.cpp` was rejected into MetaEvent: `C2039: 'rva001DB66A'
  is not a member of 'MetaMap'`, followed by `C2673` for that global function.
  No donor was accepted; two other files remain refused by protected registers.
- `Rva00356413Method.cpp` was rejected into LoadScreen: `C2143: syntax error:
  missing ';' before '*'` and `C2501: 'TheWindowManager': missing
  storage-class or type specifiers`. No source repair was attempted; the other
  donor passed unchanged and was merged separately.
- `Shell_isAnimFinished.cpp` was rejected into Shell: `C2039: 'isAnimFinished'
  is not a member of 'Shell'` and `C2065: 'm_60': undeclared identifier`.
  ShellAudioPredicate.cpp passed unchanged and was merged; no class repair was
  attempted for the rejected donor.
- `Rva00538ADCFinish.cpp` was rejected into WindowLayout with `C2039:
  'rva00538AB0' is not a member of 'BfmeQuickMatchScreenBase'` and
  `C2065: 'm_head': undeclared identifier`; its default constructor donor
  separately failed `C2600` because the composed class view does not declare
  that constructor. No donor was accepted or changed; `window_layout.cpp` rows
  remain protected-register refusals.
- `RandomSoundSelectorClientBehaviorXfer.cpp` was rejected into its TU because
  `BfmeXfer.h` reports `C2061: syntax error: identifier 'Snapshot'`. The
  `getSelectedValue` donor passed unchanged; no declaration repair was attempted.
