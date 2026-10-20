# String-record copy provider binding

`Code/GameEngine/Source/Common/Rva003371B1Copy.cpp` now declares the
`vector<BfmeStringRecord000331962>` copy constructor instead of instantiating
another definition and its allocation/copy helpers. The retail parent at
0x003371B1 calls the rowed vector copy at 0x0033629E. Its existing provider is
`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_stringrecord_331962_allocate_copy.cpp`.
This changes template ownership, not the still-uncertain record identity.

Paired legacy `tools/link_check.py` previews against census 144ed0ccab
(2026-10-20 15:34) report the caller's 122 non-padding bytes:

- Before: does not link, 0 bytes. Non-retail vector-base constructor and
  `__uninitialized_copy` definitions block the unit.
- After: LINKS, 122 bytes. Only an unreferenced vector-destructor diagnostic
  remains; retail-truth-2 does not treat it as a blocker.

`./build.sh` verifies all five caller rows, including the EH graph binding
the renumbered placement-cleanup funclet. String, float, import and source
claims checks pass. `find_declared_unmatched.py` passes.
`link_check.py --prepare-current` separately verifies the caller's five rows
and the provider's six rows with strict reusable receipts.

Checking provider and consumer together preserves the caller's legacy gain.
The provider itself remains blocked by an undefined default record constructor
and a non-retail selected record assignment. These are pre-existing provider
issues; this repair does not claim a closed-strict gain or newly authored C++
bytes. The measured improvement is +122 legacy linked bytes.
