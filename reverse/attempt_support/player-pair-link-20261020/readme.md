# Player list-removal cleanup: +127 B in the legacy link preview

Base BFME2 255eb2ceb5; published census 3f413ed3ff, 2026-10-20 18:52.
Paired current-object checks of the consumer and unchanged
LocomotorSetMapSubscript.cpp provider go from 0/2, 0 B to 1/2, 127 B.
The provider itself still has independent tree/constructor conflicts. No
closed-strict closure, executable placement or authored C++ increase is claimed.

The consumer previously emitted an implicit pair<const LocomotorSetType,
vector<const LocomotorTemplate *> > destructor that differs from the kept
copy. A destructor member specialization alone passes the byte gate but does
not stop MSVC from synthesizing that implicit copy. Declare the complete
specialization with the existing const-key/vector fields and an external
destructor instead. The call still names the existing rowed 15-byte provider
at 0x000796BC; no new pin, alias, import or helper identity is added. The
existing consumer evidence establishes the folded pair teardown; this repair
does not strengthen the original application-type inference.

Acceptance: normal build.sh gate 1/1; strict reusable receipts before and
after for the consumer and for all 18 provider rows (19/19 total); EH 4/4
EXACT; class and frozen-definition gates pass; data enforcement zero findings;
converged-data ownership ten addresses, zero second names or unjudged rows;
whitespace clean. Paired previews are attached with the same provider inputs.

Donor linking review covered the existing handoffs and BFME1 linking commits
through local revision 4483e88da1c2, including the recent helper/comparator and
owned-pointer destructor repair families. No donor code was imported: the
existing BFME2 row and provider determine this local ownership repair. The
freshness success stamp remains unchanged. A broad --refresh attempt restored
401 cached objects then waited on the shared full-build lock; it was cancelled
before compiling or changing the census. The paired explicit-provider checks
above completed independently; this is not evidence of whole-tree closure.

Other same-family sole blockers were checked: the 53-byte narrow-string tree
is below the independent-repair threshold; screen lookup has the unchanged
native 0x410688 versus 0x2175CE cleanup identity/lifetime blocker documented in
link-extra-copies-20261020. TransportContain also requires an unrowed callee.
