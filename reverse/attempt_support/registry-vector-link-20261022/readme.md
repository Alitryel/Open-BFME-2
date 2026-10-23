RegistryDeleteValues.cpp link repair, 2026-10-22

At BFME2 a3deb0d4e5 and verified BFME1 37c3022de1, the legacy local
link preview reports 269 owned bytes blocked by non-retail VectorClass<StringClass>
destructor/deleting destructor and DynamicVectorClass<StringClass> destructor.
The matched parent Deleta_All_Values 610300 is 233 bytes and inlines the vector
cleanup, including the array destructor iterator followed by scalar delete.
The canonical destructors are owned by dx8wrapper.cpp (121E20/122130/1243E0).

Two bounded visibility trials both failed the parent byte gate (3/4 rows passed):
extern-template declarations for both whole vector classes also suppress the
inlined constructor; narrowing to just the two destructors preserves that
constructor but replaces the required inlined cleanup with an external call.
The latter also changes branch widths and register scheduling. The patch here
is the narrower failed trial, not accepted source. No new identity or pin was
claimed. A future repair must preserve the parent's inline cleanup while
avoiding the independently emitted, incompatible destructor copies, or reconcile
the allocation/declaration context with the canonical provider.

Original source restored and ./build.sh passed all four rows plus literal,
float and import checks. No source change retained; claims released.
Compiler flags and dependencies remain those in the original TU, including the
WWString teardown shim and TU-local allocation declarations. t=7m;
model=gpt-6.1-sol.
