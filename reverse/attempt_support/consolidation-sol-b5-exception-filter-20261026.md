# Sol B5: exception-filter composition prerequisite, 2026-10-26

Target: `Code/Libraries/Source/debug/debug_except.cpp`, allocated to family B,
shard 1/2 by `/opt/runner/consolidation_queue.py --check-tu` (exit 0).
This prerequisite leaves the merge for Luna. No source was moved and no ledger
row, identity key, data key or hatch register was changed.

## Demonstrated unblock

The ordinary `tu_skeleton.py --merge TU --dry-run` initially accepted 13 rows.
`DebugExceptionFilter.cpp` failed because the seed's private
`DebugStackwalk::Signature` lacked Size, followed by missing exception-handler
and Debug output/buffer declarations. Reused that donor's existing operand
views in the seed and its TU-scoped header. Retained the existing stream slot
order, SetPrefixAndRadix at 0x50, and width/fill offsets 0x9f50/0x9f54.
This is a partial observed ABI view, not a recovered upstream header.

The final ordinary dry-run accepts 15 rows: the seed, DebugExceptionFilter,
DebugCopyDialogReport, Rva0088E100DialogWatchdog and
Rva0088E1A0ShowAssertCrashDialog. The newly accepted rows are ExceptionDlgProc
at 0x0003cfb0 (957 bytes) and ExceptionFilter at 0x0003dcd0 (1255 bytes):
2,212 existing retail bytes become composable. Recovered C++ bytes: zero.
File reduction: zero. Identity debt retired: zero. No later Luna landing is
claimed.

## Acceptance evidence

- `./build.sh Code/Libraries/Source/debug/debug_except.cpp Code/Libraries/Source/WWVegas/WWDebug/DebugCopyDialogReport.cpp Code/Libraries/Source/WWVegas/WWDebug/DebugExceptionFilter.cpp`:
  12/12 exact, 139 literals (13 empty), 38 imports; no mismatch.
- `find_declared_unmatched.py` on seed, filter and header: pass.
- `class_gate.py` on seed and header: pass; neither Signature nor
  DebugStackwalk is registered as a canonical class. No canonical copy added.
- `eh_verify.py` on seed/filter: no missing or nonexact funclets (zero EH rows).
- `data_check.py` on seed/filter: one existing finding, zero outside baseline;
  converged check: ten addresses, zero second symbols, zero unjudged.
- `ms_header_audit.py scan` on header/seed/filter: the three existing conflict
  entries remain, zero scan failures. No SDK declarations were changed.
- Scoped before/after receipts in `build/sol-b5-except2-{before,after}` use
  allowed_symbols load/scan/object definitions, link_census COMDAT selections,
  and data_check object facts. All 11 ledger rows, 44 relocation bindings
  (18 local labels, five aliases, 21 owners), 22 external code definitions,
  undefined symbol sets, COMDAT selections/flags and data facts compare equal.
  Local-label spelling is normalized only for references already resolved as
  labels; placement and all other binding facts remain compared.
- Only the seed includes BfmeDebugExceptionView.h. The unchanged filter and
  clipboard consumer objects were checked together with that seed. The
  unchanged standalone filter's operand view is the declaration source.
- Ordinary before/after trials and build logs:
  `build/sol-b5-except2-before-trial.log`,
  `build/sol-b5-except2-full-trial.log`,
  `build/sol-b5-except2-full-build.log`. No merge or maintainer link run applied.

## Remaining prerequisites and publication audit

The ordinary trial still rejects Common/Rva0088D8E0RecordInitialize.cpp on
bytes; that cross-family donor was not edited. Four mixed donors remain
untouched. The future merge must transfer its reported one data-check key,
12 data-ledger entries and hatch ownership through the supported merge tool.
The filter's existing wrong-name data debt remains; composition is not debt
retirement.

Audit of `origin/master..HEAD` plus this prerequisite: no source-path moves or
deletions, hence no active tooling, hooks, workflow, include, build-input or
registry paths need repointing. Historical EA paths are preserved. No TU-map
regeneration is staged. Scoped provider/consumer evidence above covers this
change; no old census is used as proof of bindings.

The session recovered and reverified the earlier browser and clipboard-view
commits before starting this task. Their held file claims and this task's
seed/header/filter/handoff claims must remain until the runner publishes the
batch, then be released. BFME 1's verified pin remains ff391a5e90; official
upstream is c0384c97c7. The reference update still needs full verification;
no successful freshness receipt was written.
