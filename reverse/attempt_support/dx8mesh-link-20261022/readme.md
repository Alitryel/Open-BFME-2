# DX8 mesh renderer link repair

At published census 08160bc2c9 (2026-10-22 17:08), a current-object check
of DX8RendererAddMesh.cpp reports two wrong retail COMDAT copies:
RefCountClass's scalar deleting destructor and the unsigned ShareBufferClass
aligned constructor. The unit's 3,960 non-padding matched bytes do not link.

Use the aligned-buffer declarations already present in
DX8SkinClearVisibleList.cpp: declare base destruction and Delete_This out of
line, and keep the unsigned aligned constructor visible as an imported forced
inline specialization. The existing ShareBufferClassUnsignedCtor.cpp supplies
the standalone constructor and buffer destructor. The target layouts and
constructor algorithm are unchanged: base count +4, raw pointer +8, array +12,
count +16, alignment +20. No pins, rows, aliases or shared headers change.

Before and after checks use the same published index. Legacy current-object
preview improves 0 -> 3,960 bytes for the renderer. All 30 rows pass the byte
gate, including their unwind actions; --prepare-current produces strict reusable
receipts. Converged-data, class, undeclared-definition and whitespace checks
pass. This is self-strict byte verification and a legacy link prediction;
closed-strict closure and a new census are not measured. Authored C++ byte
coverage is unchanged.

Same-cause sweep: DX8SkinClearVisibleList.cpp already has these declarations
and now retains two independent DynamicVectorClass<Vector3> vtable/deleting
destructor conflicts. sharebuf_vector2_copy_ctor.cpp already links with current
objects; no new credit is assigned. lookuptable.cpp and GridTextureMapperClass
have additional independent provider/vtable blockers. Do not repeat old
RefCountClass flag/novtable trials without addressing those prerequisites.

BFME1 linking review used committed clean donor 37c3022de1ab944c7ffe536440d637dc8199091c
and fetched master 024afb28c1aaeeb06c8045b52a0bf3b56ecbd25f. This repair inherits
the already adapted BFME2 sibling's emission treatment; donor identities and
layouts are not newly asserted. The pointer freshness update is held by another
worker's file:reference/open-bfme-1 claim; this seat retained committed inputs
and did not mark the stale freshness stamp successful.

A separate LineGroupClassRender.cpp attempt could not reuse the GPU transform
import recipe: both imported WWINLINE and imported forceinline Matrix4
Set_Transform definitions change Render's SSE register ordering (1/7 rows fail).
The original source was restored and verifies 7/7; the blocked verdict is in
re_attempts.log and all eight claims were released.
