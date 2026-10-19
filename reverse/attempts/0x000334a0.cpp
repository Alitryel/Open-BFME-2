// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAURva00031010Node@@I@Z
// partial score=0.9693877551020408 date=2026-10-19
// cl: /O2
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
        Rva00031010Node *next = *(Rva00031010Node * *)&node->m_linkC;
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
	CoreBlock *core = m_cores.m_next;
	bool newTop = false;
	Chunk *chunk = 0;
	unsigned int extend = 0;
	unsigned int chunkSize;
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
			chunk = fencepost;
			if (fencepost->m_size & 1) {
				chunkSize = extend;
				fencepost->m_size = extend | 1;
			} else {
				chunk = (Chunk *)((char *)chunk - fencepost->m_priorSize);
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
			core->m_firstChunk = first;
			first->m_priorSize = 0;
			unsigned int fencepostOffset = ((header & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
			first->m_size = (header & 0x80000007) | fencepostOffset;
			unsigned int *fence = (unsigned int *)((char *)first + fencepostOffset);
			fence[0] = fencepostOffset;
			fence[1] = 8;
			fence[2] = 8;
			fence[3] = 9;
			chunk = first;
			chunkSize = extend;
			((Rva00031010 *)this)->rva00031010((Rva00031010Node *)chunk, true);
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
		unsigned int remainder = chunkSize - size;
		Chunk *rest = (Chunk *)((char *)chunk + size);
		rest->m_size = remainder;
		rest->m_priorSize = size;
		*(unsigned int *)((char *)rest + remainder) = remainder;
		if (newTop)
			((Rva00031010 *)this)->rva00031010((Rva00031010Node *)rest, false);
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
