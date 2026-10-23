# Vector3 inline ownership repair

At BFME2 8f590175f7, published census c2c5ac8c27 (2026-10-18 11:36 UTC), W3DShrubBufferRva000E8365.cpp and layer.cpp were blocked by non-retail competing Vector3 constructor/assignment copies. A TU-scoped imported forward declaration preserves the existing header definitions for inlining while leaving external ownership with the existing providers. No target identities, layouts, pins or ledger extents change.

`link_check.py` on the current objects before: both blocked, 0 linked bytes. After: shrub 752 B and layer 199 B link, +951 B total. These are legacy census-preview gains with self-strict touched objects, not closed-strict gains; all external providers were not refreshed. Unreferenced Matrix3D/Vector4/refcount differences remain diagnostic only under retail-truth-2.

Acceptance: `./build.sh` for both sources passes all 6 matched rows, string/float/import checks. `link_check.py --prepare-current` passes the same rows with reusable strict receipts. Object digests and COMDAT differences are recorded in object-proof.json. The matched source bodies remain byte-exact.

Donor review: official BFME1 master d348fca17814122303884ebe194cbc877a2c0bb0 compared with verified pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5. Its Rva007E8600Clear global-definition-to-extern repair is unrelated to these Vector3 competitors. The imported-class inline technique was verified locally against BFME2; no BFME1 link result is claimed as target proof. Reference freshness verification is tracked separately.
