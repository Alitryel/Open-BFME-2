Bridge list allocator repair, 2026-10-18

Current provider/consumer preview using index c2c5ac8c27: BridgeBehavior module
data ctor 0 -> 99 linked nonpadding bytes. MapMetaDataCopy stays at 0 due to
independent tree copies; those bytes are not claimed. Strict preparation passes
all three Bridge rows, including the existing list constructor alias and the EH
handler. Native EH graph EXACT. Legacy link gain only; no closed-strict claim.

The target 89B constructor calls the rowed Coord3D sentinel ctor 0x280A8D twice.
MapMetaDataCopy owns its 41B retail body using allocator<char>::allocate(size,0).
The old Bridge copy called imported __node_alloc::allocate(size), introducing an
undefined DLL entry and a differing sentinel COMDAT. Using the existing provider's
static-library/BFME allocator settings changes that helper to the retail ABI
while preserving every owned row and relocation. No new symbol pin or alias.
The list payload is an existing projection; this repair asserts no new type
identity for the OCL/FX lists. All other 12 census emitters of this same sentinel
constructor were already retail; the incompatible Bridge emitter was unique.

Discarded trial: declaration-only sentinel ctor preserved call targets but
changed the second allocator temporary from EBP-0xD to EBP-0xE. Static-library
settings alone fixed the undefined import but retained a 38B helper. The BFME
allocator shim supplies the existing supported two-argument allocator ABI and
restores the 41B helper. No failed reconstruction is retained in Code.

BFME1 review/provenance is recorded in the preceding constructor-view evidence.
The BFME2 rowed provider and retail bytes establish the allocator choice here.
No full link cycle, census rebuild, runtime check or BFME1 pointer update.
