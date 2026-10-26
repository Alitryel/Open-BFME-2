# Snow lightning declaration prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2; base 75a93b690f. Allocated destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp`.
The runner queue authorizes this destination; normal file claims cover the
shared header, seed and all four weather/lightning consumers.

## Repair and demonstrated unblock

The normal merge dry-run originally rejects Rva0009322DLightning.cpp with
C2953/C2955 on its private OVERRIDE template. Consume the existing Snow resource
view instead. Expose only already-observed storage: receiver countdown +54,
weather duration +64 and chance +68; receiver flag +50 and weather flag +54
already exist in that view. Preserve SnowManager extent 74 and W3DSnowManager
extent B0. The donor retains its algorithm and WWMath inline helper. Its include
paths now resolve the same ASCII shim and pinned WWLib headers as the seed.
No name, pin, virtual slot, function extent or compiler optimization changes.
The first build identified a missing ascii_string.h include path; the corrected
build below verifies the intended shared environment.

Before: normal tu_skeleton.merge(dry_run=True) accepts the seed and three weather
donors, 17 composed / 18 standalone ledger rows. After: it additionally accepts
the 180-byte lightning donor, 18 composed / 19 standalone rows. No merge applied;
leave this compatible subset for Luna. This is a demonstrated prerequisite
unblock, not a confirmed later Luna landing or newly recovered bytes.

Planner: name_lane.py consolidate --under
Code/GameEngineDevice/Source/W3DDevice/GameClient/. The packet retains original
image paths and donor hints separately; it flags private types, mixed routing,
flags and quoted includes. It does not approve moves. The merge verifier rebuilds
the stale TU map in memory and independently approves this donor's routing.
No regenerated map or path-keyed register change is included.

## Verification and provider evidence

./build.sh on W3DSnow.cpp, Rva00093349.cpp, Rva000932E1Get.cpp,
Rva00093457Finish.cpp and Rva0009322DLightning.cpp: 19/19 exact; string, float and
import checks pass. find_declared_unmatched.py on all five: all definitions
matched. class_gate.py passes. data_check.py: zero findings; --converged:
10 addresses, zero second names, zero unjudged rows. eh_verify.py on seed:
EXACT 3. Microsoft-header check and CSV integrity pass.

Scoped upstream APIs (allowed_symbols, link_census COMDAT decoding and
data_check.object_facts) compare saved original/final objects. All standalone
code definitions, undefined names, COMDAT selections/flags, data definitions and
references, and all 56 relocation bindings are identical (compiler-local EH
labels normalized). Global provider selection examines 27 names: no selected
definition changes. Normal merge Verifier composition preserves all 56 bindings,
27 selected definitions and both data sets; no changed/dropped external code,
new undefined names or divergent duplicate code providers. Thus no changed
consumer binding needs a separate repair. These are scoped receipts, not a new
census or ownership receipt. Scripts/objects/JSON remain under ignored
build/sol-b5-lightning-*; the before/after build logs are retained there.

## Audit and handoff

Pre-publication audit covers staged edits and all pending commits from the
merge base with origin/master. There are no outgoing source path moves,
deletions, additions, ledger repoints or protected-register changes. Concurrent
upstream-only differences are not this batch. Combined path/basename searches
across tools, hooks, workflows, source includes, build inputs, registries and
Doxygen identify no consumer requiring repointing. The shared header now has
five direct consumers; all are verified together. Historical EA path evidence
and previous handoffs remain. Neither affected source owns a header/MS-header,
code-identity or data-debt key, so none is silently dropped or retired.

Remaining Snow donors: reset lacks its declaration; blend/state still have
private OVERRIDE and incompatible receiver/weather views; resource-update has
RefCountPtr/OVERRIDE conflicts; render/subbox need receiver/math declarations
and compatible layouts. renderAsQuads remains mixed. Do not repeat their
unchanged rejected trials without addressing those prerequisites. Apt rendering
was already compatible in the inherited handoff and remains Luna work.
MessageStream issue #116 is untouched.

BFME 1 freshness check: official remote fetched; pinned clean ff391a5e90 differs
from official 6f02ff5d0f. Keep verified inputs; advancing requires a full reference
update verification outside this scoped prerequisite. No freshness-success
receipt written. No maintainer-only runner or helper agent started.

Metrics: recovered bytes 0; file reduction 0; identity debt retired 0; data debt
retired 0. One additional existing donor is now accepted by normal dry-run.

## Final gate, allocation probes and publication state

Commit d8d48b0ce1 passed the normal header hook: 46/46 rows across six
sources, 12 funclet pins, string/float/import and remaining gates pass. The
conservative dependency scope additionally includes GameClient/Eva.cpp; its
27 rows remain exact. No Eva source change was needed. The publisher queued
this commit below its batch threshold; retain the six file claims below until
publication is confirmed. The runner publishes the final pending batch.

