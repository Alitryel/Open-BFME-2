// cl: /GX-
// ?Rva000308E0AddHeap@@YAXII@Z @ 0x000308E0 16B
// Guarded AddHeap forwarder: if the init flag at 0x00DE0821 is set, tail-jumps
// to the resolved MemoryPool _AddHeap pointer at 0x00DE03E8 with the same
// (id, size) args, else returns. Evidence: callers at 0x0022542E 0x0022543E
// 0x00225449 0x00225454 push (id, size), 0x00030730 stores _AddHeap at
// 0x00DE03E8, flag 0x00DE0821 set only while _Init runs, sibling guard thunks
// at 0x00030890 0x000308B0. Honest address-derived name. No STL.
// Forwarder global g_Va00DE03E8 (0x00DE03E8) is a SEPARATE slot filled by
// Rva00030730Init and stays untouched. The shared partial HeapTable view retains
// +0x40D and the same extern binding to memory_pool.cpp's single g_heaps.
#include "System/GameMemoryGuardView.h"
// Heap-add hook (data_ledger RVA 0x9E03E8, null .data, unowned); defined
// here, nothing else defines it.
void (__cdecl *g_Va00DE03E8)(unsigned int id, unsigned int size) = 0;

void Rva000308E0AddHeap(unsigned int id, unsigned int size)
{
	if (MemoryPool::g_heaps.m_addingHeaps != 0)
		g_Va00DE03E8(id, size);
}
