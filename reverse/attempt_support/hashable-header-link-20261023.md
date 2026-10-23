# Hashable header scope repair, 2026-10-23

Target parent c43b6cd970; verified BFME1 input 96c88c73a5cd1a58fc2f8db691beea50acd996db.
Published index b711de3634 (2026-10-23 14:28, retail-truth-4).

The first HashableClass deleting destructor was hanim.cpp's speed-optimized
copy, proven wrong at retail EF9D6. hcanim.cpp and the shadow units already
emit the retail body. HRawLoadW3D_Unresolved.cpp emitted the same wrong copy.
Include hash.h inside each unit's existing size-optimization scope before the
first transitive inclusion, following hcanim.cpp. No new pragma, alias, pin,
class view, baseline or source compiler flag is added.

The established donor contract remains the empty virtual destructor, pure
Get_Key and NextHash field from BFME1 hash.h. BFME2's rowed EF9C2/EF9CF/EF9D6
and BCEF94 table independently prove the relevant base bodies and ABI. The
BFME1 repair review already recorded in link-seat-current-providers-20261023.md
covers the verified donor revision; additionally reviewed 87dbf3e3 (EAStringC
COMDAT ownership): its direct constructor remedy is inapplicable here. This
repair uses target-proven sibling compiler settings, not a new donor layout.

Paired current-object previews of the same eleven providers, against the same
index: original 0/11, 0 B; repaired 9/11, 9,940 B (nonpadding). Nine linked
units: hanim 908, hcanim 7,257, shadow texture destructor 121, shadow geometry
destructor 149, shadow geometry constructor thunk 154, Rva00109C7F destructor
86, Rva00109C27 constructor 70, InlineDtorDeletingDtorsC01 951, shadow texture
constructor 244. This is a scoped legacy preview, not a closed-strict or
linked-image census gain.

Both edited units pass --prepare-current with strict reusable receipts and
all 26/26 byte gates. Full EH: EXACT 3/3, no baseline. Declaration checks pass.
HRawLoadW3D_Unresolved still has independent HAnim/HRawAnim vtable conflicts;
hanimmgr still references three unrowed HMorph/W3DExclusion methods. Removing
their Hashable conflict does not claim their bytes as linked.

Reproduction: link_check.py with these two edited sources plus hcanim.cpp,
hanimmgr.cpp, W3DShadowTextureDestructor.cpp, W3DShadowGeometryDtor.cpp,
W3DShadowGeometryCtorThunk.cpp, Rva00109C7FDtor.cpp, Rva00109C27Ctor.cpp,
InlineDtorDeletingDtorsC01.cpp and W3DShadowTextureCtor.cpp. Before/after logs
and the source list are local build/link-seat-hashable-{cohort-before,after,
cohort}.txt; normal/strict gates and EH logs have the same prefix. No full
link cycle or census was run.
