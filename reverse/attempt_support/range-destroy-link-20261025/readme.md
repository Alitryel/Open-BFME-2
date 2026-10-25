# Native range-destruction provider, 2026-10-25

Inspected after `e302344089`, with BFME 1 pointer `0bf534ea7ccde110c456edb9cd2dd5dae823c953`.
This is one escape-hatch retirement, not a new census linking gain.

The historical queue still lists `_Destroy<Rva005F8620Element *>` and
`_Destroy<Rva002BBB96Element *>` as unresolved. Current link tooling models
the existing alternate names. The paired control proves that the three
requested current units already preview cleanly before this source repair;
do not claim their 2,978 authored bytes as a new gain.

Target evidence: the vector destructor at RVA 005F85E1 and erase at 005F8620
call the existing 005F85C8 worker. Its full 25-byte body advances by eight
bytes and calls the rowed destructor at 005F8447. The existing worker source
and destructor owner establish that operation independently of the opaque
consumer element spelling. The original application type remains unknown;
the new eight-byte view supports this operation only and establishes no
source-level identity equivalence with another class.

The new real C++ template instantiation reproduces the complete existing
worker, including its sole destructor relocation. `proof.json` records the
whole-body comparison and preservation of the original worker. The normal
`add_match.py --icf-owner` gate admits the exact folded name at 005F85C8;
no pin, linker alias or object-symbol escape hatch was added. One superseded
alternate name is removed from StlportVectorDtorDeferred.cpp, and its single
counter key is retired through `hatch_counters.py --update`. Other tool
normalization hunks were reversed with checked narrow patches.

Validation: 71/71 body rows across the full three-source cohort; 7/7 exception
graphs EXACT; three strict current receipts. The paired ordinary previews
against index `51fde01dff` are clean both before and after. The 53 provider
bytes and 2,925 consumer bytes are preserved, not newly linked. The second
opaque range worker needs no change to resolve its current consumers; its
alias remains debt. No maintainer-only runner or census was started.
