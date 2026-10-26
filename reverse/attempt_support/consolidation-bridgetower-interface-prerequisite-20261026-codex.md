# BridgeTower interface prerequisite and retry (2026-10-26, codex)

Allocated family-A shard 0/2 target:
`Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp`.
The runner allocation check accepted this destination. Normal file claims cover
the destination, edited interface donor and this handoff. No merge or source repair is applied; the donor is restored.

## Blocker and repair

The baseline ordinary `tu_skeleton.py --merge TU --dry-run` accepted no donors.
The interface donor failed C2039 because the seed's Object declaration does not
provide its private `isBridgeTower` helper. Removing only that dependency exposed
a second mismatch: the seed's legacy module-array access is +0x18C, whereas this
retail body accesses +0x244. That intermediate trial was not accepted.

The restored trial used partial views for the existing measured accesses: Object's
template pointer at +4, the template kind-of byte at +0x10B (bit zero), and the
module-array pointer at +0x244. This preserves the existing function's name,
calling convention, null check and virtual interface scan. No complete Object
or ThingTemplate layout, new retail name or donor identity is inferred. The
private helper definitions are no longer emitted. Compiler flags, source paths,
ledger rows, data owners and protected registers are unchanged.

## Evidence and verification

The scoped naming planner ran under the target parent directory. Its placement
packets list the same original BridgeTowerBehavior.cpp path as the sole
alternative for the seed and interface body, but classify same-spelling ZH
and stale-map evidence as hints. Current routing comes from the normal TU tool's
in-memory rebuild; no regenerated map is committed. Other prerequisites include
seed/header private views, protected seed/pool data, and two mixed sources.

Before repair, `./build.sh TU DONOR` passes all six existing rows. After repair,
the donor's one row (0x0045880B, 54 bytes) remains exact. Frozen-file and class
gates pass; converged-data enforcement passes for both sources, ten addresses,
zero second names and zero unjudged rows.

Paired upstream COFF inspection shows exactly two removed sections:
`?isBridgeTower@ThingTemplate@@QBE_NXZ` (10 bytes, digest 9c4c9fb93c88) and
`?isBridgeTower@Object@@QBE_NXZ` (13 bytes, digest 536632835ca8), both select-any
COMDATs. All retained non-debug sections preserve bytes, flags, COMDAT policies
and normalized relocations. External code definitions decrease 3 to 1; data,
undefined references and alternate names are unchanged. The upstream
`allowed_symbols.Identity` object graph has no undefined referrers to either
helper before or after removal, and no remaining definition of either name.
No consumer changes provider as a result of these unused definitions disappearing.
Paired matched-row reference scans have zero facts on both sides; paired
`data_check.object_facts` are identical. No identity-register key is retired.

Scratch receipts use `build/codex-bridgetower-*`, including before/after builds,
ordinary trials, provider inventories and interface object/section/data/reference
comparisons. All comparisons read normal objects through upstream APIs; no manual
compile changes the shared match cache.

## Final accepted-set retry blocker

The ordinary full trial internally found the six-row seed/interface candidate,
but refused its final accepted-set retry with C2143/C2501 around
`Object::BehaviorModule`. The retained trial objects include the exact 54-byte
interface body with +0x244; the report must not be called an accepted merge.
This reproduces the previously recorded cached-diagnostics defect from
FireSpreadUpdate and DebugIOCon: failed candidate objects are cached without
restoring their redefinition diagnostics on a later hit. No tool was changed
or bypassed in this source attempt. The source was restored from its initial
snapshot; the patch is banked locally as
`build/codex-bridgetower-interface-attempt.patch`. The source claims are released
so this is not an unfinished conversion. Fix the verifier cache separately
with a regression test before retrying this prerequisite.

## Publication audit and remaining work

The outgoing range contains the recovered GameMemory prerequisite plus this
blocked-attempt handoff. The raw origin/master..HEAD view also contains upstream-only
changes; the actual outgoing merge-base range has no existing source path moves.
The only new source artifact is GameMemoryGuardView.h, with its two already
verified consumers. Combined path/basename searches cover tools, hooks,
workflows, source includes, build.sh, doxygen inputs and class/header registries.
They find the intended header includes and existing comments/callers; no active
consumer requires repointing. Historical EA and donor paths remain intact.

Pool-key member declarations, Xfer receiver reconciliation, damage/healing
GameLogic views, and mixed ConstIntGetters4/Disp8LeaNegSbb sources remain outside
this prerequisite. The mixed-source ownership/debt must remain accounted for.
No source-file reduction, recovered C++ bytes, debt retirement, census gain or
confirmed Luna landing is claimed. Retain file claims until publication is
confirmed, including the inherited five GameMemory/register claims. The two blocked source
claims are released; only this handoff claim remains pending publication.

## Verified retry after separate verifier repair

The diagnostic-cache fix is a separate commit, fc3e3896ff. After fresh allocation
approval, file claims, frozen checks and a regenerated scoped naming plan, the
banked source repair was reapplied. Ordinary `tu_skeleton.py --merge TU --dry-run`
now accepts the seed and interface donor: six existing rows, 266 retail bytes.
This demonstrates a prerequisite unblock, not a confirmed Luna merge. The pool,
Xfer, damage/healing and mixed-source blockers listed above remain.

`./build.sh TU DONOR` passes 6/6. `link_check.py --prepare-current TU DONOR`
passes strict reusable receipts for both explicit providers; `--new-variants
--paths-from build/codex-bridgetower-sources.txt` reports no new variants.
`allowed_symbols.py --source TU --source DONOR` reports zero references and zero
wrong bindings. Staged code identity reports one row, zero new findings; staged
data and TU ownership pass. Frozen-file/class checks and converged-data checks
also pass. No key is retired and no register is edited.

The ordinary trial's scratch object, 4536603498fb23fc.obj, preserves the input
union's 69 external code definitions including byte/relocation identity and
COMDAT selections. Its 558 external data definitions preserve bytes, relocations
and selections, as do data facts and aliases. Undefined symbols are identical
after resolving definitions inside each composition. The two apparent destructor
references are already present alongside their own definitions in the seed;
they do not introduce external dependencies. The only standalone provider delta
is removal of the two unused private helpers documented above. Both have no
external referrers in the upstream object graph. No selected consumer changes.
Receipts: build/codex-bridgetower-{retry-build,prepare,variants,allowed}.txt and
build/codex-bridgetower-composition-proof.json, plus the paired section/data/
reference/provider receipts. No scratch source was compiled through build.py.

Before this commit, the complete pending range plus staged source was audited.
There are no existing source path moves; the only pending source addition remains
GameMemoryGuardView.h with its two verified includes. The existing combined
active-tool/hook/workflow/include/build/doxygen/registry search remains current.
All source/ledger names and historical paths are retained. Source-file reduction,
recovered bytes, identity debt retirement and measured linking gain are all zero.
Keep the reclaimed seed/interface claims and earlier pending file claims until
publication is confirmed. Luna may apply the ordinary merge after publication,
using its normal protected-register transfer and full batch checks.
