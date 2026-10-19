// ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z
// partial score=0.457 date=2026-10-17
// ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z
// partial score=0.55 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z
// partial score=0.53 date=2026-10-14
// ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z
// partial score=0.45 date=2026-10-14
// Bank draft of the EA GeneralAllocator malloc at 0x00033ED0 (1466B, RET8).
// Decoded from the retail body with the MemoryPoolInit.cpp / memory_pool.cpp
// GeneralAllocator views: 8-byte chunk header (prevSize +0, size|flags +4,
// next +8, prev +0xC), 10 fast bins at +8, 128 8-byte bin heads from +0x30
// (bin i head at 0x30+8i-8, next at 0x30+8i, prev at +4), binmap at +0x430,
// top at +0x440/+0x444, grow callback at +0x4AC, lock at +0x4E4. Bin 1
// (+0x30) is the unsorted list the scan drains into the proper bins.
// cl: /O2 /MD

struct Rva00030DD0Lock
{
    unsigned char m_cs[0x18];
    int m_ref;
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

struct Rva00033ED0Chunk
{
    unsigned int m_prevSize;	// +0x00
    unsigned int m_size;		// +0x04 (bit0 in use, bit2 ...)
    Rva00033ED0Chunk *m_next;	// +0x08
    Rva00033ED0Chunk *m_prev;	// +0x0c
};

class Rva00034C90
{
public:
    void rva00033930();
};

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
    void *rva00032DF0(unsigned int size);
};
}}

class Rva006C1F60
{
public:
    void *rva00033ED0(unsigned int size, int flags);
    void *rva000334A0(unsigned int size);

private:
    unsigned int m_0;			// +0x00
    unsigned int m_flags4;		// +0x04 (max fast size | trim bit0)
    Rva00033ED0Chunk *m_fastBins[10];	// +0x08
    Rva00033ED0Chunk *m_binLinks[256];	// +0x30
    unsigned int m_binmap[4];		// +0x430
    Rva00033ED0Chunk *m_top;		// +0x440
    Rva00033ED0Chunk *m_top2;		// +0x444
    unsigned char m_pad448[0x46d - 0x448];
    unsigned char m_flag46d;		// +0x46d
    unsigned char m_pad46e[0x488 - 0x46e];
    unsigned int m_488, m_48c, m_490, m_494;
    unsigned char m_pad498[0x4ac - 0x498];
    void *(*m_grow)(Rva006C1F60 *, void *, void *, unsigned int);	// +0x4ac
    unsigned int m_4b0, m_4b4;
    unsigned char m_pad4b8[0x4e4 - 0x4b8];
    Rva00030DD0Lock *m_lock;		// +0x4e4

    Rva00033ED0Chunk *binHead(unsigned int i)
    {
        return (Rva00033ED0Chunk *)((char *)this + 0x30 + 8 * i - 8);
    }
    Rva00033ED0Chunk *&binNext(unsigned int i)
    {
        return *(Rva00033ED0Chunk **)((char *)this + 0x30 + 8 * i);
    }
    Rva00033ED0Chunk *&binPrev(unsigned int i)
    {
        return *(Rva00033ED0Chunk **)((char *)this + 0x30 + 8 * i + 4);
    }
    void *takeChunk(Rva00033ED0Chunk *c, unsigned int rounded)
    {
        unsigned int csize = c->m_size & 0x7ffffff8u;
        Rva00033ED0Chunk *next = c->m_next;
        Rva00033ED0Chunk *prev = c->m_prev;
        next->m_prev = prev;
        prev->m_next = next;
        unsigned int rest = csize - rounded;
        if (rest < 0x10)
        {
            *(unsigned int *)((char *)c + csize + 4) |= 1;
            return (char *)c + 8;
        }
        Rva00033ED0Chunk *rem = (Rva00033ED0Chunk *)((char *)c + rounded);
        Rva00033ED0Chunk *unsorted = binHead(1);
        unsorted->m_next = rem;
        unsorted->m_prev = rem;
        rem->m_next = unsorted;
        rem->m_prev = unsorted;
        c->m_size = rounded | 1;
        rem->m_size = rest | 1;
        *(unsigned int *)((char *)rem + rest) = rest;
        return (char *)c + 8;
    }
    static __forceinline unsigned int largeBinIndex(unsigned int size)
    {
        unsigned int index = size >> 6;
        if (index <= 0x20)
            return index + 0x38;
        index = size >> 9;
        if (index <= 0x14)
            return index + 0x5B;
        index = size >> 12;
        if (index <= 0x0A)
            return index + 0x6E;
        index = size >> 15;
        if (index <= 4)
            return index + 0x77;
        index = size >> 18;
        if (index <= 2)
            return index + 0x7C;
        return 0x7E;
    }
};

