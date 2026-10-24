# Copy-constructor lifetime partition

At BFME2 b7894b52ca, V3PolyCopyCtors.cpp had 34 matched rows (1,230 bytes)
but linked none. Its current indexed preview reported twelve unresolved class
or base destructors and a competing unproven Rva00318B5C vtable. The unresolved
owners are independent of the complete-lifetime copy and holder owners.

Move the thirteen rows (563 bytes) with their complete, unchanged class views
to V3PolyDeferredCopyCtors.cpp, retaining all provenance and target layout notes.
Keep Rva0028C62B and its containing Rva0028F68F together; both units use the
existing canonical Rva0028C6D6 header. Preserve the existing folded 0x00168040
float-vector twin rather than introducing an identity or relocation change.
No function body, compiler flag, class contract, pin or alias was added.

Paired `python3 tools/link_check.py Code/GameEngine/Source/Common/V3PolyCopyCtors.cpp`
against published census 268f876e3b (retail-truth-4) changed from 0 to 667
linked bytes after the ledger repoint. This is a legacy provider preview;
closed-strict closure was not measured. The new deferred unit is absent from
that census and its bytes are not counted as linking.

Both full scoped byte gates pass: retained 21/21, deferred 13/13. Scoped strict
input receipts are prepared for both sources, and all definitions are declared.
The source partition preserves the same Open-BFME-1 donor provenance already
recorded in the source; the verified donor pointer remains 32774ab03393709a7f14331ba8d98d281a55ffd9.
Remaining work is real destructor/vtable contract recovery for the deferred
owners, not speculative empty destructors. In particular the shared holder
factory's deferred 0x005970E6 base relationship remains unresolved in the prior
0x0059717F attempt, and the ArmyMoveCommand shared class has its own canonical
provider in Rva00538E22Ctor.cpp.
