# TransitionDamageFX destructor linkage

At b9b81c7b01, the published 08160bc2c9 index selects a non-retail
`DamageModule::~DamageModule` copy. The consumer destructor at 4BA47C
calls retail 4B96CC; its existing whole 25-byte owner is
`Rva004B96CC::~Rva004B96CC` in Rva0049B47CThreeVptrDerived.cpp.
The consumer now declares that row name directly, retaining its existing
three-base layout. No target class rename or new symbol pin is asserted.

Paired current-object `link_check.py` before/after: consumer 0 -> 114 B,
provider 371 -> 371 B; total 371 -> 485 B (+114). These are legacy
previews against the same published index, not closed-strict gains.
`./build.sh` and `link_check.py --prepare-current` pass all four rows,
including the deleting destructor, EH handler and unwind action; no skipped
literals/imports. The latter writes a self-strict reusable source receipt.

The same-name sweep checks all ten DamageModule class views. Other callers
already link except EvacuateDamageCtorModuleFactoryBody.cpp: its 174 B
require PB_DeepBase teardown, an EvacuateDamageInterface slot, and a matching
evacuation-list destructor in addition to its own implicit DamageModule
destructor. No speculative changes to that independent class contract.

The current-source census preview remains unchanged until a maintainer
refreshes the census. No full census or link cycle was run.
