# StatusBitsUpgrade receiver prerequisite, 2026-10-26, codex

Allocated family A shard 0/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Upgrade/StatusBitsUpgrade.cpp`.
This repair leaves compatible donors for Luna; it applies no merge or split.

The pool-key donor and apply/remove donor now share StatusBitsUpgradeView.h.
The view retains the implementation donor's measured secondary UpgradeMux
receiver at +0x10, ModuleData/Object operands and mask fields +0x118/+0x128,
and declares the pool donor's existing getModuleNameKey method. Constructors,
destructors and complete retail vtable layout remain outside this partial view.
No body, compiler flag, row, data identity or protected-register key changed.

The ordinary `tools/tu_skeleton.py --merge TU --dry-run` now accepts both direct
donors / four existing rows / 185 retail bytes, versus the pool donor alone /
two rows. This includes the ten-byte compiler-emitted EH row; ordinary methods
sum to 175 bytes. This is demonstrated composition acceptance, not newly
recovered code, a completed Luna merge or a link census gain. The constructor
remains rejected (missing ctor declaration in the chosen partial receiver;
the earlier trial additionally records a vtable byte mismatch). Both mixed
sources remain untouched. Adding a constructor declaration alone does not
establish compatibility of its emitted vtables.

Verification and evidence:

- Initial and final `./build.sh` on StatusBitsUpgradePoolKey.cpp and
  StatusBitsUpgradeUpgradeImplementation.cpp: 4/4 exact, one string verified.
  `find_declared_unmatched.py` and scoped `class_gate.py` pass.
- `eh_verify.py` on both: one EXACT graph. Converged data check: two sources,
  ten addresses, zero second names or unjudged rows.
- Before/after object comparison: all four external code definitions, twelve
  non-debug sections, data, bytes, normalized relocations, COMDAT policies,
  undefined symbols and alternates are identical. The pool's eight sections and
  the implementation's four sections are unchanged individually. All ten
  reference-identity facts and the data definition/reference facts are identical.
- The ordinary trial's composed object, `build/tu_skeleton/2a8860c24bc3de70.obj`,
  retains all four definitions, equal COMDAT policies, equal data facts and
  exactly the union's undefined references after internal resolution. No new,
  lost or changed provider, conflicting definition or binding was found.
- `tools/link_check.py --prepare-current` on the two providers passes normal
  gates with strict reusable receipts, without updating census/index/status.
  Local receipts: build/codex-statusbits-{before,after}-build.txt,
  build/codex-statusbits-{before,after}-trial.txt,
  build/codex-statusbits-object-proof.json,
  build/codex-statusbits-reference-delta.json,
  build/codex-statusbits-data-delta.json,
  build/codex-statusbits-composition-proof.json and
  build/codex-statusbits-prepare.txt. The scripts use supported scoped object,
  symbol-identity and data-check readers; no hand compile touched match caches.
- Scoped name planner regenerated after the edit; `name_lane.py consolidate
  --check build/consolidation` passes. Its hints do not approve a move; current
  in-memory TU routing and ordinary verifier supplied the composition result.

Existing pool static-key/guard data debt remains in its original register and
source. No code identity or header queue entry for these donors was removed.
No new name, pin, escape hatch or public canonical class was admitted. The
source count is unchanged; one scoped header is added, so file reduction and
identity debt retired are both zero. Recovered C++ bytes are zero.

Publication tooling audit covers all four pending local commits after the
common ancestor with origin/master, plus this staged repair. The raw two-tip
range includes upstream-only B03/hash-table changes; those are not local moves.
There is no local source move, rename or deletion. The new header has exactly
two active consumers, both verified together above; the inherited TunnelTracker
header still has its two verified consumers. Combined searches across Code,
tools, hooks, workflows and build.sh find only these includes and an intentional
SubObjectsUpgradePoolKey.cpp recipe comment. Build inputs, path-keyed ledgers,
registries and historical EA paths need no repointing. All new files are staged
explicitly. Keep source/header/handoff claims until publication is confirmed;
release the unused destination scope after the push too.
