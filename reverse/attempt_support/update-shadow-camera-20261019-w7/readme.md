# UpdateShadowCamera handoff

Result: blocked. Keep `reverse/attempts/0x0007c8ae.cpp` unchanged. No candidate improves the bank under the assignment's comparison rule. No source, pin or ledger row was added. The three supplied dependency verdicts are superseded by the hull's landed row and four subsequent camera banks; the current blocker is compiler scheduling and allocation, not the missing hull.

Target: `?UpdateShadowCamera@W3DShadowMapManager@@QAEXXZ`, RVA `0x0007C8AE`, 4176 bytes. The destination tool names `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapConvexHull.cpp`. Inputs: BFME 2 `dd0ca72bda0e0ed0ad70d6dcaef88267c6f7bf45`, BFME 1 `a18d9ed50607e9175de4d6568798d7d73119de09`. model=gpt-6.1-sol.

The fresh bank and byte-identical scratch control both emit 4173 bytes, with 24 structural regions, 97 memory differences and 30 register differences from `align_diff.py`. Relocation and branch counts are excluded from the decision. The tool's memory class includes some address relocation placeholders; the unmodified tool was used consistently. `compile_function` reports 2680 positional differing bytes after its normal relocation patching, and no unresolved names. Positional bytes are diagnostic only. The retained before and after body is identical.

Identity and ABI: `reverse/ghidra_functions.csv` lists the exact start and 4176-byte extent. Retail begins an EH-prolog function at VA `0x47C8AE`, saves incoming ECX as its receiver, and returns without stack arguments at `0x47D8FD`. WorldBuilder VA `0x7F0310`, 23902 bytes, pushes `W3DShadowMapManager::UpdateShadowCamera` and pairs by callgraph. Camera accesses, frustum and projection phases, the hull edge and the five game-free cleanups agree with the bank. These are target-derived observations; canonical EA WWMath headers provide the mathematical source guide, not a whole shadow-manager donor. The helper's source is rowed at `0x0007C637` and the fresh camera compile resolves all names.

Experiments were documented with evidence and a refuting observation before execution in `build/shadowcamera-w7/hypotheses.md`. Every scored alignment uses a freshly compiled object: the initial bank probe was repeated after explicit object and dependency-receipt deletion, and all later alignments delete them automatically. Every probe checked `build/STOP_WORKER` and used `BFME_OBJSTORE=off`. All trial sources and raw outputs remain under `build/shadowcamera-w7/`. `control.cpp` is an exact copy of the bank. Two invalid named-axis trials used a generator that expected CRLF in the LF bank; corrected trials have distinct names and the failed sources and compiler output remain available.

| Experiment | Emitted bytes | Regions | Memory | Register | Verdict |
|---|---:|---:|---:|---:|---|
| Original bank and scratch control | 4173 | 24 | 97 | 30 | Retained |
| Named frustum delta | 4165 | 34 | 143 | 28 | More regions and memory differences |
| Scalar Z/Y/X interpolation stages | 4176 | 38 | 148 | 33 | All classes regress |
| Named reference axes before or after axis1 | 4165 | 34 | 139 | 28 | More regions and memory differences |
| Axis initialization and declaration variants (four) | 4173 | 24 | 97 | 30 | No effect |
| Plane argument reference bindings (six) | 4170 or 4173 | 34 | 122 or 215 | 28 or 45 | More regions and memory differences |
| Shared cross-product zero products (six) | 4160 or 4163 | 37 or 40 | 128 to 132 | 31 to 35 | All classes regress |
| Explicit inverse accumulation, both calls | 4147 | 39 | 111 | 48 | All classes regress |
| Explicit inverse accumulation, first call | 4180 | 31 | 128 | 35 | All classes regress |
| Prebound inverse products | 4158 | 37 | 122 | 62 | All classes regress |

The remaining mismatch is the initial cross-product schedule and axis1/shared temporary placement (`-0x34..-0x2C` versus `-0x30..-0x28`), frustum interpolation scheduling and scene-camera load placement, inverse-matrix accumulation order, point-push temporary ordering, and the final plane loop reserving ESI for `0x3FC` instead of its current ceiling-point pointer. Naming temporaries can fix a local operation sequence while worsening distant allocator choices. Declaration-only changes and dead zero initialization are canonicalized away. Explicit reference assignment order, shared zero products and statement boundaries did not close the global discrepancy.

Raw evidence: `build/shadowcamera-w7/before-align-fresh.log`, `before-explain.log`, `before-metrics.log`, `identity-wb-retail.log`, `destination.log`, and each named trial's `*-align.log`. `summary.tsv` collects the measurements without substituting for those raw logs. Initial ledger and pin checks passed in `check-csv.log` and `pin-consistency.log`. No candidate was placed in `Code/`, so no `add_match.py`, source gate or unmatched-definition gate was applicable. The final record and final integrity checks have separate raw logs in the same directory.
