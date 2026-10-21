# Link-helper reconciliation handoff, 2026-10-21

No newly linked bytes. All source trials were restored and all claims released.
The four new blocked verdicts are in `reverse/re_attempts.log`. This is evidence,
not a source recovery or a linking improvement.

## Inputs and measurement

- BFME 2 HEAD: `7e457d4a3b`.
- Published index: `d08db10acb`, 2026-10-21 18:42, `retail-truth-2`.
  `link_check.py --fetch-index` restored the published objects successfully.
- BFME 1 checkout reviewed: `a80da2e3be84ebdb3b6bc280faca3f99a44788af`.
  The existing freshness check was under 24 hours old. New donor commit
  `cea1e973`'s applyPacket ILT repair did not establish an applicable BFME 2
  transplant. The earlier declaration-only tree repair is already inherited.
- Explicit-unit `link_check.py` measurements below are legacy previews. No
  closed-strict improvement is claimed. Normal byte gates checked retail bytes.

## New blocked trials

### BfmeRefVGO parameter destruction

`Code/GameEngine/Source/Common/Rva00893030RefDispatch.cpp`, row 0x006CE080,
132-byte extent. The sole blocker is the destructor COMDAT. The visible O2
destructor conflicts with the rowed O1 provider at 0x000A9822 (30 bytes).
Declaring it without a body binds that provider, but changes the caller's native
inline release to an outlined call and reshapes registers: one of three byte
rows fails. Restored. The previous imported key-cleanup/EH blocker evidence was
also reviewed; do not repeat it unchanged.

### Narrow filebuf helper visibility

`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_filebuf_underflow.cpp`,
0x00013D90 (10 bytes) and codecvt row 0x0001D140 (43 bytes), legacy 0/53 bytes.
The losing copies are `setg` and `_M_do_noconv_input`; rowed providers are at
0x0001D100 (28 bytes) and 0x0001D810 (34 bytes). A late declaration specialization
for `setg` fails C2910 because this is an explicitly specialized char class.
The input-helper declaration fails C2908: it was already instantiated while
including fstream. Narrowing whole-class emission to just underflow does not
change that boundary. Two failed builds, restored. A supported earlier
declaration boundary or class reconciliation is needed.

### Pod16 tree-node helper

`Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_pod16_subscript.cpp`,
0x00257252 (92-byte extent, 91 authored bytes), legacy 0/91 bytes. The sole
losing outline is `_M_create_node<BfmePod16>`; its native provider is 0x00413374
(34 bytes). Both a declaration-only specialization and an imported-forceinline
specialization with the exact vendor body reorder the four rep-movsd
instructions relative to address calculations and pushes. The parent retains
its extent but fails its byte row. Two failed builds, restored. The next repair
must retain the original instantiation visibility and alias analysis while
binding the outline to the native provider.

### VectorClass<Vector3> class table and helper emission

`Code/Libraries/Source/WWVegas/WWLib/vector_class_vector3_ctor.cpp`, constructor
0x000F0D2F (150 bytes), handler 0x00763A4E (10 bytes), two unwind rows:
legacy 0/160 authored bytes.

The local destructor declaration is nonvirtual, whereas the donor class and
existing provider table establish a virtual destructor and six table slots.
Restoring virtual on the declaration fixes the table and preserves all four
byte rows, but emits a 28-byte scalar deleting destructor that calls the
destructor. The kept mesh object emits a 71-byte deleting destructor with inline
Clear. Adding the actual vendor destructor and Clear bodies still preserves
4/4 rows, but emits a 34-byte deleting destructor and a conflicting 37-byte
Clear outline. Scoped `optimize("gt", on)` with an explicit destructor
instantiation also moves zero bytes. The last diagnostic patch is retained as
`vector3-trial.patch.txt`; it is not an accepted implementation.

The kept 71-byte body saves esi, sets the vptr, conditionally calls delete[] on
Vector when IsAllocated, clears Vector, IsAllocated and VectorMax, then
conditionally deletes this. Its calls clean the stack with add esp,4. Mesh,
collect, pointgr and dx8skin index copies agree (digest prefix ac2be0dc8c7c), but
this helper name has no independent retail address in the index: copy agreement
alone is not retail identity proof.

Adding `// cl: /O2` was not an effective O2 experiment. The flag-default resolver
normalizes this row's flags to `-O1 -arch:SSE -G7`; a passing default overrides
the source setting. No flag-default or gate edit was made. A supported mixed
helper-emission/compiler explanation remains necessary. Do not repeat the
table-only correction as though it were a complete repair.

## Queue checks and remaining leads

`link_rank.py --top 30`, `--near 2`, `class_views.py --blockers`, and
`repair_queue.py link` were reviewed. Many ranks are stale relative to current
source: explicit probes already link AIClosestEnemySearch (2,159 bytes), seven
Apt slot-zero units (1,873 bytes), nocase clone/copy (334 bytes),
Rva006ABC60Destructor_Rva0005925E (85 bytes), Object_topple (133 bytes), and
W3DTankDrawConstructor (202 bytes). These are pre-existing gains, not this seat's.
An Object_topple helper trial passed its byte checks but was restored because
its baseline already links.

`name_globals.py --dry-run` found zero edits in zero files.
`rehome_rows.py --limit 20` could not run because
`build/link_census/census.log` is absent. The index itself is present. Do not
start a maintainer-only census to recreate that artifact.

Other reviewed blockers retain concrete prerequisites: the CrushDie audio
element has only a four-byte opaque private view, incompatible with the full
AudioEventRTS layout; its native element ctor/dtor identities must be resolved
before rebinding. Rva0055BF4BFinish needs an unrowed derived destructor.
BridgeBehavior and the attack-approach filters need supported class/vtable
contracts. Previous banks for the larger shared vector, string, allocator,
tree, and systimer failures were read; no new evidence reopened them. Foreign
claims were respected. This is a handoff of reviewed priorities, not a claim
that every repository blocker is exhausted.

## Final verification

After restoring all trials, `./build.sh` on vector_class_vector3_ctor,
stlport_narrow_filebuf_underflow, stlport_map_int_pod16_subscript,
Object_Object_topple and Rva00893030RefDispatch passed **12/12 rows** across five
sources. `tools/check_csv.py` passed (97,933 function rows, 15,935 symbols,
1,381 data rows). `tools/progress.py origin/master` reported zero delta in
matched, authored C++, census linking, and linked bytes. No source edit remains.
