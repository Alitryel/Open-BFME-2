Render2D batch identity repair, 2026-10-18

The previous ProxyClass spelling conflated a Render2D 116-byte texture batch
with an unrelated four-byte reference handle and the HLod 32-byte proxy output.
Target Reset 0x119F00 accesses its batch vector at +0x34. Its copy constructor
0x119A80 and assignment 0x118E50 copy the first owning texture reference and
four seven-int arrays; vector machinery strides 0x74. These facts establish
the layout and Render2D relationship, not the original class name.
BfmeRender2DBatch is descriptive. The donor's existing behavior is unchanged.

Rename the batch view in Reset and its vector-destructor consumer together,
and rename the existing ledger/pin owners. No new alias is introduced. The
old default-ctor and dtor pins were replaced through pin_admission --add;
whole-body fold proofs in Reset bind the 9-byte constructor to 0x6CE7D0 and
the 12-byte release-only destructor to 0x118800, including all owner relocations.
The other ProxyClass views were not edited.

Same current-provider cohort before/after: Reset, Destructor,
VectorClassProxyAssign, MaterialInfoCopyCtor, HLodGetProxy. Legacy preview
111 -> 2606 B, +2495 B; Reset newly links, Destructor retains 111 B. The other
three remain independently blocked. This is not a closed-strict measurement.

Acceptance: build.sh two units 26/26 exact, import/string/float checks pass;
link_check --prepare-current produced two strict reusable receipts without
changing census/index/status; find_declared_unmatched passes; check_csv and
pin_consistency --check pass. No new authored C++ coverage.

Preparation recovery at upstream c87034b8cd: the three preceding repairs are
already upstream as 53e07d5cbe, e89ede6616 and c87034b8cd. Applied retained
stash dfbf0369e3 without --index after its index patch refused the moved
symbols.csv tail; all tracked edits merged without conflicts. All 31 saved
untracked files restored identically; stash and backup ref retained.
Rechecked 26/26 functions with two strict reusable provider receipts, CSV,
frozen definitions, pin consistency and the same five-provider legacy preview:
111 -> 2606 B, +2495 B. The three other providers retain independent blockers.
No census, index or link_status measurement was rewritten.
