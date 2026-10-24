# Module-data constructor link repair, 2026-10-24

BFME 2 base fae4415772, BFME 1 donor 32774ab0; same published retail-truth-4
index 268f876e3b (2026-10-24 02:54). Scoped legacy preview improves
**538 -> 750 unique linked bytes (+212 B)** across five units. All five link
cleanly after repair. This is not a closed-strict or refreshed census gain.
The initial four-unit baseline is 225 B; the unchanged family provider adds
313 B (family-before.txt). Final five-unit output independently reports the
same 538 B census baseline. No authored C++ coverage increase is claimed.

Both constructors emitted an empty UpdateModuleData helper differing from
the first indexed copy. Bridge retains its existing empty base and native
manually bound table; marking that already inlined constructor
`dllimport __forceinline` avoids emitting a second external helper copy.
Its complete body and the allocator/list ABI remain byte-identical.

LargeGroup now inherits the established novtable ModuleData interface via
novtable UpdateModuleData, whose empty constructor is also inline-only.
The native constructor installs C4D2A8. Reading retail proves all slots 1-30
agree with Bridge's established C40A10 interface; slot zero selects each
class's own deleting destructor (490472 and 45824C RVAs). The following
LargeGroup dword is not code, bounding its table at 31 slots. The member
layout remains updateRate+8, filter+C, vector+20, string+2C. See
native-tables.json for image hash and all shared target addresses. These are
target facts; the inherited slot names remain the header's structural names.

The intermediate preview exposed a second LargeGroup provider: the synthetic
EmitVtableTag constructor in FamilyDeletingDtors.cpp emitted a one-slot
table. The real constructor already emits the whole 28-byte deleting
destructor and both destructor/delete relocations. add_match.py verifies and
moves that existing row to the real constructor unit; removing the synthetic
class/constructor leaves one complete native table provider. Family retains
285 B linking, and its moved 28 B now link in the constructor. The net gain
is 99 B for Bridge plus 113 B for LargeGroup, without double-counting the
moved row or aliases. No table pin, new alias or shared-header edit.

Normal byte verification passes 18/18 touched rows, including all 11
remaining family rows. Both native constructor EH graphs are EXACT with no
baseline. Frozen-file checks, class gate, converged-data and whitespace checks
pass. Explicit safe provider receipts are prepared before and after; receipt
preparation is not proof of whole-tree closure. Both unchanged companion
destructors were included in before/after previews and continue linking.

The helper-cause sweep found these two different empty-constructor copies;
the other indexed UpdateModuleData constructor copies agree with their kept
provider. Remaining family module-data views were not changed merely because
they use a similar shape: native contract proof and a measured repair are
required for each. No previous codegen trial was repeated.
