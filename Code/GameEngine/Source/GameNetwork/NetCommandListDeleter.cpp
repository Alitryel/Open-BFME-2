// ??_GNetCommandList@@MAEPAXI@Z
// NetCommandList scalar-deleting destructor, retail 0x0058B50F, 34 bytes.
// cl: /DNDEBUG /MD /EHsc /O1
//
// NetCommandList scalar-deleting destructor, retail 0x0058B50F, 34 bytes.
// BFME1 NetCommandList_destructor.cpp recipe (EA GPL-3.0-or-later): a defined
// virtual dtor calling reset() emits the vtable, and ??_G rides along with
// it (no delete anchor needed); the dtor itself stays marked
// present-unmatched, never claimed. Retail reinstalls vtable RVA 0x00870A08
// (DIR32 auto-patch), calls matched reset 0x0058B283, then frees through the
// global one-arg operator delete (matched ??3 row, no member delete declared).
#include "NetCommandListView.h"
// ??1NetCommandList@@MAE@XZ present-unmatched (emission only, unclaimed)
NetCommandList::~NetCommandList()
{
	reset();
}
