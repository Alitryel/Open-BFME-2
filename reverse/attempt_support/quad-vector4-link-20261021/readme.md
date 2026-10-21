Quad particle renderer helper repair, 2026-10-21

The existing scoped SSE Vector4 view keeps the exact vendor component operations
visible and imports their external copies. The quad renderer emitted a four-float
constructor that differs from the rowed retail copy; neither removed constructor
nor Set has a retained incoming relocation. No new identity or layout is claimed.

Strict preparation originally refused because donor wwdebug.h's case-insensitive
parent include reaches GameEngine/Include/Common/Debug.h outside the inventoried
roots. Add the donor Code root to the search inventory and name RGBColor.h through
its actual include root. Adding Common directly was rejected as a trial because
its string.h shadows the native CRT header; the final Code root has no such effect.
Every include root exists; before and after strict receipts and the ordinary gate
pass all 3 rows, string/float/import checks and the full parent EH graph.

Paired current-object preview against unchanged legacy index 03035cf02c,
2026-10-20 22:09: 0 -> 2,120 nonpadding matched bytes. Self-strict receipts;
closed-strict closure and executable placement unmeasured. proof.py retains the
original object basename on both sides when refreshing the in-memory index.
Only the constructor and Set COMDATs disappear; every retained nondebug section,
byte, flag, definition and symbolic relocation is identical. No imported reference
is added. Diagnostic unreferenced Matrix4x4 copies are left alone.

Donor review reused BFME1 pinned 68c5ce2789e974f36b6c742d57437d157bc159e9 and
inspected c1315665a1b22beb7e6d9279548fe5b1c26ed1f9: the imported-forceinline
emission technique applies, its DamageInfo identities/layout do not. Target byte
rows, existing math owner and unchanged source operations establish this repair.
No donor update, baseline, pin or shared-header edit. t=16 model=gpt-6.1-sol.

Publication reconciliation: upstream f1485417d8 independently landed the same
particle helper/global changes before this batch rebased. The historical paired
measurements above remain reproducible but are not additional gains over that
upstream commit. Keep upstream bfme_vp_math Vector4 header. The quad include-root
and RGBColor spelling repair remains necessary: upstream source fails strict
preparation with unknown parent-traversing/out-of-inventory headers; the resolved
source passes strict 3/3 rows. This is a verified strict-receipt prerequisite for
the already-linked 2,120-byte quad unit; current incremental link gain is zero.
