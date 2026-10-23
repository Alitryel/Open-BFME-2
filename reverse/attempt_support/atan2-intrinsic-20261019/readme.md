# Intrinsic float atan2 recovery

The BFME1 small-body sweep (min-size8) serves the same11B target through
Drawable.cpp and camera.cpp. Three donor addresses have identical whole
intrinsic bytes, and their WWMath/CRT float-wrapper names are not uniquely
identified in BFME2. Existing _atan2f and float-overload pins name the separate
non-intrinsic bodies at422A0/422CD; leave them unchanged.

Native1333F0 has fifteen INT3 bytes before its aligned start and five after
its RET at1333FA. Its entire effect is FLD float[esp+4], FLD float[esp+8],
FPATAN, RET: cdecl scalar atan2(y,x), returned in ST0. The mathematical effect
and ABI are target facts. The original spelling is unknown, so this recovery
uses an address-derived name rather than a guessed donor identity.

The served camera.cpp was read completely and its existing59 rows passed
their normal byte gate (43 float literals). Its field-of-view accessors use
WWMath::Atan2, but this does not identify the unreferenced out-of-line copy.
The body belongs alongside the existing sin/cos/tan/asin/acos intrinsic
wrappers in WWMath/wwmath.cpp. Its existing /Oi compiles an ordinary C++
atan2 expression to the complete11 bytes with no relocations or masks.
No original code, compiler setting, pragma, shared header, pin or alias is
changed. The existing six bodies plus the new one pass7/7. proof.json records
the whole native hash, ABI and boundaries; no additional numerical or whole
game execution claim is made.

Strict-current preparation and new-variant admission pass. The complete math unit links in the local preview against published index8eecc93d07:85 to96 bytes (+11). This is a bounded link prediction; no census or verification runner was started. Placement resweep at minimum8 reaches a fixpoint with zero extra bodies or pins.
