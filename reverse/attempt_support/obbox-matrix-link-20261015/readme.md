# OBBox and mesh Matrix3D emission repair

Base: 6b96a49f35. The frozen runner index is a2839ea429, dated
2026-10-15 13:35, derived from census 5986a99448 (04:52). Its SHA256 is
recorded in object-proof.json. The committed link_status.csv measurement
4b7e7091c4 is separate; no new census or status was written.

OBBoxTransformO1, MeshClassCollision and MeshClassCastRay now select the
existing bfme_lineseg_math_link matrix3d.h view. It retains the complete
BFME1 matrix algorithms and layout while suppressing external emission of
Transform_Vector and Rotate_Vector using the existing dllimport/forceinline
technique. The collision sources explicitly include that view before the
render-object header. The OBBox unit retains its existing optimization
bracket, because removing it changed an unrowed Vector3 assignment helper.
That preliminary variant was discarded. No optimization pragma, pin, alias,
ledger row, data name, shared header or imported reference is added.

Target proof: strict-current before/after objects preserve every retained
nondebug section's complete bytes, characteristics, external definitions and
symbolic relocations, including local-symbol targets and exception metadata.
The changed sources retain 5, 36 and 21 such sections respectively. They
remove only the unused Matrix3D copies and helpers used solely by those
copies; no retained relocation references any removed symbol. No section is
added. The four other cohort objects are byte-for-byte unchanged. Their
retained section counts are 16 (fetch), 27 (frustum), 1,527 (W3DModelDraw)
and 37 (coltest). All seven objects have strict reusable compiler receipts.

The three Transform_Vector copies are each 196 bytes and the CastRay
Rotate_Vector copy is 181 bytes. Small unused Vector3 constructors/assignment
and Matrix3D/Vector4 indexing sections disappear with them; the JSON lists
each definition and extent. The unchanged full OBBox retail body at
000B2A4C is 231 bytes. Its external calls are independently supported by
Rva000B3649Fetch. The inline algorithms/layout come from the donor header;
byte and section evidence establish that the existing target behavior and
relationships are retained, without promoting other donor names to facts.

Paired local legacy prediction refreshes the same seven object positions in
two in-memory copies of the frozen index. Both sides include the already
landed W3DModelDraw/coltest repairs, so their gains are not credited again.

| Source | Before COMDAT / selected | After COMDAT / selected |
| --- | --- | --- |
| OBBoxTransformO1 | 1 / 0 | 0 / 0 |
| MeshClassCollision | 4 / 2 | 3 / 2 |
| MeshClassCastRay | 6 / 3 | 4 / 3 |

All other finding sets remain identical. OBBoxTransformO1 becomes clean;
the cohort changes from 2/7 to 3/7 clean and 663 to 894 existing nonpadding
LINKED bytes, a 231-byte improvement. The ordinary seven-source local
link_check confirms OBBox LINKS and exits 1 because unrelated cohort
blockers remain. This is self-strict object evidence with a legacy-index
local link prediction. No closed-strict, full-link or authored-byte gain is
claimed. Background finding sets are preserved as counts and SHA256 hashes
to avoid repeating the large unchanged W3DModelDraw report.

Acceptance: bounded strict preparation verifies 18/18 original cohort rows
and 8/8 sibling rows before and after. ./build.sh verifies all 9/9 touched
rows. Definitions, class gate, new-variants, enforced data, converged data,
ledger and whitespace checks pass. EH has no applicable rows. Converged data
covers eight addresses with no second name or unjudged row. The affected
placement resweep returns zero bodies and zero pins. Acceptance logs are
included. No maintainer-only link cycle, census build, nightly or boot runner
was started.

Donor review: retained BFME1 a7c38d3b2597121f178ab5190b3062478823257d and
repair 66b19a8e95a4add525ef808fcea088e306798e2b support the inline-emission
technique. The existing scoped matrix view differs from that revision's
game/Libraries/Source/WWVegas/WWMath/matrix3d.h only in provenance comments
and those two helpers' inline-import spelling. Receipt dependencies confirm
the selected view and resolved game/ headers exist. Official fetch reports
95eeb3bef370a7cd730b0ad5f228c317c8756e72; another worker still owns
file:reference/open-bfme-1. The overdue comparative pointer update remains
blocked; verified inputs and the missing success stamp were preserved.

Discovery/sweep: repair_queue.py link, link_rank.py top/near and provider
inspection led to the OBBox conflict. The same index lists eight authored
Transform_Vector losers. The two compatible collision units were drained.
mesh.cpp and meshgeometry.cpp are claimed by other workers. W3DModelDraw's
copy is already removed. coltest uses the distinct ZH matrix view;
LineGroupClassRender has specialized SSE/vector views. Those require a
separate supported adaptation rather than blindly substituting this header.

Remaining blockers: Collision retains Add_Ref, Fabs and Matrix3D constructor
COMDATs plus selected Get_Flag/Get_Pass_Count providers. CastRay retains its
duplicate main body, Matrix3D constructors/translation, RayCollisionTestClass
constructor and selected providers. W3DModelDraw retains 145 findings;
coltest retains ten. They were not reconstructed or papered over here.

Reproduction: strictly prepare the seven listed sources at the base, snapshot
their objects/receipts, and apply the three-source change. Strictly prepare
again and compare nondebug COFF sections and symbolic relocations; only the
listed unused sections may disappear and no section may be added. Refresh
the same object positions into separate copies of the unchanged index and
compare findings. Ignored build/obbox-matrix-link-20261015 contains the full
baseline, source backups, objects, capture/extend/proof scripts and logs.
The section parser is build/moduledata-snapshot-link-20261015/sections.py.
The committed JSON records hashes, strict currency, exact section removals
and paired findings. No shared cache, index or status was rewritten by the
comparison scripts.
