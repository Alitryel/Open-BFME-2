# part_buf.cpp link repair: ??_H and ShareBufferClass<unsigned> ??_G (2026-10-21)

The census (2b4d1fb42a) blocks part_buf.cpp (174 rows, 33,849 B) on these names:

- `??_G?$ShareBufferClass@I@@UAEPAXI@Z` (/Ot copy). **Solved** by the `/Os`
  absent-from-retail anchor in `part_buf_anchors.patch`, which keeps 174/174.
  The implicit ??_G takes the optimize state of the first function that needs
  the vtable. Neither the class-definition point nor the end-of-TU state
  governs it.
- `??_H@YGXPAXIHP6EPAX0@Z@Z` (/O2 copy 4a16af1679; retail /O1 6246c280fc at
  0x1423). The matrix3d.h include (through AABoxClassLink.h) is the first
  need. An anchor placed after it leaves the /O2 copy; this was tested at
  AABoxClassLink.h, rendobj.h, seglinerenderer.h, part_buf.h, simplevec.h,
  vector3.h, line 125 and the end of the TU.
  - An anchor at the top or after vector4.h gives the right copy.
  - **Without `#pragma auto_inline(off)` in the anchor region**, ??_H becomes
    inlinable. Later `new Vector3/Vector4[n]` then elide the
    ??_H(…, 0x47A6A9 empty ctor) call, which breaks 6 rows. This applies to
    "s", "sy", "gs" and "gsy" alike, and to a gsy region around
    `#include "matrix3d.h"`.
  - With auto_inline(off), as in MeshGeometryShareBufferInstantiations.cpp,
    only 3 rows stay wrong: ParticleBufferClass ctor 0x1AC860, Reset_Colors
    0x1A89E0 and the copy ctor. Reset_Colors is a pure ebx<->ebp swap.
  - Probable cause: ??_H's body is now compiled before its callers (same-TU
    callee lever).
  - Declaring the ShareBufferClass<Vector3> ctor specialization (row owner
    MeshGeometryShareBufferInstantiations 0x169780) breaks the copy ctor and
    does not help.
  - Untried: an unused-local count scan (docs/recipes.md, "Local count
    decides commutative operand order") on the 3 functions, and permute.py.
- Second barrier: `?Resize@?$SimpleVecClass@VVector4@@@@UAE_NH@Z` is
  wrong_selected. streak.obj emits digest 93b443b2e75a ahead of the retail
  row in StreakLineCtor.cpp (0x1A7C80); see re_attempts for the
  decl-only-block EH state shift in ??0StreakLineClass. part_buf cannot link
  until that is fixed too.
