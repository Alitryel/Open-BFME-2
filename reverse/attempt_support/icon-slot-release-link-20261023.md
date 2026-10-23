# Icon-slot reference release link repair

The `Rva005E3C90Ctor.cpp` unit was blocked only by the undefined
`Rva005F38D8Ref` destructor. The matched forwarder at 5F38D8 returns the
counted icon-slot owner produced by `CreateMemberIconSlot` at 5F3652.
Its established provider, `Rva005F2CBAProgress.cpp`, implements the lifetime
with a null test, reference count at pointee +4, and virtual slot-0 release.
Use that same inline release in the two constructor units that emit the
implicit `Rva005E39F3` destructor. Updating just one leaves incompatible
copies of that destructor. The address-derived class names remain ABI views;
no new identity, alias, pin or global is introduced.

Acceptance at bb6a52e5d9, census/index d4fa46f19a (retail-truth-4):

- `build.sh` / `link_check --prepare-current`: 10/10 matched rows across both
  changed units, with strict reusable compiler receipts. String, float and
  import checks pass. Both sources pass `find_declared_unmatched`.
- `eh_verify`: all 3 parent EH graphs EXACT, including all rowed cleanups.
- Paired three-provider legacy preview (the two constructor units plus
  `Rva005F2CBAProgress.cpp`): 4,221 -> 4,377 B linkable, +156 B. The provider
  remains 4,221 B; the unit constructor changes 0 -> 156 B; the base-constructor
  unit remains blocked at 0/289 B by seven independent icon virtuals.
- Before/after diagnostic logs: `build/icon-sweep-{before,after}-seat.log`.
  This is a bounded current-object legacy prediction, not a closed-strict
  census or placed-link measurement. Global current-ledger closure remains
  blocked by missing receipt-current objects reported in the prior handoff.

The BFME 1 linking leads at committed donor 96c88c73 were reviewed; neither
the Drawable-layout nor ASCII-comparison repairs supplies this missing owner
lifetime. The release implementation comes from the already matched BFME 2
provider and is checked against the consumers' native bytes and EH graphs.
