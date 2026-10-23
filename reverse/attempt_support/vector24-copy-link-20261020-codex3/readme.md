24-byte vector copy helper repair

Parent 51df4761ee. StlportVectorReserve0008B5B5.cpp emits an otherwise
correct 18-byte guarded construction helper at 8A173. Marking that explicit
specialization inline caused its caller, __uninitialized_copy at 8A185,
to contain the guard and constructor call instead of calling the wrapper.
Remove inline so the actual retail call boundary remains. No algorithm,
layout, name, address, pin or authored recovery row changes.

Both complete helper bodies are now exact under strict relocation resolution:
18 bytes at 8A173 call the existing 89822 constructor; 38 bytes at 8A185 call
that 8A173 wrapper. helper-proof.txt records bytes and every relocation;
no unresolved operand, masked site, DIR32 operand or extent overrun exists.
The 125-byte reserve row stays byte exact. This addresses the remaining
copy-loop mismatch after the previous guarded-constructor repair; it does not
repeat the historical unresolved constructor/type reconciliation attempt.

Donor review: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790,
inputs/vendor/stlport/stl/_uninitialized.h:61-67, provides the non-POD
_Construct loop. Target rowed Rva0008A173Copy and Rva0008A185Copy separately
establish the guarded construction identity, 24-byte stride and call boundary.
No original application element identity or payload layout is inferred.
The two other instantiating units in this family already declare construction
externally. Their previews remain linked; no same-cause edit is required.

Acceptance: strict self before/after 1/1, normal byte/literal/import gates
clean, EH0, declared definitions clean, converged data 0 second names.
Same-source-set legacy closure preview against census 5366c4f808
(2026-10-20 12:21): 423 -> 548 bytes, all three units link. Gain 125 bytes.
This is self-strict and legacy evidence, not closed-strict measurement.
