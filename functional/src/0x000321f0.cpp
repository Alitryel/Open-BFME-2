// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.0 date=2026-10-17
// ?rva000321F0@GeneralAllocator@Allocator@EA@@QAEHH@Z
// partial score=0.381 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
    int m_ref;
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
    unsigned int m_pad[2];
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

namespace EA { namespace Allocator {

class GeneralAllocator
{
public:
    int rva000321F0(int level);
    int rva00031D00(void *chunk);
    int rva00031E60(void *chunk);
    int rva00031F90(void *chunk);
    int rva00032160(void *chunk);

private:
    unsigned int m_0;			// +0x00
    unsigned int m_flags4;		// +0x04
    Rva000321F0Chunk *m_fastBins[10];	// +0x08
    Rva000321F0Chunk *m_binLinks[128];	// +0x30
    unsigned int m_binmap[4];		// +0x430
    Rva000321F0Chunk *m_top;		// +0x440
    unsigned char m_pad444[0x448 - 0x444];
    Rva000321F0Sentinel m_sentinel;	// +0x448
    unsigned int m_488, m_48c, m_490, m_494;
    unsigned char m_pad498[0x49c - 0x498];
    Rva000321F0Region m_regions;	// +0x49c
    unsigned char m_pad4a8[0x4e4 - 0x4a8];
    Rva000321F0Lock *m_lock;		// +0x4e4
};

int GeneralAllocator::rva000321F0(int level)
{
    int errors = 0;
    Rva000321F0Lock *lock = m_lock;
    if ((lock != 0) ? lock != 0 : lock != 0)
    {
        EnterCriticalSection(lock);
        int ref = lock->m_ref;
        lock->m_ref = ref + 1;
    }

    if (level < 1)
        goto unlock_return;

    {
        Rva000321F0Chunk *top = m_top;
        if (top == 0)
            goto unlock_return;
        if (top == (Rva000321F0Chunk *)((char *)this + 0x30))
            goto unlock_return;
        unsigned int maxFast = m_flags4;
        errors += (maxFast >= 0x50) ? 1 : 0;

        if (level >= 2)
        {
            // Fast-bin chains: each node must live inside a sentinel region and
            // carry the expected size flags.
            for (int i = 0; i < 10; ++i)
            {
                Rva000321F0Chunk *c = m_fastBins[i];
                int guard = 0;
                while (c != 0)
                {
                    if (guard >= 0x1e8480)
                        break;
                    Rva000321F0Sentinel *s = m_sentinel.m_next;
                    Rva000321F0Sentinel *end = &m_sentinel;
                    int found = 1;
                    while (s != end)
                    {
                        if ((unsigned int)c >= (unsigned int)s &&
                            (unsigned int)c < (unsigned int)s + s->m_size)
                        {
                            found = 0;
                            break;
                        }
                        s = s->m_next;
                    }
                    errors += found;

                    unsigned int size = c->m_size;
                    c = c->m_prev;
                    errors += (size & 0x80000000u) ? 1 : 0;
                    errors += (~(size >> 2) & 1);
                    ++guard;
                    errors += (guard >= 0x1e8480) ? 1 : 0;
                }
            }

            // Bin heads and the binmap must agree, and every bin list node
            // must be a valid chunk of its bin's size class.
            for (unsigned int i = 2; i < 0x100; i += 2)
            {
                Rva000321F0Chunk *head = (Rva000321F0Chunk *)((char *)this + 0x30 + 8 * i - 8);
                int bitSet = (m_binmap[i >> 5] & (1u << (i & 0x1f))) != 0;
                int listSet = (head->m_next != head);
                if (bitSet)
                    errors += 0;
                else
                    errors += listSet ? 1 : 0;

                Rva000321F0Chunk *c = head->m_next;
                if (c == head)
                    goto next_bin;
                while (c != head)
                {
                    errors += rva00031E60(c);
                    unsigned int size = c->m_size & 0x7ffffff8u;
                    unsigned int idx;
                    if (i >= 2)
                    {
                        if (size < 0x200)
                            idx = size >> 3;
                        else
                        {
                            idx = size >> 6;
                            if (idx <= 0x20)
                                idx += 0x38;
                            else
                            {
                                idx = size >> 9;
                                if (idx <= 0x14)
                                    idx += 0x5B;
                                else
                                {
                                    idx = size >> 12;
                                    if (idx <= 0x0A)
                                        idx += 0x6E;
                                    else
                                    {
                                        idx = size >> 15;
                                        if (idx <= 4)
                                            idx += 0x77;
                                        else
                                        {
                                            idx = size >> 18;
                                            idx = (idx <= 2) ? idx + 0x7C : 0x7E;
                                        }
                                    }
                                }
                            }
                        }
                        errors += (idx != i) ? 1 : 0;
                        if (size >= 0x200)
                        {
                            Rva000321F0Chunk *next = c->m_next;
                            if (next != head && (next->m_size & 0x7ffffff8u) < size)
                                errors += 1;
                        }
                    }
                    c = c->m_next;
                }
            next_bin:
                ;
            }

            // Walk the chunk run behind every bin node.
            for (unsigned int i = 2; i < 0x100; i += 2)
            {
                Rva000321F0Chunk *head = (Rva000321F0Chunk *)((char *)this + 0x30 + 8 * i - 8);
                Rva000321F0Chunk *c = head->m_next;
                if (c == head)
                    continue;
                do
                {
                    unsigned int size = c->m_size & 0x7ffffff8u;
                    while (size >= 0x10)
                    {
                        Rva000321F0Sentinel *s = m_sentinel.m_next;
                        Rva000321F0Sentinel *end = &m_sentinel;
                        int inside = 0;
                        while (s != end)
                        {
                            if ((unsigned int)c >= (unsigned int)s &&
                                (unsigned int)c < (unsigned int)s + s->m_size)
                            {
                                inside = 1;
                                break;
                            }
                            s = s->m_next;
                        }
                        if (inside && (unsigned int)c + size >= (unsigned int)s + s->m_size - 0x10)
                            break;
                        if ((*(unsigned int *)((char *)c + size + 4) & 1) != 0 &&
                            size >= 0x10)
                        {
                            errors += rva00031F90(c);
                            c = (Rva000321F0Chunk *)((char *)c + size);
                            size = c->m_size & 0x7ffffff8u;
                            continue;
                        }
                        _ReadWriteBarrier();
                        break;
                    }
                    c = c->m_next;
                }
                while (c != head);
            }
        }

        // Sentinel region counters.
        {
            Rva000321F0Sentinel *s = m_sentinel.m_next;
            Rva000321F0Sentinel *end = &m_sentinel;
            while (s != end)
            {
                errors += (~(s->m_size >> 1) & 1);
                Rva000321F0Sentinel *prev = (Rva000321F0Sentinel *)((char *)s - s->m_unknown0);
                errors += (~(prev->m_size >> 1) & 1);
                s = s->m_next;
            }
        }

        errors += rva00031D00(m_top);
        {
            int a = (int)m_488;
            int b = (int)m_490;
            errors += (a < 0) ? 1 : 0;
            errors += (a > b) ? 1 : 0;
        }
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
            Rva000321F0Chunk *c = (Rva000321F0Chunk *)((char *)s + 0);
            unsigned int endAddr = (unsigned int)s + size - 0x10;
            while ((unsigned int)c < endAddr)
            {
                unsigned int csize = c->m_size & 0x7ffffff8u;
                int inUse = (*(unsigned int *)((char *)c + csize + 4) & 1);
                if (inUse)
                    errors += rva00031F90(c);
                else
                    errors += rva00031E60(c);
                c = (Rva000321F0Chunk *)((char *)c + csize);
            }
            if ((Rva000321F0Chunk *)s == m_top)
                errors += (s == m_sentinel.m_prev) ? 1 : 0;
            s = s->m_prev;
        }
    }

unlock_return:
    if (lock != 0)
    {
        lock->m_ref = lock->m_ref - 1;
        LeaveCriticalSection(lock);
    }
    _ReadWriteBarrier();
    _ReadWriteBarrier();
    return errors;
}

}}
