Floor provider link repair, 2026-10-21

Inputs: BFME2 d317a046cd; verified BFME1 donor cea1e9734dc0c5355613b61226fe3cc2faab4aa4; published legacy index e20daa4e78 (2026-10-21 21:42). Reviewed donor linking repairs at cea1e973/a1b87e2c: preserve inline code while binding external calls to rowed providers; no donor claim substitutes for target byte checks.

The selected WWMath::Floor copy came from W3DTankTruckDraw.cpp and differed from retail 0x001540B0 (owned by lightenvironment.cpp). Current ScreenMapperCalculate.cpp had already lost its historical Matrix4/iterator blockers, so Floor was its only remaining blocker.

A TU-scoped copy of the exact resolved ZH wwmath.h changes only Floor to dllimport forceinline. Its body remains visible, all actual calls inline, and no import reference is emitted for Floor. Retail's existing owner then supplies the selected out-of-line body. A post-include member redeclaration was rejected by MSVC C2761 and discarded. No pins, aliases, data definitions or optimizer pragmas added.

Paired current-object legacy previews of W3DTankTruckDraw, ScreenMapperCalculate, lightenvironment, Render2DSentenceDrawBFME2: before 0/4, 0 B; after 1/4, 821 B (ScreenMapper). The provider itself still has independent AudioEventRTS/W3DModelDraw/STL blockers. The other two consumers retain independent Matrix3D inverse-rotate and Render2D/STL blockers. No closed-strict gain is asserted.

Acceptance: build.sh W3DTankTruckDraw 5/5 exact; link_check --prepare-current provider plus ScreenMapper 6/6 exact with strict reusable own-object receipts, two imports and two floats verified. These are self-strict receipts, not closed-strict measurement. No new authored C++ bytes. Diagnostic output retained locally under build/link-seat-floor/{before,after,strict,tank-gate2}.txt.