Read-only allocated probes in this session (no abandoned source edits or new
claims):

- PropDraw: current plan and frozen checks retain the prior Coord3D lifetime,
  pool-key and module-data declaration prerequisites; no unchanged trial repeated.
- DisplayStringManager: normal dry-run accepts none. Common/Rva00090360Ctor.cpp
  lacks seed declaration rva00090381; Common/W3DDisplayStringManager.cpp needs
  m_14/rva0009038. Common-owned donors require their assigned seat's repair.
- LineGroup: normal dry-run accepts none. Render's O2/arch:SSE/G7 and SetArrays'
  O2/G7 overrides differ from carried G7; destructor fails bytes. No flag or
  lifetime workaround. Receipt: build/sol-b5-linegrp-before-trial.log.
- TreeBuffer: current plan has 34 approved rows, 12 files and six mixed donors.
  Normal dry-run accepts none of its remaining donors: reset/base declarations,
  tree/count/member views, updateTexture, addTreeType, morph and Xfer declarations
  still disagree. Previously compatible donors are already in the current seed;
  this is not a lost-row claim. Common donors remain outside this seat's scope.
  Receipt: build/sol-b5-tree-before-trial.log; all temporary sources cleaned up.
- AptRenderingContext and UDP: inspected current plans and inherited evidence;
  the former is already compatible Luna work, the latter needs canonical UDP
  identity/overlap repair. No repeated unchanged trial or duplicate spelling.

Final outgoing audit covers the merge-base-to-HEAD prerequisite and this
handoff update together. No source move, deletion or repointed consumer was
introduced. Protected registers and current identity/data debt remain intact.
No new path consumer changed, so the earlier complete compatibility audit
remains applicable.

Pending file claims, all under Code/GameEngineDevice/Source/W3DDevice/GameClient/:
W3DSnowResourceView.h, W3DSnow.cpp, Rva0009322DLightning.cpp, Rva00093349.cpp,
Rva000932E1Get.cpp and Rva00093457Finish.cpp. No other seat-owned claim remains.
Release these only after confirmed push, then run claims.py release --landed.

Final progress.py origin/master: BYTE-MATCHED 7,978,500 (100%); LINKING
7,370,962 (98.11%); LINKED 7,614,012 (98.75%), census 2026-10-26 08:28 at
47e030bafc. All deltas zero; no new census or ownership receipt. This session's
result is the verified extra lightning donor accepted by normal composition;
file reduction, recovered bytes and debt retirements each remain zero.

## Recovery verification, 2026-10-26 11:12 UTC

The next session found a clean tree and two rebased, unpublished commits:
2fd1e86bfd (prerequisite) and c227ff7a1c (handoff). No preserved source edit,
preparation backup or running build needed recovery. `git pull --rebase origin
master` and `check_csv.py` passed. Keep the six file claims above until these
commits actually land; a queued publisher response is not publication.

Fresh `./build.sh` on the five Snow consumers plus GameClient/Eva.cpp passes
46/46 rows, 12 funclet pins and string/float/import checks using six current
dependency receipts. The same six-source `find_declared_unmatched.py` passes.
Rerunning the scoped provider, composed-selection and composed-binding proofs
preserves all 27 selected definitions, both data sets and all 56 relocation
bindings; no divergent duplicate provider appears. Composition uses the saved
verified artifact from the inherited trial; no unchanged merge trial was
repeated and no new merge is claimed.

The outgoing compatibility audit covers both inherited commits and this
recovery record. `git diff --name-status --find-renames origin/master..HEAD`
shows only the two prerequisite edits and this handoff. Combined path and
basename searches in tools, hooks, workflows, source/includes, docs and reverse
registers find only the five expected header consumers and historical evidence.
There are no path moves or active consumers needing updates. Neither affected
source has a code-identity, data, header or MS-header debt key; W3DSnowMath's
separate MS-header finding remains intact. File reduction, debt retirement and
recovered bytes remain zero.

Official BFME 1 master was fetched again: c0a8ed722b differs from the clean
verified input ff391a5e90. A pointer advance still requires the full reference
update verification outside this prerequisite scope; no success receipt or
input change was made. The allocation queue remains family B shard 1/2 with
no listed HELD entry. Per the inherited-work-first instruction, no new target
or claim was selected before recovering publication of this batch.

`progress.py origin/master` again reports BYTE-MATCHED 7,978,500 (100%),
LINKING 7,370,962 (98.11%) and LINKED 7,614,012 (98.75%), all deltas zero.
The remaining source prerequisites listed above are unchanged. After confirmed
publication, release the six file claims and settle landed RVAs, then select a
fresh allocated prerequisite. No maintainer-only runner or helper agent ran.
