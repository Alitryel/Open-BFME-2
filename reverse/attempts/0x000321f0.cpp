// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.804 date=2026-10-19
// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.0 date=2026-10-17
// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.381 date=2026-10-15
// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.38 date=2026-10-14
// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.4 date=2026-10-14
// Bank draft of the GeneralAllocator heap validator at 0x000321F0 (1492B,
// RET4, level argument). Decoded from the retail body with the memory_pool.cpp
// GeneralAllocator view: sentinel region list at +0x448 (next +0x18/prev
// +0x1C), region link list at +0x49C (next +0xC), fast bins +8, bins +0x30,
// binmap +0x430, top +0x440, counters +0x488/+0x490/+0x494, lock +0x4E4.
// The unrowed providers 0x31D00 / 0x31E60 / 0x31F90 keep Rva-named methods
// the Lab2 alias binds.
// cl: /O2 /MD

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

struct Rva000321F0Lock
{
    unsigned char m_cs[0x18];
    volatile int m_ref;
};

struct Rva000321F0Chunk
{
    unsigned int m_prevSize;	// +0x00
    unsigned int m_size;		// +0x04
    Rva000321F0Chunk *m_next;	// +0x08
    Rva000321F0Chunk *m_prev;	// +0x0c
};

struct Rva000321F0Region
{
    unsigned int m_base;		// +0x00
    unsigned int m_size;
    unsigned int m_pad;
    Rva000321F0Region *m_next;	// +0x0c
};

struct Rva000321F0Sentinel
{
    unsigned int m_unknown0;	// +0x00
    unsigned int m_size;		// +0x04
    unsigned int m_releaseSize;	// +0x08
    unsigned char m_unknownC;	// +0x0c
    unsigned char m_releaseDirect;	// +0x0d
    unsigned char m_releaseAllowed;	// +0x0e
    unsigned char m_unknownF;	// +0x0f
    void *m_releaseCallback;	// +0x10
    void *m_releaseContext;	// +0x14
    Rva000321F0Sentinel *m_next;	// +0x18
    Rva000321F0Sentinel *m_prev;	// +0x1c
};

inline int Rva000321F0Missing(Rva000321F0Chunk *c,
    Rva000321F0Sentinel *s, Rva000321F0Sentinel *end)
{
    while (s != end)
    {
        if ((unsigned int)c >= (unsigned int)s &&
            (unsigned int)c < (unsigned int)s + s->m_size)
            return 0;
        s = s->m_next;
    }
    return 1;
}

