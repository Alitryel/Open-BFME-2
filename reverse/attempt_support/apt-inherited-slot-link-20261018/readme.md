# APT inherited virtual slot link repair

The constructor providers in Rva006D6360Ctor.cpp and
Rva006ECFC0Siblings.cpp declare BfmeAptValue006DCD20::vtableSlot0 before
the virtual destructor. Three consumers omitted that inherited slot, so
their Rva006D6360 / Rva006D6470Owner vtables differed from the selected
copies. Retain that base view and its eight-byte footprint; replace padding
where necessary so all member offsets and allocation sizes stay unchanged.

Paired replacement of only these three objects in the published
c2c5ac8c27 census predicts legacy LINKED 0 -> 688 non-padding bytes:
Rva006EC730GetBounds 460, LadderPreferencesDtor 127, Rva006F1360Dtor 101.
The proof compares every non-debug section with symbolic relocations,
excluding only the changed vtables. All retained sections are identical.
All 12 matched rows, string/float/import references and strict reusable
compiler receipts pass. Class gate, undeclared-definition and new-variant
checks pass. This is a self-strict byte check and a legacy link prediction;
closed-strict closure and a new census were not measured. No authored C++
coverage is added.

A fourth consumer, Rva006DA4D0Finish.cpp, passes its row after the same
repair but remains unresolved at rva006D9500 and its two placeholder virtual
slots. Its edit was reverted; the attempt log records the dependency.

BFME 1 linking repairs through official master e813ba2a were reviewed.
06a23066's StringBase-backed string-destructor repair applies to a different
cause. The verified donor checkout remains 64d369b9: another seat owns the
reference pointer, so no update or successful freshness stamp is claimed.

The commit hook's shadow identity check still reports the pre-existing
GetBounds call binding to AptBasePtrStack::At at the wrong candidate address
0x006FE580. The paired object proof leaves that call and its relocation
unchanged; the inherited-slot repair does not claim to resolve it.
