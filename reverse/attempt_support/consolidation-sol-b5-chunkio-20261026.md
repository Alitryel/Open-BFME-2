# Sol B5: chunkio constructor prerequisite, 2026-10-26

Allocated family B shard 1/2 target:
`Code/Libraries/Source/WWVegas/WWLib/chunkio.cpp`, unheld in the runner queue.
The current plan has 33 approved rows, two clean donors and three mixed donors.
The WWLib naming planner records original-image paths separately from donor
structure, and flags the seed's macro/pragma context, internal linkage,
include resolution, hatch register and unledgered definition. Its snapshot
is evidence only; the ordinary merge trial supplies routing and acceptance.

## Repair and demonstrated unblock

Before: ordinary `tu_skeleton.py --merge TU --dry-run` accepts no composition;
the constructor donor fails C2511 because the seed's reference header declares
`ChunkLoadClass(FileClass *)`, not the existing BFME stream constructor.
The verified reader bodies already address a second stream pointer at +4.

The seed now uses TU-local declarations. ChunkHeader, MicroChunkHeader and
ChunkSaveClass retain the declarations and inline accessors of the pinned
BFME 1 reference's game WWLib/chunkio.h at ff391a5e90. ChunkLoadClass takes
the existing constructor donor's BFMEChunkInput argument and two-pointer
field order (File +0, Input +4, StackIndex +8, arrays +0xc/+0x40c,
InMicroChunk +0xc0c, MicroChunkPosition +0xc10, MCHeader +0xc14).
These are already byte-verified operand views, not a claim to recover a
BFME 2 header or external donor source path. No canonical class is registered.
No shared header or reference file changed.

After: the ordinary dry-run accepts seed and chunkio_load_ctor.cpp, 29 rows,
zero rejected donors. The 93-byte constructor at RVA 0x00614ef0 becomes
composable. No merge applied: leave the compatible donor for Luna. No
confirmed downstream landing is claimed. The three Common mixed donors
remain untouched; a later merge must transfer existing hatch ownership.

## Verification

- `./build.sh` on seed and constructor: 29/29 exact before and after;
  zero literal, float or import references to verify.
- `find_declared_unmatched.py` on both: pass (seed's one existing unclaimed
  static definition remains reported). `class_gate.py` on seed: pass.
- `eh_verify.py` on both: zero EH rows, zero missing/nonexact.
- `data_check.py` on both: zero findings; converged check: ten addresses,
  zero second symbols and zero unjudged rows.
- Scoped before/after receipts in `build/sol-b5-chunkio-{before,after}` use
  allowed_symbols object-definition and reference scans, link_census COMDAT
  selections and data_check object facts. All 29 ledger rows, five owner
  relocation bindings, 39 external definitions, undefined sets, COMDAT
  selections/flags and data facts compare equal. This includes existing
  compiler-generated helpers; byte verification alone is not the proof.
- Trials: `build/sol-b5-chunkio-trial.log` and
  `build/sol-b5-chunkio-after-trial.log`. Builds:
  `build/sol-b5-chunkio-{before,after}-build.log`.

File reduction: zero. Recovered bytes: zero. Identity/data debt retired:
zero. No baseline, pin, hatch, ledger or TU-map modification.

## Batch audit and handoff

Audited the outgoing commits from the merge base with origin/master through
HEAD plus this staged repair. There are no source moves/deletions in the
batch and no active tooling, hook, workflow, include, build-input or registry
paths to repoint. Historical paths remain intact. Upstream-only changes in
the moving origin/master tree comparison are not this batch's path changes.
The changed include dependency is confined to the seed, verified with its
constructor donor and scoped helper/binding receipts above.

Keep seed, constructor and this handoff's file claims until publication is
confirmed; release afterward along with the earlier browser/exception-view
batch's held claims. The exception-filter prerequisite separately increases
debug_except composition from 13 to 15 rows (2,212 existing bytes). Existing
browser BSTR, Common RecordInitialize bytes and mixed-donor blockers remain
as recorded in their handoffs. No maintainer-only census or smoke was run.
