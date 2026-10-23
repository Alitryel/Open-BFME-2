FontLibrary/Stances parser linking, 2026-10-22

Current FontLibraryInit.cpp (960 authored bytes) had three unresolved names:
StanceData's constructor and DLL imports of the STLport tree decrement and
rebalance helpers. Add the established /D_STLP_USE_STATIC_LIB setting so
helpers bind to the existing static retail providers. Define the existing
StanceData constructor to zero its two words. The native BfmePod52 constructor
at RVA 0x00425E85 passes VA 0x0047E81F, count six and stride eight to the
array-constructor iterator. This independently proves the member initializer
body/ABI. The existing field-parse table and member accesses supply the stance
relationship; the zeroing body alone does not prove the semantic field names.

The constructor's emitted whole ten bytes are 8B C1 83 20 00 83 60 04 00 C3,
with no relocations, exactly the existing PlayingAudioUnknown0C constructor
owner. No separate StanceData address exists in the ledger/pin resolver.
pin_admission.py --add admits the constructor pin using this matched source's
fold-proof, checks every owner's full body/relocations, and writes its scoped
hatch-register grant. Its generated register rewrite also drops stale pin
counts/stamps for symbols.csv; no gate is changed. Pin consistency passes.
The field type and existing real constructor owner are unchanged.

Paired same-index preview: 0 -> 960 authored bytes, legacy link prediction.
All 22 rows (including five EH funclets and their handlers) pass normal byte
and exact EH checks. All named parent bodies retain their before bytes and
relocations; compiler-local EH handler metadata offsets move with emission
and are checked by the normal byte/EH verifier. Eight code literals verify.
Three unrowed tree helpers change when their DLL-import calls become direct
static calls. The source has strict current compiler receipts. No closed-strict
closure or census improvement is claimed. The rank inventory has no other
consumer of this constructor or these two DLL-import names; the same-cause
sweep changes this one unit.

Shadow data check reports the existing const TheStanceNames declaration as a
wrong name against the stale data_ledger's unowned non-const declaration.
The source declaration is unchanged and agrees with the byte-verified real
owner in data_rows.csv (Stances/StanceNames.cpp, RVA 0x0083C210, 28 bytes).
No data alias or new data definition is introduced.

Reference context: existing BFME2 source/layout and static-library settings
from matched STLport siblings, against verified BFME1 pointer 37c3022de1ab.
No donor update or decoder source read. See proof.json for paired blockers,
object/index hashes, constructor bytes and changed helper names.
