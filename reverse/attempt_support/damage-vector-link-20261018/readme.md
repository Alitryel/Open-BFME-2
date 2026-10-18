DamageNugget vector provider repair

At BFME 2 693e5fda75, the current constructor unit fails the legacy link preview because its local vector/base teardown emits wrong COMDATs and an unresolved allocator import. Declaration-only specializations bind native calls to the existing vector destructor at RVA 00507BD0; the rowed owner is StlportVectorDtorFamily.cpp. Native constructor/dtor and EH relocations establish this relationship. Existing names/layouts are retained; no donor identity inference or new pin.

Same-index current-object before/after previews include the unchanged destructor family and DamageScalar provider together. DamageScalar already links 387 bytes before the edit; only the constructor unit newly links 463 bytes. The broad destructor family retains unrelated blockers, and this is a legacy preview gain, not a closed-strict link measurement.

All seven affected rows pass strict self preparation before and after; the two rowed destructor-provider rows pass the normal gate. Eleven local COMDATs disappear, fourteen retained COMDAT bodies/relocations are identical, and no new COMDAT is emitted (proof.json). The EH cleanup labels renumber but their parent graphs resolve exactly to their existing retail RVAs.

BFME 1 repair leads reviewed at 67f4eab2 (not imported): remove private helper owners where native calls already identify a shared provider. Verified donor inputs remain 64d369b9; the pending update is blocked by previously reproduced DIR32 vtable failures in other claimed units.
