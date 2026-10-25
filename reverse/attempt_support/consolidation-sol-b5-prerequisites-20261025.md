# Sol family B shard 1/2 prerequisites, 2026-10-25

Seat codexb5; allocation from `/opt/runner/consolidation_queue.py --limit 20`.
Started from clean d7fa8a31bf with no inherited session metadata or local commits.
Read current AGENTS.md, consolidation workflow/audit, claims and naming rules.
Initial pull and `python3 tools/check_csv.py` passed (98,252 function rows).

## Bridge allocator prerequisite verified

Target TU: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp.
The seed omitted the existing allocateBridgeBuffers method declaration; its
allocator donor used m_0C where the seed calls the verified counter at +0x0C
m_c. Add the nonvirtual declaration and use the seed's existing placeholder
in the donor. No layout, signature, body, flags or provider identity changes.

Before: normal merge dry run accepted nothing. After: accepts the seed and
W3DBridgeAllocateBridgeBuffers.cpp, preserving all 14 matched rows (10 seed,
4 allocator, including its two unwind funclets and handler). Local receipts:
build/sol-b5-bridge-before.txt and build/sol-b5-bridge-final.txt.
This demonstrates an allocator-subset unblock; no merge was applied and no
later Luna landing is claimed. The mechanical seat may merge that pair with
ordinary destination verification.

Checks: `./build.sh` on seed verifies 10/10; on allocator and the unchanged
loader verifies 5/5. Frozen-file checks pass for all three. Allocator
`eh_verify.py` reports EXACT 1, no missing objects or baseline exceptions.
Staged code-identity check: 14 rows, zero new findings in shadow mode.
Staged data checks: zero findings; converged data check: no second names or
unjudged rows. Neither changed source has header-queue, SDK-queue, data-debt
or code-identity-debt keys. No register key was retired.

Initial Bridge loader blocker: a declaration-only trial reached C2146/C2501 at
m_start because composition relocates Vector3 after W3DBridge's by-value
fields. The unused loader declarations were removed; loader source unchanged,
verdict recorded with re_log.py and its file/RVA claims released. Destructor,
vertex, load, ctor and refill donors retain their private-view/declaration
failures; getModelVerticesFixed remains protected-register keyed. Mixed donors
stay intact. The loader was subsequently reclaimed and repaired below. Do not
treat the ready allocator subset as closure for the TU.

## Bridge loader prerequisite verified

The follow-up hypothesis reconciles the two existing Vector3 views instead of
introducing a header or changing the composer. Both now use the seed's same
Vector3/WWMath declarations with the loader's existing copy constructor. An
identical type is emitted at its first occurrence, before W3DBridge's by-value
fields. The seed also declares the loader's existing nonvirtual loadBridges and
addBridge signatures, with forward declarations for their pointer arguments.
No layout, symbol identity, virtual slot, compiler flag or body was changed.

`./build.sh W3DBridgeBuffer.cpp W3DBridgeBufferLoadBridges.cpp` verifies 11/11
rows and three float literals; frozen-file checks pass; EH reports EXACT 2,
no baseline exceptions or missing objects. The normal merge dry run now
accepts seed, allocator and loader together, all 15 rows versus 14 before this
follow-up. Receipt: build/sol-b5-bridge-vector-build.txt and
build/sol-b5-bridge-vector-after.txt. This is a demonstrated three-file subset
for Luna, not an applied merge or confirmed downstream landing. Other Bridge
donor failures remain, including the AddBridge Region3D header-adoption queue.

## Bridge constructor prerequisite verified

The seed now declares the existing W3DBridge and W3DBridgeBuffer constructors.
The constructor donor uses the seed's existing m_c and m_padD7B4 spellings at
+0x0C and +0xD7B4. No field type, offset, body operation or compiler flag was
changed. Claimed W3DBridgeBufferCtor.cpp and 0x000DE52E in addition to the held
seed scope. Ordinary builds verify seed plus constructor 13/13 rows; frozen
checks pass; EH reports EXACT 3 without baseline exceptions or missing objects.
The normal merge dry run accepts seed, allocator, constructor and loader,
preserving all 18 rows versus 15 before this prerequisite. Receipts:
build/sol-b5-bridge-ctor-build.txt and build/sol-b5-bridge-ctor-after.txt.
No merge or subsequent Luna landing is claimed. Remaining rejected donors
have the same structural/view failures listed above; they were not retried
as independent unchanged attempts. Keep the constructor file and parent RVA
claims until publication as well.

