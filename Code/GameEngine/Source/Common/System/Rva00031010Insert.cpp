extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00031010@Rva00031010@@QAEXPAURva00031010Node@@_N@Z @0x00031010 66B evidence EA GeneralAllocator large-bin insert beside GetLargeBinIndex plus caller 0x000333ED plus head at +0x440 plus bin at +0x30
struct Rva00031010Node
{
    unsigned int m_priorSize;
    unsigned int m_size;
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

extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);

namespace EA
{
namespace Allocator
{
static inline void rva00032B00AddDoubleFencepost(void *, unsigned int);
// A chunk location carries the start and full raw extent into initialization.
// Keeping that value boundary retains the native copy before the flags OR.
struct Rva00032B00ChunkLocation
{
	unsigned int extent;
	unsigned int *chunk;
	Rva00032B00ChunkLocation(unsigned int n, unsigned int *p) : extent(n), chunk(p) {}
};
static __forceinline void rva00032B00InitializeChunk(Rva00032B00ChunkLocation info, unsigned int flags)
{
	info.chunk[1] = info.extent | flags;
	rva00032B00AddDoubleFencepost(info.chunk, 0);
}
class GeneralAllocator
{
public:
	Rva00031010Node *rva000334A0(unsigned int size);
	bool rva000332D0(void *core, unsigned int size, bool freeCore, bool trimCore, void *releaseFunction, void *releaseContext);
	void *rva00032B00(unsigned int size);

private:
	typedef Rva00031010Node Chunk;
	void SetTopChunk(Chunk *chunk, bool linkOld)
	{
		Chunk *old = m_top;
		m_top = chunk;
		chunk->m_linkC = chunk;
		m_top->m_link8 = m_top->m_linkC;
		if (old == &m_bin)
			return;
		if (!linkOld)
			return;
		Chunk *bin = &m_bin;
		Chunk *after = bin->m_linkC;
		old->m_link8 = bin;
		old->m_linkC = after;
		bin->m_linkC = old;
		after->m_link8 = old;
	}
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
	unsigned char m_pad468[0x498 - 0x468];
	bool m_topDown;
	unsigned char m_pad499[0x4AC - 0x499];
	int m_noNewCores;
	unsigned char m_pad4B0[0x4D4 - 0x4B0];
	unsigned int m_pageSize;				// +0x4D4
	unsigned int m_minCoreSize;
	unsigned int m_granularity;
	unsigned char m_pad4E0[4];
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

// Native 335C6..335DB stores both 8-byte markers before the final 9.
// Ordering these three real writes preserves that sequence without changing
// the surrounding core/header stores. This does not identify retail's types.
static inline void rva000334A0AddDoubleFencepost(unsigned int *chunk, unsigned int flags)
{
	unsigned int size = chunk[1];
	unsigned int fencepostOffset = ((size & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
	chunk[1] = (size & 0x80000007) | fencepostOffset;
	unsigned int *fencepost = (unsigned int *)((char *)chunk + fencepostOffset);
	*(unsigned int *)((char *)chunk + fencepostOffset) = fencepostOffset;
	((volatile unsigned int *)fencepost)[1] = flags | 8;
	((volatile unsigned int *)fencepost)[2] = 8;
	((volatile unsigned int *)fencepost)[3] = 9;
}
// Native 334A0..336FC, reached by the allocator growth path at 34244.
// Offsets and operations follow retail; the chunk/core field roles are views.
Rva00031010Node *GeneralAllocator::rva000334A0(unsigned int size)
{
	bool newTop = false;
	Chunk *chunk = 0;
	unsigned int extend = 0;
	unsigned int chunkSize;
	CoreBlock *core = m_cores.m_next;
	for (; core != &m_cores; core = core->m_next)
	{
		if (size <= core->m_committedSize - core->m_size)
		{
			extend = size;
			if (extend < m_granularity)
				extend = m_granularity;
			if (extend > core->m_committedSize - core->m_size)
				extend = core->m_committedSize - core->m_size;
			if (!VirtualAlloc((char *)core + core->m_size, extend, 0x1000, 4))
				core->m_committedSize = core->m_size;
			break;
		}
	}
	if (core != &m_cores)
	{
		if (core->m_size)
		{
			Chunk *fencepost = (Chunk *)((char *)core + core->m_size - 0x10);
			if (fencepost->m_size & 1) {
				chunk = fencepost;
				chunkSize = extend;
				fencepost->m_size = extend | 1;
			} else {
				chunk = (Chunk *)((char *)fencepost - fencepost->m_priorSize);
				chunk->m_link8->m_linkC = chunk->m_linkC;
				chunk->m_linkC->m_link8 = chunk->m_link8;
				chunkSize = fencepost->m_priorSize + extend;
				chunk->m_size = chunkSize | 1;
				newTop = chunk == m_top;
			}
			Chunk *end = (Chunk *)((char *)chunk + chunkSize);
			end->m_priorSize = chunkSize;
			end->m_size = 8;
			end = (Chunk *)((char *)end + 8);
			end->m_priorSize = 8;
			end->m_size = 9;
		}
		else
		{
			Chunk *first = (Chunk *)(((unsigned int)core + 0x27) & ~7);
			core->m_firstChunk = first;
			unsigned int *chunkCopy = (unsigned int *)first;
			unsigned int initSize = ((unsigned int)core - (unsigned int)chunkCopy + extend);
			chunkCopy[1] = initSize | 1;
			chunkCopy[0] = 0;
			rva000334A0AddDoubleFencepost(chunkCopy, 0);
			chunk = first;
			chunkSize = extend;
			SetTopChunk(chunk, true);
			newTop = true;
		}
		core->m_size += extend;
	}
	if (!chunk)
	{
		if (!m_noNewCores)
		{
			chunk = (Chunk *)rva00032B00(size);
			if (chunk)
			{
				Chunk *old = m_top;
				m_top = chunk;
				chunk->m_linkC = chunk;
				Chunk *node = m_top;
				node->m_link8 = node->m_linkC;
				Chunk *bin = &m_bin;
				if (old != bin)
				{
					Chunk *after = bin->m_linkC;
					old->m_link8 = bin;
					old->m_linkC = after;
					bin->m_linkC = old;
					after->m_link8 = old;
				}
				newTop = true;
				chunkSize = chunk->m_size & 0x7FFFFFF8;
			}
		}
	}
	if (chunk && chunkSize > size)
	{
		chunk->m_size = size | 1;
		Chunk *rest = (Chunk *)((char *)chunk + size);
		unsigned int remainder = chunkSize - size;
		rest->m_size = remainder;
		rest->m_priorSize = size;
		*(unsigned int *)((char *)rest + remainder) = remainder;
		if (newTop)
			SetTopChunk(rest, false);
		else
		{
			Chunk *bin = &m_bin;
			Chunk *after = bin->m_linkC;
			rest->m_link8 = bin;
			rest->m_linkC = after;
			bin->m_linkC = rest;
			after->m_link8 = rest;
		}
	}
	return (Rva00031010Node *)chunk;
}

}
}

namespace EA
{
namespace Allocator
{
// Native writes the offset and both 8-byte markers in this order. These
// ordered accesses preserve it without adding reads or writes; the qualifiers
// and local value type do not identify retail's original declarations.
static inline void rva00032B00AddDoubleFencepost(void *chunk, unsigned int flags)
{
	unsigned int *const header = static_cast<unsigned int *>(chunk);
	unsigned int size = header[1];
	unsigned int fencepostOffset = (size & 0x7FFFFFF8) - 9;
	fencepostOffset &= 0xFFFFFFF8;
	header[1] = (size & 0x80000007) | fencepostOffset;
	unsigned int *const fencepost = reinterpret_cast<unsigned int *>(
		reinterpret_cast<char *>(chunk) + fencepostOffset);
	((volatile unsigned int *)fencepost)[0] = fencepostOffset;
	((volatile unsigned int *)fencepost)[1] = flags | 8;
	((volatile unsigned int *)fencepost)[2] = 8;
	fencepost[3] = 9;
}

static inline unsigned int rva00032B00Align(unsigned int size, unsigned int alignment)
{
	return (size + alignment - 1) & ~(alignment - 1);
}

// Native 00032B00..00032C57 RET4; called by the matched core registration
// and growth paths. VirtualAlloc and the descriptor/list/chunk accesses
// establish this allocation path; field labels remain descriptive views.
void *GeneralAllocator::rva00032B00(unsigned int size)
{
	unsigned int coreSize = rva00032B00Align(size, m_pageSize);
	unsigned int chunkFlags = 1;
	if (coreSize < m_minCoreSize)
		coreSize = rva00032B00Align(m_minCoreSize, m_pageSize);
	unsigned int reservedSize = (coreSize + 0xFFFF) & 0xFFFF0000;
	CoreBlock *core = (CoreBlock *)VirtualAlloc(0, reservedSize, 0x2000, 4);
	if (core)
	{
		coreSize = 0x100000;
		if (m_granularity > coreSize)
			coreSize = rva00032B00Align(m_granularity, m_pageSize);
		if (coreSize > reservedSize)
			coreSize = reservedSize;
		core = (CoreBlock *)VirtualAlloc(core, coreSize, 0x1000, 4);
	}
	if (!core)
	{
		unsigned long type = 0x3000;
		if (m_topDown)
			type = 0x103000;
		core = (CoreBlock *)VirtualAlloc(0, coreSize, type, 4);
		if (core)
		{
			chunkFlags = 3;
			reservedSize = coreSize;
		}
	}
	if (core)
	{
		core->m_committedSize = coreSize;
		core->m_size = coreSize;
		core->m_firstChunk = (Rva00031010Node *)(((unsigned int)core + 0x27) & ~7);
		core->m_flag0C = (chunkFlags >> 1) & 1;
		CoreBlock *head = &m_cores;
		bool notFirst = m_cores.m_prev != head;
		// Retail writes +1C before the +0D/+0F/+0E flag group.
		*(CoreBlock *volatile *)&core->m_prev = head;
		*(volatile bool *)&core->m_freeCore = notFirst;
		*(volatile bool *)&core->m_trimCore = notFirst;
		*(volatile bool *)&core->m_freeCore2 = true;
		core->m_releaseFunction = 0;
		core->m_releaseContext = 0;
		core->m_next = head->m_next;
		head->m_next = core;
		core->m_next->m_prev = core;
		core->m_committedSize = reservedSize;
		unsigned int *chunk = (unsigned int *)core->m_firstChunk;
		const unsigned int &chunkSize = (unsigned int)core - (unsigned int)chunk + coreSize;
		chunk[0] = 0;
		// Preserve the descriptor/list and previous-size writes before the
		// size/flags and fencepost writes performed by the initializer.
		_ReadWriteBarrier();
		Rva00032B00ChunkLocation info(chunkSize, chunk);
		rva00032B00InitializeChunk(info, chunkFlags);
		return chunk;
	}
	return 0;
}


}
}
