# RainOfFireUpdate composition prerequisite, 2026-10-25

Allocated family A shard 1/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`.
Reviewed the scoped Update planner's original-path evidence, alternatives,
compiler flags, protected donors and mixed routing; its currency check passed
before editing. `tu_skeleton.py --plan TU` and the ordinary merge dry-run use
current routing rebuilt in memory. No source, map or ledger row is moved.

Before: ordinary `tu_skeleton.py --merge TU --dry-run` accepted no donors.
Slot1's incompatible RainOfFireUpdate declaration hides update, while composition
hoists BfmeXfer.h above its required Snapshot/operand declarations. A private
RainOfFireUpdateView.h now shares the existing update layout with Slot1 and Xfer,
keeps those operand declarations with their include, and declares the existing
base xfer/loadPostProcess and secondary-interface operations. Fields retain
retail offsets: frame at +0x24, four floats at +0x28 through +0x34, interface at
+0x20, total 0x38. The setters and xfer use the shared field spellings.

After: the same ordinary dry-run accepts all three eligible sources together:
RainOfFireUpdate.cpp, RainOfFireUpdateSlot1.cpp, RainOfFireUpdateXfer.cpp;
five rows, 1,028 retail bytes. This is a demonstrated unblock for Luna, not a
confirmed Luna landing. Ctor, dtor, module-data ctor and pool-key sources remain
protected; two mixed sources remain outside this subset. Their distinct views
and explicit vtable providers still need separate reconciliation before those
rows can join. No claim is made about those providers' ABI reconciliation.

Checks and ignored build receipts:
- ./build.sh all three: 5/5 exact; string (one literal), float (ten literals)
  and import checks pass. find_declared_unmatched.py passes all three.
- allowed_symbols APIs over the scoped sources: 18 references, 17 owner and one
  certified fold, zero wrong bindings; complete refs.tsv unchanged before/after.
- _object_defs over fresh baseline and final objects: every external code
  definition digest, extent, COMDAT exclusivity and undefined reference name
  identical. codex4-rain-object-defs-{before,after}.json.
- The ordinary dry-run's composed object e2f76f279651412c.obj has exactly the
  union of those same external code definitions, no new/changed/missing ones.
  Scanning its five rows with allowed_symbols gives the same 18 correct
  references. data_check.object_facts gives identical DIR32 bindings and defined
  data per source between the separate and composed objects, with no unread
  rows (codex4-rain-composed-data.txt). No selected code provider changes.
- data_check.py --converged after final build: three sources, ten addresses,
  zero second names and zero unjudged rows. An earlier check raced the final
  rebuild and correctly refused stale objects; the completed rebuild and retry
  above passed. EH: zero requiring EH, zero missing objects.
- link_check.py --new-variants all three exits 0. MS-header audit show reports
  all three clean and /MD=yes; seed retains its preexisting reference-header
  observations. No edited source has an identity, data or header queue key;
  the untouched pool-key donor retains its data identity finding.

Complete publication compatibility audit: pending commit 86e1cb7a3a plus this
staged change, relative to merge base 2538d83cfd (origin advanced independently),
has no source moves/absorptions. Reviewed origin/master..HEAD and isolated the
actual outgoing paths with origin/master...HEAD; the unrelated upstream-only
changes are not this batch. Active tools, hooks, workflows, includes, build
inputs and registries require no repointing. Only the three edited consumers
include the new private header; all compile and compose together. Protected
registers, historical EA paths and existing debt keys remain intact.
File reduction, identity debt retired and recovered C++ bytes are each zero.

Additional verification for pending UpgradeModule prerequisite 86e1cb7a3a:
its ordinary dry-run composed object 543b1ebf442f7472.obj contains the identical
union of the original external code definitions (none new/changed/missing), and
its five rows have 14 owner references, zero wrong bindings. The earlier
Upgrade handoff's thirteen-reference count concerns only its two edited sources.

Read-only allocated trials skipped without edits/claims:
- WindowLayout: seed and finish donor accept (three rows); default-ctor view
  has seven incompatible vtable slots versus seed's nine, and a different field
  view. Declaration-only guessing could select a different emitted provider.
- RadiusDecalUpdate: no accepted donors; ctor-thunk, update and Xfer views
  disagree on base-interface layout; Xfer also has operand include ordering.
- ProjectileStreamUpdate: seed plus Common/Rva0033EF86 accept; Xfer requires
  Thing/Xfer reconciliation, GetAllPoints requires canonical GameLogic/Coord3D
  header adoption. Ctor/pool-key donors remain protected.
- RadarUpgrade: documented in preceding Upgrade handoff; constructor and getter
  accept, implementation needs Object/class-view reconciliation.
Previous-session ClickReaction, AIGuardRetaliate, BridgeScaffold, ShipSlowDeath,
LivingWorldCampaign and PlayerTemplate evidence remains in their own handoffs.

Keep these claims until publication confirms: RainOfFireUpdate.cpp,
RainOfFireUpdateSlot1.cpp, RainOfFireUpdateXfer.cpp, RainOfFireUpdateView.h and
0x004AC135/0x004AC18D/0x004AC1CB/0x004AC227/0x004AC2A8. Pending Upgrade claims
are listed in its handoff. No merge has been applied in this session.
