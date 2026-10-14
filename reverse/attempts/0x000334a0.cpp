// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.502 date=2026-10-14
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
struct Snapshot;
struct BlockInfo;
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
struct BlockInfo
{
	unsigned char m_pad[0x40];
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
void *GeneralAllocator::rva000334A0(volatile unsigned int size)
{
	struct Scratch
	{
		char pad[3];
		bool moveHead;
		FreeChunk *oldHead;
		FreeChunk *tail;
	};
	register GeneralAllocator *allocator = this;
	volatile Scratch scratch;
	scratch.moveHead = false;
	register unsigned int commit = 0;
	register ListNode *segment = allocator->m_sentinel.m_next;
	FreeChunk *chunk = 0;
	while (segment != &m_sentinel)
	{
		unsigned int used = segment->m_size;
		unsigned int capacity = segment->m_size8;
		unsigned int available = capacity - used;
		if (size > available)
		{
			segment = segment->m_next;
			continue;
		}

		commit = size;
		unsigned int granularity = *(unsigned int *)((char *)allocator + 0x4DC);
		if (commit < granularity)
			commit = granularity;
		if (commit > available)
			commit = available;
		if (VirtualAlloc((char *)segment + used, commit, 0x1000, 4) == 0)
			segment->m_size8 = used;

		if (used != 0)
		{
			FreeChunk *last = (FreeChunk *)((char *)segment + used - 0x10);
			if ((last->m_size & 1) != 0)
			{
				chunk = last;
				chunk->m_size = commit | 1;
			}
			else
			{
				chunk = (FreeChunk *)((char *)last - last->m_prevSize);
				chunk->m_next->m_prev = chunk->m_prev;
				chunk->m_prev->m_next = chunk->m_next;
				unsigned int total = last->m_prevSize + commit;
				chunk->m_size = total | 1;
				scratch.moveHead = chunk == allocator->m_head440;
				FreeChunk *fence = (FreeChunk *)((char *)chunk + total);
				fence->m_prevSize = total;
				fence->m_size = 8;
				*(unsigned int *)((char *)fence + 8) = 8;
				*(unsigned int *)((char *)fence + 12) = 9;
			}
		}
		else
		{
			unsigned char *data = (unsigned char *)(((unsigned int)segment + 0x27) & 0xFFFFFFF8);
			segment->m_unk0 = (unsigned int)data;
			unsigned int blockSize = (unsigned int)((char *)segment + commit - (char *)data);
			FreeChunk *first = (FreeChunk *)data;
			first->m_prevSize = 0;
			first->m_size = blockSize | 1;
			FreeChunk *fence = (FreeChunk *)(data + (blockSize & 0x7FFFFFF8));
			fence->m_prevSize = blockSize & 0x7FFFFFF8;
			fence->m_size = 8;
			*(unsigned int *)((char *)fence + 8) = 8;
			*(unsigned int *)((char *)fence + 12) = 9;
		}
		segment->m_size = used + commit;
		if (chunk != 0)
			break;
		break;
	}

	if (chunk == 0)
	{
		if (*(void **)((char *)allocator + 0x4AC) != 0)
			return 0;
		chunk = (FreeChunk *)allocator->rva00032B00(size);
		if (chunk == 0)
			return 0;
		scratch.oldHead = allocator->m_head440;
		allocator->m_head440 = chunk;
		chunk->m_prev = chunk;
		chunk->m_next = chunk->m_prev;
		FreeChunk *bin = &allocator->m_bin30;
		if (chunk->m_prev != bin)
		{
			scratch.tail = bin->m_prev;
			scratch.oldHead->m_next = bin;
			scratch.oldHead->m_prev = scratch.tail;
			bin->m_prev = scratch.oldHead;
			scratch.tail->m_next = scratch.oldHead;
		}
		scratch.moveHead = true;
	}

	unsigned int oldSize = chunk->m_size & 0x7FFFFFF8;
	if (oldSize <= size)
		return 0;
	chunk->m_size = size | 1;
	FreeChunk *remainder = (FreeChunk *)((char *)chunk + size);
	unsigned int remainderSize = oldSize - size;
	remainder->m_prevSize = size;
	remainder->m_size = remainderSize;
	*(unsigned int *)((char *)remainder + remainderSize) = remainderSize;
	if (scratch.moveHead)
	{
		allocator->m_head440 = remainder;
		remainder->m_prev = remainder;
		remainder->m_next = remainder->m_prev;
	}
	else
	{
		FreeChunk *bin = &allocator->m_bin30;
		scratch.tail = bin->m_prev;
		remainder->m_next = bin;
		remainder->m_prev = scratch.tail;
		scratch.tail->m_next = remainder;
		bin->m_prev = remainder;
	}
	return chunk;
}

