# Linking pass 2026-10-22: blockers investigated and left open

Index: the published census-index (census 2026-10-21 21:42 at e20daa4e78)
brought to HEAD with `link_check.py --update-index`, then every object
re-judged under the current ledger (link_check.refresh over all objects;
--update-index only rereads changed objects, so verdicts tied to renamed rows
go stale). Model: claude-opus-5-5. Landed fixes are in the commit log
(search "Relink" / "Link" by NotNBR on 2026-10-22).

## Regression sweep

link_check over the 21,631 files that linked at the census: 45 no longer
link. Most "unresolved" names there are defined by units added since the
census (unpreviewable until the next one). The real causes were same-day pins
(750046c6d) and renames (751a74f3, de43a1b6f), and declaration-only
suppressions from the automated STL sweeps (645251fcd, a1fd3e23b, 0d7369275)
that changed another inline copy in the same unit (an erase, ~vector or
operator= that inlined the suppressed member now calls it), which then lost or
was kept ahead of the retail copy. All but four tiny ones are fixed; a sweep
that adds declaration-only suppressions should re-check the unit's other
COMDATs and the units that share them.

Left: `__imp_?deallocate@?$__node_alloc...`, `__imp_?__stl_throw_range_error...`
(Rva001F077DDtor.cpp, BaseHeightMap_Rva00069F4F.cpp,
BfmeStringTailRecord180Ctor.cpp, DisplayRegisterVideoBuffer.cpp) and
`___ImageBase` (atlbasemodule.cpp): unchanged units and headers that linked at
the census; most likely a link_check excuse difference, not a real break.

## Open blockers (cause established, no fix landed)

- `DX8Wrapper::Set_Transform(Matrix4)` in LineGroupClassRender.cpp (4,516 B,
  sole blocker): retail's 1,349-byte copy (owner StreakRendererSetTextureBFME1.cpp)
  and this /O2 unit's 1,198-byte copy differ from the first byte. dllimport on
  the declaration drops the copy but changes Render's inlining (FAIL).
  Set_Shader/Set_Material dllimport is byte-safe in this unit.
- `vector<unsigned>::operator=` in AIBuilder.cpp (1,751 B, sole): its copy
  differs from the five kept copies only in the free call's name
  (`Rva00030830FreeAllocation` against `_free`, both 0x00030830). Spelling it
  `free` (extern "C", with or without throw(...)) changes the frame of six
  rows: cl treats the CRT name specially. Across the index 966 copies differ
  from the first copy only in such names; resolving names to addresses in the
  digest comparison would unblock 3 files (1,880 B), not worth a rule change.
- `basic_string<char>::append<const char *>` (selected in 44 units): retail's
  body (owner stlport_narrow_string_append.cpp, a private reconstructed view)
  has no length_error check; every unit instantiating the vendored STLport
  4.5.3 template emits a copy with it, and stlport_narrow_string.cpp's comes
  first in link order. A declaration-only member-template specialization ICEs
  cl 7.1 (C1001 at _string.h:573). Needs a vendored-header decision.
- `PartitionFilterPossibleToAttack` / `PartitionFilterSameMapStatus` vtables
  (AIAttackApproachTargetStateOnEnter_Unresolved.cpp, 1,981 B): retail's
  vtables at 0x007F91B0 / 0x007F91BC have three slots (scalar deleting dtor
  0x00395A19, allow, getPlayerMask folded at 0x0036CC7A), as that unit and
  AIUpdateInterfacePrivateCommands.cpp declare. PartitionManager.cpp,
  JetAIUpdate.cpp and DozerAIUpdate.cpp see the one-slot class from the ZH
  reference header (GameLogic/PartitionManager.h under
  reference/open-bfme-1/inputs/reference/...), and come first in link order.
  Needs a BFME2 PartitionFilter base view for those units (shim header).
- DX8RendererAddMesh.cpp (3,960 B): its RefCountClass/ShareBufferClass<unsigned>
  copies differ from retail by optimisation flavour (/O2 `add esp,4` against
  retail's /O1 `pop ecx`) and by its view's destructor body.
- `_STLP_alloc_proxy<void**>` copy constructor (selected, 5 units): pinned to
  0x006CFE10 (edx form, fold-proof stlport_hash_map_int_resize.cpp); ten units
  compile the ecx form, which is retail's 0x0027EA56 body shared by the other
  alloc_proxy copy constructors. Retail's swap inlines it, so no call site
  decides which address the void** instantiation had.
- Matrix3D default constructor (9 units): 127 private layouts; units whose
  Vector4 rows are trivial emit `mov eax,ecx; ret` against retail's vector
  constructor iterator body. Needs the class-header lane.
- Eva clearer `Rva001DCD3C::rva001DCD3C` duplicate (Eva.cpp /
  EvaRva001DF42D.cpp): known trade-off documented at the top of
  EvaRva001DF42D.cpp.
- Streak renderer duplicates (streakRender.cpp, StreakRendererRenderStreak.cpp,
  StreakRendererSetTextureBFME1.cpp): strong (NODUPLICATES) and inline
  (select-any) definitions of getVertexBuffer, subdivision_util and
  RenderStreak collide; under active work (8a936d9bd), left alone.
