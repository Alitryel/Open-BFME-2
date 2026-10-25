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
