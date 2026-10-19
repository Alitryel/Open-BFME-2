# Link repair recipes: generated teardown copies (2026-10-19, opencode-dsv41)

Two repeatable repairs for the `duplicate` / `comdat ... (retail: ...)` blockers
that dominate the link queue. Both were verified with `tools/build.py` (rows
unchanged) and `tools/link_check.py` (`LINKS`) before landing.

## 1. Declare the generated teardown the view emits for free

A private per-unit view that declares no destructor makes the compiler emit one.
That implicit teardown loses to the rowed/kept copy whenever the two views name a
different base (the deleting/destructor relocation target is part of the COMDAT
digest) or when only one view declares it. Declaring the teardown in the losing
view stops this TU emitting a copy, and the name binds to the kept definition.

Landed:

- `Code/GameEngine/Source/Common/Rva000B9AC2Dtor.cpp` + view fix in
  `Code/GameEngineDevice/.../W3DScriptedModelDrawEventUpdate.cpp`
  (`??1Rva000BB4AC@@QAE@XZ`; the view generated an empty implicit teardown), +61.
- `Code/GameEngine/Source/Common/Rva0032A082Ctor.cpp`
  (`??1Rva0032A082@@UAE@XZ`; our view derives from `Rva003B3417`, the agreeing
  views from `Rva0032989F`), +48.
- `Code/GameEngine/Source/Common/Rva00132C28PrototypeCtor.cpp`
  (`??1BfmeThingSJ@@UAE@XZ`; base named `GenBase009EB7D0` here), +90.

Fails when the unit's matched row itself inlines the teardown: declaring it turns
the inline expansion into a call and the row stops matching. `__declspec(dllimport)
__forceinline` keeps the row but leaves `__imp_<name>` unresolved (`error C2264`
on destructors; ScoredKillEvaAnnouncerController.cpp `??1Rva004147CF@@UAE@XZ` is
one such case, +223 held out). Defining that import pointer with `__identifier`
did not resolve it either.

## 2. `#pragma inline_depth(0)` around a shared view include

When a shared view header defines `virtual ~Base() {}` inline and the rowed copy
was compiled `/Ob0`, a `/O1` TU inlines the empty teardown into the generated
scalar deleting destructor and the COMDAT digest differs. Wrapping only the
`#include` keeps the call out-of-line without touching the TU's own bodies.

Landed: `Code/GameEngine/Source/Common/Rva001095B2Dtor.cpp` (+93) and
`Rva00109610Dtor.cpp` (+79), both `??_GBfmeShadowBufferOwnerBase@@UAEPAXI@Z`
against the /Ob0 copies in `BfmeShadowBufferOwnerBaseDtor.cpp` /
`W3DVolumetricShadowBufferOwnerDtor.cpp`.

Same shape, not yet solved: `??_GRefCountClass@@MAEPAXI@Z` minority copies
(`GridTextureMapperClassCopyCtor.cpp`, `MaterialInfoCopyCtor.cpp`,
`sharebuf_vector2_copy_ctor.cpp`, `mesh_geometry_copy.cpp`, `lookuptable.cpp`
digest `b66afec61ab4` vs `302af674788e`); declaring that view's teardown added two
more vtable blockers, so the difference is upstream of the teardown itself.
`BfmeHeroElement005C39DE` (`Rva004072D2.cpp`,
`CreateAHeroDataResetElements.cpp`) differs from the retail-proven owner
`CreateAHeroElementCopy.cpp` by compiler flags (`/O1 /Ob2` vs `BFME_ASCII_DTOR_DECL`),
not by the dtor declaration.
