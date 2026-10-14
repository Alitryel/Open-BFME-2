// ?rva000347A0@GeneralAllocator@Allocator@EA@@QAEPAXPAXIH@Z
// partial score=0.92 date=2026-10-15
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000347A0@GeneralAllocator@Allocator@EA@@QAEPAXPAXIH@Z
// Retail 0x000347A0..0x00034A60 (704 bytes including the eight-entry case
// table at 0x00034A40) RET0C: the general allocator's reallocation,
// dlmalloc's rEALLOc shape. A null block is a plain allocation (malloc
// engine 0x00033ED0). A chunk that is already big enough, or that grows
// into the top chunk (+0x440) or a free successor, is resized in place and
// any remainder of 16 bytes or more is split off and freed (0x00033150)
// with the field at +0x478 held at zero; otherwise a new block is
// allocated, the old contents copied (memcpy above 32 bytes, else the
// unrolled word copy) and the old block freed. Mmapped chunks (head bit 1)
// are kept when large enough, else copied. Chunk heads keep their size in
// the low 31 bits and flags in bits 0..2 and 31.
// Evidence: retail body and table, the sibling zeroing (0x00034A60) and
// multiple (0x00034B30) allocation entries; names are address-derived.
#include <string.h>
#pragma intrinsic(memcpy)

class Rva006C1F60
{
public:
	void *rva00033ED0(unsigned int size, int flags);
};

class Rva00033E90
{
public:
	void freeBlock(void *block);
};

static inline unsigned int Rva000347A0RequestSize(unsigned int request)
{
	unsigned int size = request + 11;
	return size > 16 ? size & ~7u : 16;
}

struct Rva000347A0Chunk
{
	unsigned int prevSize;
	unsigned int head;
	Rva000347A0Chunk *fd;
	Rva000347A0Chunk *bk;
};

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva000347A0(void *oldMem, unsigned int bytes, int flags);

private:
	unsigned char m_pad000[0x440];
	Rva000347A0Chunk *m_top;		// +0x440
	unsigned char m_pad444[0x478 - 0x444];
	int m_478;				// +0x478
};
}
}

void *EA::Allocator::GeneralAllocator::rva000347A0(void *oldMem, unsigned int bytes, int flags)
{
	if (oldMem == 0)
		return ((Rva006C1F60 *)this)->rva00033ED0(bytes, flags);
	unsigned int nb = Rva000347A0RequestSize(bytes);
	Rva000347A0Chunk *oldp = (Rva000347A0Chunk *)((char *)oldMem - 8);
	unsigned int oldSize = oldp->head & 0x7ffffff8;
	Rva000347A0Chunk *newp;
	unsigned int newSize;
	if (!(oldp->head & 2)) {
		if (nb <= oldSize) {
			newp = oldp;
			newSize = oldSize;
		} else {
			Rva000347A0Chunk *next = (Rva000347A0Chunk *)((char *)oldp + oldSize);
			if (next == m_top && (newSize = oldSize + (next->head & 0x7ffffff8)) >= nb + 16) {
				oldp->head = (oldp->head & 0x80000007) | nb;
				Rva000347A0Chunk *top = (Rva000347A0Chunk *)((char *)oldp + nb);
				m_top = top;
				unsigned int topSize = newSize - nb;
				top->bk = top;
				top->fd = top;
				top->head = topSize | 1;
				*(unsigned int *)((char *)top + topSize) = topSize;
				return oldMem;
			} else if (next != m_top && !(((Rva000347A0Chunk *)((char *)next + (next->head & 0x7ffffff8)))->head & 1) && (newSize = oldSize + (next->head & 0x7ffffff8)) >= nb) {
				newp = oldp;
				next->fd->bk = next->bk;
				next->bk->fd = next->fd;
			} else {
				void *newMem = ((Rva006C1F60 *)this)->rva00033ED0(nb - 7, flags);
				if (newMem == 0)
					return 0;
				newp = (Rva000347A0Chunk *)((char *)newMem - 8);
				newSize = newp->head & 0x7ffffff8;
				if (newp == next) {
					newSize += oldSize;
					newp = oldp;
				} else {
					unsigned int copySize = oldSize - 4;
					if (copySize > 0x20) {
						memcpy(newMem, oldMem, copySize);
					} else {
						unsigned int *d = (unsigned int *)newMem;
						unsigned int *s = (unsigned int *)oldMem;
						switch ((copySize >> 2) - 1) {
						case 7: *d++ = *s++;
						case 6: *d++ = *s++;
						case 5: *d++ = *s++;
						case 4: *d++ = *s++;
						case 3: *d++ = *s++;
						case 2: *d++ = *s++;
						case 1: *d++ = *s++;
						case 0: *d = *s;
						}
					}
					((Rva00033E90 *)this)->freeBlock(oldMem);
					return (char *)newp + 8;
				}
			}
		}
		unsigned int remainderSize = newSize - nb;
		if (remainderSize < 16) {
			newp->head = (newp->head & 0x80000007) | newSize;
			((Rva000347A0Chunk *)((char *)newp + newSize))->head |= 1;
		} else {
			newp->head = (newp->head & 0x80000007) | nb;
			Rva000347A0Chunk *remainder = (Rva000347A0Chunk *)((char *)newp + nb);
			remainder->head = remainderSize | 1;
			Rva000347A0Chunk *after = (Rva000347A0Chunk *)((char *)remainder + remainderSize);
			after->prevSize = remainderSize;
			after->head |= 1;
			int saved = m_478;
			m_478 = 0;
			((Rva00033E90 *)this)->freeBlock((char *)remainder + 8);
			m_478 = saved;
		}
		return (char *)newp + 8;
	}
	if (nb + 4 <= oldSize)
		return oldMem;
	void *newMem = ((Rva006C1F60 *)this)->rva00033ED0(nb - 7, flags);
	if (newMem != 0) {
		memcpy(newMem, oldMem, oldSize - 8);
		((Rva00033E90 *)this)->freeBlock(oldMem);
	}
	return newMem;
}
