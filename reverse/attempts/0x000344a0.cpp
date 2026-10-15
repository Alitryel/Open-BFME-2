// ?rva000344A0@GeneralAllocator@Allocator@EA@@QAEPAXIIIH@Z
// partial score=0.98 date=2026-10-15
// ?rva000344A0@GeneralAllocator@Allocator@EA@@QAEPAXIIIH@Z
// Home TU: Code/GameEngine/Source/Common/System/memory_pool.cpp (default flags). It MUST compile
// after GetLargeBinIndexFromChunkSize in the same unit: retail keeps the offset in EDX across
// that call, which cl 13.10 only does for a callee defined earlier in the TU.
// Insert: class Rva006C1F60 { public: void *rva00033ED0(unsigned int size, int flags); }; next to
// class Rva00033E90; the member declaration in GeneralAllocator; the body below after rva000338F0.
// nd7 at 759/761 B: retail builds each scan sentinel in EAX then copies it to ESI
// (lea eax,[edi+30h]; mov esi,eax and mov eax,[edi+eax*4+30h]; mov ecx,[eax+0Ch]; mov esi,eax).
// ?rva000344A0@GeneralAllocator@Allocator@EA@@QAEPAXIIIH@Z @0x000344A0 759B RET10
// Aligned allocation (size, alignment, offset, flags), dlmalloc's mEMALIGn
// with EA extensions: alignment of at most 8 with no offset is a plain
// allocation (malloc engine 0x00033ED0); otherwise the alignment is raised
// to 16 and rounded up to a power of two, the offset to a multiple of 8.
// Flags bit 2 first looks for an exact-size free chunk whose mem + offset is
// already aligned, in the unsorted list (+0x30) and then in the size's bin.
// Else it over-allocates, gives the misaligned leader back to the free path
// (0x00033150, with +0x478 held at zero) and splits off a trailing remainder
// that coalesces into a free successor or the top chunk (+0x440). Mmapped
// chunks (head bit 1) only shift their prev-size. Evidence: retail body, the
// wrapper 0x00035100 and the sibling malloc/realloc/calloc entries; the name
// is address-derived. GetLargeBinIndexFromChunkSize must be defined earlier
// in this unit: retail keeps the offset in EDX across that call.
static inline Rva00031BF0Chunk *Rva000344A0Unsorted(void *self)
{
	return (Rva00031BF0Chunk *)((char *)self + 0x30);
}

static inline Rva00031BF0Chunk *Rva000344A0Bin(void *self, unsigned int idx)
{
	return ((Rva00031BF0Chunk **)((char *)self + 0x30))[idx];
}

static inline void *Rva000344A0Take(Rva00031BF0Chunk *p, unsigned int nb)
{
	*(unsigned int *)((char *)p + nb + 4) |= 1;
	void *mem = (char *)p + 8;
	p->previous->next = p->next;
	p->next->previous = p->previous;
	return mem;
}

void *GeneralAllocator::rva000344A0(unsigned int size, unsigned int alignment, unsigned int offset, int flags)
{
	typedef Rva00031BF0Chunk Chunk;
	if (alignment <= 8 && offset == 0)
		return ((::Rva006C1F60 *)this)->rva00033ED0(size, flags);
	if (alignment < 16)
		alignment = 16;
	unsigned int mask = alignment - 1;
	if (alignment & mask)
	{
		mask |= mask >> 1;
		mask |= mask >> 2;
		mask |= mask >> 4;
		mask |= mask >> 8;
		mask |= mask >> 16;
		alignment = mask + 1;
	}
	if (offset & 7)
		offset = (offset + 7) & ~7u;
	unsigned int nb = size + 11;
	nb = nb > 16 ? nb & ~7u : 16;

	if (flags & 4)
	{
		Chunk *bin = Rva000344A0Unsorted(this);
		Chunk *p;
		for (p = bin->next; p != bin; p = p->next)
		{
			if ((p->size & 0x7ffffff8) == nb && (alignment == 0 || (((unsigned int)p + offset + 8) & (alignment - 1)) == 0))
				return Rva000344A0Take(p, nb);
		}
		unsigned int idx = nb < 0x200 ? nb >> 3 : GetLargeBinIndexFromChunkSize(nb);
		bin = Rva000344A0Bin(this, idx);
		for (p = bin->next; p != bin; p = p->next)
		{
			if ((p->size & 0x7ffffff8) == nb && (alignment == 0 || (((unsigned int)p + offset + 8) & (alignment - 1)) == 0))
				return Rva000344A0Take(p, nb);
		}
	}

	void *mem = ((::Rva006C1F60 *)this)->rva00033ED0(nb + alignment + offset + 16, flags);
	if (mem != 0)
	{
		Chunk *p = (Chunk *)((char *)mem - 8);
		if (((unsigned int)mem + offset) % alignment != 0)
		{
			Chunk *newp = (Chunk *)((((unsigned int)mem + alignment + offset - 1) & -alignment) - offset - 8);
			if ((unsigned int)((char *)newp - (char *)p) < 16)
				newp = (Chunk *)((char *)newp + alignment);
			unsigned int leadSize = (char *)newp - (char *)p;
			unsigned int newSize = (p->size & 0x7ffffff8) - leadSize;
			if (p->size & 2)
			{
				newp->previousSize = p->previousSize + leadSize;
				newp->size = newSize | 2;
				return (char *)newp + 8;
			}
			newp->size = newSize | 1;
			*(unsigned int *)((char *)newp + newSize + 4) |= 1;
			*(unsigned int *)((char *)newp + newSize) = newSize;
			p->size = (p->size & 0x80000007) | leadSize;
			newp->previousSize = leadSize;
			int saved = *(int *)((char *)this + 0x478);
			*(int *)((char *)this + 0x478) = 0;
			((::Rva00033E90 *)this)->freeBlock((char *)p + 8);
			*(int *)((char *)this + 0x478) = saved;
			p = newp;
		}

		unsigned int chunkSize = p->size;
		if (!(chunkSize & 2))
		{
			chunkSize &= 0x7ffffff8;
			if (chunkSize > nb + 16)
			{
				unsigned int remSize = chunkSize - nb;
				Chunk *rem = (Chunk *)((char *)p + nb);
				rem->size = remSize | 1;
				p->size = (p->size & 0x80000007) | nb;
				Chunk *next = (Chunk *)((char *)rem + remSize);
				unsigned int nextSize = next->size & 0x7ffffff8;
				if (((Chunk *)((char *)next + nextSize))->size & 1)
				{
					int saved = *(int *)((char *)this + 0x478);
					*(int *)((char *)this + 0x478) = 0;
					((::Rva00033E90 *)this)->freeBlock((char *)rem + 8);
					*(int *)((char *)this + 0x478) = saved;
					return (char *)p + 8;
				}
				next->previous->next = next->next;
				next->next->previous = next->previous;
				remSize += nextSize;
				rem->size = remSize | 1;
				*(unsigned int *)((char *)rem + remSize) = remSize;
				Chunk *&top = *(Chunk **)((char *)this + 0x440);
				if (rem == top || next == top)
				{
					top = rem;
					rem->next = rem;
					rem->previous = rem;
					rem->size = remSize | 1;
					*(unsigned int *)((char *)rem + remSize) = remSize;
				}
				else
				{
					Chunk *bck = (Chunk *)m_bins;
					Chunk *fwd = bck->next;
					rem->previous = bck;
					rem->next = fwd;
					bck->next = rem;
					fwd->previous = rem;
				}
			}
		}
		return (char *)p + 8;
	}
	return 0;
}

