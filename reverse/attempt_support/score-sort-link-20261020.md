# Score sort linking, 2026-10-20

Base: 48bc97d94d. Published census: 3f413ed3ff, 2026-10-20 18:52.
BFME 1 donor provenance remains in the source (1281192f68); the current
reference pointer is 4483e88da1c2f3b9a273f779baac7458bd8bb891.

Current-object legacy preview before: 0 / 2,127 bytes linked. Blockers were
S4SortElem8B::operator< unresolved and a selected non-retail bool
ThingTemplate::isKindOf copy. The recently recovered S4SortElem8 comparator
is now available in this same source; older comparator reconstruction
failures do not block this repair.

Both native sort families call 0x005EC52E. Specialize less<S4SortElem8B> to
use that rowed comparison while preserving every existing B instantiation
name and ABI. Read the existing BitFlags<218> view directly inside the
comparison: native code inlines these tests, whereas the generated bool
ThingTemplate member copy differs from the separately rowed int helper.
No new pin, alias, extent, marker or optimization directive is needed.

After: legacy preview 0 -> 2,127 bytes, one unit link clean. Full byte gate
32/32; string, float and import reference checks pass. Explicit
link_check --prepare-current also verifies all 32 rows and writes a strict
reusable receipt. This is self-strict provider validation and a legacy
preview gain, not closed-strict closure or a full link-cycle measurement.
find_declared_unmatched passes. Other users of these record names only
declare them; there is no second sort implementation to repair.

Rejected first trial: inline forwarding B::operator< plus forceinline
ThingTemplate::isKindOf preserves 32/32 but still emits both wrong COMDAT
copies and links zero. The retained specialization removes the unnecessary
B member definition, and direct bit tests remove the incorrect member copy.

Recovery reconciliation: upstream commit 1cac3fabb9 independently landed the
2,127-byte legacy improvement, with a rowed B comparator ICF twin and all
33 rows verified. Keep that implementation instead of replaying this
specialization: the saved source change is superseded, not a new linked gain.
The assignment-wrapper blocker in the accompanying attempt log is retained.
