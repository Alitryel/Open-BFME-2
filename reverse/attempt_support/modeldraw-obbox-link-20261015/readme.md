# W3DModelDraw OBBox provider repair

Base: 867f0534dc765e17b812dae45211267c31888af6. The paired local index is
at a2839ea429 (2026-10-15 13:35), derived from census 5986a99448 (04:52).
Its SHA256 and the strictly prepared objects are recorded in object-proof.json.
The committed link_status.csv measurement is 4b7e7091c4 (12:36); it is a
separate measurement and is not used to claim this improvement.

W3DModelDraw.cpp selects the existing bfme_obbox_transform_link header view
before the ordinary include paths. The view retains the ZH class layout,
declarations and other inline bodies, omitting only OBBoxClass::Transform's
definition. The external call keeps its existing name. Its rowed provider is
OBBoxTransformO1.cpp, 231 bytes at 0x000B2A4C. Rva000B3649Fetch.cpp independently
proves the same name/address through its retail calls. No ledger rows, pins,
imports, aliases, layout changes or optimization pragmas are added.

The paired object comparison removes exactly the non-retail 237-byte
OBBoxClass::Transform COMDAT and its now-unused 196-byte
Matrix3D::Transform_Vector COMDAT. All 1,527 retained non-debug sections have
identical bytes and symbolic relocations, including unrowed code and data.
The provider and fetch consumer objects are byte-for-byte unchanged. The
header source carries the operation's semantics; target byte gates and call
relocations establish the provider relationship independently. This does not
promote ZH's private Matrix3x3 spelling into a target identity.

Donor review: BFME1 66b19a8e95a4add525ef808fcea088e306798e2b establishes the
repair pattern of suppressing competing inline definitions. Its damageinfo
repair c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 was also reviewed. Here the
existing declaration-only view is sufficient. Verified BFME1 inputs remain
at a7c38d3b2597121f178ab5190b3062478823257d: the overdue upstream update is
held by another worker's file:reference/open-bfme-1 claim. The freshness
success stamp was not advanced, and no unverified pointer was substituted.

Acceptance: W3DModelDraw's ordinary byte gate passes 9/9. Bounded strict
preparation of W3DModelDraw, OBBoxTransformO1 and Rva000B3649Fetch passes all
12 rows before and after; all objects have strict-current receipts.
find_declared_unmatched, class_gate, new-variants and check_csv pass. EH has
zero applicable rows; enforced data identity has zero findings. Converged
data has eight addresses, zero second names and zero unjudged rows. The
placement rescan finds zero bodies and zero pins. git diff --check passes.

Paired local legacy prediction, refreshing those same three objects into
separate copies of the unchanged index:

| Unit | Before U / COMDAT / selected | After U / COMDAT / selected |
| --- | --- | --- |
| W3DModelDraw | 15 / 92 / 42 | 14 / 90 / 41 |
| OBBoxTransformO1 | 0 / 1 / 1 | 0 / 1 / 0 |
| Rva000B3649Fetch | 0 / 0 / 1 | 0 / 0 / 0 |

Duplicates and address findings are zero throughout. Every unit loses the
wrong-selected Transform finding. The three-source cohort improves from
0/3 to 1/3 clean: the fetch consumer's 350 existing non-padding retail bytes
now pass this local legacy prediction. Its row extents total 351 bytes;
one padding byte is excluded. The ordinary post-change link_check confirms
these findings and exits 1 because the other two units remain blocked.

This is zero new authored C++ bytes. No census, closed-strict gain, dependency
closure or full-link success is claimed. W3DModelDraw retains 145 findings;
OBBoxTransformO1 retains its competing Matrix3D::Transform_Vector copy.
mesh.cpp is separately claimed by another worker. Six other near-linking
probes were already repaired in the current index, so they were not retried.

Reproduce by preparing the three sources at the base and saving the original
W3DModelDraw source, all three objects and .deps.json sidecars in ignored
build/modeldraw-obbox-link-20261015. before.json records the paired baseline
and index hash. Apply the one-line flags change, strictly prepare again and
run proof.py from the repository root. It compares all retained sections,
asserts strict receipts and writes object-proof.json without changing the
census/index/status/history. The section parser is the existing sibling
moduledata-snapshot proof helper. The JSON and acceptance logs here preserve
the measured result; the scratch objects are not committed. No full census,
link cycle, nightly, boot or scheduler runner was started.
