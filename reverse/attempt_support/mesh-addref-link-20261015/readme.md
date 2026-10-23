# Refcount copy suppression in three WW3D2 consumers

At BFME2 base `fc2ba933053bbe63042da48629ca232ab4c9c261`, reuse the
existing scoped `bfme_mesh_refcount_link/refcount.h` before `rendobj.h` in
MeshClassCollision, HAnimComboClassGetMotion and RenderObjSceneAndCost.
No shim, layout, compiler flags, ledger row or body algorithm changes.

Target evidence: all 20 matched rows pass the full byte gate. Complete COFF
comparison preserves all 63 retained nondebug sections, including bytes,
characteristics, external definitions and symbolic relocations. It removes
only three unused 5-byte Add_Ref copies and one unused 11-byte Release_Ref
copy. No retained relocation targets a removed helper and no import reference
is introduced. Before/after object hashes and findings are in object-proof.json.
The strict-current dependency receipts include the intended scoped shim after
the change, instead of the retained BFME1 refcount header.

Paired in-memory refreshes use the identical index and replace the same three
object slots. Local legacy findings fall from 10 to 6; all other findings
are identical. Whole-unit linked nonpadding bytes remain 0 before and after;
new authored C++ bytes are 0. This is four removed COMDAT blockers, not a
closed-strict or linked-byte gain. Owned objects are self-strict; other
providers retain legacy index currency. Neither the index nor committed
link_status.csv was rewritten. No full census or link cycle was run.

The runner index is dated 2026-10-15 13:35 at `a2839ea429`, with underlying
census dated 2026-10-15 04:52 at `5986a99448`; SHA256
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
It differs from the committed repair-queue measurement `ac77c85054` (14:25).
No per-row artifact or closed-strict ranking was inferred from that mismatch.

Donor review: retained BFME1 `a7c38d3b2597121f178ab5190b3062478823257d`;
reviewed `66b19a8e95a4add525ef808fcea088e306798e2b` for the established
inline-import suppression pattern. The reused shim records donor
`9cbfb551fe20dae985f91f2319d8997287b6a705`. Against the retained native
WWLib/refcount.h it changes only its provenance comment and the Add_Ref /
Release_Ref declaration annotations. Target byte preservation establishes
applicability here; donor source supplies the class semantics, not an
independently recovered target identity or new layout claim.
BFME1 official master was fetched at `95eeb3bef370a7cd730b0ad5f228c317c8756e72`;
the reference-update file is held by another live claim. Inputs and freshness
stamp were preserved; donor update verification remains with that owner.

Remaining blockers: collision has Fabs and Matrix3D default-constructor copies,
plus selected Get_Flag and Get_Pass_Count providers. HAnim retains the
WeightInfoStruct vector-deleting destructor conflict. RenderObj retains the
selected Set_Visible provider conflict. These require distinct evidence;
this change does not retry them. Mesh.cpp and meshgeometry.cpp were held by
other claims, so the refcount sweep did not edit them.

Acceptance commands/results are in acceptance.txt and accompanying logs.
proof.py and accept.py reproduce the recorded checks using local baseline
objects under build/mesh-addref-link-20261015; baseline objects are not tracked.
The section comparison helper is the existing evidence parser under
reverse/attempt_support/moduledata-snapshot-link-20261015/sections.py.
