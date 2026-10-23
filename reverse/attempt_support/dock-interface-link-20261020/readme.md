# DockUpdate interface: +151 B in the legacy link preview

BFME2 base 9bce084b53; frozen published index 5366c4f808, retail-truth-2.
Paired previews refresh both touched provider slots against the same index.
Rva0058A0F4Dtor changes from 0 to 151 linked nonpadding bytes; DockUpdateCtor
retains its 1,245 linked bytes. All 18 function rows remain byte-exact,
including their EH data. Both providers have current self-strict reusable
receipts. No closed-strict, census, link.exe placement or C++ coverage gain is
claimed.

The failing name was ??_7DockUpdate@@6BUpdateModule@@@. The constructor
emitted one relocation to void UpdateModule::update; the destructor emitted
one to the unrelated opaque f2 placeholder. Neither declaration represented
the complete native interface. The native constructor/destructor vptr stores
and data ledger identify secondary table RVA 0x851D68, whose complete 12 bytes
point to 0x589F09, 0x253376 and 0x44DF8D. Existing rowed providers name these
DockUpdate::update, UpdateModule::getDisabledTypesToProcess and
UpdateModule::rva0044DF8D. Their signatures establish the UpdateSleepTime
return, BitFlags<11> return and wake-delay argument respectively.

Both local views now declare those three slots and the appropriate overrides.
No method implementation, ABI layout, hard-coded target or alias is added.
paired.json verifies each table's full 12 bytes after resolving all three
DIR32 relocations to the target rows. It also records before/after source and
object hashes, index hash, blockers and self-strict receipts. The affected
machine-code bodies and their bindings pass the ordinary complete byte gate.

Donor review: verified BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790,
game/GameEngine/Include/GameLogic/Module/UpdateModule.h supplies the familiar
update/getDisabledTypesToProcess interface semantics. The extra wake slot,
its position, types, target addresses and BFME2 offsets come independently
from the target's existing rowed UpdateModuleSetWakeFrame.cpp and native table.
No donor body or layout was transferred.

Sweep: this exact DockUpdate table name has only these two indexed emitters.
Other losing UpdateModule tables belong to PhysicsBehavior (many separate
blockers), BridgeBehavior (previously recorded inheritance prerequisite),
BattlePlanUpdate and BezierProjectileBehavior (separate unrowed interface
slot00 targets). They require their own class contracts, so are not changed
merely to equalize sparse tables. name_globals --dry-run proposes no edits in
this cohort. Frozen-source checks, check_csv, byte/string/float/import gates
and strict preparation pass. No shared header or verifier change and no
maintainer-only runner is involved.