void *Rva006C1F60::rva00033ED0(unsigned int size, int flags)
{
    unsigned int dummy0 = 0;
    struct { unsigned int v; unsigned char pad[8]; } roundedSlot;
    unsigned int dummy1 = 0;
    unsigned int binIdx = 0;
    unsigned int dummy2 = 0;
    roundedSlot.v = 0;
    *(volatile unsigned int*)&dummy1 = 0;
    *(volatile unsigned int*)&dummy2 = 0;
    {
        if ((flags) & 8)
            return ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(size);
    }
retry:
    roundedSlot.v = size + 0xb;
    if (roundedSlot.v > 0x10)
        roundedSlot.v &= ~7u;
    else
        roundedSlot.v = 0x10;
    unsigned int &rounded = roundedSlot.v;

    // Fast bins.
    if (rounded <= m_flags4)
    {
        unsigned int fi = rounded >> 3;
        Rva00033ED0Chunk * volatile *slot = (Rva00033ED0Chunk **)((char *)this + 4 * fi);
        Rva00033ED0Chunk *c = *slot;
        if (c != 0)
        {
            c->m_size = c->m_size & 0x7ffffffbu;
            *slot = c->m_next;
            return (char *)c + 8;
        }
    }

    // Exact small bin.
    if (rounded < 0x200)
    {
        binIdx = rounded >> 3;
        Rva00033ED0Chunk *c = binNext(binIdx);
        Rva00033ED0Chunk *head = binHead(binIdx);
        if ((c) != head)
        {
            *(unsigned int *)((char *)c + rounded + 4) |= 1;
            c->m_next->m_prev = c->m_prev;
            c->m_prev->m_next = c->m_next;
            return (char *)c + 8;
        }
    }
    else
    {
        binIdx = largeBinIndex(rounded);
        if (m_flags4 & 1)
            ((Rva00034C90 *)this)->rva00033930();
    }

    // Drain the unsorted list at bin 1 into the proper bins.
    {
        Rva00033ED0Chunk *unsorted = binHead(1);
        for (;;)
        {
            Rva00033ED0Chunk *c = unsorted->m_next;
            if (c == unsorted)
                break;
            for (;;)
            {
                unsigned int csize = c->m_size & 0x7ffffff8u;
                Rva00033ED0Chunk *cnext = c->m_next;
                if (rounded < 0x200 && c == m_top2 && cnext == unsorted && csize > rounded + 0x10)
                {
                    unsigned int rest = csize - rounded;
                    Rva00033ED0Chunk *newTop = (Rva00033ED0Chunk *)((char *)c + rounded);
                    unsorted->m_next = newTop;
                    unsorted->m_prev = newTop;
                    newTop->m_next = unsorted;
                    newTop->m_prev = unsorted;
                    m_top2 = newTop;
                    c->m_size = rounded | 1;
                    newTop->m_size = rest | 1;
                    *(unsigned int *)((char *)newTop + rest) = rest;
                    return (char *)c + 8;
                }
                unsigned int idx;
                Rva00033ED0Chunk *next;
                Rva00033ED0Chunk *prev;
                if (csize != 0)
                {
                    unsorted->m_next = cnext;
                    cnext->m_prev = unsorted;
                }
                if (csize == rounded)
                {
                    *(unsigned int *)((char *)c + rounded + 4) |= 1;
                    return (char *)c + 8;
                }
                if (csize < 0x200)
                {
                    idx = csize >> 3;
                    next = binNext(idx);
                    prev = binHead(idx);
                }
                else
                {
                    idx = largeBinIndex(csize);
                    next = binPrev(idx);
                    prev = binHead(idx);
                    if (prev != next)
                    {
                        Rva00033ED0Chunk *first = prev->m_next;
                        if (csize < (first->m_size & 0x7ffffff8u))
                        {
                            next = prev;
                            prev = first;
                        }
                        else
                        {
                            next = prev->m_next;
                            while (csize < (next->m_size & 0x7ffffff8u))
                                next = next->m_prev;
                            prev = next;
                            next = next->m_next;
                        }
                    }
                }
                m_binmap[idx >> 5] |= 1u << (idx & 0x1f);
                c->m_next = next;
                c->m_prev = prev;
                prev->m_next = c;
                next->m_prev = c;

                c = unsorted->m_next;
                if (c == unsorted)
                    break;
            }
        }
    }

    // Large bins: prescan the target bin, then walk the binmap upward.
    if (rounded >= 0x200)
    {
        Rva00033ED0Chunk *end = binHead(binIdx);
        for (Rva00033ED0Chunk *c = binNext(binIdx); c != end; c = c->m_next)
        {
            unsigned int csize = c->m_size & 0x7ffffff8u;
            if (csize >= rounded)
                return takeChunk(c, rounded);
        }
    }
    {
        unsigned int idx = binIdx + 1;
        unsigned int wi = idx >> 5;
        unsigned int map = m_binmap[wi];
        Rva00033ED0Chunk *b = binHead(idx);
        unsigned int bit = 1u << (idx & 0x1f);
        for (;;)
        {
            if (bit > map || bit == 0)
            {
                for (;;)
                {
                    wi++;
                    if (wi >= 4)
                        goto topPath;
                    map = m_binmap[wi];
                    if (map != 0)
                        break;
                }
                b = binHead(wi * 32);
                bit = 1;
            }
            if ((map & bit) == 0)
            {
                do
                {
                    bit <<= 1;
                    b = (Rva00033ED0Chunk *)((char *)b + 8);
                }
                while ((map & bit) == 0);
            }
            if (b->m_next != b)
            {
                Rva00033ED0Chunk *c = b->m_next;
                return takeChunk(c, rounded);
            }
            m_binmap[wi] = map & ~bit;
            b = (Rva00033ED0Chunk *)((char *)b + 8);
            bit <<= 1;
        }
    }

topPath:
    {
        Rva00033ED0Chunk *top = m_top;
        unsigned int topSize = top->m_size & 0x7ffffff8u;
        if (topSize >= rounded + 0x10)
        {
            unsigned int rest = topSize - rounded;
            top->m_size = rounded | 1;
            Rva00033ED0Chunk *newTop = (Rva00033ED0Chunk *)((char *)top + rounded);
            newTop->m_size = rest | 1;
            m_top = newTop;
            newTop->m_next = newTop;
            newTop->m_prev = newTop;
            *(unsigned int *)((char *)newTop + rest) = rest;
            return (char *)top + 8;
        }
        if (m_flags4 & 1)
        {
            ((Rva00034C90 *)this)->rva00033930();
            goto retry;
        }
        if (m_flag46d)
        {
            if (rounded < m_494 && m_488 < m_490)
            {
                void *p = ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(size);
                if (p != 0)
                    return p;
            }
            void *p = rva000334A0(rounded);
            if (p != 0)
            {
                unsigned int psize = *(unsigned int *)((char *)p + 4) & 0x7ffffff8u;
                *(unsigned int *)((char *)p + psize + 4) |= 1;
                return (char *)p + 8;
            }
        }
        if (m_grow == 0)
            return 0;
        if (++m_4b4 >= m_4b4)
            return 0;
        Rva00030DD0Lock *lock = m_lock;
        int refs = lock->m_ref;
        for (int i = 0; i < refs; ++i)
        {
            lock->m_ref = lock->m_ref - 1;
            LeaveCriticalSection(lock);
        }
        bool ok = m_grow(this, (void *)size, (char *)size + 0x40, m_4b0) != 0;
        for (int i = 0; i < refs; ++i)
        {
            EnterCriticalSection(lock);
            lock->m_ref = lock->m_ref + 1;
        }
        if (ok)
            goto retry;
        return 0;
    }
}
