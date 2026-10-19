// ?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z
// partial score=0.995 date=2026-10-19
// cl: /O2 /GR- /EHsc-
// 2026-10-19 (claude-opus-5-5): EXACT 374/374 with no volatile/barrier, but it relies on ONE
// __assume(m_mapBytes >= mappingSize) in the mapped arm as a code-free fence: without it cl
// reassociates m_48C - (prev+size+16) into m_48C + (-16-prev-size) (about 40 plain spellings stay
// at nd 31; `if (total) m_48C -= total;` reproduces the order but adds a test). Kept banked
// because a fence with no source evidence is not landable under the no-hack rule; find a real
// second use of the total (an EA assert/metric) instead. Home: memory_pool.cpp (all 40 rows stay
// exact with this body there: build/nbr/gf/33150/home_memory_pool.cpp). Landing also needs the
// two other names pinned at 0x00033150 in reverse/symbols.csv reconciled.
// ?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z, retail 0x00033150 (374 bytes), RET4.
// PPMalloc free (dlmalloc fREe shape with EA extensions): fast-bin push for
// small chunks; otherwise boundary-tag coalesce with a free predecessor and
// successor, insert into the unsorted list (+0x30) or become the top chunk
// (+0x440), and trim through 0x32C60 once a >= 64 KB chunk ends a core
// (0x31BB0) and reaches the +0x4C8 threshold. Mapped chunks (size bit 2)
// unlink their trailing fence node from the mapped list, drop the mapped
// count/bytes (+0x488/+0x48C, the counters 0x32DF0 raises) and release the
// whole mapping. Method name address-derived; member labels descriptive.
// The __assume in the mapped arm is the release form of an allocator
// assertion (EA_ANALYSIS_ASSUME); it keeps the mapping size a computed value
// ahead of the unlink, as retail's lea/sub shows.
extern "C" __declspec(dllimport) int __stdcall VirtualFree(void *address, unsigned int size, unsigned long type);

namespace EA
{
namespace Allocator
{

struct Rva00031BF0Chunk
{
	unsigned previousSize;
	unsigned size;
	Rva00031BF0Chunk *previous;
	Rva00031BF0Chunk *next;
};

class GeneralAllocator
{
public:
	void rva00033150(const void *block);
	bool rva00031BB0(const void *block);
	unsigned int rva00032C60(unsigned int size);

private:
	unsigned int m_unknown0;
	unsigned int m_maxFastSize;
	Rva00031BF0Chunk *m_fastBins[10];
	Rva00031BF0Chunk *m_bins[256];
	unsigned char m_pad430[0x440 - 0x430];
	Rva00031BF0Chunk *m_topChunk;
	unsigned char m_pad444[0x488 - 0x444];
	unsigned int m_mapCount;
	unsigned int m_mapBytes;
	unsigned char m_pad490[0x4C8 - 0x490];
	unsigned int m_trimThreshold;
	unsigned int m_trimPad;
};

void GeneralAllocator::rva00033150(const void *block)
{
	typedef Rva00031BF0Chunk Chunk;
	if (block == 0)
		return;
	Chunk *chunk = (Chunk *)((char *)block - 8);
	unsigned int header = chunk->size;
	unsigned int size = header & 0x7FFFFFF8;
	if (size <= m_maxFastSize)
	{
		m_maxFastSize |= 1;
		Chunk **bin = &m_fastBins[(size >> 3) - 2];
		chunk->next = *bin;
		chunk->size |= 0x80000004;
		*bin = chunk;
		return;
	}
	if ((header & 2) == 0)
	{
		Chunk *next = (Chunk *)((char *)chunk + size);
		unsigned int nextSize = next->size & 0x7FFFFFF8;
		if ((header & 1) == 0)
		{
			unsigned int prevSize = chunk->previousSize;
			chunk = (Chunk *)((char *)chunk - prevSize);
			size += prevSize;
			chunk->size = size | 1;
			next->previousSize = size;
			chunk->previous->next = chunk->next;
			chunk->next->previous = chunk->previous;
		}
		if ((*(unsigned int *)((char *)next + nextSize + 4) & 1) != 0)
		{
			next->size &= ~1u;
			next->previousSize = size;
		}
		else
		{
			next->previous->next = next->next;
			next->next->previous = next->previous;
			size += nextSize;
			chunk->size = size | 1;
			*(unsigned int *)((char *)chunk + size) = size;
		}
		if (chunk != m_topChunk && next != m_topChunk)
		{
			Chunk *unsorted = (Chunk *)((char *)this + 0x30);
			Chunk *first = unsorted->next;
			chunk->previous = unsorted;
			chunk->next = first;
			unsorted->next = chunk;
			first->previous = chunk;
		}
		else
		{
			m_topChunk = chunk;
			chunk->next = chunk;
			chunk->previous = chunk;
			chunk->size = size | 1;
			*(unsigned int *)((char *)chunk + size) = size;
		}
		if (size >= 0x10000)
		{
			if (rva00031BB0((char *)chunk + size) && size >= m_trimThreshold)
				rva00032C60(m_trimPad);
		}
	}
	else
	{
		Chunk *fence = (Chunk *)((char *)chunk + size);
		unsigned int prevSize = chunk->previousSize;
		void *mapping = (char *)chunk - prevSize;
		unsigned int mappingSize = prevSize + size + 0x10;
		fence->previous->next = fence->next;
		fence->next->previous = fence->previous;
		__assume(m_mapBytes >= mappingSize);
		m_mapBytes -= mappingSize;
		--m_mapCount;
		VirtualFree(mapping, 0, 0x8000);
	}
}

}
}
