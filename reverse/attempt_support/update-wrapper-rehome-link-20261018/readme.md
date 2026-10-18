# Update deleting-wrapper ownership repair

At BFME2 4a42d12029, UpdateModuleDeletingDtors.cpp emitted three synthetic
constructor/vtable scaffolds solely to instantiate deleting destructors.
AttributeModifierAuraUpdate's partial table competed with its real provider,
blocking the unit's 328 matched bytes.

Each existing destructor unit already emits its complete 28-byte deleting
wrapper. `rehome_rows.all_exact` verified all three copies against their own
retail rows, including resolved relocations, through normal build.sh gates.
Move the rows to those units and remove the three scaffolds and obsolete Dock
alternate binding. Class identities remain based on the audited retail
class-name getter and vtable slot 0, independently of this placement proof.
No new name, pin, layout, extent or authored coverage is claimed.

The same four current objects, compared against published index c2c5ac8c27
(2026-10-18 11:36), change from 232 to 532 linked bytes: +300 B. The parser
unit now contributes 244 B and the already-linked AttributeModifierAuraUpdate
and EmotionTrackerUpdate units each gain their existing 28-byte wrapper.
ProductionUpdateDtor's remaining secondary-vtable mismatch still blocks its
247 B; its rehomed wrapper is not counted as linked gain.

Acceptance: strict reusable self-byte preparation and normal byte gate 12/12,
one empty-string reference, CSV, frozen-source, class and converged-data checks.
This is a legacy index prediction with self-strict current objects, not a
closed-strict or full-link measurement. The census index/status were unchanged.
The generic rehome picker could not run because the published artifact lacks
build/link_census/census.log; the equivalent focused exact-copy check used
the existing tool without changing it.

Donor linking review: official BFME1 4040498c15 and 06a23066c were reviewed for
ownership/lifetime repair patterns. This repair imports no donor code or ABI.
The verified submodule pointer remains 64d369b901; freshness is still blocked
by the documented conflicting Rva005E394EPrimaryBase vtable identities, with
the reference scope held by another seat. See ../bfme1-freshness-20261018/.
