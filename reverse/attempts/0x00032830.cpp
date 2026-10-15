// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBXH@Z
// partial score=0.93 date=2026-10-15
// cl: /O2 /MD /EHsc /DNDEBUG
// Hack-free ValidateAddress-like body (no volatile, no barriers): RAII lock guard, plain
// loops, in-use test sharing the not-found unlock tail. 228/227 B; after register renaming
// the only residue is one allocation choice: retail keeps block in EDX and turns this into
// the sentinel in place (add esi,0x448), ours keeps block in ESI and the sentinel in ECX
// (lea), which also costs the 1-byte cmp byte [esp+0x14],0 (ours mov dl/test dl).
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	bool rva00032830(const void *block, int addressType);

private:
	struct Chunk
	{
		unsigned int prevSize;
		unsigned int head;
	};
	struct ListNode
	{
		Chunk *m_first;
		unsigned int m_size;
		unsigned char m_pad[16];
		ListNode *m_next;
		ListNode *m_prev;
	};
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	struct AutoLock
	{
		Lock *m_lock;
		AutoLock(Lock *lock) : m_lock(lock)
		{
			if (m_lock != 0)
			{
				EnterCriticalSection(m_lock);
				++m_lock->m_count;
			}
		}
		~AutoLock()
		{
			if (m_lock != 0)
			{
				--m_lock->m_count;
				LeaveCriticalSection(m_lock);
			}
		}
	};
	static unsigned int chunkSize(const Chunk *chunk) { return chunk->head & 0x7FFFFFF8; }
	static Chunk *nextChunk(const Chunk *chunk) { return (Chunk *)((char *)chunk + chunkSize(chunk)); }

	unsigned char m_pad0[0x448];
	ListNode m_sentinel;
	unsigned char m_pad468[0x4E4 - (0x448 + sizeof(ListNode))];
	Lock *m_4E4;
};

}
}

bool EA::Allocator::GeneralAllocator::rva00032830(const void *block, int addressType)
{
	AutoLock lock(m_4E4);
	for (ListNode *node = m_sentinel.m_next; node != &m_sentinel; node = node->m_next)
	{
		if ((const char *)block >= (const char *)node && (const char *)block < (const char *)node + node->m_size)
		{
			Chunk *chunk = node->m_first;
			Chunk *next = nextChunk(chunk);
			while ((const char *)next < (const char *)block && next != chunk)
			{
				chunk = next;
				next = nextChunk(next);
			}
			bool result = true;
			if (nextChunk(chunk)->head & result)
			{
				const char *payload = (const char *)chunk + 8;
				if ((char)addressType)
					return block == payload;
				if (block < payload || block >= next)
					result = false;
				return result;
			}
			break;
		}
	}
	return false;
}
