# Geometry owning-record lifecycle reconciliation

Input master d0247c24e4; verified BFME1 pointer0bf534ea unchanged.
This first independent commit retracts only the96-byte vector copy row at
9292B whose element identity was inferred from an incompatible private view.
The existing old call-candidate pin remains temporarily: unchanged parent
GeometryInfo at929E8 still actually calls9292B, so its native call binding is
preserved. No new pin or compatibility alias is introduced. The retraction is
not to be published without the subsequent verified actual typed admission.

## Identity and native operation

Native GeometryInfo copy929E8 copies its +2C vector via9292B, which calls
const range-copy64289, which calls construction63C8F and copy63BE4.
The existing BfmeStringRecord00063BE4 owner is a36-byte owning record: seven
scalar words, AsciiString at1C, two retained tail bytes20/21. GeometryShape
assignment63627 independently uses precisely those fields. The original
application type is not newly named: BfmeStringRecord remains the honest
structural view. Native teardown chain50A79 ->50A60 ->255D17 ->releaseBuffer
at36410 establishes its owning lifecycle and stride24.

Existing160C70 view instead copies a plain pointer without addref and zeros
three tail bytes. Existing5EA922/5EA9A9/5EA9BB family addrefs a field20 and is
related to the PlayerData family. Neither is globally renamed in this repair;
the old mutable range-helper source is retained independently. No placement
construction through an unrelated type is used in the coherent candidate.

## Private full-file evidence before production admission

Three complete translation-unit candidates are preserved as cpp.txt.
Original compiler VS2003, source flags and the canonical AsciiString/header
contracts are retained. The existing native count-base allocator expression
requires bfmealloc and removal of the obsolete private proxy::allocate
specialization declaration; the actual allocator is already owned at5DFB2C.

GeometryInfo's original EHsc assumes C functions such as free cannot throw,
removing the native4-byte unwind-state reset from the generated vector dtor.
Using the actual existing50A79 provider's EHsc- contract restores that reset;
GeometryInfo173 and the independent mutable38 helper stay unchanged. This
records the native C-callee exception assumption, not invented throwing code.

proposed-graph-proof.json is an explicit in-memory proposed typed map, with no
ledger or pin writes. Every proposed helper maps to a whole native body
independently emitted by the complete candidates:96vector,60count-base,
7allocator getter,38const range-copy,173GeometryInfo,old38mutable helper,
63vector destructor,8record destructor and25range destruction. All match
strictly without masks/unresolved calls under that reviewed hypothetical map;
all3EH-bearing parents are EXACT. This is diagnostic evidence, not landing
verification or a link-census gain. Ordinary supported admission and whole-file
byte/EH/data/import gates remain required for the subsequent production change.

The actual8-byte record destructor uses canonicalAsciiString destruction.
A genuine typed range-destruction instantiation emits its inlineCOMDAT/noinline
body, matching the existing provider's emission pattern; no fake anchor or
wrapper. All3existing tail dtors have identical raw COFF bytes and relocation
names before/after this canonical header view and pass the ordinary3/3 byte
gate with zero string/float/import findings. No baseline/tool/hatch reseed.

## Production admission and current verification

The separate retirement commit is followed by normal add_match admissions:
actual96-byte record-vector copy at9292B, and complete existing-body folds
at21983A/7,10E5A2/60,255D17/8,50A60/25,50A79/63 and7FAB3/14.
Every admission runs its ordinary whole-source byte gate; no no-verify option,
new pin, source alias, assembly, baseline change or gate modification.
The old96-byte call-candidate pin is now removed. All other existing private
GeometryShape family rows and pins remain outside this identity correction.

The additional14-byte base cleanup is independently read from the external
REL32 operands in both exact EH graphs:760003 and75D6F2 reach7FAB3, whose
full body frees the first pointer through30830. This closes the actual
exception cleanup as well as the nine bodies in the initial diagnostic proof.

Only the actual vector-copy member is explicitly instantiated. The unrelated
Rva002AF6C5 erase/copy bodies were already rehomed to their correct existing
GeometryInfoRva002B0E55.cpp owner; their obsolete unowned instantiation is
removed here. No owning body is dropped. Native record default-insertion and
assignment families are not invented to support a whole-class instantiation.

Final ordinary verification covers all7 current consumer/provider TUs:
114/114 matched bodies,37 EH-bearing rows EXACT, one empty-string reference
verified, no unverified/skipped literals, floats or named imports. The3existing
tail destructors retain identical raw COFF bytes and relocation names.

Joint current-object published-index preview:7/7 LINKS,3532 ->3839 unique
linked bytes (+307). The actual copy unit changes0 ->96 and GeometryInfo copy
unit0 ->211; tail23 and four other providers remain linked. The two one-byte
GeometryRecord helper-copy diagnostics are explicitly unreferenced and do not
block selection under the existing retail-truth rules. This is a prediction,
not a new census or a link-cycle run.

Freshly fetched origin/master progress comparison: C++exact7984346 and
Totalexact7997261, both +0. Unique coverage is preserved across retirement and
readmission; the gain is that existing matched code can link. Census-derived
LINKED/LINKING remains unchanged until a maintainer's normal census. Final
normal commit and publication hooks remain required.
