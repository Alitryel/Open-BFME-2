// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBA88 @0x002EBA88 67B. Init with defaults
// (0x80, 0, 0, alloc 0x0002FFC0, free 0x0002FFE0, 0) then the pinned 6-arg
// 0x001FF36A; returns this. The two code addresses are the rowed default
// allocator wrappers (DefaultAllocatorWrappers.cpp). Identity unproven.
void *Rva0002FFC0Alloc(int a1, int a2);
void Rva0002FFE0Free(void *p, int a2);
class Rva001FF36A
{
public:
	bool rva001FF36A(int a1, int a2, int a3, int a4, int a5, int a6);
};
class Rva002EBA88
{
public:
	Rva002EBA88 *rva002EBA88(int nodesPerBlock, int arena, int size, int a4, int a5, int context);
private:
	int m_nodesPerBlock;
	int m_blockList;
	int m_freeList;
	int m_C;
	int m_10;
	int m_context;
};
// ?rva002EBA88@Rva002EBA88@@QAEPAV1@HHHHHH@Z @0x002EBA88 67B.
Rva002EBA88 *Rva002EBA88::rva002EBA88(int nodesPerBlock, int arena, int size, int a4, int a5, int context)
{
	m_nodesPerBlock = 0x80;
	m_blockList = 0;
	m_freeList = 0;
	m_C = (int)&Rva0002FFC0Alloc;
	m_10 = (int)&Rva0002FFE0Free;
	m_context = 0;
	((Rva001FF36A *)this)->rva001FF36A(nodesPerBlock, arena, size, a4, a5, context);
	return this;
}
