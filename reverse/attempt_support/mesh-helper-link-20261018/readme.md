# Mesh helper provider linkage, 2026-10-18

Paired current-object checks against the published retail-truth-2 census
c2c5ac8c27 (2026-10-18 11:36) change 0/7 clean units and 0 linked bytes to
2/7 and 1,644 bytes: MeshClassRender.cpp (1,427) and
MeshModelClassGetSortFlagsPass.cpp (217). This is a **legacy LINKED preview**;
no authored-byte or closed-strict gain is claimed. Comparing core findings
removes 45 and adds none. The other five peer units remain blocked.

The donor MeshGeometryClass view used by dx8renderer.cpp and shattersystem.cpp
puts MeshModelClass::CurMatDesc at +0x98. The existing BFME2 meshgeom shim
instead reproduces the target base size 0x8c and CurMatDesc at +0x94, as the
native shader/material accessor bodies require. Include that established
layout before the donor header's guard is set. The matched target bodies,
not donor names or byte placement alone, establish these offsets. Both units
retain their donor provenance and compiler settings.

The dynamesh color shim is a separate legacy view: its inline
MeshMatDescClass::Get_Single_Shader reads +0x94, while native RVA 00143370
reads +0x98. Leave its declaration external only for dynamesh.cpp, binding
the call to the existing rowed provider; other users retain their prior view.
No pin, new data name or vtable alias is introduced.

MeshClassRender.cpp also emitted an /O2 RefCountPtr<FXShader::RenderingMethod>
destructor with add -1 instead of the native size-optimized decrement.
Use the already established rinfo.cpp specialization and local size setting;
its out-of-line body now agrees with the native EH provider at 0007B724.
A preliminary class-import trial changed a matched Define_FVF call and was
rejected; the final layout repair preserves every matched body.

Acceptance: build.sh and explicit prepare-current pass 101/101 rows across
four providers, including 22 renumbered funclet labels verified from parent
EH graphs, one string literal and nine float literals. The prepare-current
receipts are strict reusable source receipts, not LINK closure evidence.
EH verification passes 7/7 EXACT. Frozen-source and class checks pass. Data
enforcement reports one baseline finding and zero outside baseline;
converged-data ownership reports nine addresses, no second names and no
unjudged objects. git diff --check passes.

The shadow new-variant check reports three dx8renderer incidental copies:
Vertex_Split_Table::Peek_Shader, Vertex_Split_Table::Peek_Material and
DX8FVFCategoryContainer::Generate_Texture_Categories. Their code changes
with the corrected layout, but no native whole-body claim is made for them.
They add no core link blocker in the paired retail-truth-2 preview; do not
suppress unreferenced copies merely to silence shadow diagnostics.

The seven preview sources are dynamesh.cpp, dx8renderer.cpp, meshmdlio.cpp,
shattersystem.cpp, MeshModelClassGetSortFlagsPass.cpp, MeshClassRender.cpp and
MaterialCollectorCollectMaterials.cpp. Local before/after sources and logs
are retained in build/mesh-link-20261018/. BFME1 freshness remains owned by
another seat as recorded in the preceding camera-overlap repair.
