# Renderer material/category ownership, 2026-10-18

Base: 25aa764078; same published census c2c5ac8c27, 2026-10-18 11:36.
Continues the Peek_Shader ownership repair in the same renderer family.
Donor survey and pinned BFME1 freshness blocker are documented in
peek-shader-link-20261018/readme.md; no donor update or shared-header edit.

Remove the old, unrowed Zero Hour Generate_Texture_Categories definition
from dx8renderer.cpp. Its independently verified BFME2 owner at 0x00146BA0
is DX8GenerateTextureCategoriesBFME2.cpp; the old definition was a strong
duplicate and also emitted divergent split-table material helper copies.
The native owner still contains all five rows and its established layout.
Its MeshMatDescClass::Peek_Single_Material stays available for inlining but
imports the outlined copy from the existing dynamesh provider.

Removing the old definition also removes the last emission trigger of the
already rowed 11B GapFillerClass::Get_Material_Array at 0x005796A8. Preserve
its exact outlined body via a member-pointer anchor, analogous to the
shader-array accessor anchor in the preceding repair. These anchors are
compiler scaffolding, not retail data. First trial failed only because that
row stopped emitting; the second whole-byte build passed all 88 rows.

Acceptance:

- Paired identical FOUR-provider local LEGACY previews: 131 -> 1009 linked
  bytes, +878 existing retail bytes. Provider cohort includes unchanged
  shattersystem.cpp: its current model helper removes an old census-only
  selection blocker. Recompiling the pre-change source pair against that
  same cohort still gives only 131B; its earlier repair is not counted here.
- Strict reusable byte receipts: 91/91 rows across four explicit providers;
  string, float and import references pass. All six EH graphs are EXACT.
- New-variants passes for all three edited/provider witnesses (exit 0).
  Before this repair the renderer had three variant refusals, evidenced in
  the preceding shader repair. Class and declared-definition checks pass.
- No new functions/rows or authored coverage. No self-strict LINK,
  closed-strict or full-link gain is claimed. No full link runner used.

Remaining renderer blockers include native constructor ABI differences
(AppendLock, DynamicVB, sorting vertices and WriteLock), normal-array bool
argument, procedural material-pass return type, the skin delayed-pass copy,
and separate lock/vector/model/transform COMDATs. The shatter unit has its
own unrelated material and geometry blockers. Follow-up needs evidence for
these providers/layouts, rather than repeating the removed copies.
