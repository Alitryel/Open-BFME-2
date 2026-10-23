# Region-query iterator emission repair

Rva005009AANextStep.cpp emitted a competing int/int tree iterator prefix
increment even though its callers inline the operation. Use the existing
STLport step directly in the first query loop: assign the node returned by
_Rb_global_inst::_M_increment. This is exactly the vendor operator body;
the unused return reference is unnecessary. The other query iterator type
and all retail behavior stay intact. No headers, flags, names, pins, ledger
rows, globals or verifier rules change.

Base checkout: 863e4456b8 (origin/master 1d591774d7). Measurement index:
28269d8e8d, 2026-10-15 09:31 UTC, SHA256
6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
The paired preserved/current object checks independently reproduce one
retail-wrong iterator COMDAT before, zero local findings after. The normal
CLI agrees: legacy local LINKED 0 -> 413 existing nonpadding retail bytes.
This is no new authored C++ coverage or executed-link/census measurement.
Consumer receipts are self-strict; no closed-strict closure is claimed.
The index, link_status and history are unchanged.

object-proof.json establishes that the only removed COMDAT is that increment,
all 37 retained COMDATs are unchanged, and every retained nondebug section has
identical bytes, extent, flags and symbolic relocations. Local destinations
include their section content and offsets; SafeSEH indices are normalized.
No retained relocation references the removed copy. External/weak bindings
are unchanged; no imports or undefined symbols were added.

Acceptance: ordinary byte gate and bounded --prepare-current pass 7/7 rows;
all three renumbered funclets bind through their exact parent EH graphs.
EH verification is 2/2 EXACT. Local link preview and --new-variants admission
pass. Data enforcement has zero findings; converged enforcement has zero
second names or unjudged rows at eight addresses. Frozen-file, class gate,
CSV and whitespace checks pass. place_bodies finds zero bodies or pins.
Scratch snapshots and the complete comparison script are under ignored
build/region-iterator-link-20261015. Verification used gpt-6.1-sol.

The ranked queue contains many other instances of the same iterator name,
but only this file has it as its sole finding. The other unit with two
findings, Rva0041573FParse.cpp, already has an explicit imported-inline
increment repair; no redundant edit is made. Other consumers need separate
provider/layout work. Eva's simple comparison repair was unavailable because
another worker holds its file claim.

Donor linking review: retained verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d.
The previously documented dedicated sweep and donor d3f9000fe08615a100e844adfff57fa4a39cd615
support suppressing incidental emitters while preserving retail callers;
no donor layout or implementation is imported. Here the operation comes
verbatim from the target's existing STLport dependency. Official BFME 1 master
was fetched at 4d506dbb57690a913403c09a0ab83b2a22e80f83. A live foreign
file claim still owns the overdue pointer update. Preserve the verified
checkout and pointer; comparative full verification remains outstanding,
and no freshness-success stamp was written.

Independent blocked trial: BoneFXUpdateUpdate's node allocator allocate and
deallocate conflicts survive two verbatim imported-forceinline specialization
placements. Both trials pass 5/5 byte checks, retain both conflicting 26-byte
wrappers and incoming allocator-helper references. The original source was
restored, the claim released, and evidence recorded through re_log.py.
An erroneous locator was explicitly voided and corrected to 0x00487DEE.
No full census, link cycle, nightly or boot runner was started.
