# RefCountClass helper selection, 2026-10-22

Index: retail-truth census 2026-10-22 11:05, ae3b3e68e2. Current objects
were paired for each comparison; stale census gains were excluded.

## Independently verified, already upstream

`WWLib/sharebuf_vector2_copy_ctor.cpp`, constructor 0x0015CD00, 249 bytes:
its emitted protected scalar deleting RefCountClass destructor was the /O2
body, whereas retail 0x00072899 uses /O1. Scope the existing private base
view with the same gsy optimization setting proven in MaterialInfoClassCtor.
The reference-count layout, virtual order and copied buffer remain unchanged.
The byte gate passes 1/1; legacy link_check changes 0/249 to 249/249.
Self-strict preparation passed for the trial provider. During publication an
upstream repair to the same file was discovered; the local code commit was
dropped on rebase in favor of upstream. Credit zero incremental bytes here.
No closed-strict
closure or full link-cycle gain is claimed.

## Renderer blocker, restored

`WW3D2/DX8RendererAddMesh.cpp` currently has 3,960 matched bytes and two
blockers: the same RefCountClass deleting destructor and the unsigned
ShareBufferClass allocation constructor (retail 0x000D1DE2, owned by
ShareBufferClassUnsignedCtor.cpp). Both providers were included in previews.

1. Size-scope refcount.h and declare the allocation constructor externally
   before the callers: Add_Mesh retains 919 bytes but four commutative SIB
   operand encodings change. An EH action also becomes ambiguous after compiler
   label renumbering. The full gate fails.
2. Size-scope only refcount.h: 30/30 rows byte-exact, but the allocation
   constructor remains the sole blocker; legacy 0 -> 0.
3. Extend the size scope through sharebuf.h: 30/30 still exact, constructor
   still wrong; legacy 0 -> 0.
4. Keep the inline view and put the declaration after all callers: MSVC C2908,
   specialization after instantiation.

No renderer edit retained. Do not repeat these declaration/scoping trials
without a new way to preserve the caller's code and constructor ownership.
DX8SkinClearVisibleList already has the base conflict resolved; its current
blockers are DynamicVectorClass<Vector3> virtual bodies. GridTextureMapper's
private base and derived vtables need reconciliation as well as RefCountClass.
BFME1 donor pointer remains 37c3022de1; the newer fetched donor has no relevant
link recipe beyond the already-reviewed shared-helper repairs.
