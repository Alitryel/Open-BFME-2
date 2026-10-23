# Object-list pool ownership repair

Seat s6, model gpt-6-astra, 2026-10-23. Source snapshot manifest
50ae624af20875c5e2802c845f04874062932a250f689d34764cb92048143dd9,
base772586001ef8ece5827559c44f091338519b2dc7.

The false-reject record for ctor RVA001EB984 was reproduced by the per-file
link preview. Its pool g_freelistPool00DB8FEC had only an empty one-byte class
definition and no data ownership row. Its head at pool+8 was separately owned
as g_freeList001EB130. This was incomplete source ownership, not a verifier bug.

Native RVA009B8FEC contains exactly24 bytes, recorded in native.json:
0x80, null, null, VA0042FFC0, VA0042FFE0,0. Matched ctor001EB1CB,
pop002393E2, grow001EAEF9, init002AA35C and clear001EAF7B independently
establish the six-field layout. Existing matched allocator wrappers identify
both callback targets. The next table begins at RVA009B9004.

Move the single complete definition to Rva001EB130Clear.cpp as a ctor-less
aggregate. Replace all standalone head users with the existing pool plus8.
Replace the old4-byte head data row with the24-byte pool row. No verifier,
pin, function row, baseline, whitelist or shared header changes.

## Verification

All106 existing rows in rows.tsv pass their scoped ./build.sh source checks:
GapBodiesGE51 22; Rva001EB130Clear3; Rva007AD348PoolInits70;
FormationBuildRow3; HordeContainChangeToFormation4; HordeContainRva00473212
2; HordeContainRva00475F61 2. Declared row extents total6176 bytes; alias
accounting differs from the link preview total. Pool sizeof24, initialized
bytes and both callback relocations pass data_rows --verify. Data ledger
integrity passes2140 rows. No former head symbol remains in Code or data_rows.

The saved in-memory link preview uses published census2026-10-23 03:12 at
491a8b3d87 with current edited objects: all7 units link,4473->6144 bytes;
HordeContainRva00475F61 alone changes0->1671 bytes. This is preview evidence,
not a newly run linked image or census. Three unreferenced allocator diagnostics
remain, not blockers.

Enforced data_check on7 sources finds one pre-existing wrong-name for compiler
static ?$S1 in changeToFormation at RVA00A0368C. An isolated compile of the
original source reproduces exactly the same finding with no unread rows
(before-data-findings.json). Pool bindings have no findings. No baseline was
expanded and no claim of globally clean data_check is made.

## Review and scope

Standard SureForge: retail-byte and native-field research; complete consumer
and claim inventory; acceptance/step mapping and dependency dry run; scoped
byte/data execution plus structural reference/definition audit; final manifest
and original-source regression comparison. Fresh-context Devin GLM5.3 plan
review found READY, independently checking native data and gate addends.
Full106-row inventory and aggregate-only initialization address its advisories.
Sibling pools remain separate follow-ups. One actual sibling consumer claim
was InGameUICtor.cpp RVA000B3FD0 held by fleetw4; reviewer examined different
sibling RVAs. Bounded scope remains valid independently of later claims.
Fresh-context GLM5.3 delivery review also READY: complete8-file diff,106-row inventory, source/COFF ownership sweep, native data, independent relocation-aware owner-body comparison. Its advisory stale heuristic ledger and historical prose remain unchanged. Reviewer called24-byte data minus two4-byte relocations20 bytes; correct arithmetic is16 non-relocated bytes, all covered by the actual native/data checks. Four Standard gates READY on this manifest; required publication hooks still apply. No enforced read-only sandbox was
available for reviewers; they were instructed to inspect only approved paths.
