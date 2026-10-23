# Split data ownership link repair, 2026-10-18

At BFME2 fa0a9efb6e, remove duplicate strong data definitions from four split
consumer units. Retain the existing original definition in each home unit.
No function rows, data rows, symbols, layouts or compiler flags change.

| Owner | Before | After | Matched bytes newly linking |
| --- | --- | --- | ---: |
| Rva005A990BTactic.cpp | duplicate key and startup counter | LINKS | 239 |
| Rva005AB309Tactic.cpp | duplicate key, counter and name table | LINKS | 605 |
| W3DView.cpp | duplicate frame length and nine camera-save globals | LINKS | 1019 |
| GapBodiesS3E.cpp | six duplicate static parse tables | LINKS | 238 |
| Total | 0/8 affected units | 4/8 affected units | 2101 |

Measurement: ordinary tools/link_check.py, all eight owner/consumer paths in
one invocation. This is a legacy census-index preview, using the published
2026-10-18 08:17 index at 2967eab33e. It is not self-strict or closed-strict
LINK credit and no full link/census/cycle was run. Attached before logs use
current original objects; after.txt uses all eight changed/current objects.
The owner's LINK result changes because the duplicate consumer definitions
are removed. The existing census/index/status were not rewritten.

Target evidence: the original and split sources duplicate the same named
objects and retail locations. Tactic keys are VA E06404/E06410, counters
E06408/E06414, and the ring name list RVA 9BC1B8. W3D frame length and saved
camera data have the identical types and initial values in both sources;
the saved data occupy RVA 9E2024..9E2067. Each GapBodies table has identical
entries, callbacks and offsets in both sources; table references bind to
the same six existing symbols after the duplicate definitions are removed.
This repair preserves those established identities rather than inferring
new target names or layouts. No aliases or alternate data owners are added.

The two tactic edits were preserved from the preceding interrupted seat and
validated here. The W3DView and GapBodies edits apply the same single-owner
repair. Removing unused startup counter helpers in the tactic consumers also
removes their duplicate initialization; the home units retain it.

Acceptance: link_check.py --prepare-current on each pair (four tactic paths
in one invocation) runs the ordinary source, body, data and reference gates:
19/19 tactic rows, 11/11 W3DView rows and 13/13 GapBodies rows, 43/43 total.
The W3DView gate also verifies ten data rows. All eight sources have strict
reusable compiler receipts; this proves the compiler inputs and byte gates,
not LINK closure. All four edited files pass find_declared_unmatched and
git diff --check. The first W3D strict preparation was invalidated by an
overlapping preview and discarded; its serial rerun succeeded (attached).

Remaining consumer blockers, unchanged by this repair:
- tactic CanRun: AITacticOffensive::checkTarget;
- ring Run: AIReturnTheRingTactic::buildReturnTeam;
- spline init: Rva00312C95::rva00312118 plus CameraClass Get/Set_Viewport copies;
- GapBodies split: Rva003F9C11 constructor, g_00C61830, g_00C61884 and rva00425842.

## Reference repair review and freshness

The clean verified BFME1 pointer is 64d369b90170b7e9ec917d646f020b11f13eb0d5.
Official master was fetched at d348fca17814122303884ebe194cbc877a2c0bb0.
The eleven changed paths include no headers, tools or layout changes.
Reviewed its Rva007E8600Clear linking repair: a second g_rva007e8530 datum
becomes extern with the original Rva007E8530Call owner retained. This is an
applicable single-owner precedent, not BFME2 byte/link proof. The donor
BufferedStreamAttach repair changes its destructor trampoline to an
out-of-line declaration; no corresponding fix is asserted here.

The current BFME2 layout resolver resolves game/ and inputs/reference/;
the expected source, shim and GeneralsMD header directories exist. Attempted
the routine pointer update and full ./build.sh verification with the new
pointer staged. It reached the host's shared compile_rows portable_lock
(tools/build.py line 3235, fcntl.flock; /proc wchan locks_lock_inode_wait)
and was interrupted rather than starting a duplicate build. The local log
is build/bfme1-freshness-d348fca1-full.txt. No verification result or success
stamp was recorded. Restored both checkout and index to the previously
verified pointer. Freshness remains due; no changed donor inputs are used
for this repair. Full link runners remain maintainer-only.
