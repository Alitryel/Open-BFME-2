# SimpleScene secondary-provider reconciliation, 2026-10-18

Reviewed BFME1 donor 64d369b90170 and current target-owned scene providers.
The target constructor installs the complete 28-slot SimpleScene table:
RefCountClass::Delete_This in slot 0, deleting destructor in slot 1, then
Add_Render_Object and Remove_Render_Object. The old destruction shard models
only four slots and aliases its placeholder slot to the deleting destructor.
The attached patch reconciles those declarations and the no-argument
Create_Iterator signature with the existing native provider. It also makes
the scene destructor inline so the existing weak and strong copies agree.
No patch is applied to production sources.

The three-source byte gate passed 28/29 rows. The remaining native unwind
cleanup only lacked the SceneClass destructor binding; there was no measured
instruction mismatch. Both current objects emit the same seven-byte
SceneClass destructor: restore RefCountClass's vtable and return, with the
same DIR32 relocation at offset 2. Retail's existing seven-byte owner at
RVA 0x00724510 is CullableClass::~CullableClass; older trivial-destructor
pins already share this address. No new pin was written.

Pin admission rejected the complete-body fold proof because only three bytes
are outside relocations. The minimum-concrete-byte test exempts a five-byte
jump, but not this seven-byte vtable-restore body. This is recorded as a
false-reject candidate in re_attempts.log, not bypassed. A tooling seat must
reproduce and establish an appropriately narrow admission rule with a
regression test before this repair can proceed.

Evidence: reconciliation.patch, gate.txt and pin-admission.txt. The current
legacy baseline is scene.cpp clean (527 B), constructor blocked (1,074 B),
destructor blocked (290 B). This attempt establishes no new linked bytes,
no authored bytes and no closed-strict gain. All three source files were
restored and all file/RVA claims released.
