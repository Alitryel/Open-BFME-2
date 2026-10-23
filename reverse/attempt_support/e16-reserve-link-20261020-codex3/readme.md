# E16 reserve provider selection

At 6e3cb37055, stlport_vector_e16_o1.cpp emits a non-retail
vector<BfmeE16>::_M_allocate_and_copy<BfmeE16 *> through its unrowed
reserve. The same pinned name is a whole-body retail fold at 0x0022105B
in Rva002214C5Vec.cpp, Rva00579731Dtor.cpp and stlport_vector_e16_noexc.cpp.
The index selects the first, wrong copy. Declare reserve to use its existing
rowed provider at 0x0022118F rather than emitting that competing chain.
No names, pins, layouts, or ledger rows change. BfmeE16 remains a size-only
placeholder, not an asserted recovered target type.

Paired legacy link_check against b73720bed9 (2026-10-20 05:34) on the
provider and two consumers: 0 -> 1,147 B, from 285 + 862 B in the callers.
The provider remains blocked by independent assignment/copy/overflow
variants. The second caller is read-only (claimed by another worker).
This prediction establishes no self-strict or closed-strict link-cycle gain.

Acceptance: ./build.sh provider 11/11; eh_verify.py 1/1 EXACT;
find_declared_unmatched.py all defined functions matched; diff check clean.
Compiler flags unchanged. Direct member-template specialization was tested
first and causes VC7.1 C1001 at _vector.c:50; ordinary reserve specialization
is sufficient and compiles cleanly. No compiler or check workaround used.

BFME1 donor review is unchanged from the script-cleanup evidence in this
session (0dc8a26a9). The target's own existing STLport providers establish
this repair; no donor layout assumptions are required.
