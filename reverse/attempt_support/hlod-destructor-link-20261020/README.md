HLOD link repair handoff, 2026-10-20

No repair landed; restore both original sources. Frozen published index
5366c4f808 predicts 14,709 nonpadding bytes held in hlod.cpp and 30 in
HLodModelArrayDeletingDtor.cpp. Before trial, strict byte checks passed 157/157.

The fixture defines a wrong strong complete ModelArrayClass destructor and a
wrong vtable; hlod.cpp emits the real 45-byte destructor at 0x0019E580.
The fixture owns the verified 30-byte scalar deleting destructor at 0x0019F4E0.
Making the dummy complete destructor inline removes its strong ownership but
also stops emitting the rowed scalar destructor. An additional unused static
construction anchor did not recover emission. Both trials failed only that row.

A separate hlod.cpp blocker is HLodDefClass scalar deleting destructor: current
30-byte body calls the correct complete destructor but uses add esp,4, while
retail 0x0017FEA5 uses pop ecx (28 bytes). Existing /O1 providers are exact.
A local size-optimization delete anchor after hlod.h did not change this body,
probably because an earlier header inline delete site fixes instantiation.
No remaining existing main-unit byte mismatches were observed.

The patch preserves the second trial for diagnostics, not a viable candidate.
A next attempt needs a coherent ModelArray shared class/emission contract and
an evidence-backed compiler-setting treatment of HLodDef's deleting wrapper.
Do not repeat inline/noinline or the post-header unused static anchors alone.
No new pin, alias, data symbol or verifier exception is justified.
Target bytes establish destructor identity/cleanup; donor class layout is from
reference/open-bfme-1 at 92f6bbe8, game/Libraries/Source/WWVegas/WW3D2/hlod.h.