## Other investigated allocation

W3DPropDraw normal dry run accepts the seed and module-data destructor but
rejects reactToTransformChange with Coord3D redefinition at Coord3DCtorView.h.
The react donor deliberately needs the destructor-bearing shared view for
retail EH. No source or claim was changed for that read-only trial; the
existing Prop handoff remains applicable. Receipt: build/sol-b5-prop-before.txt.

BufferedFile tooling false reject: the allocated WWLib/bufffile.cpp normal
merge dry run rejects the seed under every candidate flag set. Ordinary
`./build.sh .../bufffile.cpp` verifies 10/10 rows; composing only the seed
with its original flags also verifies 10/10. Reproducing `_merge`'s flag
selection drops managed `/arch:SSE /G7`, leaving Read (0x0061AE30) and Seek
(0x0061B000) mismatched, 8/10 rows. The destination is in flag_overrides.csv,
so Verifier.effective intentionally does not restore region defaults.
Composing seed plus BufferedFileClassConstructor.cpp with the seed's original
flags verifies all 11 rows. This isolates a composer flag-selection false
reject, not a source prerequisite. No tool, flags register or source changed;
no manual merge applied. Recorded via re_log.py; Read/Seek and automatic seed
scope claims released. Receipt: build/sol-b5-bufffile-before.txt and
build/sol-b5-bufffile-build.txt. A tooling owner should preserve overridden
managed flags in candidate selection and add a regression test separately.

Other allocated plans: DisplayStringManager's two donors live under Common,
outside this seat's family; retain the existing cross-family handoff.
Thread's constructor prerequisite is already verified in
consolidation-sol-thread-20261025.md and ready for Luna; lifecycle/yield remain
protected-register keyed. HTree's recent storage/split handoff already covers
its accepted subset; no unchanged prerequisite was repeated. PolygonRenderer
and LadderDefs are also already ready per the projectile handoff. NAT retains
cross-family declaration dependencies. No claim or source change was made for
these read-only plans.

GameInfo initial normal dry run accepted seven files and 28 rows (including one Common
donor); no merge applied. Remaining rejects: GameSlotSetState lacks isAI and
m_connectInfo in the chosen view; GetSlotNum differs in bytes; map-path donor
has TheGameState declaration ordering; destructor expects m_C8. Mixed and
protected donors remain. Receipt: build/sol-b5-gameinfo-before.txt. No source
edit or claim for this initial read-only investigation.

## GameInfo path prerequisite verified

Claimed GameNetwork seed, Rva00621350GameInfoMapPath.cpp, its 0x00400898
parent, and GameInfoSetMapSize.cpp. The Common portable-path donor stays
untouched. A GameState forward declaration in the seed allows the earlier
TheGameState pointer declaration while the combined view is emitted later.
The GameNetwork GameState view also declares the Common donor's two already
matched portable-path methods. MapCache's map-based view in SetMapSize now
declares the existing getMapExtension method used by the path donor. These
three declaration-only edits preserve layouts, flags, bodies and providers.

The forward-only trial accepted 34 rows but displaced SetMapSize. Declaring
both GameState path directions then exposed MapCache's missing inherited
find/end interface in the selected view; the MapCache reconciliation above
retains the map-based view and its extension method together. Final normal
dry run accepts all eight files and 37 rows, keeping every file in the old
28-row accepted set and adding the nine-row map-path donor. Receipt:
build/sol-b5-gameinfo-allpath-final.txt. This is ready for Luna; no merge or
downstream landing is claimed. SetState still needs isAI/m_connectInfo;
GetSlotNum's current chosen view lacks its declaration; destructor needs the
complete GameInfo lifetime/layout view. Mixed/protected rows stay in place.

Ordinary builds verify seed plus map-path donor 19/19 rows and SetMapSize
3/3 rows, including the original EH companions. Frozen-file checks pass
(the seed retains its existing one unclaimed definition). EH: EXACT 1 for
the map-path donor, EXACT 2 for SetMapSize, no exceptions/missing objects.
No applicable identity/header/data-debt keys were found or retired. No file
path changed; the outgoing compatibility audit still requires no repoints.
Keep these three source file scopes and 0x00400898 until publication.

