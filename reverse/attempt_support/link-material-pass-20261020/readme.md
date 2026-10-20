# Material pass helper binding, 2026-10-20

Input: 64342c100c. Paired original and edited previews use the same published
b73720bed9 census (2026-10-20 05:34, retail-truth-2 legacy predictor).
MaterialPassInstallMaterials.cpp improves from 0 to 271 matched bytes linked.

The existing native Install_Materials body inlines StringClass(int,bool) and
DX8Wrapper::Set_Shader. Its out-of-line /O2 helper copies differ from the rowed
retail implementations. Imported forceinline definitions preserve the existing
expressions and native inlining while suppressing the competing copies. Other
unreferenced diagnostic copies remain under retail-truth-2. No identities,
layouts, pins, aliases or globals were added. The source comments retain the
ZH matpass donor provenance and target vtable/layout evidence. The same helper
binding technique already exists in Line3DClassRender.cpp and Rva00155AD0.cpp.

Original and edited --prepare-current checks each pass 2/2 complete byte rows
and references, with strict reusable compiler receipts. Edited EH graph is
EXACT 1/1. Frozen-file check passes. The staged identity shadow check reports
two divergent definitions in unchanged Add_Ref and Set_Material helpers; both
are unreferenced diagnostics in the link preview, not retail-truth-2 blockers.
Attached previews show
the legacy gain; no closed-strict link closure or C++ coverage growth is claimed.
Related Set_Shader and StringClass constructor conflicts were checked in the
ranked census: all other affected units have additional independent blockers.
