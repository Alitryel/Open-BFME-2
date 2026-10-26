# Consolidation trial: profile_highlevel.cpp

Allocated destination: `Code/Libraries/Source/profile/profile_highlevel.cpp` (shard 0/5, allocation check passed). The scoped name-lane report passed its freshness check before the trial. `tu_skeleton --plan` identified 29 approved rows and two mixed donors. The unchanged merge dry run accepted the destination plus `ProfileIdConstructor.cpp`, `ConstIntGetters7Addr.cpp`, and `ProfileBlock.cpp` (31 rows), with no rejected donors.

The mixed donor `ConstGlobalGetters2.cpp` row 0x006C5E70 was refused by split dry-run because a copied helper or datum would grow an escape-hatch count. `GapBodiesSeat10O2B.cpp` row 0x006C5EB0 was refused because the namespace/extern-C block defines something and carve is unsupported. Neither split was applied.

The applied merge built successfully: 31 matched function rows, 1 byte-verified data row, EH pin verified, literals/imports verified. Post-merge `code_identity_gate.py --staged` found a new divergent definition `??0Id@ProfileHighLevel@@QAE@XZ`; `data_check.py --staged` found an outside-baseline wrong-name data symbol `?testEvent@ProfileFastCS@@0PAXA` at 0x00A0C774. These composition findings require Sol's manual identity/data investigation. The trial was not published and was restored; its patch evidence is preserved at `build/profile-highlevel-merge-20261026.patch`. No debt was retired.
