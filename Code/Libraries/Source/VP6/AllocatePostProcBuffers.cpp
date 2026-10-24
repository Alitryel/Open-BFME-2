// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b66b0.md plus retail only.
// No decoder source was consulted.
//
// AllocatePostProcBuffers (retail 0x001B66B0, 292 bytes): frees any earlier
// buffers, then allocates six 32-byte-aligned working buffers of the
// post-processor instance through the duck-memory allocator (0x001B6400), in
// order: intermediate frame (0xB8/0xBC), filter bounding array (0xA0/0x34),
// deblock bounding array (0xA4/0x3C), fragment Q index array (0xA8/0x24),
// fragment variance array (0xAC/0x28), fragment deblocking flags (0xB0/0x2C).
// Each buffer is kept as its raw pointer and the rounded-up aligned pointer.
// Any failure frees everything and returns 0.

// 0x001B6400 is the tagged duck_malloc overload (DuckMem.h); it forwards the
// size to the core at 0x001B63C0.
#include "DuckMem.h"

extern "C" void __cdecl DeletePostProcBuffers(void *what);

// Instance field view; the layout is owned by the post-processor instance.
struct PostProcBufferState
{
	unsigned char m_pad0[0x24];
	void *m_at24;
	void *m_at28;
	void *m_at2c;
	unsigned char m_pad1[0x34 - 0x30];
	void *m_at34;
	unsigned char m_pad2[0x3c - 0x38];
	void *m_at3c;
	unsigned char m_pad3[0x44 - 0x40];
	unsigned int m_rows;
	unsigned char m_pad4[0x8c - 0x48];
	unsigned int m_count;
	unsigned char m_pad5[0x98 - 0x90];
	unsigned int m_stride;
	unsigned char m_pad6[0xa0 - 0x9c];
	void *m_atA0;
	void *m_atA4;
	void *m_atA8;
	void *m_atAC;
	void *m_atB0;
	unsigned int m_factorB4;
	void *m_atB8;
	void *m_atBC;
};

// RVA 0x001B66B0
extern "C" int __cdecl AllocatePostProcBuffers(PostProcBufferState *self)
{
	DeletePostProcBuffers(self);

	self->m_atB8 = duck_malloc(
		((((self->m_factorB4 * 2 + self->m_rows) * self->m_stride) * 3 >> 1) + 0x20),
		0);
	if (self->m_atB8 == 0)
		goto failure;
	self->m_atBC = (void *)(((unsigned int)self->m_atB8 + 0x1f) & ~0x1f);

	self->m_atA0 = duck_malloc(0x820, 0);
	if (self->m_atA0 == 0)
		goto failure;
	self->m_at34 = (void *)(((unsigned int)self->m_atA0 + 0x1f) & ~0x1f);

	self->m_atA4 = duck_malloc(0x820, 0);
	if (self->m_atA4 == 0)
		goto failure;
	self->m_at3c = (void *)(((unsigned int)self->m_atA4 + 0x1f) & ~0x1f);

	self->m_atA8 = duck_malloc(self->m_count * 4 + 0x20, 0);
	if (self->m_atA8 == 0)
		goto failure;
	self->m_at24 = (void *)(((unsigned int)self->m_atA8 + 0x1f) & ~0x1f);

	self->m_atAC = duck_malloc(self->m_count * 4 + 0x20, 0);
	if (self->m_atAC == 0)
		goto failure;
	unsigned int byteSize = self->m_count + 0x20;
	self->m_at28 = (void *)(((unsigned int)self->m_atAC + 0x1f) & ~0x1f);

	self->m_atB0 = duck_malloc(byteSize, 0);
	if (self->m_atB0 == 0)
		goto failure;
	self->m_at2c = (void *)(((unsigned int)self->m_atB0 + 0x1f) & ~0x1f);
	return 1;

failure:
	DeletePostProcBuffers(self);
	return 0;
}
