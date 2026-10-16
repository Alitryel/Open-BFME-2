// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "../../../../GameEngine/Source/Common/RegionIconSlotResizeView.h"
// Native005EFDE9..005EFE52 RET8; existing byte-verified value-fill ABI.
void _STL::vector<Rva005EFDE9Element,_STL::allocator<Rva005EFDE9Element> >::resize(size_type newSize,Rva005EFDE9Element value) {
 if(newSize<(_M_finish-_M_start)) erase(_M_start+newSize,_M_finish);
 else {
  Rva005EFDE9Element *finish=_M_finish;
  const size_type count=newSize-(_M_finish-_M_start);
  _M_fill_insert(finish,count,value);
 }
}
// Native005EFE6E..005EFE87 RET4; invoked by icon slot-count005EFE87.
void _STL::vector<Rva005EFDE9Element,_STL::allocator<Rva005EFDE9Element> >::resize(size_type n) { resize(n,Rva005EFDE9Element()); }

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005EFC30 reads ?_M_fill_insert@?$vector@URva005EFD53Element@@V?$allocator@URva005EFD53Element@@@_STL@@@_STL@@QAEXPAURva005EFD53Element@@IABU3@@Z
#pragma comment(linker, "/alternatename:?_M_fill_insert@?$vector@URva005EFDE9Element@@V?$allocator@URva005EFDE9Element@@@_STL@@@_STL@@QAEXPAURva005EFDE9Element@@IABU3@@Z=?_M_fill_insert@?$vector@URva005EFD53Element@@V?$allocator@URva005EFD53Element@@@_STL@@@_STL@@QAEXPAURva005EFD53Element@@IABU3@@Z")
//   0x005EF8FA reads ?erase@?$vector@URva005EF8FAElement@@V?$allocator@URva005EF8FAElement@@@_STL@@@_STL@@QAEPAURva005EF8FAElement@@PAU3@0@Z
#pragma comment(linker, "/alternatename:?erase@?$vector@URva005EFDE9Element@@V?$allocator@URva005EFDE9Element@@@_STL@@@_STL@@QAEPAURva005EFDE9Element@@PAU3@0@Z=?erase@?$vector@URva005EF8FAElement@@V?$allocator@URva005EF8FAElement@@@_STL@@@_STL@@QAEPAURva005EF8FAElement@@PAU3@0@Z")
