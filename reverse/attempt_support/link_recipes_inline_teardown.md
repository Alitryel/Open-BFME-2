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

## 3. Duplicate strong definitions of an inline body

A `duplicate` blocker is the pair rule: link.exe compares every definition with
the first one in link order and reports it when either side is exclusive. Two
units that both define the same out-of-line body therefore charge each other
even when the bytes agree. Which fix works depends on whether the symbol is one
of *your* rows:

* **Not your row -> rename it.** `DeployStyleAIUpdateCtor.cpp` carried an
  in-class `Rva0048E634Reset()` while `DeployStyleAIUpdateHelper.cpp` owns the
  rowed `?Rva0048E634Reset@DeployStyleAIUpdate@@QAEXXZ` @0x48E634. Renaming the
  in-class helper (`resetMember3E4`) removes the colliding strong definition and
  keeps every call inlined, so all nine rows keep retail bytes; the unit went
  from 1,495 to its full 2,723 held-out bytes. This is the cheapest form and it
  needs no declaration change at all.
* **Not your row, and it must stay callable -> `__declspec(dllimport)
  __forceinline`.** Same unit, same symbol, before the rename: the suppression
  removed the COMDAT and left the rows identical (1,495 -> 2,723). It is the
  same recipe as `MeshModelTextureReplacement.cpp`; only the emission goes away.
* **It is your row -> neither works.** `Rva00559CE5Wrapper.cpp` needs
  `Rva00559B4BCheck`'s body visible for its own 39-byte wrapper row, while
  `Rva00559B4BCheck.cpp` holds that row at 0x00559B4B. Both alternatives were
  measured and both change the wrapper's bytes:
  - `inline` on the duplicate definition (SELECT_ANY fold, `noinline` kept):
    `83 c4 04` (add esp,4) becomes `59` (pop ecx) after the checker call;
  - deleting the definition and calling the external symbol: the same `59`
    substitution, from the caller's side.

  So a duplicate whose symbol is your own row cannot be folded by declaration
  tricks; one of the two units has to stop claiming the body.
