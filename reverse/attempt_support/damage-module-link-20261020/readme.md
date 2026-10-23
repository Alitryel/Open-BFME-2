# DamageModule link prerequisite

Inputs: BFME2 0aa1fcff3d; BFME1 68c5ce2789e974f36b6c742d57437d157bc159e9;
published link index 3f413ed3ff (2026-10-20 18:52). Compiler flags remain
those in the source comments.

The TransitionDamageFX constructor's implicit public destructor conflicted
with its verified protected destructor at 0x004BA47C. Declaring the protected
destructor makes the constructor's 71 bytes link in the legacy preview and
removes the destructor unit's primary-vtable conflict. The constructor passes
its byte gate; all three relevant units passed their original nine-row gate.
Strict compiler receipts were prepared; no closed-strict gain is measured.

The remaining selected-wrong definition is DamageModule::~DamageModule,
implicitly emitted by EvacuateDamageCtorModuleFactoryBody.cpp. Declaring that
destructor external removes the competing definition, but fails the row named
public EvacuateDamage::~EvacuateDamage at 0x0002CD7B (53 bytes): its final base
call no longer matches. The trial was reverted completely.

That placement has no valid EvacuateDamage identity. The independently verified
protected destructor is 0x004BAEC8, in EvacuateDamagePoolKey.cpp. Attempt-log
entry for PB_DeepBase at 0x0002CCC3 already identifies its purported base call
as a STLport hashtable destructor. The public placement and its associated EH
and list claims need an explicit identity repair before removing their implicit
DamageModule definition. Do not retry declaration-only suppression unchanged.

After the landed declaration fix, legacy preview of constructor/dtor/Evacuate
factory is 71/0/0 bytes, previously 0/0/0. The 114-byte TransitionDamageFX
destructor unit still selects the wrong DamageModule implementation; the
174-byte Evacuate factory unit additionally has unresolved PB_DeepBase and
interface slots and allocator/list COMDAT conflicts. This is a prerequisite
repair, not a completed base-class reconciliation.
