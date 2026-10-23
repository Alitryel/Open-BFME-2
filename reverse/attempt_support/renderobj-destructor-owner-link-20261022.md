# RenderObj destructor owner, 2026-10-22

Inputs: BFME2 1b42f8c583; BFME1 verified pointer 37c3022de1ab944c7ffe536440d637dc8199091c; published census 08160bc2c9 (2026-10-22 17:08).

The SimpleStreakLine constructor and copy units use /O1 with EHsc. Their inherited inline RenderObjClass destructor emits a 60-byte factored-EH-prologue body, differing from the 79-byte inline-SEH retail owner at 0x0013BE20 in RenderObjCopy.cpp (/O2). Target bytes and the existing owner establish the identity and destructor relationship; no new layout or donor identity is inferred.

Add BFME_RO_DTOR_DECL_ONLY around the shared header's empty inline destructor definition and select it in the two /O1 clients. Their existing destructor declaration binds exception cleanup to the native owner. All three matched rows (99-byte constructor, 119-byte copy and 10-byte handler) remain exact. No vtable layout, pin or function identity changes.

Before: both clients have just the non-retail RenderObjClass destructor conflict, 0 linked bytes. After: 99 + 129 = 228 linked bytes. Explicit paired legacy preview with the unchanged native owner: 578 -> 806 bytes, all three units link. This is a legacy prediction, not a closed-strict linked measurement. The bounded --prepare-current check validates the three units' own current receipts and byte gates; it does not prove the transitive closure.

Checks: ./build.sh on both changed clients 3/3 exact; link_check.py with both clients and RenderObjCopy.cpp; link_check.py --prepare-current on the same three sources. The commit hook additionally verifies all matched sources reached by the shared header and runs normal ledger, class, data and source gates.

Other destructor-conflicting units from the census (dynamesh, segline, sphereobj, BaseHeightMapConstructor and the streak destructor) have independent blockers. They are not claimed as gains from this repair.
