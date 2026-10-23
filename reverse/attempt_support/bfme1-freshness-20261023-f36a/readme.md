# BFME 1 freshness, 2026-10-23

Verified the clean donor update from `f890413e75e671748215ba2ef3304aa7953993e9`
to official Open-BFME/Open-BFME-1 master fetched during this session,
`f36a4db066aa61edeee90085a31d628eb829001d`. The old revision is an ancestor
of the new one. No dirty or unpublished donor work was overwritten. This
prerequisite accompanies the continuing 0x237D3D attempt; it claims no new
authored BFME 2 C++ or linked bytes.

Both runs use fixed BFME 2 revision
`0fa5a5b477dbcce1ec612e730ed954120ff59f11`, the ordinary `./build.sh`, and
`BUILD_POOL=8`. The production-tree fingerprint is
`7f6f0ffa21189755b27a63dee7dbb3b0b2bf6393ab296dcf9922a08455d440b4`.
The old baseline compiled 201 of 23,424 TUs after dependency validation;
the new pointer reused all 23,424. Neither run omits byte or data checks.
Both ordinary full gates exited zero: all 98,070 function rows and 2,138
data rows byte-verified, every check green. No pre-existing production failure
or update regression was observed. The old run took 19.4 minutes and the
new run 22.5 minutes. `verification.json` records both outcomes, fixed
inputs, durations and full-log hashes; `old-gate.txt` and `new-gate.txt`
retain the full outputs.

The initial default-serial baseline was deliberately terminated with exit 143
after confirming no active compiler child. It is not verification evidence.
One newly written object without a completed receipt was invalidated before
the full baseline restarted. The successful baseline is the `old` entry of
`verification.json` and `old-gate.txt`, not the interrupted run.

## Inputs and layout

The donor delta contains 17 files and no header, toolchain or build-tool change.
The initial audit read 25,575 dependency receipts, found none malformed and
none depending on a changed donor file. `input-audit.json` retains this result.
The existing resolver selects `game/`, `inputs/reference/`,
`inputs/toolchains/`, `inputs/vendor/`, `inputs/baselines/` and
`targets/game/reverse/`; all exist. The five intended WWMath/WWLib headers and
`tools/lift_lane.py` exist and have identical hashes at both revisions.
The four `inputs/` subtrees also have identical Git tree IDs. No path repair,
missing-directory substitution or header substitution was needed.

## Discovery checks

The local ZH cache contained stale objects, so it was rebuilt with
`python3 tools/zh_sweep.py compile --force --jobs 8`: 918 built, zero cached,
68 failed of 986 units. All 68 failed identities agree with the previous
verified update; no new failed unit appears. Their obsolete-source, SDK and
other discovery limitations are listed in `zh-failed-units.txt`, separately
from production verification. All surviving objects were freshly written.

After rebuilding, 912 objects have valid source/command/header receipts.
Six successfully rebuilt objects have no usable receipt (meshdam.cpp,
soundrobj.cpp, texfcach.cpp, point.cpp, tgatodxt.cpp and W3DGranny.cpp).
Their fresh compilation is recorded without claiming reusable dependency
proof for them. The new-pointer audit checks the same counts and binds the
918-object set by hashes; the update changes no ZH source, shim, compiler,
header or settings input.

The refresh runs BFME 1 scan/ranked/near, the named-lift lane with limit 1000,
and ZH match/packets. All six commands exited zero. The scan checked 38,768 donors with 5,515
independent control placements and 616 near comparisons; ranked and near
each serve zero candidates. The lift lane reports 147 bodies (105,709 B),
103 servable leads. ZH match examined 26,993 functions from 918 objects;
packets writes zero candidates. Individual counts and log digests are
recorded in `discovery-receipt.json`. These are lead searches, not source
identity or recovery claims. No candidate outside this seat's assigned task
is claimed or retried. The six pre-existing untracked `reverse/zh_sweep/`
files are backed up and restored byte-for-byte after regeneration; regenerated
results are retained separately under `build/trust237-round15/`.

The published link index at `0fa62a2841` was fetched successfully, adding
22,981 objects to the reusable store. No census, link cycle, nightly or boot
runner was started. The shared BFME 1 updater lock is released after this
verified pointer is published.
