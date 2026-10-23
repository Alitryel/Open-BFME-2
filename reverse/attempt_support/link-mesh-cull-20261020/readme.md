# Mesh cull header reconciliation, 2026-10-20

Input c06338fc81; published census b73720bed9 (2026-10-20 05:34).
Paired current-object legacy previews improve MeshModelPostProcess.cpp from
0 to 102 matched bytes linked. The two rowed helper provider units remain
linked at 1,213 B; the three-unit cohort improves 1,213 -> 1,315 B.

The ZH shader header puts the cull flag at bit 19; target Set_Cull_Mode at
0x00065FD6 and Disable_Backface_Culling at 0x00188670 use bit 20. The latter
also accesses Shader at +0x98 and ShaderArray at +0xF8 in the target's 0x118
material description. Existing bfmeshader/shader.h and meshmatdesclayout/
meshmatdesc.h encode those independently measured target facts. Include
these views before the donor headers, as existing sibling units do. This
replaces both incorrect helper copies with retail copies, rather than
suppressing a helper with the wrong behavior. No shared header, pin, alias,
layout definition or symbol identity was edited.

Original and edited strict --prepare-current byte receipts both pass the
entire 102 B parent and references. Ordinary build of consumer and both
providers passes 25/25 rows. No EH graph belongs to the touched consumer.
Frozen-file check passes. Attached paired previews and provider check are
legacy link measurements, not closed-strict closure. No authored C++ byte
coverage growth or full link-cycle result is claimed. Other indexed units
with these helper conflicts retain 17-25 independent findings and were
not modified without a whole-unit improvement.
