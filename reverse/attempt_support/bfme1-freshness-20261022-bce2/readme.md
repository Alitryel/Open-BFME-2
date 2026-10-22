# BFME 1 freshness comparison, 2026-10-22

Verified the update from `37c3022de1ab944c7ffe536440d637dc8199091c` to
official Open-BFME/Open-BFME-1 master as fetched this pass,
`42bba2ddbd5cb895d99293583891d3b7315fa49e`.
The donor checkout was clean. The old revision is an ancestor of the new one;
no dirty or unpublished donor work was overwritten.

Both full gates used BFME 2 production sources, function/data ledgers and
verifier inputs from `3c0234e9763`. The intervening local mesh-evidence commit
changes only attempt records. Only the staged donor pointer differed for the
comparison. The existing layout resolver selects `game/`, `inputs/reference/`,
`inputs/toolchains/`, `inputs/vendor/`, `inputs/baselines/` and
`targets/game/reverse/`; all directories exist. The intended WWMath/WWLib
headers and `tools/lift_lane.py` were checked directly (hashes in
`intended-inputs.json`). No layout repair or header substitution was needed.

## Full byte verification

`./build.sh` exited zero for both revisions. Both passed all 98,039 function
rows and 1,727 data rows, plus the baseline, literal, import, DIR32, pin,
module-registry, source-claim and no-op-patch checks. No pre-existing byte
failure or update regression was observed. Full output is retained in
`old-gate.txt` and `new-gate.txt`.

The 76 changed donor files include no changed header or toolchain input.
The initial audit read 25,946 dependency receipts with no malformed receipt
and found no dependency on a changed donor file (`input-audit.json`).
The old gate found 2,089 stale TUs, restored 870 from the object store and
compiled the rest. The new gate found all 23,435 TUs current and required no
production recompile. These cache results did not replace byte verification.

Observed wall times were approximately 65m40s for the old gate and 38m39s
for the updated-reference gate. Read-only stack snapshots during the old
run located the long tail in `data_rows.compiled_size` waiting for compiler
size probes (`tools/data_rows.py:391`). The ordinary data verification path
runs these sequentially and recreates their objects, so a warm production
object cache does not eliminate this cost. Both runs were allowed to finish;
no gate, baseline or receipt mechanism was changed.

## Discovery refresh

- BFME 1 scan: 38,763 donors, 5,514 independent control placements and 616
  near comparisons. Ranked and near each serve zero unclaimed candidates.
- The required lift lane ran at the updated pointer: 149 bodies, 109,294 B;
  104 are servable leads. These are leads, not recovered BFME 2 C++.
- The ZH cache audit found no changed shim dependency among 913 readable
  receipts, but six old objects lacked receipts. Ran the normal
  `zh_sweep.py compile --force --jobs 2` refresh: it reports 919 built and
  68 failed out of 987 units. Failures include unavailable platform and
  SDK declarations such as Miles headers; the underlying ZH sources,
  dependency headers and compiler settings are unchanged by this donor update.
- Regenerated ZH match and packets after that refresh: 27,011 emitted
  functions from 919 objects, zero viable unclaimed packets. The old cache
  had reported 27,016 emitted functions; its results were superseded.

`discovery-receipt.json` records the donor revision and hashes of the local
discovery logs under `build/resume-eh-local/turn67-*`. A retried
`link_check.py --fetch-index` succeeded after HTTP 500 failures, installing the
published `ae3b3e68e2` index and adding 9,817 objects to the content-addressed
store. No census, link cycle or other maintainer-only runner was started.

This prerequisite update claims no new authored C++ or newly linked bytes.
The separate mesh evidence commit preserves 82 unsuccessful helper-shape
trials and leaves the better existing bank unchanged.
