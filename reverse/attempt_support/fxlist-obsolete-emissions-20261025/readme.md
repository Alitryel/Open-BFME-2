# FX-list obsolete emission cleanup

Inspected master `9edfc2834c`, BFME 1 reference
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`, published index
`ef9c691284` (2026-10-25 18:23 UTC). This repairs two blockers in one
620-byte unit; it does not make that unit link and claims no census gain.

The native parser table already belongs to FXListStoreParse.cpp and the native
per-nugget callbacks to FXListNuggetParse.cpp. The unused Zero Hour reference
table in FXList.cpp nevertheless instantiated obsolete constructors and virtual
tables. Remove its other callbacks, retaining the particle callback temporarily
for the original inline method's compiler shape. Define the existing bone-position
doFXObj out of line so its verified body survives without its obsolete constructor.
The particle reference entry remains compiler-only and unreferenced; it is not
the table the game uses.

Normal byte verification passes all seven existing rows, the owned global data
row and the compiler float. Independent comparison proves every complete owned
body and every relocation unchanged. EH verification reports no EH-bearing owned
row and no missing object. Strict preparation passes; the object's actual MD5
equals its receipt. Enforced data checking has zero findings. Frozen-file and
CSV checks pass. No pin, alias, baseline, hatch or verifier change is applied.

The paired preview holds ledger facts, index and all other provider facts fixed.
The obsolete ThingFactory::newDrawable call and FXListAtBonePosFXNugget table
conflict disappear. Two particle/terrain calls, the particle table and two list
lifetime conflicts remain, with the same two selected-copy findings. Neither
phase links this unit. See paired-preview.json and whole-body-proof.json.

## Identity prerequisite discovered

Do not turn the remaining list operations into declarations and call this fixed:
the diagnostic does preserve all seven bodies, but introduces two unresolved
references. The old list-copy pin targets 000365F0, the native StringBase<char>
copy constructor. The list-base destructor pin targets 00036E70, the native wide
StringBase release operation. These are not list semantics. The 31-byte
FXList copy claim at 0052BD3A installs C61A20 and calls 000365F0 for member +4;
the existing Rva004E156B constructor/destructor own that same one-string table.
The target observations are recorded in native-identity-leads.json. The current
data ledger itself lists the competing FXList/Rva004E156B table names. Their
original application spelling is not established here.

This is a prerequisite for a coherent type/provider/consumer ownership repair,
not a reason to add replacement pins or an alias. Existing FXList vector copies
also depend on the 0052BD3A claim, while the 0060CF5A/0060CFB6 helpers lie in
the approved XferSave range and carry separate string-teardown evidence. Preserve
coverage and verify the dependency family when correcting these claims. This
cleanup leaves all those source bodies, rows and pins unchanged.

## Discarded experiments and debt checker

Removing every reference callback while moving particle doFXObj out of line
preserves six rows but emits 367 bytes instead of 371: float atan2 stops inlining.
Explicit double arguments or one/two forced-inline adapters emit 371 bytes with
different x87/SSE scheduling. /Ot changes other owned bodies; /Ob2 does not fix
the mismatch. A qualified-call retention anchor also fails. None is applied;
the original exact particle body remains. Unchanged fresh controls compiled from
both the real path and a scratch copy reproduce all its 371 bytes and relocations.

The supported identity-retirement command refused to change anything: 66 ledger
objects were absent, 17 referenced provider receipts were stale, and the known
list-copy key was now classified wrong instead of divergent. No register was
edited to hide that result. Global-current closure is not claimed.