namespace EA { namespace Allocator {

class GeneralAllocator
{
public:
    int rva000321F0(int level);
    int rva00031D00(void *chunk);
    int rva00031E60(void *chunk);
    int rva00031F90(void *chunk);
    unsigned int rva00032160(void *chunk);

private:
    unsigned int m_0;			// +0x00
    unsigned int m_flags4;		// +0x04
    Rva000321F0Chunk *m_fastBins[10];	// +0x08
    Rva000321F0Chunk *m_binLinks[256];	// +0x30
    unsigned int m_binmap[4];		// +0x430
    Rva000321F0Chunk *m_top;		// +0x440
    unsigned char m_pad444[0x448 - 0x444];
    Rva000321F0Sentinel m_sentinel;	// +0x448
    unsigned char m_pad468[0x488 - 0x468];
    unsigned int m_488, m_48c, m_490, m_494;
    unsigned char m_pad498[0x49c - 0x498];
    Rva000321F0Region m_regions;	// +0x49c
    unsigned char m_pad4ac[0x4cc - 0x4ac];
    unsigned int m_4cc, m_4d0, m_4d4;
    unsigned char m_pad4d8[0x4e4 - 0x4d8];
    Rva000321F0Lock *m_lock;		// +0x4e4
};

// Retail offsets and loop boundaries corrected from the complete native body.
int GeneralAllocator::rva000321F0(int level)
{
    int errors = 0;
    int index;
    Rva000321F0Lock *lock = m_lock;
    if (lock != 0)
    {
        EnterCriticalSection(lock);
        ++lock->m_ref;
    }

    if (level >= 1)
    {
        unsigned int totalFast = 0;
        if (m_top == 0 || m_top == (Rva000321F0Chunk *)m_binLinks)
        {
            if (lock != 0)
            {
                --lock->m_ref;
                LeaveCriticalSection(lock);
            }
            return 0;
        }
        unsigned int maxFast = m_flags4;
        errors += (maxFast >= 0x50) && 1;
        if (level >= 2)
        {
            // Fast-bin chains: each node must live inside a sentinel region and
            // carry the expected size flags.
            Rva000321F0Chunk **slot = m_fastBins;
            for (index = 10; index != 0; --index, ++slot)
            {
                Rva000321F0Chunk *c = *slot;
                int guard = 0;
                while (c != 0)
                {
                    if (guard >= 0x1e8480)
                        break;
                    errors += Rva000321F0Missing(c, m_sentinel.m_next, &m_sentinel);
                    unsigned int size = c->m_size;
                    c = c->m_prev;
                    errors += ((size & 0x80000000u) == 0) && 1;
                    errors += (((unsigned char)~(size >> 2)) & 1) && 1;
                    ++guard;
                    errors += (guard >= 0x1e8480) && 1;
                }
            }

            Rva000321F0Chunk **link = m_binLinks;
            for (index = 0; index < 0x100; index += 2, link += 2)
            {
                Rva000321F0Chunk *c = *link;
                if (index < 2)
                    errors += (c != 0) && 1;
                else
                {
                    errors += (c == 0) && 1;
                    Rva000321F0Chunk *p = c->m_prev;
                    Rva000321F0Chunk *head = (Rva000321F0Chunk *)(link - 2);
                    int count = 0;
                    if (p == head)
                        count = 1;
                    while (p != c)
                    {
                        if (p == head)
                            ++count;
                        else
                        {
                            errors += Rva000321F0Missing(p, m_sentinel.m_next, &m_sentinel);
                        }
                        p = p->m_prev;
                    }
                    errors += (count == 0) && 1;
                }
            }

            unsigned int control = m_4cc;
            unsigned int divisor = m_4d0;
            unsigned int page = m_4d4;
            errors += (control >= 0x186a0) && 1;
            errors += (divisor == 0) && 1;
            errors += ((page & (page - 1)) != 0) && 1;
            maxFast &= ~1u;
            int maxFastIndex = (maxFast >> 3) - 2;
            errors += (maxFast > 0x58) && 1;
            slot = m_fastBins;
            for (index = 0; index < 10; ++index, ++slot)
            {
                Rva000321F0Chunk *c = *slot;
                if (index > maxFastIndex)
                    errors += (c != 0) && 1;
                while (c != 0)
                {
                    unsigned int size = c->m_size;
                    c = c->m_prev;
                    totalFast += size & 0x7ffffff8u;
                    errors += (((size >> 3) & 0x0fffffffu) - 2 != (unsigned int)index) && 1;
                }
            }
            if (totalFast != 0)
                errors += ((unsigned char)~m_flags4 & 1) && 1;

            // Bin heads and the binmap must agree, and every bin list node
            // must be a valid chunk of its bin's size class.
            Rva000321F0Chunk *head = (Rva000321F0Chunk *)m_binLinks;
            for (index = 1; index < 0x80; ++index, head = (Rva000321F0Chunk *)((char *)head + 8))
            {
                if (index >= 2)
                {
                    bool bitSet = (m_binmap[index >> 5] & (1u << (index & 0x1f))) != 0;
                    bool listSet = head->m_next != head;
                    if (!bitSet)
                        errors += listSet && 1;
                }
                Rva000321F0Chunk *c = head->m_next;
                while (c != head)
                {
                    errors += rva00031E60(c);
                    unsigned int size = c->m_size & 0x7ffffff8u;
                    if (index >= 2)
                    {
                        unsigned int idx;
                        if (size < 0x200)
                            idx = size >> 3;
                        else if ((size >> 6) <= 0x20)
                            idx = (size >> 6) + 0x38;
                        else if ((size >> 9) <= 0x14)
                            idx = (size >> 9) + 0x5b;
                        else if ((size >> 12) <= 0x0a)
                            idx = (size >> 12) + 0x6e;
                        else if ((size >> 15) <= 4)
                            idx = (size >> 15) + 0x77;
                        else if ((size >> 18) <= 2)
                            idx = (size >> 18) + 0x7c;
                        else
                            idx = 0x7e;
                        errors += (idx != (unsigned int)index) && 1;
                        if (size >= 0x200)
                        {
                            Rva000321F0Chunk *next = c->m_next;
                            int outOfOrder;
                            if (next == head || (next->m_size & 0x7ffffff8u) >= size)
                                outOfOrder = 0;
                            else
                                outOfOrder = 1;
                            errors += outOfOrder;
                        }
                    }

                    // Walk the chunk run behind every bin node.
                    Rva000321F0Chunk *run = (Rva000321F0Chunk *)((char *)c + size);
                    for (;;)
                    {
                        unsigned int runSize = run->m_size & 0x7ffffff8u;
                        if (runSize < 0x10)
                        {
                            Rva000321F0Sentinel *s = m_sentinel.m_next;
                            Rva000321F0Sentinel *end = &m_sentinel;
                            while (s != end)
                            {
                                if ((unsigned int)run >= (unsigned int)s &&
                                    (unsigned int)run < (unsigned int)s + s->m_size)
                                    break;
                                s = s->m_next;
                            }
                            if (s != end && (unsigned int)run >= (unsigned int)s + s->m_size - 0x10)
                                break;
                        }
                        if ((*(unsigned char *)((char *)run + runSize + 4) & 1) == 0 || runSize < 0x10)
                            break;
                        errors += rva00031F90(run);
                        run = (Rva000321F0Chunk *)((char *)run + (run->m_size & 0x7ffffff8u));
                    }
                    c = c->m_next;
                }
            }

            // Sentinel region counters.
            Rva000321F0Region *r = m_regions.m_next;
            Rva000321F0Region *rend = &m_regions;
            while (r != rend)
            {
                errors += (((unsigned char)~(r->m_size >> 1)) & 1) && 1;
                unsigned int base = r->m_base;
                Rva000321F0Chunk *prev = (Rva000321F0Chunk *)((char *)r - base);
                r = r->m_next;
                errors += (((unsigned char)~(prev->m_size >> 1)) & 1) && 1;
            }
        }
        errors += rva00031D00(m_top);
        int a = (int)m_488;
        int b = (int)m_490;
        errors += (a < 0) && 1;
        errors += (a > b) && 1;
    }

    if (level >= 3)
    {
        // Region link list: each link must report a valid owner.
        Rva000321F0Region *r = m_regions.m_next;
        Rva000321F0Region *rend = &m_regions;
        while (r != rend)
        {
            errors += rva00032160((void *)((char *)r - r->m_base));
            r = r->m_next;
        }

        // Full sentinel walk: every chunk run must be valid and end at the top.
        Rva000321F0Sentinel *s = m_sentinel.m_prev;
        Rva000321F0Sentinel *end = &m_sentinel;
        while (s != end)
        {
            unsigned int size = s->m_size;
            Rva000321F0Chunk *c = (Rva000321F0Chunk *)s->m_unknown0;
            unsigned int endAddr = (unsigned int)s + size - 0x10;
            while ((unsigned int)c < endAddr)
            {
                unsigned int csize = c->m_size & 0x7ffffff8u;
                int inUse = (*(unsigned int *)((char *)c + csize + 4) & 1);
                if (inUse)
                    errors += rva00031F90(c);
                else
                {
                    errors += rva00031E60(c);
                    if (c == c->m_prev)
                    {
                        errors += (c != m_top) && 1;
                        break;
                    }
                }
                c = (Rva000321F0Chunk *)((char *)c + (c->m_size & 0x7ffffff8u));
            }
            s = s->m_prev;
        }
    }

    if (lock != 0)
    {
        --lock->m_ref;
        LeaveCriticalSection(lock);
    }
    return errors;
}

}}
