# B03 destructor provider isolation, recovered 2026-10-24

Rebased onto BFME 2 8847b96bb5 with census 11b3872700 (2026-10-23
23:06, retail-truth-4). This recovery retains only B03 from the original
B02/B03/B04 isolation commit. Upstream d53db44d30 and 52409f99aa
already supplied the B02/B04 provider repairs, so those units and their
ledger ownership stay exactly upstream's. The B09 isolation was skipped
because d53db44d30 already links its whole unit. The B14 isolation was
removed because 52409f99aa already supplies its providers. The original
attempts remain in refs/runner/preparation/1792806564685037381.

B03 still needs the Rva001FE06A and Rva0037DEE4 complete destructors
and the Rva001505CD class/vtable contract. Preserve those three unchanged
class/constructor anchors in OpaqueScalarDeletingDtorsB03Deferred.cpp,
with their three 28-byte ledger rows. No name, layout, ABI, pin, body or
compiler flag changes. Upstream's native-provider rehomes stay intact.

The indexed original admits 114 nonpadding bytes in the current-object
legacy preview (zero baseline linked bytes). The deferred unit is absent
from this census and receives no credit. Neither self-strict nor closed-strict
closure is measured. The old 1,369 B sibling total belongs to older inputs.
Acceptance is the scoped byte gate, EH graph, declared definitions, CSV,
and normal outgoing push hook; recovery logs live under build/recovery-*.

BFME 1 inputs are unchanged. The earlier reference review found no donor
for these opaque providers, and reference/open-bfme-1 remains foreign-claimed.
No freshness success, census, full link cycle, nightly or boot run is claimed.
