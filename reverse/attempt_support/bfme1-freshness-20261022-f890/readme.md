# BFME 1 freshness update, 2026-10-22

Verified the clean donor update from
`42bba2ddbd5cb895d99293583891d3b7315fa49e` to official
Open-BFME/Open-BFME-1 master as fetched this pass,
`f890413e75e671748215ba2ef3304aa7953993e9`. The old revision is an
ancestor of the new one; no dirty or unpublished donor work was overwritten.

The resumed session found the previous baseline process terminated without an
exit receipt. Runner publication had also rebased onto changed production
inputs. That interrupted run was discarded as verification evidence, and both
full gates were rerun at fixed BFME 2 revision
`7dd19625eee60f4893236411f3f2d21ed085998a`. The only input difference between
the paired runs was the donor pointer. `verification.json` records revisions,
times, the production-input fingerprint and full-log hashes.

## Production verification

Both ordinary `./build.sh` runs exited zero: 98,064 function rows and 2,128 data
rows byte-verified, every full-gate check green. No pre-existing byte failure or
update regression was observed. Full output is in `old-gate.txt` and
`new-gate.txt`. The old run took 27m33s, the new run 22m31s. The old run compiled
412 of 23,429 production TUs; the new run reused all 23,429 after dependency
validation. Both still performed the full byte and data checks.

The 44 changed donor files include no header or toolchain change. The initial
audit read 24,371 dependency receipts, found none malformed and none depending
on a changed donor file. The existing resolver selects `game/`,
`inputs/reference/`, `inputs/toolchains/`, `inputs/vendor/`, `inputs/baselines/`
and `targets/game/reverse/`; all exist. Five intended WWMath/WWLib headers and
`tools/lift_lane.py` were checked directly (six files total); their hashes agree
at both revisions. No layout repair or header substitution was needed.

## Discovery refresh and limits

- BFME 1 scan: 38,765 donors, 5,514 independently matched control placements,
  616 near comparisons. Ranked and near each serve zero unclaimed candidates.
- Lift lane: 148 lifted bodies, 106,458 B; 103 servable leads. These are discovery
  leads, not recovered BFME 2 C++.
- The actual ZH object cache is `build/spike_zh`. Its initial 918 objects had
  912 readable receipts, six missing receipts and nine distinct changed
  dependency paths. None of those paths changed in this donor delta.
- Ran `zh_sweep.py compile --force --jobs 2`: 918 built, zero cached, 68 failed
  of 986 units. All 918 remaining objects were written by this run. Failed
  builds removed their older objects. `zh-failed-units.txt` lists the remaining
  platform/SDK, obsolete-source and other compilation limitations. The donor
  update changes none of these ZH sources, headers, shims or compiler settings;
  these discovery failures are separate from the fully passing production gates.
- Refreshed ZH match: 26,993 emitted functions from 918 objects. Packet
  regeneration and `next_work.py --tier packet` each report zero viable packets;
  the queue hides two previously investigated candidates. No blocked body was
  retried. Eleven pre-existing untracked discovery files were backed up and
  restored byte-for-byte after saving the regenerated results separately.

`discovery-receipt.json` binds the refreshed results, local logs and object set
to the tested donor and production revisions. The published link index
`08160bc2c9` was fetched successfully, adding 22,901 objects to the reusable
store. No census, link cycle, nightly, boot or scheduler operation was started.

This completes the pending reference-freshness prerequisite only. It claims no
new authored C++ or linked bytes, and makes no closed-strict linking claim.
