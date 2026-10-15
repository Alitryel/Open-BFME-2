# Suppress surplus locomotor getter copies

At BFME 2 08a8c38fe3d259609b1365460062d050dc378558, six owned units
emit an unused seven-byte AIUpdateInterface::getLocomotorSet COMDAT,
digest 1e3de62314d1. Each caller already inlines its existing +0x1CC address
calculation. Mark these accessors imported forceinline, following the matched
AIFollowWaypointPathStateOnEnter sibling. Only the surplus external definition
disappears. No layout, identity, ABI, flags, headers, pins or ledger rows change.

Discovery used repair_queue.py link and link_rank.py, followed by strict current
object screening. The index has twelve getter definers: nine optimized copies
and three copies with another compiler shape. Six optimized copies are repaired
here; AIFollowPathStateMethods, AIStatesBfmeOnExit and HordeContainIface11CSlots
have foreign file claims. The other compiler shape is outside this bounded
repair. No benefit from those six remaining copies is counted.

The paired preview uses measurement 19a2565407, 2026-10-15 09:33, derived
from census 5986a99448 at 04:52. index-meta.json pins its unchanged SHA256.
Both directions refresh the same six objects in memory. Local findings drop
55 -> 49, exactly one getter conflict per source; every other finding is
unchanged. The units cover 20,363 existing nonpadding bytes. All six retain
independent blockers, so authored C++ growth and predicted linked-byte gain
are both zero. link-after.txt lists the unresolved names, duplicate definitions
and other COMDAT/selected-definition findings; its exit 1 is expected.

Acceptance:

- Strict bounded preparation before and after and independent ./build.sh:
  69/69 rows, 62 string literals plus four empty-string references, 32 float
  literals, zero named imports, zero skipped or baselined references.
- proof.py compares all retained nondebug sections, bytes, flags, definitions
  and normalized relocations, including EH and compiler directives. Exactly
  one seven-byte COMDAT disappears per object; 487 retained COMDATs are
  unchanged. There are no incoming nondebug relocations to any removed getter,
  and no new COMDAT variants against the saved before objects.
- All six current objects have strict reusable receipts. External providers
  retain legacy index currency: no closed-strict gain or link.exe placement is
  claimed. No census, index, status or history is modified.
- EH: 18/18 EXACT, no baselines or missing objects. Frozen-definition, class,
  CSV and whitespace checks pass. Placement resweep: zero bodies, zero pins.
- Converged data: six sources, eight addresses, zero second names/unjudged.
  Enforced shadow data check passes with three existing baselined wrong-name
  findings (guard, derived states and wall update). Paired data facts are
  identical; no data or baseline change is hidden by the getter repair.

Original sources, objects and dependency receipts remain in ignored
build/production-exit-locomotor-link-20261015/before. To reproduce, prepare
the six sources from sources.json at the base revision, snapshot each source,
object and receipt there, save index-meta.json, apply the source changes,
prepare again, then run proof.py. It reads the index without modifying it and
writes object-proof.json under that build directory.

One preparation was rejected because a different owned source was edited
while its global inventory snapshot was being checked. Retrying after edits
stopped passed; no witness from the rejected run is used. An earlier particle
display candidate already omitted its ranked getter and linked in the current
object. Its attempted source edit was restored, the stale finding was recorded
blocked in re_attempts.log and the claim released. Rva001F3C20Slots was screened
but left with its foreign file owner.

Reference linking review: verified BFME 1 gitlink and checkout remain
a7c38d3b2597121f178ab5190b3062478823257d. Donor repair
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 suppresses unused nonretail
DamageInfo constructors using imported forceinline. Only that emission
mechanism applies; no donor layout or body is imported. Target identities and
provenance remain in the existing ledger. Official master was fetched at
37b26691e7ebd3aca0881d8a216f4e2b3955012e. Updating the reference remains
blocked by its foreign file claim and the outstanding comparative full-gate
verification documented in ../unicode-comparator-link-20261014/readme.md.
The verified pointer is preserved and no freshness-success stamp is written.

This completes one bounded shared-dependency repair. No maintainer-only link
cycle, census build/measure/history, nightly, boot runner or publisher was
started. Remaining class/data reconciliation and broader link closure are
follow-up work.
