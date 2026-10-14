// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// EA GeneralAllocator (retail 0x00032DF0, 194 bytes): allocate a fresh 4 KB-rounded VirtualAlloc
// mapping for a large request, align the 8-byte header to 8, link the end node into the mapped list.
// Target facts: size rounding 0x101E/0xFFFFF000, flags 0x3000 (or 0x103000 top-down), the 8-byte
// misalignment pad, node constants 0x13 and the list layout come from the retail bytes.
// Closing lever (0x32DF0 nd1, SIB base/index of the pad add): pad is declared at function scope WITH an
// initializer, which gives it the earlier definition and flips the base/index order of the lea.
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	void *rva00032DF0(unsigned int size);

private:
	struct SmallNode
	{
		unsigned int m_base;
		unsigned int m_size;
		SmallNode *m_prev;
		SmallNode *m_next;
	};

	unsigned char m_pad0[0x488];
	unsigned int m_mapCount;
	unsigned int m_mapBytes;
	unsigned char m_pad490[0x498 - 0x490];
	unsigned char m_topDown;
	unsigned char m_pad499[0x49C - 0x499];
	SmallNode m_mapList;
};

void *GeneralAllocator::rva00032DF0(unsigned int size)
{
	unsigned int pad = 0;
	unsigned int total = (size + 0x101E) & 0xFFFFF000;
	if (total >= size)
	{
		unsigned long type = 0x3000;
		if (m_topDown)
			type = 0x103000;
		void *memory = VirtualAlloc(0, total, type, 4);
		if (memory != 0)
		{
			++m_mapCount;
			m_mapBytes += total;
			total -= 0x10;
			unsigned int *header;
			unsigned int misalign = (unsigned int)memory & 7;
			if (misalign != 0)
			{
				pad = 8 - misalign;
				header = (unsigned int *)((char *)memory + pad);
				total -= pad;
				header[0] = pad;
				header[1] = (total - pad) | 2;
			}
			else
			{
				header = (unsigned int *)memory;
				header[0] = 0;
				header[1] = total | 2;
			}
			SmallNode *node = (SmallNode *)((char *)header + total);
			node->m_base = total;
			node->m_size = 0x13;
			SmallNode *head = m_mapList.m_next;
			SmallNode *list = &m_mapList;
			node->m_prev = list;
			node->m_next = head;
			list->m_next = node;
			head->m_prev = node;
			return header + 2;
		}
	}
	return 0;
}

}
}