## Reference freshness and outgoing audit

Official BFME 1 fetch found local 0bf534ea7ccde110c456edb9cd2dd5dae823c953
behind upstream f633d0e97a953289405438821be0c09b28527bbb. Retained the verified
pinned inputs, as in the prior consolidation-device-20261025.md freshness
handoff. No success receipt or reference-pointer update was invented. A
separate full verification/update remains necessary outside this lane.

The complete pending origin/master..HEAD range plus the staged prerequisite
has no moved/deleted sources. Active tools, hooks, workflows, includes, build
inputs and registries need no path repoints; historical EA paths are preserved.
Functions, data and identity owners remain unchanged. Provider/consumer code
and selected COMDATs have no new identity findings. File reduction: zero;
identity debt retired: zero; recovered C++/retail bytes: zero.

Keep seed, allocator, loader and this handoff file claims plus 0x000DD8B8 and
0x000DFB3C until
publication is confirmed. Release file scopes and settle landed RVAs afterward.

## Next-session publication recovery

Recovered the four clean, pending prerequisite commits through c3472f19b7.
Fresh `./build.sh` on all seven changed source files passes 40/40 rows,
one string literal and three float literals (receipt:
build/sol-b5-inherited-recheck.txt). The outgoing range contains only source
edits, this evidence file and the attempt log; no source move, deletion,
owner transfer or active path consumer needs repointing. Existing per-commit
identity/data/EH checks and composition receipts above remain applicable;
this recovery introduces no source change or new provider binding.

A fresh official BFME 1 fetch now finds local c0385ef6ba2031d152781f9a8343bfef40c7bd29
behind upstream 967c7e1cf5bbda24ea52f802caffa7164c1368ff. The checkout is clean.
Retained these existing inputs; full reference-update verification is still
pending outside this prerequisite lane. No freshness success receipt written.


## GameSlot state shared-view prerequisite verified

Target GameNetwork/GameInfo.cpp remains allocated to Sol B shard 1/2. The
current planner's original-path alternatives point to GameInfo.cpp (hints,
not merge approval); the normal TU resolver approves the donor. Claimed the
seed, GameSlotCtor.cpp, GameInfoSlotView.h, GameSlotSetState.cpp and 0x003FFC28.
The header has only those three source consumers after this adoption.

GameSlotSetState now includes the existing shared slot view instead of its
private GameSlot/SlotState/connect-info declarations. Added only the existing
nonvirtual isAI declaration; the body uses the view's text30 and connect38
names for its already-proven +0x30/+0x38 accesses. No layout or virtual slot
changed, and no new real field-name inference is claimed.

Before/after ordinary builds verify 29/29 rows across all three consumers,
six string literals, and three EXACT EH graphs. Frozen checks pass (the seed
retains its existing informational unclaimed definition). Class gate passes.
Normal merge dry run increases eight files/37 rows to nine files/46 rows,
retaining every previously accepted donor and adding all nine SetState rows.
Receipts: build/sol-b5-slot-{before,after}-build.txt and
build/sol-b5-gameinfo-{before,after}-slot.txt (the before receipt is named
sol-b5-gameinfo-before-slot.txt). No merge applied or Luna landing claimed.

Code identity checks have no binding/selected-definition findings before or
after (shadow, 29 rows). Direct allowed-symbol reports have zero wrong
bindings and identical alias receipts. The raw reference count falls 40 to
33 solely because seven existing SetState local funclet labels renumber;
the byte gate resolves each through the exact parent EH graph. Applying
build.located_funclet in memory to the scoped allowed-symbol scan recovers
all twelve consumer cleanup references: 45 total, 37 owner/5 alias/3 EH,
zero wrong. All seven state cleanups bind UnicodeString's destructor at
0x005B804E. Receipt: build/sol-b5-slot-eh-bindings.txt; no ledger pins edited.
Data checks have zero findings; converged: 10 addresses, zero second names
or unjudged rows. No relevant identity/data/header/SDK register key was
present or retired. Remaining GameInfo donor blockers are GetSlotNum's
missing declarations/chosen view and the destructor's incomplete lifetime
view; mixed and protected donors remain untouched.

