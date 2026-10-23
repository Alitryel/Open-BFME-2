# Existing mesh-material providers

BFME2 input 76f06c1239, published census b711de3634 (2026-10-23 14:28,
retail-truth-4). Existing meshmdlio.cpp row ownership holds helpers in a
blocked unit even though current material-reader units already emit complete
retail-exact copies. Rehome ten rows without changing names, ABI, layout,
source, flags, pins or aliases. This adds no authored C++ coverage.

Preflight verifies each full receiving body and all relocations: ten exact,
zero unresolved relocations and no wrong identity bindings in moved rows.
These are existing named methods on the same classes, reached by their
material-reader callers; original source/notes preserve target identity
and layout evidence. Same bytes alone do not establish a new class identity.
The target-specific context gap before Textures remains opaque.

BFME1 reviewed at verified f5140c1c: meshmdlio.cpp's Add_Shader,
Add_Vertex_Material and legacy peek methods, plus current split reader
implementations. Its published status still marks meshmdlio and both split
providers blocked, so no donor linking result is imported. The existing
BFME2 split units already contain supported target-layout/ABI repairs and
retail-exact helpers; those are the proof used here. The previous full donor
comparison is recorded in link_library_providers_20261023/readme.md.

Rows (RVA, size, receiver):

- 0x0018A290, 93 B, Code/Libraries/Source/WWVegas/WW3D2/MeshLoadContextAddLegacyMaterial.cpp
- 0x0018A230, 87 B, Code/Libraries/Source/WWVegas/WW3D2/MeshLoadContextAddLegacyMaterial.cpp
- 0x00188090, 54 B, Code/Libraries/Source/WWVegas/WW3D2/MeshLoadContextAddLegacyMaterial.cpp
- 0x00189390, 38 B, Code/Libraries/Source/WWVegas/WW3D2/MeshModelLegacyMaterials.cpp
- 0x00189360, 34 B, Code/Libraries/Source/WWVegas/WW3D2/MeshModelLegacyMaterials.cpp
- 0x001886C0, 22 B, Code/Libraries/Source/WWVegas/WW3D2/MeshLoadContextAddLegacyMaterial.cpp
- 0x00149520, 28 B, Code/Libraries/Source/WWVegas/WW3D2/bfme2_mesh_material_pass.cpp
- 0x00143490, 9 B, Code/Libraries/Source/WWVegas/WW3D2/MeshModelTextureReplacement.cpp
- 0x001886E0, 16 B, Code/Libraries/Source/WWVegas/WW3D2/MeshLoadContextAddLegacyMaterial.cpp
- 0x000D205F, 11 B, Code/Libraries/Source/WWVegas/WW3D2/FXShaderRendererSkin.cpp

Paired scoped legacy preview: 8,088 -> 8,479 B, **+391 B linked**,
5/6 units clean before and after. Moved row extents sum to 392 B;
link_check's non-0xCC coverage metric counts 391 B. Both preview runs exit 1
for meshmdlio, whose independent Load_W3D/texture calls and Has_Shader_Data
copy remain blocked. No self-strict, closed-strict or full-image gain claimed.

Acceptance: 59/59 function rows pass the scoped byte gate, five string
literals plus ten empty references, seven floats and three imports verified.
EH 7/7 exact without baseline. All ten existing code-identity findings are
unchanged; moved rows introduce none. Frozen-definition check, check_csv and
git diff --check pass. No new pin, alias, compiler option or verifier change.
