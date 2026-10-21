# Reflection helper ownership and Matrix4 spelling

Inputs: BFME2 7a2d918535, frozen retail-truth-2 census 03035cf02c
(2026-10-20 22:09), verified BFME1 pointer 68c5ce2789 unchanged.
No donor implementation imported. Existing Vector4ScaleO1 and particle draw
repairs establish the imported force-inline declaration pattern.

The reflection unit emitted wrong outline copies of Vector4's four-float
constructor, vector-first scalar multiplication and Matrix4(Matrix3D).
Use the existing bfme_vp_math constructor declaration and suppress only the
other outline copies with imported force-inline declarations. Their native
inline arithmetic remains byte-exact. Retail owners remain matrix3d.cpp
(0x006D8A30), seglinerenderer.cpp (0x00191070), and
Matrix4FromMatrix3DO1.cpp (0x0006A2CD); no new pin, alias or datum.
The indexed seglinerenderer unit retains unrelated blockers.

Reflection's private struct Matrix4 mangled the projection global with U,
where the existing DX8Wrapper::DeviceProjectionMatrix owner uses V at
0x009EDBF0. Changing the public view to class also requires changing the sole
reflection setter provider and its ledger spelling from ABUMatrix4 to
ABVMatrix4. Provider layout, access, extent, purpose and all 150 bytes are
unchanged; this is a declaration repair, not a new identity claim.

Paired current-object LEGACY predictions against the same frozen index:
reflection 0 -> 1,925 nonpadding bytes; setter 150 -> 150 bytes.
Total 150 -> 2,075, gain 1,925 B. Both units link in this predictor.
All three ledger rows byte-match; reflection EH graph EXACT. Both explicit
providers pass prepare-current with strict reusable compiler receipts.
No self-strict or closed-strict placement gain is claimed.

Logs: build/seat8-sweep-current.log (reflection before),
seat8-water-setter-before.log, seat8-water-paired-after.log,
seat8-water-byte2.log, seat8-water-eh.log, seat8-water-receipt.log.
Initial trial exposed the setter spelling dependency; the paired provider
repair resolves it without introducing a second name at any address.
