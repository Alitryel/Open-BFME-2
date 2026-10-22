# TransitionDamageFX destructor linkage

At b9b81c7b01, the published 08160bc2c9 index selects a non-retail
`DamageModule::~DamageModule` copy. The consumer destructor at 4BA47C
calls retail 4B96CC; its existing whole 25-byte owner is
`Rva004B96CC::~Rva004B96CC` in Rva0049B47CThreeVptrDerived.cpp.
The consumer now declares that row name directly, retaining its existing
three-base layout. No target class rename or new symbol pin is asserted.

Paired current-object `link_check.py` before/after: consumer 0 -> 114 B,
provider 371 -> 371 B; total 371 -> 485 B (+114). These are legacy
previews against the same published index, not closed-strict gains.
`./build.sh` and `link_check.py --prepare-current` pass all four rows,
including the deleting destructor, EH handler and unwind action; no skipped
literals/imports. The latter writes a self-strict reusable source receipt.

The same-name sweep checks all ten DamageModule class views. Other callers
already link except EvacuateDamageCtorModuleFactoryBody.cpp: its 174 B
require PB_DeepBase teardown, an EvacuateDamageInterface slot, and a matching
evacuation-list destructor in addition to its own implicit DamageModule
destructor. No speculative changes to that independent class contract.

The current-source census preview remains unchanged until a maintainer
refreshes the census. No full census or link cycle was run.

## Remaining bounded work

The EvacuateDamage constructor row at 4BAE1D has a proven 96-byte extent;
its unit contains 174 matched bytes. A fresh legacy `link_check.py` still
reports 0/174 with unresolved `PB_DeepBase::~PB_DeepBase` and
`EvacuateDamageInterface::slot`, plus non-retail and wrong-selected
DamageModule and evacuation-list base destructors. No source trial was
retained. Reopen after supported class/interface and list-provider repairs;
the direct consumer binding above alone cannot make this unit link.

Session fallback audit: link_rank top 30, near 2 and near 1 expanded to 300;
class_views --blockers; repair_queue link; current-object provider checks;
and name_globals --dry-run (0 files/edits). The remaining bounded leads
retain the class, vtable, callee or compiler prerequisites documented in
20261022-link-current-provider-triage.md and the linked earlier evidence.
No new gain was found in the inherited fixes already linking with current
providers. BFME1 repair commits were reviewed at fetched 19d28f2bd; the
verified 42bba2ddbd pointer remains unchanged because freshness integration
is claimed by another seat. No donor freshness success was recorded.

The earlier completed rehome scan found three exact homes whose six units
already link (4,432 -> 4,432 B). This session's read-only
`rehome_rows.py --limit 120` repeat was interrupted during home verification;
it is not an exhaustion result and applied no changes. No optional data-back
ranking artifact matching the census was available.

Progress against origin/master reports +0 authored C++ and +0 published
census linking bytes. The measured +114 B above is a current-object legacy
preview, not an updated census or closed-strict result. The unrelated -24 B
generated coverage delta is present in the pulled parent, not this repair.
