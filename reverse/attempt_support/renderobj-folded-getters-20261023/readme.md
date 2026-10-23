# WW3D folded getter identities

Model gpt-6-astra, seat s5. Input b8613df467; BFME1 pinned 138757e9b74645fbcbb7724a7af2764e34931e11. No source, header, donor, pin or compiler-setting changes.

The existing matched Animatable3DObjClass constructors at RVA1A4900 (413 bytes) and RVA1A5C50 (213 bytes) both write VA BD6D10 as their primary RefCountClass vtable. Their COFF DIR32 operands are respectively +48 and +4D; reading the corresponding native operands independently gives BD6D10. The table emitted by their unchanged, verified source names the methods below at the stated offsets. Reading native table slots independently gives the listed code addresses. Thus these are concrete inherited/overridden entries in this already established class view, not names guessed from four-byte bodies.

| Table offset | Existing source method | Native RVA | Bytes |
| --- | --- | --- | --- |
| 144 | RenderObjClass::Get_LOD_Count | 910FB | 4 |
| 48 | RenderObjClass::Peek_Scene | 4F04F1 | 4 |
| 10C | CompositeRenderObjClass::Get_Obj_Space_Bounding_Sphere | 1A54C0 | 42 |
| 110 | CompositeRenderObjClass::Get_Obj_Space_Bounding_Box | 19BFA0 | 60 |
| E8 | Animatable3DObjClass::Get_HTree | 19F010 | 7 |

Donor/header semantics independently describe return-one, scene pointer at78, sphere atCC..D8, box atDC..F0, and hierarchy pointer atF8. Native getter accesses agree. Normal add_match --icf-owner admits each full emitted body against all existing owners at that address. All 46 rows in animobj.cpp pass, including four funclets independently resolved through parent EH graphs, one string and six floating references. There are no new unique bytes: these five bindings cover 117 bytes already represented by other owners.

Same-index 456ce161c5 (2026-10-23 06:28) eleven-source current preview before/after: five sources link in both runs, aggregate current totals 9027 -> 9143 counted bytes solely because the newly bound getter rows add 116 non-CC bytes to the already linking animation unit. No newly linking unit or unique-byte gain is claimed. The cohort removes the Get_LOD_Count and Peek_Scene unknown-address conflicts and two composite bounds conflicts where present, but old RenderObj views retain unrelated blockers. Prior upstream fixes already account for the 2724 -> 9027 difference from the census; that is not this change. This is a bounded legacy preview, not a full census/closed-strict result.
