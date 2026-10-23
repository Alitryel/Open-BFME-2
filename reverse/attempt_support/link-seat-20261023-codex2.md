# Link-repair audit and unavailable verification inputs, 2026-10-23

Model: gpt-6.1-sol; seat: yasinschroeder-codex2. Initial tree was clean at
2e703afb59; final read-only pull advanced it to d54fbccdef. No authored code,
ledger, pin, dependency, or verifier changes and no new linked-byte gain.
The published retail-truth-4 index is 0fa62a2841, dated 2026-10-22 23:07.
The index fetch succeeded and imported 22,885 published objects.

## Current-object triage

Checked `link_rank.py --top 30 --near 2`, a wider `--top 100 --near 1`
ranking, `class_views.py --blockers`, current claims, and the existing
link-repair handoffs before investigating providers. Excluded live file/RVA
claims and generated units from the preview cohort. At 2e703afb59, current
legacy previews covered 330 eligible sources: 49 explicit current objects
and 281 source resolutions. Of those, 74 already linked, totaling 51,742
nonpadding matched bytes. These are inherited repairs, not session gains or
self-strict/closed-strict measurements. They must not be counted again as
repairs merely because the older census still ranks them.

Leading current examples already linked without edits: LineGroupClassRender
(4,516 B), SidesList (6,726 B), Render2DSentenceDraw (2,392 B), and fxshaderasset
(1,007 B). The final pull brought further upstream subsystem, particle, STL
and debris fixes; none is credited to this audit.

One useful counterexample to older handoffs: previewing current Thing.cpp
and HordeContainIface11CSlots.cpp together still leaves the Horde unit at
0/23,871 B. Its only reported blocker is the selected non-retail
ThingTemplate::isKindOf(KindOfType) copy. The current Thing.cpp object emits
no copy of that member. Published object facts also show the 8-byte
`add ecx,68h; jmp helper` copies in W3DModelDraw.cpp, Player.cpp, MapUtil.cpp,
ParkingPlaceBehavior.cpp and ScoreKeeper.cpp. Retail is the 21-byte wrapper
over the kind mask at +108h, now rowed at 000456AC. Refreshing Thing.cpp alone
therefore does not resolve the provider chain. No shared-header or caller
rewrite was tried, and the old int-to-bool naming trial was not repeated.
Reproduce with `link_check.py` on the Thing and Horde units together; inspect
all earlier selected providers before claiming a fix.

Other leading examined blockers remain the documented BfmeE16 destructor
identity, load-bearing STL copies, CreateAHeroData/DX8 vector/Eva class
contracts, and unrecovered camera, VP6 and destructor callees. The banks and
diagnostics in e16-destructor-link-20261023.md,
link-seat-stlport-growth-20261022.md, link-seat-current-audit-20261023.md,
link-seat-20261023b.md and link-ctor-followup-20261022/readme.md were retained.
No unchanged visibility experiment or nonmatching reconstruction was added.

## Fallbacks and unavailable inputs

* `name_globals.py --dry-run`: zero files changed, zero edits.
* `repair_queue.py link`: inspected the ranked fallback entries; its printed
  acceptance recipes are not successful current link checks.
* `rehome_rows.py --limit 3`: failed because
  `build/link_census/census.log` is missing. Fetching the published index and
  objects does not fetch that log. This is an unavailable fallback, not an
  empty queue. The prior audit's three exact home pairs already linked on
  both sides. Do not synthesize a census log or start a full census here.
* No measurement-commit-matched data-back status artifact was available;
  no data ranking was manufactured.

BFME 1 freshness is due. The clean committed pointer remains
f36a4db066aa61edeee90085a31d628eb829001d. Official upstream was fetched at
138757e9b74645fbcbb7724a7af2764e34931e11. Its 21-file delta has no header or
toolchain changes; the GUI StringBase teardown repair was reviewed as a
linking lead, with no direct BFME 2 counterpart found. The existing verified
pointer proof is bfme1-freshness-20261023-f36a/readme.md.

Started `BUILD_POOL=8 ./build.sh` for the required old-input baseline, but
after six minutes it remained in `locks_lock_inode_wait` on the shared
`~/.cache/open-bfme-build.lock`, with no compiler child. Stopped only this
seat's waiting process (exit 143). Its output ended after baseline and
library-member preparation, so it is not a completed byte gate. No donor
checkout/pointer or success stamp was changed. Retry the paired old/new full
gates when the shared compiler is available; refresh affected donor trials
before publishing a pointer update. No maintainer-only runner was started.

## Handoff

`check_csv.py` passed at entry (98,101 functions, 15,853 symbols, 2,139 data
rows), and the final pull's ledger hook passed (98,104 / 15,858 / 2,140).
There is no fresh source-byte or strict-closure gain to report. The Thing
file and donor-submodule file claims taken during triage were released;
no source attempts or claims remain. Resume the unavailable verification
inputs or a newly resolved provider/class prerequisite, rather than
repeating these unchanged blockers. A temporary input failure is not proof
that every eligible repair queue is empty.
