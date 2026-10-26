# Sol B5: index-buffer composition provider blocker, 2026-10-26

Allocated family B shard 1/2 target:
`Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.cpp`.
Current runner allocation was unheld; scope claims covered the seed, clean donor
DynamicIBAccessWriteLock.cpp and experimental TU-local header. The WW3D2
name_lane planner was refreshed before and after the trial. Its original-path
and structural evidence approves neither a merge nor a compiler environment.
The ordinary plan reports 27 approved rows and two foreign Common mixed donors;
neither mixed donor was edited. No merge was applied.

## Trial and disposition

Ordinary dry-run initially fails on a void-versus-bool mutex release declaration.
The matched owner at RVA 0x00120f50 in dx8wrapper.cpp returns bool; the void
spelling is an existing alias. A TU-local copy of the existing indexbuffercount
shim header corrected that return declaration and adopted the existing clean
donor's write-lock device-lock member and release helper. Donor constants were
spelled at their uses to avoid existing header enum and SDK macro collisions;
its Lock pointer argument was aligned to the already included D3D8 interface.
WIN32/_WINDOWS definitions matched the seed's existing compile environment.
The donor kept its compact standalone views: adopting the full header there
also changed unrowed helpers and was rejected.

That final trial byte-verifies 36/36 standalone ledger rows and ordinary
`tu_skeleton.py --merge TU --dry-run` accepts seed plus donor (35 rows in its
report, zero rejected donors). This would compose constructor 0x00138ca0,
218 bytes, and destructor 0x00138d80, 120 bytes, but **is not an accepted
prerequisite**: the composed object fails the provider comparison below.
All Code edits were reverted. The adjacent patch preserves the exact final
trial; do not apply/merge it without resolving the provider blocker.

## Verification and provider boundary

- `./build.sh TU DynamicIBAccessWriteLock.cpp`: 36/36 exact.
- `find_declared_unmatched.py` on both sources and header: pass; seed's four
  existing unclaimed definitions remain reported. `class_gate.py`: pass.
- `eh_verify.py`: eleven exact EH rows, zero missing or nonexact.
- `data_check.py`: two existing findings, zero outside baseline; converged:
  ten addresses, zero second symbols and zero unjudged rows. No debt retired.
- Standalone before/after receipts using allowed_symbols object definitions,
  relocation scans, link_census COMDAT selections and data_check object facts:
  36 rows, 62 bindings, 48 seed and nine donor external definitions. Only four
  rowed calls and one guard tail jump change from the void release alias to
  its bool owner at 0x00120f50. Normalizing that proven correction leaves all
  other function bodies, external definitions, undefined sets, COMDAT
  selections/flags, data facts and bindings equal. This alone was insufficient.
- The stronger trial uses the actual object produced by the supported merge
  verifier, without hand compilation or edits to any repository check.
  It compares every external definition and COMDAT selection/flags against
  both standalone providers. It finds larger RefCountClass::Add_Ref (4 -> 5),
  Release_Ref (10 -> 11), scalar deleting destructor (29 -> 31), and vector
  constructor iterator (34 -> 50). Several RefCount sections also change
  alignment flags. The unrowed bfmeEmitGetIndexCount changes 9 -> 1 byte.
  The attached JSON records all eight differences, including unchanged bodies
  whose section flags changed. The trial must stay unpublished as source.

Scratch receipts: build/sol-b5-index-{before,after}/proof.json,
sol-b5-index-binding-proof.py, sol-b5-index-composition.py/.json,
sol-b5-index-final-{build,trial,planner}.log. The composed artifact is
build/sol-b5-index-composed.obj; these scratch files are not durable progress.
Next work must investigate the merge's placement of unrowed anchors/preamble
and its effective compiler environment, then recheck all helpers and bindings.
Do not add optimization pragmas, pins or force a merge to suppress the result.

## Batch and remaining handoff

No source moves, ledger, TU map, baseline, pin or hatch changes. File reduction,
identity debt retired and recovered C++ bytes are all zero for this attempt.
The outgoing range starts at published 7c2777f0b2; this evidence-only commit
has no active tool/include/build-input paths to repoint. Claims on the trial's
source files can be released because the source trial was abandoned.

The earlier published browser, debug exception and chunkio prerequisites remain
separate from this blocked trial. They demonstrate ordinary dry-run acceptance,
not confirmed Luna landings. Their scoped before/after source receipts do not
replace checking the composed objects and the later complete merge batch.

The earlier five-commit publish passed 67/67 rows but its link batch audit was
INCONCLUSIVE: index f995f30157 predates outgoing base 97cecf650b, and three
source objects lacked strict-current receipts (first Eva.cpp). No broad link
improvement or census closure is claimed. LINK-008's shared obstacle file was
claimed by another worker when an update was attempted; its history was left
intact. Carry this freshness evidence into its next update/maintainer census.
No maintainer-only link cycle, smoke or nightly run was started.
