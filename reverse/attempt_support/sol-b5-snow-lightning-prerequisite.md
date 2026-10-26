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
