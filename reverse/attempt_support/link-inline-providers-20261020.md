# Inline provider link repairs, 2026-10-20

Inputs: BFME 2 `44d0196f61`, published census `b73720bed9`
(2026-10-20 05:34), BFME 1 `a2c8039e61ad`. Reviewed BFME 1's
`.codex/reports/2026-10-15-bfme2-linking-transfer.md`; its provider-binding
repairs support this approach, but the measurements below are BFME 2 evidence.

| Source suffix | Sole original conflict | Before | After |
| --- | --- | ---: | ---: |
| `ScreenMotionBlurFilterSet.cpp` | `DX8Wrapper::Set_Material` COMDAT | 0 B | 448 B |
| `LivingWorldAIArmyMoverDefendHomeTerritory.cpp` | `vector<BfmePod20>::push_back` COMDAT | 0 B | 341 B |

The filter's material helper remains fully inline; `dllimport` suppresses its
unused competing out-of-line copy. The army mover now declares the complete
out-of-line `push_back` provider instead of instantiating a different copy.
The caller's verified relocation continues to select retail RVA `0x0059B8C6`.
Neither repair changes any row's compiled bytes or relocations.

Acceptance: `link_check.py --prepare-current` on both sources passes the normal
byte gate for all six rows and creates self-strict reusable receipts.
`find_declared_unmatched.py` passes both sources. `link_check.py` on the same
pair reports 2/2 link cleanly, 0 -> 789 B. This is the legacy census prediction;
no closed-strict or full-link gain is claimed. No census or full link cycle ran.

Cause sweep: other material-helper consumers also have independent blockers.
The two ModuleData parse consumers preserve all eight rows with an inline
`_M_set` specialization but still lose their growth COMDAT; declaration-only
growth changes their frame from 0x90 to 0x94. Both were restored. AssetRegistry
tree insertion and HordeContain list-find suppression also changed matched
frames and were restored. Their concise blockers are in `re_attempts.log`.

Further probes were restored with no linked gain:

- `CreateAHeroDataAssign.cpp`: the implicit pair destructor still emits despite
  a declaration; import-inline moves the conflict into tree erase through an
  unresolved import. Seven byte rows remain exact in the diagnostic trial.
- `Rva00410DDFInsert.cpp`: the screen pair cleanup at `0x00410688` differs from
  the canonical pair destructor `0x002175CE`. A native record wrapper changes
  the parent construction spill and EH state. No source change retained.
- `Rva000BBE29.cpp`: `_M_find<int>` specialization either ICEs MSVC or is
  rejected; header-scoped frame omission preserves both row bodies but does
  not reconcile the emitted helper. Legacy prediction remains 0 -> 0 B.
- `stlport_vector_e8_allocate_copy.cpp`: declaring AudioTriggerArea growth
  merely moves the conflict to push_back. The original growth has the exact
  184-byte shape but unresolved AudioTriggerArea uninitialized-copy/fill calls
  to retail `0x004C3121`/`0x00507958`. Establishing their identities and complete
  relocation-correct fold proofs is a prerequisite. All original four rows
  pass their scoped byte gate.

The read-only global naming sweep found zero rewrites. Rehome found three
exact placements: two already link, while the third would move a working row
into a blocked home unit. Its six-unit preview stayed 11,733 -> 11,733 B.
The hero-selection destructor candidate was not edited: the unit claim could
not be acquired from origin; both acquired RVA claims were released.

Local diagnostic sources and logs are in ignored `build/link-seat-*` files;
no nonmatching source is retained in `Code/`. The concise verdicts are also
recorded in `reverse/re_attempts.log`.

BFME 1 freshness: compared committed clean `a2c8039e61ad` with fetched
official master `0dc8a26a9c60`, preserving the previous commit on local branch
`bfme2-verified-a2c8039`. Nine changed paths include no headers or toolchain
settings. The layout resolver maps legacy Code/reference/vendor paths to
physical game/inputs/reference/inputs/vendor directories; the resolved WW3D2
and ZH engine include directories, AsciiString header and STLport vector
header were checked on disk.

Full byte verification passed on BOTH inputs at BFME 2 `7855eeb71e`:
97,302/97,302 functions, 1,116 data rows, strings, floats, imports, DIR32
consistency, pins, module registry, source claims and no-op patch all green.
The initial run overlapped temporary probe objects and is discarded; the
valid baseline was rerun after restoring those probes. Logs are
`build/link-seat-freshness-restored.log` and
`build/link-seat-freshness-updated.log`. The update compiled zero stale units;
all 23,379 dependency-cached units remained current, confirming no dependency
input changes. The verified gitlink is advanced and the ignored freshness
stamp updated only after both full gates passed.

Refreshed the donor scan at `0dc8a26a9c60`: 5,513 placements reproduce an
independent BFME 2 boundary; ranked serves zero exact unclaimed files and
near serves one 25-byte lead outside this lane. Refreshed lift_lane with
--limit 1000: 154 lifted bodies, 107 servable. No changed donor implementation
is compiled by the repaired units; their headers and compiler settings are
unchanged. The linking-transfer report reviewed earlier is unchanged.

The stronger `link_check.py --current-ledger --refresh` preview refused a
result because 11,861 providers lack current compiler-evidence receipts
(including DispByteFieldSetters and RvaSmallVtableCtors). It compiled no tree
and changed no census. This does not establish closed-strict closure; retain
the self-strict six-body proof and legacy +789 B prediction separately.

The commit hook also reported a `_Vector_base<const ModuleData *>` variant
from the army mover in shadow code-identity mode. The complete byte gate
and legacy unit preview pass; that shadow report does not supply strict
link-closure evidence and was not suppressed or baselined.

Probe model: `gpt-6.1-sol`; CreateAHeroData pair-cleanup trials took four
minutes and the screen-pair wrapper trials six minutes.

## Preparation recovery, 2026-10-20

Rebased the saved commit onto `11a657d8bb`. Upstream commit `2544fb61fa`
already carries the identical screen-material repair; retained its explanatory
comment when resolving the sole conflict. The outgoing source repair therefore
adds **341 B** of legacy predicted linked coverage, not another 789 B. The
original two-unit 789 B measurement above remains historical evidence.

Applied stash `c9174b864a7b` with `--index`: tracked changes were already
current. All six untracked files under `reverse/zh_sweep/` were restored and
verified against the stash's saved blob IDs. They remain untracked diagnostics;
the stash and `refs/runner/preparation/1792482023514320037` remain intact.

Recovery acceptance: `check_csv.py` passes (97,326 function rows); both units
pass `find_declared_unmatched.py`. `link_check.py --prepare-current` verifies
all six bodies and creates strict reusable receipts. Legacy `link_check.py`
still predicts 341 B for the army mover and 448 B for the upstream filter
repair. No closed-strict or full-link gain is inferred. Recovery logs are
`build/recovery-prepare-current.log` and `build/recovery-push-dry-run.log`.
