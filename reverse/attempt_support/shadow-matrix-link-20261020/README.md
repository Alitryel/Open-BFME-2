Shadow matrix callback binding, 2026-10-20

At parent 25b65d1b36 W3DVolumetricShadowCtor.cpp has 355-byte constructor
0x000F1528 and its 10-byte EH handler, but calls undefined Matrix4x4().
Retail at RVA 0x000F1564 pushes VA 0x0047671F, then count 160 and stride 64,
into vector_constructor_iterator for the matrix history at this+0x1980.
The callback is the existing 22-byte Rva0007671F constructor. Other matrix
consumers already reuse this owner (e.g. W3DSmudgeManagerRender.cpp).

Rename only this constructor unit's matrix view to that existing address owner.
The native 64-byte storage and four 16-byte rows are target evidence; the
matrix role and named application class come from the already established ZH
constructor transfer. No original matrix class identity is claimed and no new
pin is added. The owner's older Region2D representation is not changed here.
Its folded empty element callback remains the same native address.

Both consumer rows and the 22-byte provider pass normal byte verification and
strict current preparation. EH remains EXACT; converged-data and definition
checks pass. Provider independently LINKS 22 -> 22 bytes. The same-index paired
consumer prediction is legacy 0 -> 365 linked nonpadding bytes. Closed-strict
gain is unmeasured. No census/full link cycle is run.

The before/after proof checks all nondebug section bytes, definitions, flags
and relocations, allowing only the constructor's external name and the local
view's unused Make_Identity member name to change. Make_Identity's code is
identical. There are no other units with this exact unresolved callback in the
published blocker index. proof.json records index/object hashes. To rerun,
preserve build/shadow-matrix-link/before.obj or rebuild the parent source in
an isolated trial; first prepare the current provider through the byte gate.
