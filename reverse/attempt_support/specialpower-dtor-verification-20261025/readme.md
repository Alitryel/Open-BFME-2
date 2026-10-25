# Verify the landed special-power destructor interface repair

Inspected BFME2 revision: 777d0ff0aa. Verified BFME1 checkout and committed
pointer: 0bf534ea7ccde110c456edb9cd2dd5dae823c953. Upstream repair
bcac7d81eb makes the SpecialPowerModule destructor public in the existing
BFME2 layout header and selects that header for CashHackSpecialPower.
DefectorSpecialPower already selects it. This resolves the previous protected
signature without a second name, wrapper, pin or alternate-name directive.
This verification changes no source, header, compiler setting or ledger row.

The native 184-byte destructor at 0x00493DEF already owns
`??1SpecialPowerModule@@UAE@XZ`. Current objects for both callers reference
that public signature and contain no reference to the obsolete protected
`??1SpecialPowerModule@@MAE@XZ`. The existing target constructor/destructor
relationship supplies the provider binding; the header's pool declarations
come from the ZH reference. Access reconciliation does not establish retail's
original C++ access specifier, nor reconcile the remaining private layouts.

Normal verification passes all 14 rows across CashHackSpecialPower.cpp,
DefectorSpecialPower.cpp, SpecialPowerModuleDtor_Unresolved.cpp and
SpecialPowerModuleDtor.cpp. Bounded prepare-current passes all four units
with strict reusable receipts (8 caller rows and 6 provider rows). All four
strict source/object/dependency receipts are current; their hashes and selected
module headers are recorded in current-receipts.json. The full EH check passes
both graphs EXACT, without baseline or missing object.

The published index has provider facts updated to 51fde01dff at 2026-10-25
13:53 UTC and retains the 09:42 census at d2636bb381. The ordinary four-unit
preview replaces all four units' facts in memory with their current compiled
objects. It predicts CashHack's 356 bytes and Defector's 66 bytes link cleanly.
The companion SpecialPowerModuleDtor.cpp retains its 284 linked bytes.
These 706 bytes already count in this index; this verification adds zero
predicted bytes, zero C++ coverage and no new headline measurement.

The actual 184-byte provider's own unit, SpecialPowerModuleDtor_Unresolved.cpp,
still fails the preview on three first-copy COMDAT conflicts:

- `??_7BehaviorModule@@6BBehaviorModuleInterface@@@`
- `??_7BehaviorModule@@6BObjectModule@@@`
- `??_7SpecialPowerModule@@6B@`

The index gives those tables no retail address, so it compares against the
first copy in link order. This is a remaining class/vtable reconciliation
prerequisite, not an unresolved destructor or a proven false reject. Reconcile
the supported native declarations and complete vtable data/providers before
claiming closure of the destructor family. No conflicting table was suppressed
or aliased. The cleared scope is the two callers' destructor binding and
ordinary per-unit preview; broader family clearance, closed-strict closure,
actual executable placement and later census confirmation are unclaimed.

No link cycle, census, nightly, boot/smoke or shadow publisher was started.
