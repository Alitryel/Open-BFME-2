# ScreenMotionBlurFilter material helper

The setter at 0x000FDB21 inlined Set_Material successfully but also emitted
a competing out-of-line copy. The target ledger owns Set_Material at
0x000662B1 in HeightMap.cpp. Imported forceinline visibility retains the
inlined behavior while removing that competing definition; no import calls
are emitted (the import-reference gate passes). No layout, rows or pins change.
The donor semantics remain as documented in the source; BFME 1 a2c8039e61
WW3D2/dx8wrapper.h has the same reference assignment and material-changed bit.
No donor layout or header changes were imported.

Same-index legacy prediction against b73720bed9 (2026-10-20 05:34):
0 -> 448 bytes linked, 0/1 -> 1/1 unit. Four rows pass the byte gate and strict
self preparation. Two funclet label renumberings resolve through verified
parent EH data. No new variants, CSV errors or undeclared definitions.
Closure has not been checked; no closed-strict or census gain is claimed.

The six other units with this blocking helper have 8-65 findings apiece.
They are not changed because this fix alone would link none of their bytes.
