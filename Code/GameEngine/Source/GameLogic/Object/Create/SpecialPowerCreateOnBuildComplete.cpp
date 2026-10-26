// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Target004B93EF..004B9428: Create-interface callback, gate slot3, clear
// the interface-local flag4, then scan Object244 modules and notify the
// interface returned by each module's C-subobject slot8 through its slot7.
// Twin: matched Object::rva0028AB4E uses the same loop at0028AB4E with
// different measured slots. SpecialPowerCreate identity is carried by the
// established SpecialPowerCreate ctor004B9345 installing secondary table
// 008596A4 at10; its slot1 points004B93EF. CreateModule.h provides the
// callback name; names of the queried interfaces remain
// unresolved. No Object or module layout beyond these accesses is inferred.
#include "SpecialPowerCreateView.h"

void SpecialPowerCreate::onBuildComplete()
{
 if(shouldDoCreate()) {
  flag=false;
  for(SpecialPowerModuleScan **specialPowerModuleScan=object->modules;*specialPowerModuleScan;++specialPowerModuleScan) {
   SpecialPowerBuildResult *specialPowerBuildResult=(*specialPowerModuleScan)->face.s8();
   if(specialPowerBuildResult)specialPowerBuildResult->s7();
  }
 }
}
