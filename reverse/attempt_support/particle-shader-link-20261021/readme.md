Particle shader binding repair, 2026-10-21

LightningDrawModule's type-2 shader uses the existing BfmeParticleType2ShaderBits
storage owner from StreakDrawModuleDoParticles.cpp at RVA 009B6250. Both consumers
copy the complete four-byte word as a ShaderClass view; native Lightning selection
at 00561564 has the same DIR32 address before/after. No second data definition,
new layout or original shader name is asserted. Preserve the existing inline
copy constructor body and mark its out-of-line copy imported forceinline, as in
the matched quad/streak/default particle siblings. No import reference is emitted.

Paired legacy preview against frozen index 03035cf02c (2026-10-20 22:09):
0 -> 1,740 nonpadding matched bytes. Current self-strict receipts and ordinary
byte/literal/float/import gates pass 2/2 rows; full parent EH graph EXACT.
The only removed COMDAT is ShaderClass's copy constructor. Normalized nondebug
sections, complete bytes, flags, definitions and relocations are identical after
renaming only the known global referent. Unreferenced assignment diagnostic stays.
No closed-strict closure or executable-placement gain claimed.

Sibling cause sweep: DefaultModule6 already uses this data owner and inline
copy; no edit or gain counted. ButterflyDrawModule is the only remaining use
of the old global name, but its source is absent from this published census;
strict preparation passes 4/4 rows and ordinary preview refuses to measure it.
Its unchanged source was left alone and all claims released; revisit after a
new runner-published census. No manufactured ranking or index modification.

Donor emission review at pinned BFME1 68c5ce2789e9, including c1315665a1b22,
is documented in ../quad-vector4-link-20261021/readme.md. This repair uses target
address/ABI/row evidence and BFME2's established global, not donor shader layout.
t=8 model=gpt-6.1-sol.

Publication reconciliation: upstream f1485417d8 independently landed the same
particle helper/global changes before this batch rebased. The historical paired
measurements above remain reproducible but are not additional gains over that
upstream commit. Keep upstream bfme_vp_math Vector4 header. The quad include-root
and RGBColor spelling repair remains necessary: upstream source fails strict
preparation with unknown parent-traversing/out-of-inventory headers; the resolved
source passes strict 3/3 rows. This is a verified strict-receipt prerequisite for
the already-linked 2,120-byte quad unit; current incremental link gain is zero.
