// ?rva00032F60@GeneralAllocator@Allocator@EA@@QAEPBUBlockInfo@23@PAXH@Z
// partial score=0.3662 date=2026-10-14
// Shared GeneralAllocator view: sibling member offsets from the banked
// siblings 0x00032B00/0x00031E60/0x000334A0 (bin +0x30, head +0x440,
// core-list sentinel +0x448, granularity +0x4DC, lock +0x4E4).
#include <string.h>
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);
extern "C" __declspec(dllimport) int __stdcall VirtualQuery(const void *address, void *information, unsigned long informationSize);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
namespace EA {
namespace Allocator {
struct BlockInfo
{
	unsigned int m_blockType; // +0x00
	unsigned char m_pad[0x10];
};
struct Snapshot
{
	unsigned int m_magic;      // +0x00
	unsigned char m_pad04[0x10 - 4];
	unsigned int m_state[3];   // +0x10
	unsigned int m_arg2;       // +0x1C
	unsigned int m_values[5];  // +0x20
};
struct ListNode
{
	unsigned int m_unk0; // +0x00
	unsigned int m_size; // +0x04
	unsigned int m_size8; // +0x08 committed limit
	unsigned int m_padC;
	unsigned int m_pad10;
	void *m_releaseContext;
	ListNode *m_next; // +0x18
	ListNode *m_prev; // +0x1C
};
struct FreeChunk
{
	unsigned int m_prevSize; // +0x00
	unsigned int m_size; // +0x04
	FreeChunk *m_next; // +0x08
	FreeChunk *m_prev; // +0x0C
};
struct Lock
{
	unsigned char m_pad[0x18];
	volatile int m_count;
};
class GeneralAllocator
{
public:
	void *rva00032B00(unsigned int size);
	void *rva000334A0(volatile unsigned int size);
	bool rva000332D0(int coreInfo, int coreSize, int blockType, int blockFlags, int context, int arg6);
	const BlockInfo *rva00032F60(void *context, int blockTypes);
	void rva00032EC0(const void *block, BlockInfo *info);
	int rva00031E60(const void *block);
	int probe31D00(const void *block);
	unsigned char m_pad0[0x30];
	FreeChunk m_bin30; // +0x30 (free-bin sentinel)
	unsigned char m_pad40[0x440 - 0x40];
	FreeChunk *m_head440; // +0x440
	unsigned char m_pad444[0x448 - 0x444];
	ListNode m_sentinel; // +0x448 (core list)
	unsigned char m_pad468[0x4D4 - 0x468];
	unsigned int m_4D4; // +0x4D4
	unsigned char m_pad4D8[0x4DC - 0x4D8];
	unsigned int m_granularity4DC; // +0x4DC
	unsigned char m_pad4E0[0x4E4 - 0x4E0];
	Lock *m_4E4; // +0x4E4
};
}}
typedef EA::Allocator::GeneralAllocator GeneralAllocator;
typedef EA::Allocator::ListNode ListNode;
typedef EA::Allocator::FreeChunk FreeChunk;
typedef EA::Allocator::Lock Lock;
typedef EA::Allocator::BlockInfo BlockInfo;
typedef EA::Allocator::Snapshot Snapshot;
const BlockInfo *GeneralAllocator::rva00032F60(void *context, int blockTypes)
{
	Snapshot *report = (Snapshot *)context;
	if (report == 0 || report->m_magic != 0x534E4150)
		return 0;
	register unsigned int mask = (unsigned int)blockTypes;
	if (report->m_state[2] != 0)
	{
		mask &= (unsigned int)report->m_arg2;
		ListNode *node = (ListNode *)report->m_values[0];
		while (node != (ListNode *)((char *)this + 0x448))
		{
		unsigned int end = (unsigned int)node + node->m_size - 0x10;
		unsigned int block = report->m_values[1];
		if (block == 0)
			block = node->m_unk0;
		else
			block += *(unsigned int *)(block + 4) & 0x7FFFFFF8;
		report->m_values[1] = block;
		while (block != end)
		{
			unsigned int header = *(unsigned int *)(block + 4);
			if ((blockTypes & 0x10) != 0 || (header & 4) == 0)
			{
				unsigned int size = header & 0x7FFFFFF8;
				unsigned char allocated = (unsigned char)(*(unsigned char *)(block + size + 4) & 1);
				if ((header & 0x80000000) != 0)
					allocated = 0;
				if ((blockTypes & 6) == 6 || ((blockTypes & 2) != 0 && allocated != 0) ||
					((blockTypes & 4) != 0 && allocated == 0))
				{
					BlockInfo *info = (BlockInfo *)((char *)context + 0x24);
					rva00032EC0((const void *)block, info);
					return info;
				}
			}
			block += *(unsigned int *)(block + 4) & 0x7FFFFFF8;
			report->m_values[1] = block;
		}

		if (node->m_size == 0)
			break;
		node = node->m_next;
		report->m_values[0] = (unsigned int)node;
		if (node == (ListNode *)((char *)this + 0x448))
		{
			report->m_values[1] = 0;
			break;
		}
		report->m_values[1] = 0;
	}

		if ((blockTypes & 2) != 0)
	{
		unsigned int external = report->m_values[2];
		if (external != (unsigned int)((char *)this + 0x49C))
		{
			BlockInfo *info = (BlockInfo *)((char *)context + 0x24);
			rva00032EC0((const void *)(external - *(unsigned int *)external), info);
			report->m_values[2] = *(unsigned int *)(external + 0x0C);
			return info;
		}
	}
	}
	while (report->m_values[4] < report->m_values[3])
	{
		BlockInfo *entry = (BlockInfo *)((char *)context + 0x24 + report->m_values[4] * 0x14);
		if ((mask & entry->m_blockType) != 0)
		{
			++report->m_values[4];
			return entry;
		}
		++report->m_values[4];
	}
	return 0;
}

