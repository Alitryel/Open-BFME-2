# Reference freshness comparison, 2026-10-23

At BFME 2 2bb4ace602, compared the clean committed BFME 1 pointer
138757e9b74645fbcbb7724a7af2764e34931e11 with official master
21ef97bd08952c60197cc69c79fcc8dc383e9332. The latter changes 239 files,
with no changed h/hpp/inl headers. The existing layout resolver points to
present game/, inputs/reference/, inputs/vendor/, inputs/toolchains/ and
inputs/baselines/ directories. The STLport vector header, GeneralsMD engine
include directory and tools/lift_lane.py are present at their resolved paths.

Full ./build.sh runs on both pointers give the same result:

- 98,138/98,138 function rows across 23,426 sources pass.
- 31,533 strings, 2,257 empty references, 9,103 floats and 6,411 imports pass.
- All 2,144 data rows, pin consistency, module registry, source claims and
  the no-op patch pass.
- Both exit 1 solely on DIR32 consistency:
  `??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@` resolves to both
  0xc496e8 and 0xc497b4. This is a pre-existing class-view conflict, not a
  reference update regression. Existing investigation is in
  reverse/attempt_support/link-seat-fireweapon-20261023.md; reconciling the
  complete multiple-inheritance views remains necessary.

The reference checkout and index were restored to 138757e9. No success stamp
was written to build/bfme1-last-check.txt; the freshness check remains due.
Local complete outputs are build/link-repair-20261023/freshness-{old,new}.log.
The old run preceded the two vector growth edits; their 151-row scoped gate
passes independently, and the new full run includes them. No reference
headers or baseline were substituted to obtain these results.

Donor linking review covered StringBase/MD repairs at 138757e9 and 0a12ba59,
compiler settings at c5880f3b, inline-getter changes at c20e733a, and the
FunctorNotSet MD change at 54493f97. Applicable shared inputs are inherited;
remaining BFME 2 blockers require target-specific class or compiler work.
The new-pointer scan found 38,781 donors, 5,515 proven placements and 616
near leads; ranked returned zero eligible files. The lift lane ran with
--limit 1000. New-pointer scan artifacts must not be reused as old-pointer
evidence; regenerate after any subsequent pointer update.
