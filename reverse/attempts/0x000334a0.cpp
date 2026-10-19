// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAURva00031010Node@@I@Z
// partial score=0.99 date=2026-10-19
// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAURva00031010Node@@I@Z
// partial score=0.9693877551020408 date=2026-10-19
// cl: /O2
// 0x000334A0 bank 2026-10-19 (claude-opus-5-5): 604/604 hack-free, nd 8 (was 608 B nd 140 with a
// volatile insert helper). Levers: chunk assigned per branch in the merge path (removed the 4-byte
// region), locals declared newTop,chunk,extend,chunkSize,core (cl symbol numbering fixes +0xF8/+0xFC;
// found by permuting all 120 orders), Chunk *rest before remainder (+0x212), and a plain inline
// SetTopChunk member instead of the volatile insert copy. Left: first->m_priorSize = 0 store placed
// after the fence[1] store; retail between `and edx,0x80000007` and `sub ecx,9`. Ruled out: every
// placement of the core/first stores, all 24 fencepost store orders, typed/stepped fencepost forms,
// the home AddDoubleFencepost text. Sibling 0x332D0 needed a barrier for the same fencepost schedule.
// Home candidates: memory_pool.cpp (real GeneralAllocator; re-check declaration order after porting)
// or Rva00031010Insert.cpp. Scratch: build/nbr/gf/334a0/.
// Notes kept from the earlier banks of this body:
// ?rva00031010@Rva00031010@@QAEXPAURva00031010Node@@_N@Z @0x00031010 66B evidence EA GeneralAllocator large-bin insert beside GetLargeBinIndex plus caller 0x000333ED plus head at +0x440 plus bin at +0x30
// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAURva00031010Node@@I@Z @0x000334A0 604B
// Core growth for a size (PPMalloc ExtendCore-like), caller 0x00034244: finds
// the first core (list after the sentinel at this+0x448, next +0x18) whose
// reserved-minus-committed span (+0x08 - +0x04) fits, commits max(size,
// +0x4DC granularity) capped to that span with VirtualAlloc (on failure the
// reserve is dropped to the committed size), then grows the chunk ending at
// the core's trailing fencepost (merging a free predecessor, which may be the
// top chunk) or lays out a fresh first chunk and makes it the top through the
// 0x00031010 insert above. Without such a core, and unless +0x4AC forbids
// it, a new core from 0x00032B00 becomes the top. A chunk larger than the
// request is split; the remainder becomes the top or heads the bin at +0x30.
// Target bytes supply offsets and flow; field labels are descriptive.
struct Rva00031010Node;
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	Rva00031010Node *rva000334A0(unsigned int size);
	void *rva00032B00(unsigned int size);

private:
	struct Chunk
	{
		unsigned int m_priorSize;
		unsigned int m_size;
		Chunk *m_prev;
		Chunk *m_next;
	};
	struct CoreBlock
	{
		Chunk *m_firstChunk;
		unsigned int m_size;
		unsigned int m_reservedSize;
		unsigned char m_flags[4];
		void *m_releaseFunction;
		void *m_releaseContext;
		CoreBlock *m_next;
		CoreBlock *m_prev;
	};
	void SetTopChunk(Chunk *chunk, bool linkOld)
	{
		Chunk *old = m_top;
		m_top = chunk;
		chunk->m_next = chunk;
		m_top->m_prev = m_top->m_next;
		if (old == &m_bin)
			return;
		if (!linkOld)
			return;
		Chunk *bin = &m_bin;
		Chunk *after = bin->m_next;
		old->m_prev = bin;
		old->m_next = after;
		bin->m_next = old;
		after->m_prev = old;
	}
	unsigned char m_pad000[0x30];
	Chunk m_bin;						// +0x30
	unsigned char m_pad040[0x440 - 0x40];
	Chunk *m_top;						// +0x440
	unsigned char m_pad444[4];
	CoreBlock m_cores;					// +0x448
	unsigned char m_pad468[0x4AC - 0x468];
	int m_noNewCores;					// +0x4AC
	unsigned char m_pad4B0[0x4DC - 0x4B0];
	unsigned int m_granularity;				// +0x4DC
};

Rva00031010Node *GeneralAllocator::rva000334A0(unsigned int size)
{
	bool newTop = false;
	Chunk *chunk = 0;
	unsigned int extend = 0;
	unsigned int chunkSize;
	CoreBlock *core = m_cores.m_next;
	for (; core != &m_cores; core = core->m_next)
	{
		if (size <= core->m_reservedSize - core->m_size)
		{
			extend = size;
			if (extend < m_granularity)
				extend = m_granularity;
			if (extend > core->m_reservedSize - core->m_size)
				extend = core->m_reservedSize - core->m_size;
			if (!VirtualAlloc((char *)core + core->m_size, extend, 0x1000, 4))
				core->m_reservedSize = core->m_size;
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
				chunk->m_prev->m_next = chunk->m_next;
				chunk->m_next->m_prev = chunk->m_prev;
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
			unsigned int header = ((unsigned int)core - (unsigned int)first + extend) | 1;
			unsigned int fencepostOffset = ((header & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
			core->m_firstChunk = first;
			first->m_size = (header & 0x80000007) | fencepostOffset;
			unsigned int *fence = (unsigned int *)((char *)first + fencepostOffset);
			fence[0] = fencepostOffset;
			fence[1] = 8;
			first->m_priorSize = 0;
			fence[2] = 8;
			fence[3] = 9;
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
                chunk->m_next = chunk;
                Chunk *node = m_top;
                node->m_prev = node->m_next;
                Chunk *bin = &m_bin;
                if (old != bin)
                {
                    Chunk *after = bin->m_next;
                    old->m_prev = bin;
                    old->m_next = after;
                    bin->m_next = old;
                    after->m_prev = old;
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
			Chunk *after = bin->m_next;
			rest->m_prev = bin;
			rest->m_next = after;
			bin->m_next = rest;
			after->m_prev = rest;
		}
	}
	return (Rva00031010Node *)chunk;
}

}
}
