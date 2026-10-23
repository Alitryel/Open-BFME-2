# Link repair, 2026-10-23

Inputs: BFME2 0fa5a5b477; verified BFME1 pointer f890413e75e6.
Published index: 0fa62a2841, 2026-10-22 23:07 UTC.

## Narrow money reader: +2,831 B legacy linked

The narrow money-string reader emits the first copies of iterator dereference
and preincrement. Its opaque streambuf and visible noinline cache fill preserve
retail caller shape but make those outlined copies differ from retail's native
55/45-byte owners. Marking both visible definitions dllimport forceinline
retains the same inline operations and emits neither competing outline.
Dereference uses the vendor `_M_getc(); return _M_c;`; preincrement retains the
existing `sbumpc(); _M_have_c=false; return *this;` specialization.
No import references remain in the matched bodies.

Same-index explicit current-object preview before: money-string reader 0/2584 B,
iterator owner 0/247 B. After: both LINKS, 2831 B total. The third affected unit,
stlport_money_get.cpp, still has independent mismatch/string-do_get copies.
Its remaining findings are not hidden or credited as a repair.

Acceptance: reader 17/17 full byte gate; prepare-current on reader and native
iterator provider 22/22 with strict reusable receipts; new-variants passes.
Strings, floats and imports checks pass. This is self-strict source acceptance
and a legacy preview gain, not closed-strict, census, full-link or runtime proof.
No symbol, baseline, ledger ownership, allocator behavior or compiler flags change.

## BfmeE16 destructor sweep: restored, +0 B

Nine files were claimed, tested and restored; claims released. Retail's pinned
vector destructor at 0x52D1CD belongs to Rva0056616BCopy.cpp and calls a
nontrivial element range cleanup. Its generic BfmeE16 identity cannot be assumed
to represent every private element view. A TU-local imported forceinline
specialization retaining vendor `_Destroy(start,finish)` was tested:

- AIUnitBuilderRva00598D7A: 28/28 bytes pass, but an EH reference to the imported
  vector destructor remains unresolved. Declaration only changes the 399-byte
  decideWhichTemplateToMake body; adding throw() changes it and a cleanup.
- Rva00082EF5Ctor: the 96-byte base destructor and its cleanup lose the native
  inline free shape. Restored after that independent test.
- MissileLauncherBuildingUpdateDtor, W3DFloorDrawModuleDataDtor,
  AODHordeContainDtor, CritterEmitterUpdateModuleDataDtor,
  PartTheHeavensUpdateModuleDataDtor, WeaponDtor and Rva002AC340Dtor:
  no-throw-spec variant fails 8/28 rows; throw() variant fails 16/28.
  Parent destructor/cleanup visibility is load-bearing.

Diagnostic source pattern (after BfmeE16.h; throw() was the second variant):

```cpp
namespace _STL {
template <> __declspec(dllimport) __forceinline vector<BfmeE16>::~vector()
{ _STLP_STD::_Destroy(this->_M_start, this->_M_finish); }
}
```

Do not repeat these visibility-only trials. Further work needs target-supported
real element identity or class/outline ownership reconciliation. No nonmatching
candidate remains in Code, and no partial bank is claimed.

## Read-only checks and limits

Current previews already link the three string consumers PeerThreadStats,
Pinger_getPing, XferSave farm (808 B), StandingWaterArea, SelectionXlat,
Apt quick-match, LineGroup, BuddyThread and both particle writers; inherited
improvements are not credited. ArmySummaryEntry still needs its native adjustor
and class ABI reconciliation; the existing blocker was not retried. The structure
creep tactic needs a cross-unit table/constructor contract; SkirmishPreferences
needs its table and selected AsciiString provider reconciled.

name_globals dry-run: zero edits. Rehome discovery's old 0x4F6318 lead is already
blocked because its proposed home does not link. No matching data-back artifact
was used. Existing reference freshness evidence is less than 24 hours old;
reviewed BFME1 linking fixes are already inherited or require independent layout
work. The donor checkout and success stamp were not advanced.

## Generic money-get follow-up: restored

After the iterator repair, stlport_money_get.cpp retains wrong mismatch and
string do_get copies. Declaring those two separate providers and explicitly
instantiating the retained __get_string helper passes 6/8 rows, but loses the
pair constructor at 0x16CB20 and neg_format at 0x19690. More seriously, the
existing harvested mismatch<char-iterator,char*> pin is 0x12CA0, owned by the
wide iterator/const-ushort mismatch row. The native helper identity/provider
needs independent reconciliation; opaque declarations alone would hide this
pre-existing pin ambiguity. No new pin, type cast, row move or weak alias was
introduced. Restored the whole source and released its eight RVAs/file claim.

## Box visibility partition: +4,054 B legacy linked

The ordinary box renderer's only unresolved dependencies were Render_Triangles
and Set_Model_Transform in three present-unmatched visibility methods. Mesh
already owns the same visibility path and both unresolved callees. Moved those
three unchanged donor methods into mesh.cpp, keeping the existing markers.
The box geometry tables retain one definition in boxrobj.cpp and are declared
extern C at the visibility callers, retaining the data ledger's __BoxFaces and
__BoxVerts identities. No matched row moves or dependency stubs.

Same-index explicit current-object pair before: box 0/4054 B, mesh 0/1268 B.
After: box LINKS 4054 B; mesh remains 0/1268 with the same five blockers.
Ring and sphere share the visibility call but have several independent rendering
and class blockers; the same move alone cannot free their units.

Acceptance: both sources pass 56/56 full byte gate and prepare-current with
strict reusable receipts; new-variants and declared-unmatched checks pass.
This is self-strict source acceptance and +4054 B legacy preview, not a
closed-strict/census/full-link/runtime gain. The outstanding mesh visibility,
shadow-rendering and string-provider dependencies remain explicit. The shadow
hatch counter reports the same three markers moving between files; total markers
do not grow. A compiler-renumbered local guard ($S10 in render_box) remains a
shadow data-name finding; its verified body and storage address are unchanged.
