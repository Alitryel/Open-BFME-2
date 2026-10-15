# MeshGeometryCopy refcount link repair

At BFME2 base `46c6ab72343a30c461f65ef0454d5a747f564b54`, include the existing
scoped `bfme_mesh_refcount_link/refcount.h` before `rendobj.h`. No layout,
compiler flags, shared header, ledger row or algorithm changes.

Target proof: seven ledger rows byte-match, including both complete parent
bodies (assignment 0x00168FE0..0x001692EA, copy constructor
0x0016A230..0x0016A31B), three funclets and two compiler EH handlers. Both
parent EH graphs remain EXACT. Full COFF comparison preserves all 24 retained
nondebug sections, their bytes, characteristics, external definitions and
symbolic relocations. Only unused 5-byte Add_Ref and 11-byte Release_Ref copies
are removed. No retained relocation targets either helper and no import is
introduced. Object hashes and exact findings are in object-proof.json.

Paired in-memory refreshes replace the same single owned object in the same
unchanged index. Legacy findings fall 7 -> 5. All other findings are identical.
Whole-unit LINKED nonpadding bytes remain 0 -> 0; authored C++ byte delta is 0.
The consumer has a strict-current receipt; other providers use legacy index
currency. This is not closed-strict evidence. Neither census/index nor committed
link_status.csv is rewritten. No full census, link cycle or nightly was run.

Index measurement: 2026-10-15 13:35 at a2839ea429, underlying census
2026-10-15 04:52 at 5986a99448; SHA256 recorded in object-proof.json. This
is different from repair_queue's committed ac77c85054 measurement. No missing
or mismatched per-row artifact was used for a data-back ranking.

Donor review is inherited from the unchanged mesh-addref-link-20261015 pass:
BFME1 a7c38d3b2597121f178ab5190b3062478823257d; emission-suppression repair
66b19a8e95a4add525ef808fcea088e306798e2b and existing shim donor
9cbfb551fe20dae985f91f2319d8997287b6a705. No donor scan was repeated.
Donor source supplies class semantics; identical retained target code establishes
applicability without a new identity/layout claim. Actual dependency receipts
resolve the existing scoped shim and intended game/ headers. Official BFME1
master was fetched at 95eeb3bef370a7cd730b0ad5f228c317c8756e72; its update
remains held by another live file claim. Retained inputs were preserved and no
freshness success was stamped.

The same pattern was checked in MeshGeometryReset: its current local baseline
already has zero findings. Its trial passed 14 rows and removed an unused
correct helper, but was reverted because it repaired no link blocker. Its file
claim was released. MeshGeometryCopy is the only changed consumer.

Acceptance: byte gate 7/7, definition/class admission, new-variant check,
data/converged-data checks, both EH graphs, check_csv and diff --check pass.
place_bodies reports zero new bodies or pins. Local link_check returns 1 with
five expected residual findings, exactly checked by proof.py. prepare-current
was used for the owned object only; proof.py refreshes only its in-memory slot.
The scripts use ignored baseline objects under build/refcount-link-seat and the
existing section parser under moduledata-snapshot-link-20261015.

Remaining independent blockers: RefCount scalar deleting destructor, MultiList
constructor and scalar deleting destructor, MeshGeometry secondary vtable,
and the selected MultiList deleting-destructor provider. These require separate
evidence. Other live mesh.cpp/meshgeometry.cpp claims were respected.
