River-area parser allocator link repair

Discovery: repair_queue.py link, then link_rank.py --near 1 --kind L.
Base checkout, measurement commit, census ancestry, exact index hash and
paired findings are recorded in object-proof.json. The local index measures
19a2565407 (2026-10-15 09:33), from census 5986a99448. The committed status
instead measures 28269d8e8d (09:31); it was not used for before/after claims.

RiverAreasDataChunkParserParse.cpp had exactly one current blocker: its
Rva005388AB destructor's COMDAT differed from the first copy, emitted by
Rva0030C1FCOwnerCtor.cpp. Both copies have identical 14-byte instructions,
but the parser referenced ?free@_STL@@YAXPAX@Z while the constructor uses
?Rva00030830GameFree@@YAXPAX@Z. The latter already has a verified, rowed
17-byte provider at 0x00030830, a whole-body/relocation twin of _free.
The original _STL spelling is pinned to that same address. This establishes
the allocator binding from target bytes and existing ledger evidence; no
new identity or layout is inferred from matching bytes.

Use that existing provider in the parser too. The destructor has an incoming
EH cleanup relocation and must remain defined. Both normal inline cleanup
and its out-of-line EH copy retain all instructions and target addresses.
No flags, headers, pins, ledger rows, baselines or census records change.

Acceptance:

- ./build.sh Code/GameEngine/Source/GameLogic/Map/RiverAreasDataChunkParserParse.cpp
  passes both rows and all applicable reference checks.
- link_check.py --prepare-current on the parser, Rva0030C1FCOwnerCtor.cpp and
  Rva00030830GameFree.cpp passes 7/7 rows, three string literals and one float
  literal, with strict reusable receipts for all three sources.
- EH verification is EXACT (one row). Frozen-definition, class, data,
  converged-data, CSV and new-COMDAT-variant checks pass; see checks.json.
- proof.py compares every retained nondebug section, bytes, flags, external
  leader and symbolic relocation. Everything agrees after substituting only
  the allocator name. Nine other COMDAT bodies are unchanged. The destructor
  family goes from two digests to one, with the same selected provider.
- Same-index paired preview, refreshing the explicit consumer and both peers
  in memory: the parser's sole COMDAT finding disappears; LEGACY linked bytes
  0 -> 440 (442 bytes of row extent). Both peers' findings are unchanged.
  The allocator provider links. The constructor keeps its four unresolved
  virtual slots and two unrelated wrong COMDATs; these are separate work.
- place_bodies.py on the parser finds zero bodies and zero pins.

This is self-strict byte verification and a LEGACY local link prediction.
No closed-strict gain, new authored C++ bytes, full-link placement or runtime
verification is claimed. No maintainer-only runner was started. Baseline
source/object/receipt snapshots remain in ignored build/river-parse-link-20261015.

Donor review: retained BFME1 pointer a7c38d3b2597121f178ab5190b3062478823257d;
official master fetched read-only at 1c4d808d. Reviewed donor linking repairs
4966496c5ae401ec877a044e1ae6dd04f9d9f65c and
6b9800e65dc6f0e7e4660ac55f27b44094f9e590: inline-wrapper COMDAT reconciliation
is applicable, but their removal technique is inapplicable to this referenced
destructor. BFME2 instead reconciles its existing allocator provider, proved
locally. No donor source or new dependencies are imported. Another worker
holds file:reference/open-bfme-1; the recorded comparative-full-gate freshness
blocker also remains. No pointer change or success stamp was made.

Queue triage: pristine-bone query, attack-approach exits, hero pointer
algorithms, reinforcement parser and object registration already pass current
local previews. Damage-neighbor parsing, NoCaseTreeValue4 destruction and
particle-base construction retain separate COMDAT blockers; no edit or claim
was made for them. Peers hold several higher-ranked files, including
ActiveBody, ScriptActions and the animation/skirmish display units.
