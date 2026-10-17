extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00031010@Rva00031010@@QAEXPAURva00031010Node@@_N@Z @0x00031010 66B evidence EA GeneralAllocator large-bin insert beside GetLargeBinIndex plus caller 0x000333ED plus head at +0x440 plus bin at +0x30
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
void Rva00031010::rva00031010(Rva00031010Node *node, bool flag)
{
    Rva00031010Node *old = m_head;
    m_head = node;
    node->m_linkC = node;
    node = *(Rva00031010Node * volatile *)&m_head;
    Rva00031010Node *bin;
    {
        Rva00031010Node *next = *(Rva00031010Node * volatile *)&node->m_linkC;
        bin = (Rva00031010Node *)((char *)this + 0x30);
        node->m_link8 = next;
        if (old == bin)
            return;
    }
    if (!flag)
        return;
    Rva00031010Node *after = bin->m_linkC;
    old->m_link8 = bin;
    old->m_linkC = after;
    bin->m_linkC = old;
    after->m_link8 = old;
}

// Add-core (PPMalloc AddCore-like) under the counted +0x4E4 lock. With a
// supplied core of at least 0x40 bytes: rounds the size down to the +0x4D4
// page size and to 16, fills the core descriptor (first chunk at core+0x27
// aligned to 8, sizes +4/+8, flag bytes +0x0C..+0x0F, release callback and
// context +0x10/+0x14), links it after the sentinel at this+0x448 (next
// +0x18, prev +0x1C), clears the committed size when VirtualQuery reports
// the core MEM_RESERVE and no callback is given, writes the first chunk with
// the double fencepost at its end and makes it the top chunk through the
// 0x00031010 insert above. Without a core it allocates page-rounded core
// through 0x00032B00 and installs it as the top chunk inline. Callers:
// 0x00033700 forwards all six arguments. Field labels are descriptive.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
struct Rva000332D0MemoryInfo
{
	void *m_baseAddress;
	void *m_allocationBase;
	unsigned long m_allocationProtect;
	unsigned int m_regionSize;
	unsigned long m_state;
	unsigned long m_protect;
	unsigned long m_type;
};
extern "C" __declspec(dllimport) unsigned int __stdcall VirtualQuery(const void *address, Rva000332D0MemoryInfo *info, unsigned int length);

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	bool rva000332D0(void *core, unsigned int size, bool freeCore, bool trimCore, void *releaseFunction, void *releaseContext);
	void *rva00032B00(unsigned int size);

private:
	struct CoreBlock
	{
		Rva00031010Node *m_firstChunk;
		unsigned int m_size;
		unsigned int m_committedSize;
		bool m_flag0C;
		bool m_freeCore;
		bool m_freeCore2;
		bool m_trimCore;
		void *m_releaseFunction;
		void *m_releaseContext;
		CoreBlock *m_next;
		CoreBlock *m_prev;
	};
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	unsigned char m_pad000[0x30];
	Rva00031010Node m_bin;					// +0x30
	unsigned char m_pad040[0x440 - 0x40];
	Rva00031010Node *m_top;					// +0x440
	unsigned char m_pad444[4];
	CoreBlock m_cores;					// +0x448
	unsigned char m_pad468[0x4D4 - 0x468];
	unsigned int m_pageSize;				// +0x4D4
	unsigned char m_pad4D8[0x4E4 - 0x4D8];
	Lock *m_4E4;						// +0x4E4
};

static inline void rva000332D0AddDoubleFencepost(unsigned int *chunk, unsigned int flags)
{
	unsigned int size = chunk[1];
	unsigned int fencepostOffset = ((size & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
	chunk[1] = (size & 0x80000007) | fencepostOffset;
	unsigned int *fencepost = (unsigned int *)((char *)chunk + fencepostOffset);
	*(unsigned int *)((char *)chunk + fencepostOffset) = fencepostOffset;
	fencepost[1] = flags | 8;
	fencepost[2] = 8;
	fencepost[3] = 9;
}

bool GeneralAllocator::rva000332D0(void *core, unsigned int size, bool freeCore, bool trimCore, void *releaseFunction, void *releaseContext)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	if (core)
	{
		if (size >= 0x40)
		{
			if (size % m_pageSize)
				size &= ~(m_pageSize - 1);
			if (size & 0xF)
				size = size / 16 * 16;
			CoreBlock *block = (CoreBlock *)core;
			block->m_freeCore = freeCore;
			block->m_freeCore2 = freeCore;
			block->m_firstChunk = (Rva00031010Node *)(((unsigned int)core + 0x27) & ~7);
			block->m_size = size;
			block->m_committedSize = size;
			block->m_flag0C = false;
			block->m_trimCore = trimCore;
			block->m_releaseFunction = releaseFunction;
			block->m_releaseContext = releaseContext;
			CoreBlock *head = &m_cores;
			block->m_prev = head;
			block->m_next = head->m_next;
			head->m_next = block;
			block->m_next->m_prev = block;
			if (!releaseFunction)
			{
				Rva000332D0MemoryInfo info;
				info.m_baseAddress = block;
				VirtualQuery(block, &info, sizeof(info));
				if (info.m_state == 0x2000)
					block->m_size = 0;
			}
			unsigned int *chunk = (unsigned int *)block->m_firstChunk;
			unsigned int *chunkCopy = chunk;
			unsigned int initSize = ((unsigned int)block - (unsigned int)chunkCopy + size);
			unsigned int initFlags = (1 ? initSize : initSize) | 1;
			chunkCopy[1] = initFlags;
			chunkCopy[0] = 0;
			rva000332D0AddDoubleFencepost(chunkCopy, 0);
			_ReadWriteBarrier();
			((Rva00031010 *)this)->rva00031010((Rva00031010Node *)chunk, m_top != &m_bin);
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return true;
		}
	}
	else if (size > 0)
	{
		Rva00031010Node *top = (Rva00031010Node *)rva00032B00((size + m_pageSize - 1) & ~(m_pageSize - 1));
		if (top)
		{
			((Rva00031010 *)this)->rva00031010(top, true);
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

}
}
