# WorkOrder class reconciliation, 2026-10-19

Retail table VA00C62E40 contains RVAs004F1D1C,000B3FD0,004F1116,
004F0716. The getter returns WorkOrder; ctor4F10E6 installs this table
and TeamInQueue::xfer allocates48 bytes before calling it. Dtor4F1B56
destroys AsciiString+20 and restores Snapshot's BBB554 base table.
These target facts establish the class identity, extent and base.
The transfer and AI consumers witness the fields; ZH supplies the
member spellings and purpose. BFME2-only fields retain offset names.

The automatic contract chose no base and placeholder v00/v01/v02 by
majority. Its data, data+ctor and data+methods headers each failed0/5:
missing pointer types, constructor and xfer declaration. The reviewed
contract instead records the target-supported Snapshot base and four
real slots. The fixed-header adoption lane then passed4/5; AIPlayer's
queueUnits differed because a rewritten inline predicate used return<.
Restoring its original if>=false/true form passed the fifth consumer.
No game algorithm changed. All five private WorkOrder views are gone.
The constructor's three unrelated /alternatename placeholders are gone.

WorkOrder.h is shared by those five consumers, the destructor and name
getter. Existing destructor/deleting-destructor/getter rows are renamed
to their proven class; the empty post-load slot is a complete1B RET
fold of the existing owner, admitted by add_match --icf-owner. No pin.
Both emitted16-byte tables were inspected: each has the four native
targets, each complete owner body verifies, and the compiler's local
COFF SEARCH_LIBRARY weak vector-dtor reference falls back to the
same-class28-byte scalar destructor (build.proven_weak_dtor_default).
The class is48B by compile-time assertion. All115 rows in seven units
byte-match; all107 literals and three empty-string refs verify. Data
checks report no finding; the destructor's associative EH graph is EXACT.

Six of seven units link, retaining1224 linked bytes. AIPlayerTeamBuild
already had six unresolved, four COMDAT and three wrong-selected
blockers before this change; its exact blocker list is unchanged.
Those concern TeamInQueue, ScriptEngine, BuildListInfo and STLport
list<TeamPrototype*> and are separate work, not a WorkOrder regression.
No runtime or whole-game link success is claimed.

Source inputs: BFME1 6b9d92bf92debd03e4357462bab41f701651e67c.
Existing per-TU compiler flags retained. The ctor retains its witnessed
nonthrowing declaration; no global compiler or verifier changes.
Local receipts: build/resume-oct19-workorder-{all-build,all-link,
vtable-proof,eh} and reviewed-adoption/adoption-shape logs. The original
failed contract and tool trial remain under build/ as diagnostic evidence.