Outgoing compatibility review: this prerequisite and the five inherited
pending commits contain no source-path changes. Incoming origin commits
must be excluded from a divergent-tip diff when identifying our outgoing
moves; the merge-base-to-HEAD range has only the seven earlier source edits,
this header/state edit and evidence. Active tools/hooks/workflows/includes,
build inputs and registries need no path repoints. The new quoted include
resolves beside the donor and all its consumers were verified together.
File reduction, retired identity keys and recovered retail bytes are each
zero. Hold these file scopes and parent until publication is confirmed.

Scoped Microsoft-header audit scanned the header and all three consumers: zero local Microsoft declarations or findings; no relevant queue rows to refresh.


## TreeBuffer type-lookup prerequisite verified

Target W3DTreeBuffer.cpp is allocated to this shard. Planner review retains
GameClient/W3DTreeBuffer.cpp as the lookup's path alternative, while normal
TU routing approves it; mixed/protected donors stay untouched. Claimed the
seed, W3DTreeBufferRva000ECDF5.cpp and 0x000ECDF5. The original normal dry
run accepts five files/22 rows. Moving the existing bfme2_ascii include path
first clears StringBase redefinitions for five donors, but by itself adds
no accepted rows (build/sol-b5-tree-include-after.txt). Their next failures
are private declarations/member views, not additional duplicate templates.

The lookup donor now uses the existing registered Rva000EC67F type record,
its m_string4C/m_string50 fields, and the seed's m_typeCount/m_44556 names.
The seed declares the two existing nonvirtual lookup/add-type signatures.
The donor adds the seed's WWMath include directory for the canonical record's
Coord2D include. No registered header, field offset, virtual slot, operation,
name ownership or optimization flag changed. No donor-source naming inference
was added. The new canonical include resolves beside both sources.

Ordinary builds verify seed+lookup 18/18 rows (17+1), two literals and one
empty-string reference. Frozen and class gates pass. EH: EXACT 2, no missing
objects or exceptions. Before binding reports sum to 40 references (35
owner/3 alias/2 EH); after the combined scan has the same counts, zero wrong.
Code-identity/selected-definition checks show no findings before or after;
data checks: zero findings, converged ten addresses with no second names
or unjudged rows. Neither file has a relevant identity/data/header/SDK queue
key, and no debt key was retired. The unchanged canonical header is not
hand-edited. Receipts: build/sol-b5-tree-type-{before,after}-*.txt.

Final normal merge dry run (build/sol-b5-tree-type-after.txt) accepts six
files/23 rows, preserving the prior five-file set and adding the lookup.
This is a demonstrated one-row unblock for Luna, not a merge or confirmed
landing. Remaining toppling/reset/morph/add/xfer donors retain their view,
base declaration, lifetime or protected-register blockers; EA327's prior
array/codegen attempts were not repeated. Common donors are outside this
seat's scope. The five include-blocked donors need those structural repairs
before they count as accepted rows.

Rebased the complete inherited range onto current origin/master. Incoming
source changes did not touch either target or their donors. The outgoing
range plus staged edit still has no path moves/deletions, so tools, hooks,
workflows, includes, build inputs and registries need no repoint. Historical
EA strings remain intact. The GameSlot header hook additionally reaches Eva.cpp
through its dependency closure and verified 56/56 rows over all four sources;
its direct includes remain the three Network sources documented above.
File reduction: zero; identity debt retired: zero; recovered retail bytes:
zero. Retain TreeBuffer seed/donor/RVA claims until confirmed publication.


## GameInfo slot lookup declaration prerequisite (2026-10-25)

Allocated GameInfo.cpp remains the target. Claimed the seed/shared view,
GameInfoGetSlotNum.cpp and 0x0040009A; the current network planner retains
GameInfo.cpp as a placement hint, with normal TU resolution approving the
move. Added existing nonvirtual getConstSlot/getSlotNum declarations to the
seed and the exact by-value UnicodeString isPlayer overload to the shared
GameSlot view. No body, layout, virtual slot, flags or provider changed.
The Unicode overload resolves the earlier chosen-view failure rather than
retrying the same incomplete declaration set.

