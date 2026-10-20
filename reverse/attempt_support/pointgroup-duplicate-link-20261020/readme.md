PointGroup duplicate-definition repair, 2026-10-20

Retire the strong Get_Flag definition in pointgr.cpp by making it inline,
and move its existing 15-byte row to the copy already emitted in
PointGroupClassRender.cpp. Both copies had COFF digest 1f9edb2c622f, including
relocations; add_match verifies the new row at retail 0x00179090. The old
present-unmatched marker now correctly describes the body outside its row unit.
No new marker, anchor, pin or header change is needed.

Make Render's 488-byte rva00917920 helper noinline inline, matching the existing
copy in RenderVolumeParticle. Both emitted copies have digest 46a867201d51.
Donor identity remains the existing BFME1/ZH provenance in the source and ledger;
this change establishes only target code ownership and COFF selection.

Self-strict before/after: 53/53 rows, all float/string/import checks exact.
EH: EXACT 2; frozen-source check passes. Paired legacy preview against census
e7a7769fe5: Render 0 -> 1,517 bytes; the 15-byte getter changes row unit but is
counted once. Net +1,517 linked bytes. pointgr and RenderVolumeParticle retain
independent blockers listed in the reports; no closed-strict or census gain is
claimed. Baseline sources and ledger were restored temporarily and byte-verified
before capturing the saved before report; final sources were then re-verified.

BFME1 4483e88da and recent linking commits reviewed this session: no applicable
same-name repair. This uses the established BFME2 selectable-copy pattern while
preserving target identities and all native bodies.
