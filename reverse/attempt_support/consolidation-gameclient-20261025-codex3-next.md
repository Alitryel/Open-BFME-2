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