Baseline lookup build: 4/4 rows. After declarations: 33/33 across GameInfo,
GameSlotCtor, GameSlotSetState and GameInfoGetSlotNum, six string literals,
four EXACT EH graphs. Frozen and canonical-class checks pass. Normal merge
dry-run now accepts ten files/50 rows, retaining all nine files/46 rows
from the state repair and adding all four lookup rows. Remaining rejected
single-owner donor is GameInfoDtor.cpp: incomplete member/lifetime view
(m_C8). Twelve mixed and two protected donors remain untouched. No merge
or downstream Luna landing is claimed. Receipts:
build/sol-b5-slotnum-{before,after}-build.txt,
build/sol-b5-gameinfo-after-slotnum.txt, and
build/sol-b5-slotnum-after-eh.txt.

Scoped allowed-symbol scan: 44 references, 34 owner/6 alias/4 EH, zero
wrong bindings. Existing standalone lookup body is unchanged, including
its getConstSlot and Unicode isPlayer targets. Code-identity check covers
33 rows, no binding or selected-definition findings (shadow). Data checks:
zero findings; converged ten addresses, zero second names or unjudged rows.
No identity debt retired. The shared-header consumer closure is also
verified by the full commit hook (including Eva.cpp).

Complete outgoing path audit: pending commits plus this staged change
contain no source moves/deletions. No active tools, hooks, workflows,
includes, build inputs or registries require path repoints. Divergent
origin-only changes are not outgoing path changes. The full staged diff
contains only existing method declarations and this evidence. File
reduction, identity keys retired and recovered C++ bytes are each zero.
Hold all still-unpublished file/RVA claims until confirmed publication.


## BuddyThread parser false reject and bounded fallback review

Allocated BuddyThread.cpp was investigated with the current Thread planner,
--plan and normal --merge --dry-run. The seed baseline verifies 6/6 rows,
53 literals and one named import. The baseline trial cannot keep the seed:
C2628, CallbackType followed by void, after the composer loses the enum's
semicolon. tools/tu_skeleton.py chunks() recognizes only optional template
and typedef before class/struct/enum/union; static enum is wrongly classified
as a function ending at its closing brace. The original standalone C++ is
accepted by MSVC 7.1 and the byte verifier.

Diagnostic only: remove static from the no-object enum declaration. This
preserves all six rows, literals and import, EXACT 3 EH graphs, 24 code refs
(17 owner/4 alias/3 EH), no wrong binding or selected-definition findings,
and no data/converged findings. The normal dry-run then accepts five files,
12 rows: seed, stlport_vector_pod2148_allocator.cpp,
S1PointerOrDefaultGetters.cpp, Rva00550995LockCleanup.cpp, and
stlport_queue_buddyrequest_ctor.cpp. This isolates the parser defect; it is
NOT a published unblock. Per AGENTS.md's false-reject rule, restored the
source exactly and recorded blocked through re_log.py (callbackWrapper,
0x00551FB3, 116 bytes). No workaround or gate change is landed. Released
file:Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp.
Receipts: build/sol-b5-buddy-before.txt, sol-b5-buddy-enum-after.txt,
sol-b5-buddy-{before,enum-after,restored}-build.txt. Remaining independent
Buddy prerequisites: duplicate private STL templates, FESL response view,
constructor string/class views and startThread field names. Twelve mixed
and six protected sources were not edited. A tooling seat should fix the
chunker with a static-enum regression test in a separate verified change.

Read-only fallback reviews: debug_io_con's prior factory/destructor handoff
already admits ten rows for Luna; do not repeat that completed prerequisite.
BufferManager's plan leaves slot methods in a protected donor; its seed
also has an admitted present-unmatched accessor, so no speculative edit was
started. Apt's clean CleanPool donor belongs to Common, outside this seat's
family; leave it to its assigned owner. No claims were taken for these
reviews. Existing unchanged PropDraw, bufffile and Tree SSE blockers above
were not retried.

Outgoing audit through this handoff: no source moves, ledger repoints or
protected-register changes in this seat's batch. Source restoration is
verified before commit. Active path consumers need no repair; historical
EA paths remain intact. Buddy diagnostic gains are excluded from progress.
