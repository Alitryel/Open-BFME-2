// cl: /O2 /MD /DNDEBUG
//
// ?rva00034A60@GeneralAllocator@Allocator@EA@@QAEPAXIIH@Z @ 0x00034A60 204B, ret 0xC (body 172B then its 8-entry jump table at 0x00034B0C)
//
// Calloc-style entry of the EA general allocator: allocates count * size
// bytes through the malloc engine 0x00033ED0 (flags passed through) and, for a
// block that is not separately mapped (chunk header bit 1 clear), zeroes its
// usable size (header & 0x7FFFFFF8, less the four-byte header). Up to 32
// bytes are cleared word by word through a fall-through switch on the word
// count (jump table at 0x00034B0C); larger blocks go to memset, which /O2
// expands inline as rep stosd/stosb. Returns the block (or null).
//
// Evidence: retail body only (the dlmalloc-style unrolled small clear is the
// shape the jump table encodes). The original name is not established; the
// name is address-derived, and 0x00033ED0 is reached through its existing
// address-derived pin.

#include <string.h>

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva00034A60(unsigned int count, unsigned int size, int flags);
};
}
}

struct Rva00034A60Chunk
{
	unsigned int priorSize;
	unsigned int size;
};

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
	void *rva00033ED0(unsigned int size, int flags);
};

void *EA::Allocator::GeneralAllocator::rva00034A60(unsigned int count, unsigned int size, int flags)
{
	void *block = ((Rva006C1F60 *)this)->rva00033ED0(count * size, flags);
	if (block != 0)
	{
		const Rva00034A60Chunk *chunk = (const Rva00034A60Chunk *)((char *)block - 8);
		unsigned int chunkSize = chunk->size & 0x7FFFFFF8u;
		if (!(chunk->size & 2))
		{
			if (chunkSize - 4 > 0x20)
				memset(block, 0, chunkSize - 4);
			else
			{
				unsigned int *p = (unsigned int *)block;
				switch (((chunkSize - 4) >> 2) - 1)
				{
				case 7: *p++ = 0;
				case 6: *p++ = 0;
				case 5: *p++ = 0;
				case 4: *p++ = 0;
				case 3: *p++ = 0;
				case 2: *p++ = 0;
				case 1: *p++ = 0;
				case 0: *p = 0;
				}
			}
		}
	}
	return block;
}
