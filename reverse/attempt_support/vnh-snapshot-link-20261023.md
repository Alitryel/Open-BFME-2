# Reconcile the event base cleanup with Snapshot

2026-10-23, gpt-6.1-sol; parent aa3dcf761b. Published census b711de3634,
2026-10-23 14:28, retail-truth-4. BFME1 reviewed at verified 96c88c73:
game/GameEngine/Source/Common/BfmeRectVNH_ctor.cpp defines an empty base
destructor and removes an invented handle slot. That donor repair cannot be
copied directly: BFME2's native cleanup requires the Snapshot table reset.

The prior blocked record identified the precise prerequisite. Native whole
66-byte BfmeRectVNH constructor 0x003FD498 records its unchanged receiver;
its EH cleanup 0x007845EA loads that receiver and jumps to 0x0049B47C.
The complete seven-byte callee writes Snapshot's table 0x00BBB554 and returns.
The existing base constructor at 0x003FD199 independently proves the vptr at
zero, scalar at +4 and byte at +8. The base's native table 0x00BFE008 has
the four Snapshot slots followed by an event callback. Derive the existing
neutral BfmeBaseVNH view from canonical Snapshot and define its empty C++
destructor; the compiler emits the exact required body and table relocation.
add_match admits the ICF alias with Snapshot.cpp as fold-proof. Application
identity and intermediate inheritance remain unknown. No pin is added.

Paired legacy current-object previews against the same index:

- BfmeRectVNH_ctor.cpp: 0 -> 174 existing nonpadding B, LINKS.
- Rva003BBAF0Ctor_Rva003FD199.cpp: 0 -> 0 B; its missing BfmeBaseVNH
  table provider remains a distinct prerequisite.
- Cohort gain: **+174 B linked**, zero new unique retail coverage.

This repairs the exact lifetime binding, not the remaining private virtual
surfaces. The base-constructor table and the derived event table still need
their existing neutral owners reconciled with their complete native slots.
No closed-strict or self-strict closure gain is claimed. Other views that
declare this base destructor now have a real provider; no other indexed unit
is held out solely by that name. The incompatible BFME1 table shape is not
imported. Census/index/status remain unchanged.

Acceptance: all five edited-source rows pass the scoped byte gate;
link_check --prepare-current verifies them with strict reusable receipts;
find_declared_unmatched and --new-variants pass. Normal commit hooks check
the native EH graph. Diagnostics are ignored build/link-seat-vnh-*.log.

The preceding hash-record repair's normal hook also reported a shadow
code-identity finding for its separate _M_insert call binding at 0x002A1D4B.
That repair's +176 B remains explicitly a legacy current-object preview;
it does not establish strict closure or resolve that helper's identity debt.
