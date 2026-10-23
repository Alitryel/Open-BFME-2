# Defector base destructor ownership repair

At BFME 2 4edbba02ca, DefectorSpecialPower.cpp emits a wrong 53-byte
Zero Hour SpecialPowerModuleData destructor (digest b22ca044c4fa), plus
five-byte ModuleData and BehaviorModuleData destructor thunks. The matched
BFME 2 owner is SpecialPowerModuleDataDtor.cpp, RVA 0x0049334F, 115 bytes.
The Defector derived destructor already tail-jumps to that decorated name.

Use the declaration-only SpecialPowerModuleData header shim already present
at the verified BFME 1 pointer a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed donor commit a962c730ccf2d30205d3e5863955a5263331bb41 and the shim's
complete difference from the Zero Hour header: it adds only the virtual
out-of-line destructor declaration and provenance comments. The donor's
addresses describe BFME 1. BFME 2's ownership, extent and call relationship
come independently from its existing matched rows and verified relocations.
No donor layout is promoted to a new BFME 2 layout claim.

Only Defector's compiler include path changes. The actual strict receipt
confirms that the layout resolver selected
reference/open-bfme-1/inputs/reference/shims/specialpowermoduledata/GameLogic/Module/SpecialPowerModule.h.
No shared header, ledger, pin, alias, data name or baseline changes.
The frozen index contains no other emitter of this wrong destructor copy.

## Verification

The measurement is ac77c85054, 2026-10-15 14:25; proof.json records the
immutable index SHA256. proof.py pairs four strictly current objects against
that same index, refreshing only those objects in memory. It does not write
the index, census status or history. The original source/object/receipt and
index metadata are retained under ignored build/defector-base-dtor-link-20261015/before.

- Strict preparation and ordinary byte/ref gates pass all nine rows across
  Defector, the canonical destructor owner, CashHack and Taint. Defector's
  four rows are unchanged. No baselined string, float or import refs.
- Every retained COMDAT body and relocation is identical. A normalized
  whole-object comparison verifies every retained nondebug section: exactly
  the three destructor bodies, their two EH companion sections, and that
  destructor's SafeSEH entry disappear. No retained code/data changes.
- Defector loses five findings (14 -> 9): two unresolved destructor names,
  the base destructor duplicate, its losing COMDAT, and its wrong-selected
  finding. The owner loses its duplicate and wrong-selected findings.
- CashHack (69 bytes) and Taint (63 bytes) each lose their sole wrong-selected
  finding and become clean in the paired local legacy preview. Predicted
  legacy LINKED: 0 -> 132 existing bytes. Authored C++ growth: zero.
- All four sources have strict receipts (self-strict witnesses). Closure
  remains unmeasured: no closed-strict, executable placement or runtime gain
  is claimed. The owner still has a wrong Snapshot deleting destructor.
- Data enforcement has zero findings; converged-data enforcement checks eight
  addresses with zero second names or unjudged rows. Frozen definitions,
  class gate and new-variants admission pass. Placement resweep: zero bodies
  and zero pins. CSV and whitespace checks pass.
- EH verification: CashHack and Taint EXACT; canonical owner retains its
  existing baselined one-byte .text$x difference at RVA 0x0078CD53. No missing
  objects or new EH debt. This unchanged owner object is used on both sides.

The prescribed local link_check reports 2/4 clean, 0 -> 132 bytes, and exits
1 because Defector and its canonical provider retain unrelated blockers.
All remaining findings are enumerated in proof.json. Defector still needs
Object::defect, constructor/parser ownership, Object::isDisabled and
SpecialPowerModule::pauseCountdown reconciliation. These are separate tasks.

The overdue BFME 1 pointer/layout freshness update is held by another
worker's file:reference/open-bfme-1 claim. This change preserves the verified
pointer and asserts no successful freshness stamp. No maintainer-only link
cycle, census build/measurement, nightly, boot or scheduler runner was used.

Model: gpt-6.1-sol.
