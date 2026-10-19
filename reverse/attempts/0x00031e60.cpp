// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.9601328903654485 date=2026-10-19
// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.194 date=2026-10-17
// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.179 date=2026-10-15
// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.565 date=2026-10-15
// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.5455 date=2026-10-14
// Shared GeneralAllocator view: sibling member offsets from the banked
// siblings 0x00032B00/0x00031E60/0x000334A0 (bin +0x30, head +0x440,
// core-list sentinel +0x448, granularity +0x4DC, lock +0x4E4).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
	int rva00031D00(void *block);
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
// Retail 0x31E60..0x31F8D is 301 bytes; the saved size drives its checks.
// Remaining difference: zero/one fencepost blocks at +0xB9..+0xC4 are reversed.
int GeneralAllocator::rva00031E60(const void *block)
{
 Lock *lock = m_4E4;
 if (lock != 0)
 {
  EnterCriticalSection(lock);
  ++lock->m_count;
 }
 unsigned int size = (*(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8);
 unsigned int blockEnd = (unsigned int)block + size;
 int score = rva00031D00((void *)block);
 unsigned int header = *(const unsigned int *)((const char *)block + 4);
 score += (*(const unsigned char *)((header & 0x7FFFFFF8) + (unsigned int)block + 4) & 1) && 1;
 score += ((unsigned char)(header >> 1) & 1) && 1;
 if (size >= 0x10)
 {
  score += (((unsigned char)size & 7) != 0) && 1;
  score += (((unsigned char)(unsigned int)block & 7) != 0) && 1;
  score += (*(const unsigned int *)blockEnd != size) && 1;
  score += ((unsigned char)~*(const unsigned char *)((const char *)block + 4) & 1) && 1;
  score += (block != m_head440 && (*(const unsigned char *)((*(const unsigned int *)(blockEnd + 4) & 0x7FFFFFF8) + blockEnd + 4) & 1) == 0) && 1;
  const unsigned int *next = *(const unsigned int **)((const char *)block + 8);
  const unsigned int *after = *(const unsigned int **)((const char *)block + 0xC);
  score += (after[2] != (unsigned int)block) && 1;
  score += (next[3] != (unsigned int)block) && 1;
  if (block == after || block == next)
  {
   score += (next != after) && 1;
   score += (block != m_head440) && 1;
  }
 }
 else
  score += (size > 4) && 1;
 if (lock != 0)
 {
  --lock->m_count;
  LeaveCriticalSection(lock);
 }
 return score;
}
