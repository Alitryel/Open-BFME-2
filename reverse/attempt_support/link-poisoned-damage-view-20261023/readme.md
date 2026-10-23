# PoisonedBehavior damage interface link repair

Inputs: BFME2 parent de463f1501; published census 456ce161c5 (2026-10-23
06:28); BFME1 reference 96c88c73a5cd1a58fc2f8db691beea50acd996db.

The constructor unit emitted three damage callbacks, with the third pure;
the first selected destructor unit emitted only onDamage. Reconcile these two
views to the native three-slot interface, implement the empty third callback,
and retain the existing rowed onDamage and onHealing providers.

Target evidence: ctor 0x00482F7D and dtor 0x00482ED9 store the damage table at
object +0x20. Retail table RVA 0x008497E8 has exactly the three entries
0x004830FB, 0x00483111, 0x000D1407 (RVA); the following word belongs to the
next table. The first two callbacks already have independent matched rows.
The third is a whole RET12 body shared with RenderObjClass::Set_Animation.
Its emitted body and relocation list are identical; add_match --icf-owner
admits the real callback as a gen-alias, with no new unique bytes or pins.

Donor evidence: the GeneralsMD GameLogic/Module/PoisonedBehavior.h under
reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour declares
onDamage, onHealing, and an empty onBodyDamageStateChange with three arguments.
DamageModule.h declares all three base callbacks pure. These establish the
semantic/signature lead; native table membership, adjustment, and complete
RET12 independently support its placement. No enum values or other class
members are inferred from the empty callback.

## Acceptance

Same two explicit sources and same census for both previews:

- Before: ctor 0/130 B, dtor 60/60 B; total 60 B linked.
- After: ctor 130/130 B, dtor 60/60 B; total 190 B linked, +130 B.
- This is a legacy scoped preview, not a closed-strict link measurement.
- build.sh: original five rows exact, then six with the shared callback.
- link_check --prepare-current: six rows exact, two strict reusable receipts;
  this is self-strict preparation and does not establish LINK closure.
- eh_verify: one EH graph EXACT, no debt, including the constructor's existing
  unwind funclet (compiler label renumbered; parent EH binds it correctly).
- find_declared_unmatched: all definitions matched.

No linker aliases, pins, flags, data rows, class exemptions, or baselines changed.
The full primary/update class views remain outside this scoped damage-view
repair. The other census DamageModuleInterface mismatch is SpawnBehaviorCtor,
whose separate single-slot placeholder also has unrelated vtable blockers;
that requires a coordinated SpawnBehavior class repair rather than copying
PoisonedBehavior methods into it.
