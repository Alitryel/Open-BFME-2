# ArmyDetails unsigned vector-growth emitter repair

Base BFME 2 commit: d2f3f5eb49a767c9b0f81c4aa06198f059b6f7ab.
The ArmyDetails progress unit emits an incidental external
`_STL::max<unsigned int>` COMDAT whose standalone body differs from retail.
Give vector growth a local unsigned overload before its headers, using the
existing comparison and reference-return semantics. All vector-growth calls
already inline the comparison. Compiler flags and shared dependencies stay
unchanged; existing target rows supply identity and layout evidence.

## Acceptance and object evidence

- `./build.sh Code/GameEngine/Source/Common/Rva005F2CBAProgress.cpp` passes
  27/27 matched rows, 31 literals plus 12 empty string references, nine float
  literals and eight named imports. The renumbered funclet remains verified
  through its parent EH map.
- `link_check.py --prepare-current` passes both before and after and gives the
  current object a strict reusable receipt. This establishes current byte
  verification, not self-strict LINK closure.
- The full-object comparison preserves all 138 retained external COMDATs,
  including whole bytes, extents and relocation digests. Every other nondebug
  section and relocation remains equal after normalizing COFF indices. Strong,
  undefined and weak bindings stay equal. The sole removed external COMDAT is
  the 16-byte max template, `8b4424048b108b4c24083b110f42c1c3`. The private
  replacement is eight bytes, `8b113b100f43c1c3`. Neither helper has outgoing
  relocations or incoming nondebug relocations.
- The archived object-proof.py makes those assertions; object-proof.json records
  hashes and the measurement identity. Before/after objects, sources, receipts
  and executable comparison inputs remain under ignored
  `build/link-seat-20261014b/`.
- Six EH rows are EXACT, with no nonexact, missing or baselined row. Declared
  function, class, new COMDAT variant, CSV and whitespace checks pass. Enforced
  data checks find no new datum; converged-data check finds no second names or
  unjudged rows across eight protected addresses. Placement resweep finds zero
  additional bodies or pins.

## Measured result and remaining blockers

Both legacy previews use the unchanged runner index at 147cfae2cb,
2026-10-14 07:27, SHA256 recorded in object-proof.json. The newer committed
reverse/link_status.csv is discovery evidence only, not a compatible before
measurement. For the touched consumer's 4,213 existing unique bytes:

| Check | Before | After |
| --- | ---: | ---: |
| Legacy local link findings | 5 | 4 |
| Legacy local LINKED bytes | 0 | 0 |
| New authored C++ coverage | 0 | 0 |

The max COMDAT finding disappears. Four unresolved names remain:
`??0Rva005D4DA9@@QAE@HABVAsciiString@@@Z`,
`??1Rva005F3444Base@@QAE@XZ`,
`??BAptTextPlusStringPlusStringText@@QAE?AVAsciiString@@XZ`, and
`?rva005F3652@Impl@ArmyDetailsMovieClip@StrategicHUD@@QAE?AURva005F38D8Ref@@H@Z`.
No other consumer or cohort gain is claimed. The bounded closed-strict request
`link_check.py --refresh --current-ledger SOURCE` refuses judgment because 150
current-ledger provider objects are missing. No self-strict or closed-strict
LINK gain, fresh census result or runtime result is claimed. No census
build/measure/history, full link cycle, nightly or boot runner ran.

A neighboring trial in StrategicHUDRegionDetailsStructuresMovieClip.cpp is
inapplicable: its current object emits no unsigned max COMDAT. Adding this
pattern changes the already competing, unrowed element-vector insert helper
from 262 to 257 bytes. The source was restored and its seven-row strict byte
gate passes again. Its separate virtual-method/layout/provider blockers need
independent evidence, not this repair.

## Donor review and reference freshness

Reviewed BFME 1 repair de59a7e9f891b3ed2d4221d151ca881f4b75a583 at retained
reference revision a7c38d3b2597121f178ab5190b3062478823257d. It reconciles
incidental Apt isUndefined COMDATs whose inline shapes agree but standalone
copies differ. That repair principle applies; its code, layout and measured
link result are not transferred. BFME 2's established local unsigned-max
repairs in StrategicHUDRegionDetailsArmiesMovieClip.cpp and
HordeContainModuleDataParse.cpp supply the concrete implementation pattern.
Target whole-object equality independently supports its application here.
The donor allocator repair fea964f85433012ec0c95a44a8d88f77b4c29af5 was also
reviewed and is inapplicable to this unused max emitter.

Official BFME 1 master was fetched at
fc5aa8096e78297c2955e69de93aa0516ecbbe4f. The clean verified a7c38d3 checkout
and gitlink are retained. Comparative full verification remains outstanding:
the previous baseline was interrupted with 2,806 stale matched units and no
completed comparison. No freshness-success stamp is written. This session
uses the retained verified inputs for the bounded checks above.
