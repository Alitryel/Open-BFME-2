// ?rva000332D0@GeneralAllocator@Allocator@EA@@QAE_NHHHHHH@Z
// partial score=0.6424 date=2026-10-14
// Shared GeneralAllocator view: sibling member offsets from the banked
// siblings 0x00032B00/0x00031E60/0x000334A0 (bin +0x30, head +0x440,
// core-list sentinel +0x448, granularity +0x4DC, lock +0x4E4).
#include <string.h>
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);
extern "C" __declspec(dllimport) unsigned long __stdcall VirtualQuery(const void *address, void *information, unsigned long informationSize);
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
extern "C" __declspec(dllimport) unsigned long __stdcall VirtualQuery(const void *address, void *information, unsigned long informationSize);

struct Rva00031010Node
{
	unsigned char m_pad[8];
	Rva00031010Node *m_link8;
	Rva00031010Node *m_linkC;
};
class Rva00031010
{
public:
	void rva00031010(Rva00031010Node *node, bool flag);
private:
	unsigned char m_pad0[0x30];
	Rva00031010Node m_bin;
	unsigned char m_pad1[0x440 - 0x30 - sizeof(Rva00031010Node)];
	Rva00031010Node *m_head;
};

namespace EA { namespace Allocator {
// ?rva000332D0@GeneralAllocator@Allocator@EA@@QAE_NHHHHHH@Z present-unmatched
// The caller at 0x00033700 forwards six integer arguments. Target bytes
// establish this allocator through its lock at +0x4E4, use count at +0x18,
// descriptor list at +0x448, and bin links at +0x30/+0x440. The labels below
// describe target stores; they do not claim donor field names.
bool GeneralAllocator::rva000332D0(int coreInfo, int coreSize, int blockType,
	int blockFlags, int context, int arg6)
{
	GeneralAllocator *const allocator = this;
	Lock *lock = allocator->m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	if (coreInfo != 0)
	{
		unsigned char *const record = reinterpret_cast<unsigned char *>(coreInfo);
		unsigned int size = static_cast<unsigned int>(coreSize);
		if (size < 0x40)
		{
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return false;
		}

		unsigned int granularity = *reinterpret_cast<unsigned int *>(
		reinterpret_cast<char *>(allocator) + 0x4D4);
		if (size % granularity != 0)
			size &= ~(granularity - 1);
		if ((size & 0xF) != 0)
			size = (size >> 4) << 4;

		record[0xD] = static_cast<unsigned char>(blockType);
		record[0xE] = static_cast<unsigned char>(blockType);
		unsigned char *const data = reinterpret_cast<unsigned char *>(
			(reinterpret_cast<unsigned int>(record) + 0x27) & ~7);
		*reinterpret_cast<int *>(record + 0x14) = arg6;
		*reinterpret_cast<unsigned char **>(record) = data;

		unsigned char *const descriptorHead = reinterpret_cast<unsigned char *>(allocator) + 0x448;
		unsigned char *const oldFirst = *reinterpret_cast<unsigned char **>(descriptorHead + 0x18);
		*reinterpret_cast<unsigned char **>(record + 0x1C) = descriptorHead;
		*reinterpret_cast<unsigned int *>(record + 4) = size;
		*reinterpret_cast<unsigned int *>(record + 8) = size;
		record[0xC] = 0;
		record[0xF] = static_cast<unsigned char>(blockFlags);
		*reinterpret_cast<int *>(record + 0x10) = context;
		*reinterpret_cast<unsigned char **>(record + 0x18) = oldFirst;
		*reinterpret_cast<unsigned char **>(descriptorHead + 0x18) = record;
		*reinterpret_cast<unsigned char **>(oldFirst + 0x1C) = record;

		if (context == 0)
		{
			unsigned char information[0x1C];
			*reinterpret_cast<void **>(information) = record;
			VirtualQuery(record, information, 0x1C);
			if (*reinterpret_cast<unsigned int *>(information + 0x10) == 0x2000)
				*reinterpret_cast<unsigned int *>(record + 4) = 0;
		}

		unsigned int *const header = reinterpret_cast<unsigned int *>(data);
		unsigned int fenceSize = size - (reinterpret_cast<unsigned int>(data) -
			reinterpret_cast<unsigned int>(record));
		unsigned int taggedSize = fenceSize | 1;
		unsigned int fencepostOffset = (taggedSize & 0x7FFFFFF8) - 9;
		fencepostOffset &= 0xFFFFFFF8;
		header[0] = 0;
		header[1] = (taggedSize & 0x80000007) | fencepostOffset;
		unsigned int *const fencepost = reinterpret_cast<unsigned int *>(data + fencepostOffset);
		fencepost[0] = fencepostOffset;
		fencepost[1] = 8;
		fencepost[2] = 8;
		fencepost[3] = 9;

		Rva00031010Node *const oldBinHead = *reinterpret_cast<Rva00031010Node **>(
		reinterpret_cast<char *>(allocator) + 0x440);
		Rva00031010Node *const binSentinel = reinterpret_cast<Rva00031010Node *>(
			reinterpret_cast<char *>(allocator) + 0x30);
		reinterpret_cast<Rva00031010 *>(allocator)->rva00031010(
			reinterpret_cast<Rva00031010Node *>(data), oldBinHead != binSentinel);

		if (lock != 0)
		{
			--lock->m_count;
			LeaveCriticalSection(lock);
		}
		return true;
	}

	if (static_cast<unsigned int>(coreSize) != 0)
	{
		unsigned int granularity = *reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(allocator) + 0x4D4);
		unsigned int roundedSize = (granularity + static_cast<unsigned int>(coreSize) - 1) & ~(granularity - 1);
		void *const block = allocator->rva00032B00(roundedSize);
		if (block != 0)
		{
			Rva00031010Node *const oldHead = *reinterpret_cast<Rva00031010Node **>(
				reinterpret_cast<char *>(allocator) + 0x440);
			*reinterpret_cast<void **>(reinterpret_cast<char *>(allocator) + 0x440) = block;
			*reinterpret_cast<void **>(reinterpret_cast<char *>(block) + 0xC) = block;
			Rva00031010Node *const newHead = *reinterpret_cast<Rva00031010Node **>(
				reinterpret_cast<char *>(allocator) + 0x440);
			newHead->m_link8 = newHead->m_linkC;
			Rva00031010Node *const binSentinel = reinterpret_cast<Rva00031010Node *>(
				reinterpret_cast<char *>(allocator) + 0x30);
			if (oldHead != binSentinel)
			{
				Rva00031010Node *const oldLast = binSentinel->m_linkC;
				oldHead->m_link8 = binSentinel;
				oldHead->m_linkC = oldLast;
				binSentinel->m_linkC = oldHead;
				oldLast->m_link8 = oldHead;
			}
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return true;
		}
	}

	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return false;
}


} }
