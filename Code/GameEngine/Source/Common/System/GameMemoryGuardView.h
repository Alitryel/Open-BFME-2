// Partial HeapTable view used by the guarded allocation helpers. These fields
// retain the offsets already measured in the two consumers and memory_pool.cpp.
// The single g_heaps definition remains in memory_pool.cpp; no storage is owned
// here. This view does not describe the other fields of the heap table.
#ifndef BFME_GAME_MEMORY_GUARD_VIEW_H
#define BFME_GAME_MEMORY_GUARD_VIEW_H

namespace MemoryPool
{
struct HeapTable
{
	unsigned char _pad404[0x404];
	bool m_clearAllocations;
	unsigned char _mid[0x40D - 0x405];
	bool m_addingHeaps;
	unsigned char _tail[0x410 - 0x40E];
};

extern HeapTable g_heaps;
}

#endif
