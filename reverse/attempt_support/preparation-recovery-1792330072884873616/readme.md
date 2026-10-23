# Preparation recovery, 2026-10-18

Recovered the six commits retained at
refs/runner/preparation/1792330072884873616 (old tip 9e3e62eb33), rebasing onto
8f3fc23feb. No commit was skipped and the rebase was not aborted.

Upstream cd40722ad8 already removed the duplicate FadeInTextRender asset loader.
The conflict resolution retains its implementation and combines the provenance
comments. The previous seat's measurement and evidence remain historical; this
recovery does not claim its gain again.

Upstream 5f1c587026 already suppressed the two prerequisite vector size copies.
The automatic merge inserted a second identical explicit specialization in
ProductionPrerequisiteInsertOverflow.cpp. The first dry-run push hook correctly
refused it (MSVC C2995). Restore both prerequisite units to upstream's exact
8f3fc23feb blobs, retaining the upstream verified implementation. This is a
necessary compilation repair for the recovered batch, not another +592 B gain.

Applied stash 7cb6aae8e6141cd53fb5db298052d5d8ef571bf6 with --index after the
rebase. It contained no tracked changes and six untracked reverse/zh_sweep files:
drift_report.csv and packets 0076b6a3, 00796558, 007a4b17, 007a86af, 007a8d18.
Every restored file's git hash-object equals its stash third-parent blob. These
pre-existing generated leads remain untracked; the stash and backup ref remain.
No saved edit was discarded and no new task was drawn.

Acceptance at recovered tip 99d351d8aa with the redundant specializations removed:
- build.sh both prerequisite units: 9/9 matched, reference checks pass.
- link_check.py --prepare-current on the nine touched units and four existing
  providers: 89/89 rows exact across 13 units, one data row verified, eight
  strings and fourteen compiler float literals verified; strict reusable
  receipts, census/index/status unchanged.
- eh_verify.py on the same 13 units: 14/14 EH rows EXACT, no debt or missing object.
- link_check.py --new-variants on all 13 units: passes.
- data_check.py --enforce on all 13 units: zero findings; --converged checks
  all 13 units against nine addresses, zero second names or unjudged rows.
- check_csv.py and data_rows.py --check: pass; frozen-file and whitespace
  checks pass for the two reconciled prerequisite units.

Local link_check.py on all 13 objects predicts 11 clean, 8933 -> 11149 linked
bytes against the unchanged published c2c5ac8c27 census. That total includes
upstream repairs and is not attributable to this recovery. ThingTemplate.cpp
and ThingFactory.cpp retain their broader unresolved/provider findings. No
closed-strict, full link-cycle, runtime or census-history gain is claimed.
The original independent link repair evidence is retained in the adjacent
NullShader, getBuildable and rank parser directories. No verification rule,
baseline, pin or dependency was weakened. Current dry-run push acceptance and
publication are reported in the runner completion metadata; ignored detailed
check logs are in build/recovery-*.
