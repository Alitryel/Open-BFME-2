# Keyboard resync declaration prerequisite — 2026-10-26 codex

Allocated family A, shard 0/2 destination:
`Code/GameEngine/Source/GameClient/Input/Keyboard.cpp`.
This recovers the previous session's preserved source edits and before objects;
no merge, split, rename or ledger movement is applied.

## Proven prerequisite and remaining work

The Input-prefix planner's original paths, alternatives, differing compiler
settings, private receiver/vector definitions and path-keyed registers were
reviewed. Its stale map is context only: `tu_skeleton.py --plan` and ordinary
`--merge --dry-run` rebuild routing in memory. There are 23 approved rows,
seven whole-file inputs and two mixed donors. No regenerated map is committed.

The original trial accepted no composition. The resync donor failed C2039:
`rva00232A42` was missing from the seed's Keyboard declaration. The shared
KeyboardView.h keeps the seed's existing SubsystemInterface inheritance,
measured fields, KeyboardIO record and key definitions, and adds the existing
resync and checkKeyRepeat declarations. The donor uses that receiver and its
field vocabulary while retaining the original KeySlot accesses and aliasing.
No name, slot identity, layout, compiler option or address pin is recovered.

The repeated ordinary `tu_skeleton.py --merge <TU> --dry-run` accepts
Keyboard.cpp and KeyboardRva00232A42.cpp: **13 existing rows**, including the
newly compatible **166-byte** resync donor. This is a demonstrated prerequisite
unblock for Luna, not a confirmed downstream landing. Other donors still fail:
initKeyNames has duplicate key enums; init/update has duplicate KEY_STATE_DOWN
and missing virtual declarations; checkKeyRepeat duplicates allocator/enums;
the two vector cleanup donors conflict with STLport allocator declarations.
GapBodiesSeat1A.cpp and GapBodiesGE04.cpp remain mixed and untouched. These
unchanged failures are handoffs, not reasons to repeat the same trial.

## Acceptance and provider/consumer evidence

- `./build.sh <Keyboard.cpp> <KeyboardRva00232A42.cpp>` passes **13/13**;
  `find_declared_unmatched.py` passes both files. The shared header also passes
  class_gate.py; it does not add a private registered class.
- `link_check.py --prepare-current <both>` passes 13/13 with strict reusable
  receipts, sequentially after the read-only trial ended. No index is updated.
- Supported `allowed_symbols.Obj`, `_object_defs` and census COMDAT APIs compare
  the preserved pre-edit objects with the strict current objects. Both retain
  every non-debug, non-directive section byte, normalized relocation, section
  flag and COMDAT selection policy; 14 and 1 external code definitions and all
  undefined references are identical. Keyboard.cpp retains 18 such sections;
  the donor retains one. The donor now inherits existing AsciiString directive
  aliases from SubsystemInterface.h; the union of directive aliases in the
  two-object batch is identical. No provider candidate, selection policy,
  selected executable body or consumer binding changes.
- Paired `allowed_symbols.scan` results keep all **16 reference facts**, with no
  addition/removal. `data_check.object_facts` retains every definition and
  reference fact. Existing code/data identity register keys are unchanged.
- `data_check.py --converged <both>` passes two sources/ten addresses, zero
  second names and zero unjudged rows. `eh_verify.py <both>` reports **1 EXACT**,
  no non-exact graph. `link_check.py --new-variants --paths-from
  build/codex-keyboard-sources.txt` and `git diff --check` pass.
- Header/MS-header queues have no row for either edited consumer. The existing
  initKeyNames/Win32 keyboard entries remain owned by their unchanged files;
  a fresh scoped ms_header_audit.py show is saved. No debt is silently dropped.
  The Input planner is regenerated and its input/output check passes.

Scratch receipts: build/codex-keyboard-{before,after}.txt,
*-before-files/, *-before-objects/, *-recovery-dryrun.txt,
*-recovery-proof.py/json, *-reference-delta.json, *-data-delta.json,
*-variants.txt, *-ms-header-show.txt. The retained scripts use supported object
inspection APIs; no shared match cache is compiled by hand.

## Publication audit and measurements

The complete pending range (inherited RepairDock 36240d337d plus this staged
repair) has no existing source path moves, deletions or renames. Combined
searches of tools, hooks, workflows, source includes, build inputs, source
registries and protected/header queues find only the two intended consumers of
each new header. No path consumer needs repointing; original EA paths and all
ledger/data/debt owners remain intact. Audit: build/codex-keyboard-path-audit.txt.
Review the hook's batch audit at publication and carry freshness uncertainty
into the next census. No maintainer-only runner is invoked.

File reduction: **0** (one header added). Registered debt retired: **0**.
Recovered/authored C++ bytes: **0**. Linked/ownership gain: **not measured**.
Keep destination, donor, shared header, handoff and obstacle claims until the
batch lands, then release the file scopes and settle claims with --landed.
