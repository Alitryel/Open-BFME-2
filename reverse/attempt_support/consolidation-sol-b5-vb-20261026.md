# dx8vertexbuffer declaration prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2. The allocated runner queue authorized
`Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp`. No merge was applied.
Leave the now-compatible whole donors for the consolidation seat.

## Target facts and change

`dx8vertexbuffer_engine_ref.cpp` already matches Add_Engine_Ref at RVA
0x00139480 and Release_Engine_Ref at 0x00139490, each 5 bytes. Both const
members update the mutable counter at +0x10. `VertexBufferLockClasses.cpp`
already places its engine_refs at +0x10, but omitted these method declarations
and the mutable qualifier. Add the two nonvirtual declarations and qualify
that existing member. No field, offset, virtual slot, body, flag, name, pin,
global, path or protected-register key changes.

The scoped planner packet was reviewed under Code/Libraries/Source/:
original-path assertion evidence names dx8vertexbuffer.cpp; alternative
DynamicVBAccessClass placement and donor hints alone do not approve moves.
Current in-memory TU routing and normal merge checks supplied approval for
this trial. The planner's stale-map/mixed-donor warnings remain relevant to
other rows; no regenerated reverse/tu_map.csv was committed.

## Demonstrated acceptance change

Before and after:

    python3 tools/tu_skeleton.py --plan Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp
    python3 tools/tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp --dry-run

Before: 7 verified rows from VertexBufferLockClasses.cpp,
DynamicVBAccessClassDeinit.cpp and BoxDynamicVBAccessClassDestructor.cpp.
The engine-ref donor was rejected with C2504: VertexBufferClass base class
undefined. Union composition had moved the combined class behind its derived
classes; earlier strategies lacked the const method declarations.
After: all four whole donors accepted, 9 verified rows, no rejected donors.
Two additional existing rows (10 retail bytes) are now compatible. This is a
prerequisite result, not a confirmed downstream merge or linking gain.

## Verification and binding evidence

Before and after, ./build.sh on VertexBufferLockClasses.cpp and
 dx8vertexbuffer_engine_ref.cpp: 6/6 rows exact, zero string/float/import
failures. find_declared_unmatched.py on both: all definitions matched.
class_gate.py: passed. No canonical-class copy was added.

Ignored scratch build/sol-b5-vb-proof.py uses allowed_symbols.load/scan,
_object_defs, Obj, link_census._comdat_selections and data_check.object_facts.
Its before/after receipts compare all 13 external code definitions (11 lock
object, 2 engine-ref object), code digests/extents, selection and section
flags, undefined symbols, data facts and all 13 relocation bindings:
9 owner, 3 EH, 1 alias. All are identical. No shared inline provider or
consumer binding changed in the authored prerequisite. The actual merge must
repeat the composition and batch link audit; this receipt does not approve
future changes to provider selection.

allowed_symbols.py --source both: 13 references, zero wrong bindings.
data_check.py both: zero findings; --converged: ten addresses, no second names
or unjudged rows. eh_verify.py both: EXACT 3, zero missing objects or debt.
ms_header_audit.py scan both: zero local Microsoft declarations/conflicts or
failures. No code-identity, data, header or MS-header debt keys for either
changed/compared source; no retirement claimed. The future merge still
proposes transferring two data baseline keys and nine data-ledger rows from
other donors; those remain untouched here.

## Publication audit and remaining work

Reviewed pending own commits 8fdd04e212, 988d839dc0 plus this staged change.
`git diff --name-status --find-renames origin/master..HEAD` also displays
incoming upstream changes because origin advanced; these are not local
edits. No outgoing source paths move or disappear, no include/build input,
active tool/hook/workflow, registry or fold-proof consumer changes. Historical
EA path strings are retained. All local source edits preserve object and
binding facts; protected registers and ledgers are untouched.

Mixed bfmedynamicvertexbuffer.cpp and the two Common getter donors remain
outside the accepted whole-donor set. They require the supported split lane
and routing/identity review; cross-family Common work belongs to its owner.
Do not treat these remaining rows as accepted or change their names here.
The BFME 1 freshness limitation recorded in the AptInput handoff remains:
upstream tip verified, checkout unchanged, full-update verification pending.
File reduction 0; debt retired 0; recovered C++ bytes 0.

Keep this destination, two compared donor and handoff file claims until this
commit is published. The publisher queues small batches; the runner publishes
remaining commits at session end. Then release file claims and settle landed
RVA claims with claims.py release --landed. No RVA claim was created by this
prerequisite trial, and no maintainer-only runner was invoked.
