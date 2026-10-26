# Supply-draw pool-key declaration prerequisite

Seat codexb5, allocated family B shard 1/2, 2026-10-26. Destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp`.
This prerequisite declares the existing virtual `getModuleNameKey() const` and
uses the donor's existing NameKeyType enum. No name, method body, virtual slot
implementation, ledger owner, compiler flags or header changed.

## Demonstrated unblock

The current GameClient planner and `tu_skeleton --plan` approve ten rows,
three clean sources and three mixed sources. Normal merge dry-run initially
accepts none: pool-key compilation fails because the seed lacks the method;
module-data destructor fails bytes. With this declaration the normal dry-run
accepts seed plus `GameClient/Drawable/W3DSupplyDrawPoolKey.cpp`, five approved
rows/216 retail bytes (including the 10-byte EH handler). The pool-key pair
accounts for two newly compatible rows/79 already-matched bytes.
No merge was applied: Luna can take this compatible pair through the normal
merge and protected-key transfer path. No subsequent Luna landing is claimed.

The destructor donor still fails bytes because the seed's explicit-member base
view and the destructor's shared virtual-base view differ. The three mixed
sources need their existing routing/split prerequisites; Common donors belong
to family A. No destructor trial, manual split, speculative base/header change
or unrelated naming vote was made.

## Acceptance evidence

- `./build.sh DEST POOLKEY`: baseline 4 functions exact plus the existing EH row.
- `./build.sh DEST`: after edit, 3/3 exact, literals/floats/import checks pass.
- `find_declared_unmatched.py DEST POOLKEY`: all defined functions matched.
- `tu_skeleton --merge DEST --dry-run`: seed plus pool-key, five rows; destructor bytes reject persists.
- `name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/`, then snapshot check: current.
- `class_gate.py`: pass. Scoped `eh_verify.py`: one EXACT handler, zero missing/nonexact.
- `ms_header_audit.py scan DEST POOLKEY`: no local Microsoft declarations or definitions.
- `data_check.py --converged DEST POOLKEY`: ten converged addresses, zero second/unjudged names.

Ignored receipts/scripts use `build/sol-b5-supply-key-*`:
`proof.py` compares current standalone objects before/after, all five rows:
external definitions/digests, selected COMDAT flags, undefined symbols, eight
code references (six owner, one alias, one EH), and data facts are identical.
There is no added or changed emitted virtual table. This is the published
prerequisite's complete provider/consumer scope.

`composition.py` observes supported normal dry-run verification, captures its
object and re-verifies all five rows: six external providers retain bytes and
COMDAT flags, no definitions dropped/changed, no new unresolved names.
`composed-bindings.py` finds the same eight code references with no added/removed
bindings and no preexisting divergent scoped providers. `data-selection.py`
compares the composed object using the supported row-object fact helpers:
nine data bindings and zero definitions unchanged; all six external definitions
match their earliest scoped provider under current ledger link order. This
composition evidence uses current objects, not an old census or a link cycle.

The pool-key donor already reports two shadow wrong-name data findings for its
local guard/key (0x009EBB88/0x009EBB84). Its baseline still contains an older
address-derived method spelling. Before/after data facts prove these findings
are unchanged by the declaration. Preserve the existing data key and ledger;
a later merge must carry them and use `repair_queue.py retire data SOURCE`
only after a separate proven repair. No debt retirement is claimed.
No header queue keys are affected; the existing BoneStatus Microsoft-header
entry is unchanged. All identity/hatch registers remain untouched.

## Batch audit and publication handoff

Audited the complete own outgoing range (merge-base of current origin/master
and HEAD through HEAD, plus staged source/evidence): inherited buffer-release
prerequisite, restored ghost-object attempt, and this declaration. No source
path move/addition/deletion, include/build-input/registry repoint or historical
EA path change exists. Source consumers and protected registers are unchanged.
The shared linking obstacle register is held by codex4, so this scoped evidence
is the handoff; no link/ownership/census clearance is claimed.

Keep destination, pool-key and this evidence file's claims until publication
is confirmed; release scopes and settle landed RVAs afterward. Inherited buffer
claims and the ghost-attempt evidence claim remain pending with the same batch.
No recovered C++ bytes, source file reduction or debt retirement is counted.
