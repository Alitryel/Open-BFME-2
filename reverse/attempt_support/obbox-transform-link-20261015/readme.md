# OBBox Transform provider repair

Base: cc7e658748f5dd175489d82647b45d68d4ad2d6c.
The local index is a2839ea429, dated 2026-10-15 13:35, derived from census
5986a99448 at 04:52. The JSON files pin the index and object hashes.

coltest.cpp now selects a declaration-only obbox.h link view. Its class layout,
declarations and other inline bodies are unchanged from the ZH header at the
verified BFME1 pointer a7c38d3b2597121f178ab5190b3062478823257d. Only the
Transform definition is omitted. The existing external name resolves to the
rowed 231-byte provider at RVA 000B2A4C in OBBoxTransformO1.cpp. No new name,
pin, import, linker alias or compiler optimization pragma was introduced.

Target evidence: the provider passes its full byte gate, and the existing
Rva000B3649Fetch.cpp consumer's retail calls independently select that same
name and address. The ZH header supplies the layout and operation's source
semantics; this does not establish ZH's private Matrix3x3 spelling as a target
identity. The paired object proof establishes that the change removes only
coltest's non-retail 165-byte Transform COMDAT. Every retained non-debug
section has identical bytes and relocations, including unrowed code and data.
No bodies were reconstructed or added to the ledger.

Donor review: BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b demonstrates
suppressing competing inline copies while preserving the existing operation.
Here a normal declaration suffices, avoiding an import or inline-body change.
The official BFME1 fetch reports e082760734795655f086939df77b393f4b728375;
another worker holds file:reference/open-bfme-1, so the verified pointer and
freshness success stamp were preserved.

Acceptance: normal coltest byte gate passes 2/2 rows; bounded strict preparation
of coltest, OBBoxTransformO1 and Rva000B3649Fetch passes 5/5. The objects have
strict reusable receipts. Undeclared-definition, class and new-variant checks
pass. EH reports zero EH rows. Enforced data identity reports zero findings;
the eight converged addresses have zero second names and zero unjudged rows.
The affected-source placement rescan reports zero bodies and zero pins.

The paired local legacy preview refreshes the same three objects together in
separate in-memory copies of the unchanged index. coltest loses one wrong
COMDAT finding and its undefined Matrix3x3::Multiply reference (13 findings
to 11). The normal post-change local link check confirms these removals.
Other conflicting Transform providers remain in mesh.cpp and W3DModelDraw.cpp;
mesh.cpp is held by another worker. Thus the selected-provider finding remains,
the three-source cohort remains 0/3 clean and LINKED remains 0 -> 0.
No census, closed-strict, full-link or new authored-byte gain is claimed.
Additional coltest blockers include Matrix3x3 assignment and nine competing
math inline copies; OBBoxTransformO1 also retains its Transform_Vector conflict.

The preliminary GPU constructor audit was handed back: its one-slot table
differs from the four-slot Snapshot-derived destructor provider, but retail
C1D9B0 has at least twelve concrete slots. Merely inheriting Snapshot would
not establish a correct virtual contract. The blocked attempt was recorded
and both claims released without editing source. Other near-linking probes
mostly found repairs already present; no unchanged blocked reconstruction
was retried.

Reproduce by strictly preparing the three sources at the base revision and
saving coltest.cpp, its object and dependency sidecar under ignored
build/obbox-transform-link-20261015. Save the paired findings and index hash
as before.json, apply this change, strictly prepare again and run proof.py
from the repository root. It reads those snapshots, writes object-proof.json
in that scratch directory and never updates census/index/status/history.
The section parser is the existing sibling moduledata-snapshot proof helper.
No full link cycle, census build, nightly, boot or scheduler runner was used.
