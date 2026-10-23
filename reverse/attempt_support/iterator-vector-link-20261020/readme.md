# Iterator and vector helper ownership

At BFME2 b73720bed9, published census/index 2026-10-20 05:34, two current
consumer units gain 845 nonpadding matched bytes in the legacy link preview:

- ArrowStormUpdate.cpp: 0 -> 504 B. Import the STLport iterator base before
  including list, preserving inline operations while suppressing its nonretail
  external comparison. The rowed comparison remains in stlport_list_int.cpp
  (0x006CFE40).
- LivingWorldAIArmyMoverDefendHomeTerritory.cpp: 0 -> 341 B. Declare the
  BfmePod20 push_back specialization, binding the existing retail 55-byte
  provider in stlport_pod_vector_bodies.cpp (0x0059B8C6).

No game algorithm, layout, compiler flags, pin or ledger range changes.
Both consumer objects have strict reusable receipts. This is a self-strict
byte result and legacy linked preview, not measured closed-strict linkage.
Both helper providers still have independent link blockers; no full link
cycle or census was run or claimed.

Acceptance: build.sh on both consumers and both providers passes 160/160
matched rows and all string/float/import checks. The paired current-object
link_check reports both consumers LINKS, 845 B, with independent provider
blockers unchanged. Both parent EH graphs are EXACT. Class gate, declared-
unmatched, data enforce/converged checks and diff whitespace checks pass.
Scratch logs: build/arrow-{before,after,strict}.txt,
build/stl-batch-{before,after}.txt, build/link-batch1-{accept,paired}.txt.
The baseline and paired checks reuse the same published index and the provider
checks report dependency-current objects (no provider recompile).

Reference review: BFME1 checkout and committed pointer are
 a2c8039e61ad4dfb20c095d8eafe048248d31f25. Reviewed donor linking repairs
 daf5810bfc2d5a32be6b2709dd840e077629f6e8 (bind AIGroup's private pathfinder
 wrapper to the rowed callee) and 67f4eab2437e8a7ab3f22d3b3f9bf1eac91e081b
 (avoid an incompatible Thing helper copy). The ownership principle applies;
 no donor application identity or layout was imported. Local previously
 verified Horde iterator ownership is the direct implementation precedent.
 Official BFME1 master was fetched at 0dc8a26a9c6041c73dc564754cd059dc54faa72a;
 its nine-file delta has no shared header changes. Freshness baseline full
 verification remains pending on the host-wide full-build lock. No pointer
 or successful freshness timestamp has been changed.

Cause sweep: these are the only remaining single-blocker census units for
these exact names. Horde formation also has a deferred find conflict;
list-int provider has independent blockers; w3d_dep also lacks ChunkLoadClass.
They are not claimed as repaired. The pair destructor trial in
CreateAHeroDataAssign remained blocked after two variants and was restored,
recorded and released. Rva0060147B's imported EH cleanup blocker was
reconfirmed against its existing handoff, restored and released.
