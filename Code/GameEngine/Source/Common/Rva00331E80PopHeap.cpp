// cl: /Ireference/shims/bfme2_ascii /MD /Oy-
#include "ascii_string.h"
// ?Rva00331E80PopHeap@@YAXPAUS4SortElem12@@0HUS4Cmp002E1690@@@Z @0x00331E80 45B
// S4 pop_heap wrapper via rowed Bfme copy and rowed PopHeap.
// Evidence: unlock lane unblocks 0x003320B0; callees rowed; caller pushes 4 args.
struct S4SortElem12
{
	int m_a;
	AsciiString m_name;
	char m_flag;
	// LINK: declaration-only copy ctor (no body in this TU). The by-value
	// argument below E8-calls it; with no local body the call binds the kept
	// (first-in-order) copy instead of this TU's loser copy, and the call
	// bytes are unchanged (same reloc name). No flags touched.
	S4SortElem12(const S4SortElem12 &other);
};

struct S4Cmp002E1690
{
	void *m_state;
};

namespace _STL
{
template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator result, Tp value, Compare comp, Distance *);
}
// Rowed at 0x00331DAE in Rva002E0BC0PopHeap12_Rva00331dae.cpp.

void __cdecl Rva00331E80PopHeap(S4SortElem12 *first, S4SortElem12 *last, int unused, S4Cmp002E1690 comp)
{
	_STL::__pop_heap(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}
