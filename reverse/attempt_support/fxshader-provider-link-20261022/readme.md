# FX shader provider repair (2026-10-22)

Current-object legacy cohort at census08160bc2c9:
fxshaderasset.cpp 0 -> 1,007 linked bytes; the constructor/reset owner stays
194/194 and folded setter owner stays2,347/2,347. GrowthFootprints remains
independently blocked, with no coverage credit claimed. No closed-strict claim.

Target facts: existing Load call pins identify default construction at151597
and setter at2B230F. The ledger owns these through Rva00151248's constructor
and Rva0042CBB6::rva002B230F. The record has36B storage with handle slots0/8,
type4, vectorC, integer1C and boolean20. Its copy constructor1513AD is already
owned by GrowthFootprints; declare it instead of emitting a competing implicit
copy. Reuse the setter's row spelling through an explicit ABI view.

The constructor wrapper uses a36B base storage view and calls the proven
constructor. This is an ABI adaptation, not evidence of original inheritance
or application identity. Raw handles avoid implicit AsciiString initialization.
The existing SetName body retains its exact bytes through a handle cast.
Imported-forceinline keeps the forwarding constructor out of the callable
COMDAT pool while preserving the native call and exception graph. Plain
forceinline emits a wrong wrapper body under the old ctor pin, so is insufficient.
A placement-new forwarding version changes the parent's temporary stack slots;
that failed trial is not retained.

Validation:7/7 rowed code bodies,1 data row,13 string refs,2 named imports;
find_declared_unmatched clean; strict reusable self receipts via
link_check --prepare-current; check_csv clean. Before and after legacy checks
explicitly include fxshaderasset.cpp, Rva00151248Reset.cpp,
StlportVectorGrowthFootprints.cpp and Rva0042CB81.cpp. Scratch logs:
build/fxshader-cohort-baseline.txt, build/fxshader-final-legacy.txt,
build/fxshader-final-self-strict.txt. Reproduce with those explicit units.

Same-name sweep: the vector destroy unit already declares both constructors
and is not fixed by this consumer's ABI forwarding. No zero-gain sweep retained.
