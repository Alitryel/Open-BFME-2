Path::rva00365B8A link handoff, 2026-10-20

Strict original row 0x00365B8A..0x00365DF0 (614 bytes) passes. Frozen
5366c4f808 legacy preview holds 611 nonpadding bytes solely on the emitted
Coord3D::length copy: private /Os body is 33-byte x87 fsqrt, retail's rowed
owner in coord3d.cpp at 0x3571 is 69-byte SSE arithmetic with external sqrt.
The caller itself calls rowed Coord3D::normalize (0x35B6); its emitted 86-byte
copy calls length and matches. Thus length remains referenced by a COMDAT.

Two trials restored: dllimport forceinline on only the definition fails C2375
because canonical Lib/Coord3D.h declares ordinary linkage. Removing the local
length definition leaves a direct owner call but loses the compiler's no-escape
summary: main frame 0x4C becomes 0x58, many stack homes/registers move, byte gate
fails. No canonical-header or pragma experiment was made. Any future repair
must preserve interprocedural effects or reproduce the retail helper under the
caller's flags. Do not repeat simple definition removal/import redeclaration.
Original source restored; no altered C++ or pin landed. No closed-strict gain.

## Pragma/body-form sweep (claude-opus-5-5, t=60)

21 variants of the unit (scratch, not landed): `#pragma function(sqrt)` before
the includes (G), the same plus `#pragma intrinsic(sqrt)` after math.h (GI), or
a local `#pragma function(sqrt)` after math.h (L), each crossed with 7 length
bodies (`(float)sqrt(f)`, `sqrtf`, named sum, `(double)` cast, named sum plus
cast, `::sqrt`, `(float)sqrtf`). normalize stays the exact 86-byte copy in all.
They split into two disjoint outcomes: either the main body 0x365B8A is EXACT
and length is the 33-byte intrinsic copy (GI_d, GI_e, L_a/b/c/f/g), or length
is retail's 69-byte SSE copy (or 43 bytes with an x87 call) and the main body
has nd=37 (the constant lands in xmm0 instead of xmm3, the direction temp at
-0x28 instead of -0x10, frame still 0x4C). Also disproven: pragma optimize
windows (g, gy, gs, gsy, gt) around length/normalize, "g" off around math.h, a
rename sweep of the main body's locals.

Inference: retail's parent bytes need this TU to see an intrinsic (call-free)
length through normalize, so retail's Path TU emitted the 33-byte copy and the
linker kept coord3d.obj's 69-byte copy instead (it came first in link order). The
census rule that fails a unit whose COMDAT copy differs from retail's body is
stricter than the real link here. This was recorded as a false-reject lead for
link_census and should not be retried by source edits.
