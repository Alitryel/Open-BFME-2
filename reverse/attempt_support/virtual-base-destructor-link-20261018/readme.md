# Virtual-base destructor link repair

Baseline 83c7c25968, published census c2c5ac8c27 (2026-10-18 11:36).
The recovered Rva005CC5E5 constructor only declared its empty destructor,
while three derived units define it inline. Its first-in-order deleting
wrapper therefore called the external destructor and used 42 bytes;
the derived copies inline teardown and use 31 bytes. Define the same empty
destructor in the constructor unit. The compiler emits its natural 28-byte
complete-object helper and the same 31-byte deleting wrapper as the derived
units. No class layout, compiler flag, pin, alias, ledger or shared header changes.
The retained constructor, vtables and every nondebug section's bytes, flags
and symbolic relocations are identical. Derived objects are byte-identical.
This reconciles a reachable helper, not an unreferenced diagnostic copy.

All 36/36 ordinary rows in the four-unit scope pass with strict reusable
receipts (self-strict currency). Paired objects on the frozen index give
legacy LINKED 57 -> 1076 B: +1019 nonpadding matched bytes in three units.
The CLI census-only before and current after predictions agree. Closed-strict
closure and full-game linking are unmeasured. No authored-byte gain claimed.
BFME1 verified donor revision reviewed remains 64d369b90170b7e9ec917d646f020b11f13eb0d5;
the reference pointer update is held by another seat's live submodule claim.
This repair uses the existing target class graph and exact objects.

Class gate, declared-unmatched, converged-data and case-collision checks pass.
The optional data --enforce check reports existing vbtable name debt at
0x00874ED4; proof.py verifies identical findings on baseline/current objects.
No baseline additions or verifier changes. proof.json records the paired
results, strict object hashes, exact retained sections and unchanged data debt.
Baseline objects are ignored scratch under build/virtual-base-link-20261018.
The separately logged CountedPairSet trial was restored after two byte failures.
