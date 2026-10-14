# Local math-wrapper link repair

BFME2 starting commit: f972786c444e4d2751e739718dfefbc467b4efe3.
The unchanged local census index measured 147cfae2cb at 2026-10-14 07:27;
SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
The committed link-status report is newer and was used only for discovery.
No census, status, baseline, pin, class, data binding, compiler flag or row changed.

FlightDeckBehavior.cpp and WorldHeightMap.cpp each emitted external `_sqrtf`
and `sqrt(float)` copies that lose to the first link-order provider. Include
math.h early with the established scoped static-inline pattern. Their compiled
math operations and wrapper bodies remain identical; only these two wrapper
symbols change from external to local storage. This prevents these units from
competing with the retained provider. These losing copies were not kept
providers; other consumers retain their existing bindings.

Controlled strict-current objects before and after prove all non-debug section
bytes and symbolic relocations identical after normalizing only those two
wrapper storage changes. No section is dropped from the comparison. Every
retained external COMDAT has unchanged byte/relocation digest and size;
FlightDeck retains 973 and WorldHeightMap retains 865. Strong definitions,
undefined externals and weak bindings are identical. Per-unit proof.json and
facts-summary.json record object hashes, index identity and these assertions.
Full objects, receipts, original source and executable comparison scripts remain
under build/flightdeck-math-link-20261014 and build/worldheight-math-link-20261014.

Same-index legacy local previews remove exactly two blockers in each unit:
FlightDeck 69 -> 67, WorldHeightMap 53 -> 51, with no added blockers. Both still
have unrelated unresolved symbols and competing class COMDATs; their LINKED
bytes remain zero. The units preserve 238 and 352 existing authored retail
bytes respectively. This is four repaired COMDAT blockers, zero new authored
C++ bytes, and strict self verification. Closed-strict closure, actual link.exe
placement and a fresh measured census gain are not claimed.

Acceptance: explicit strict reusable preparation before/after, ordinary batched
./build.sh (12/12 function rows and one data row), string/float/import checks,
new-variants admission, declared-definition, canonical-class, enforced data,
converged data (eight addresses, zero second names/unjudged rows), EH (zero
applicable rows), CSV and whitespace checks pass. Placement rescans find zero
new bodies or pins. No full link cycle, census build/measure/history, nightly
or boot runner was started.

The related huge-four-legs consumer was claimed first. Its original matched
1558-byte body calls the external float atan2 adapter. Static-inline math and
then declaration-only atan2f/sqrt both failed full byte comparison by changing
inlining, the square-root call and SSE/x87 scheduling. The source was restored
and its full byte gate passed again. This is a link-repair deferral, not a
revocation of its existing match. re_log.py records the evidence and its file
claim was released. blocked-huge-four-legs.txt records the gate outcomes.
RailroadGuide's broader fabs/atan math and remaining class/provider conflicts
need separate controlled evidence; this patch does not assert its applicability.

BFME1 donor review: clean checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d;
reviewed fea964f85433012ec0c95a44a8d88f77b4c29af5 (real allocator operators) and
a7c38d3b (free-callback adapter), plus the earlier surplus-emitter/COMDAT repair
leads d2e213690 and de59a7e9. The applicable surplus-emitter principle is already
established in BFME2's distance-opacity repair; no donor code, layout or address
is imported. Official master was fetched at 56e108dc; retained donor inputs were
not advanced and no freshness-success stamp was written. The earlier full
comparison has no completed baseline (interrupted exit 130, 2,806 stale TUs,
new-input gate not started): build/link-seat-freshness-20261014/comparison.json.
That broader freshness verification remains outstanding; bounded checks here
verify these units against the committed retained inputs.
