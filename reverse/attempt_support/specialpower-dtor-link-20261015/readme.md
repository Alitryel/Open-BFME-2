SpecialPowerModuleData destructor ownership repair, 2026-10-15

Base: 4b0a28415848876b6025f30393a49b16abc043bd. Both provider files were
claimed before editing; only DefectorSpecialPower.cpp changes. No new authored
C++ bytes, ledger rows, pins, aliases, shared headers or verifier changes.

The frozen census index (ac77c85054, 2026-10-15 14:25; exact SHA256 in
index-meta.json) selects DefectorSpecialPower.cpp's 53-byte implicit Zero Hour
SpecialPowerModuleData destructor ahead of the existing BFME2 owner. Its target
is already established independently: SpecialPowerModuleDataDtor.cpp owns the
115-byte native body at 0x0049334F, from native constructor/member accesses and
27 derived destructor callers. This repair does not claim that Zero Hour's
class layout is BFME2's layout.

Reuse the existing BFME1 specialpowermoduledata include view, which adds only
an out-of-line virtual destructor declaration to the original Zero Hour header.
The include path is first in this TU's flags. The strict dependency receipt
proves that exact header was read. No donor layout, address or body is imported.
The native owner remains unchanged. The explicit declaration suppresses the
wrong implicit destructor and its now-unreferenced BehaviorModuleData and
ModuleData destructor copies (53, 5 and 5 bytes), plus only their associative EH.
Retained virtual callers continue to use the same external destructor name.

Full object proof: every retained nondebug section, its complete bytes, extent,
flags, external definitions and symbolic relocations are unchanged. SafeSEH
metadata loses only the removed destructor's handler. All 624 retained external
COMDATs in the edited object and all unchanged owner COMDATs keep their bytes
and relocation digests. Undefined AudioEventRTS and nonvirtual Snapshot
destructor names disappear with the wrong body; the native SpecialPowerModuleData
destructor becomes the sole new undefined reference. No import call is added.
Exact retained counts and all hashes are in object-proof.json.

Paired local link preview: both sides replace the same 21 explicitly prepared,
strict-current cohort objects against the same frozen index. Only the edited
object differs. The five core findings removed are two unresolved references,
one duplicate, one COMDAT loser and one wrong-selected finding. The native owner
loses its duplicate and wrong-selected finding. Nineteen further consumers lose
the wrong-selected destructor finding. No new or changed unrelated finding is
allowed by proof.py. Legacy predicted clean units rise 0 -> 14 and nonpadding
linked bytes 0 -> 1,008. These are existing matched bytes, not new authored code.
Individual object currency is self-strict; executable placement and closed-strict
provider closure are unmeasured. No fresh census or actual link.exe gain is claimed.

Acceptance: bounded prepare-current passes 39/39 rows across 21 providers;
before/after core prepares and ordinary ./build.sh pass 5/5. String/float/import
checks pass (cohort: one empty reference, no baselines/skips). Enforced touched
source data check has zero findings; converged-data checks eight addresses with
zero second names or unjudged rows. Class, frozen-definition, new-variant,
check_csv and whitespace checks pass. Affected-unit placement resweep finds
zero bodies and zero pins. The owner has one unchanged existing baselined EH
.text$x mismatch (one byte at 0x0078CD53), verified before and after; it is not
reported as exact or repaired. The local link CLI exits 1 because seven units
retain independent blockers, while confirming 14/21 clean and +1,008 legacy bytes.

Remaining: Defector has Object::defect unresolved, competing DefectorModuleData
constructor/parser definitions, isDisabled COMDAT and selected parser/countdown
providers. The native destructor owner's unrelated Snapshot scalar-deleting
destructor remains wrong. Devastate and Scavenger data constructors retain wrong scalar-deleting
destructor COMDATs (Devastate and WeaponChange, respectively). The OCL data
constructor retains vector<OCLUpgradePair>::erase COMDAT/selection findings;
the ElvenWood data destructor lacks RvaPair004C3D4C::~RvaPair004C3D4C; the family
deleting-destructor consumer retains OpenContainModuleData selection. Full lists are in object-proof.json
and link-after.txt. None of these unchanged bodies was retried.

Donor review: clean BFME1 checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d.
Reviewed inputs/reference/shims/specialpowermoduledata/GameLogic/Module/
SpecialPowerModule.h against the original header: only comments and the
virtual destructor declaration differ. It is applicable as a declaration-only
repair, while its BFME1 address comment is inapplicable to BFME2. Also reviewed
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 for the unused-emission repair strategy.
Official upstream fetch reached 9f335a9ec9ff012c5103195540fa82ccc3e7877e.
The overdue comparative pointer verification remains under another live
file:reference/open-bfme-1 claim. Neither pointer nor freshness stamp advanced.

Discovery used repair_queue.py link, link_rank.py help/top/near, and the existing
runner index, followed by link_check.py --fetch-index (same measurement; cached
objects fetched). The same-cause index has only this wrong emitter and the
retained native owner. No data-back ranking was inferred from absent artifacts.
Unrelated reverse/zh_sweep preparation is preserved. No full link cycle, census
build/measure/history, nightly, boot or scheduler runner was started.

Reproduction: save strict before objects, source and receipts under the same
basenames in build/specialpower-dtor-link-20261015/before at the base above.
Apply the source change, prepare the 21 explicit cohort.txt sources, and run
proof.py from the repository root. It verifies index identity, strict receipts,
consumed donor header, whole retained objects and paired link findings, without
writing the census. Ignored object/source backups remain in that scratch tree.
