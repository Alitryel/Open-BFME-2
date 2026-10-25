# ModelConditionUpgrade consolidation restored for identity review (2026-10-25)

The allocated TU dry run accepted the destination plus `ModelConditionUpgradeConstructor.cpp` and `Rva004B63BDUpgradeImplementation.cpp` unchanged. The merge preserved three rows, built, and passed its declaration checks. The commit hook's scoped identity scan found one new shadow finding: `definition: divergent | ?set@WeaponTemplateSetHead@@QAEXH@Z` (three rows scanned, one new finding).

Because the selected COMDAT/provider for this symbol was not verified against the changed composition, I reverted only this merge trial, restored both donor files and their prior ledger paths, and released the trial's file/RVA claims. No source move or identity-baseline edit remains from this trial. Sol should resolve or verify this divergent COMDAT before another attempt.
