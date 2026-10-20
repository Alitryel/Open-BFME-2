// ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z
// partial score=0.982 date=2026-10-20
// cl: /O2 /MD
// dlmalloc 2.7 mALLOc structure, EA GeneralAllocator layout.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

struct Rva00030DD0Lock
{
    unsigned char m_cs[0x18];
    int m_ref;
};

struct malloc_chunk
{
    unsigned int prev_size;
    unsigned int size;
    malloc_chunk *bk;
    malloc_chunk *fd;
};
typedef malloc_chunk *mchunkptr;
typedef malloc_chunk *mbinptr;
typedef malloc_chunk *mfastbinptr;

class Rva00034C90
{
public:
    void rva00033930();
};

struct Rva00031010Node;
namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
    void *rva00032DF0(unsigned int size);
    Rva00031010Node *rva000334A0(unsigned int size);
};
}}

typedef bool (*GrowCallback)(void *, unsigned int, unsigned int, unsigned int);

#define SIZE_BITS 0x80000007u
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define chunk2mem(p) ((void *)((char *)(p) + 8))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= 1)
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define MINSIZE 16
#define in_smallbin_range(sz) ((unsigned long)(sz) < 0x200)
#define smallbin_index(sz) (((unsigned)(sz)) >> 3)
#define largebin_index(sz) \
(((((unsigned long)(sz)) >>  6) <= 32)?  56 + (((unsigned long)(sz)) >>  6): \
 ((((unsigned long)(sz)) >>  9) <= 20)?  91 + (((unsigned long)(sz)) >>  9): \
 ((((unsigned long)(sz)) >> 12) <= 10)? 110 + (((unsigned long)(sz)) >> 12): \
 ((((unsigned long)(sz)) >> 15) <=  4)? 119 + (((unsigned long)(sz)) >> 15): \
 ((((unsigned long)(sz)) >> 18) <=  2)? 124 + (((unsigned long)(sz)) >> 18): \
                                        126)
#define bin_at(m, i) ((mbinptr)((char *)&((m)->bins[(i) << 1]) - 8))
#define next_bin(b) ((mbinptr)((char *)(b) + 8))
#define last(b) ((b)->bk)
#define unsorted_chunks(M) (bin_at(M, 1))
#define idx2block(i) ((i) >> 5)
#define idx2bit(i) ((1U << ((i) & 31)))
#define mark_bin(m, i) ((m)->binmap[idx2block(i)] |= idx2bit(i))
#define fastbin_index(sz) ((((unsigned int)(sz)) >> 3) - 2)
#define have_fastchunks(M) (((M)->max_fast & 1))
#define unlink(P, BK, FD) { P->bk->fd = P->fd; P->fd->bk = P->bk; }
#define request2size(req) \
    (((req) + 4 + 7 <= MINSIZE) ? MINSIZE : ((req) + 4 + 7) & ~7u)

class Rva006C1F60
{
public:
    void *rva00033ED0(unsigned int bytes, int flags);

    unsigned int m_0;			// +0x00
    unsigned int max_fast;		// +0x04
    mfastbinptr fastbins[10];		// +0x08
    mchunkptr bins[256];		// +0x30
    unsigned int binmap[4];		// +0x430
    mchunkptr top;			// +0x440
    mchunkptr last_remainder;		// +0x444
    unsigned char m_pad448[0x46d - 0x448];
    bool m_46d;				// +0x46d
    unsigned char m_pad46e[0x488 - 0x46e];
    int n_mmaps;			// +0x488
    int m_48c;
    int n_mmaps_max;			// +0x490
    unsigned int mmap_threshold;	// +0x494
    unsigned char m_pad498[0x4ac - 0x498];
    GrowCallback m_grow;		// +0x4ac
    unsigned int m_4b0;			// +0x4b0
    unsigned int m_4b4;			// +0x4b4
    unsigned char m_pad4b8[0x4e4 - 0x4b8];
    Rva00030DD0Lock *m_lock;		// +0x4e4
};

void *Rva006C1F60::rva00033ED0(unsigned int bytes, int flags)
{
    unsigned int attempts = 0;
    void *result = 0;

    unsigned int nb;
    int idx;
    mbinptr bin;
    mchunkptr victim;
    unsigned int size;
    int victim_index;
    mchunkptr remainder;
    unsigned int remainder_size;
    unsigned int block;
    unsigned int bit;
    unsigned int map;
    mchunkptr fwd;
    mchunkptr bck;
    mbinptr unsorted;

    if (flags & 8)
        return ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(bytes);

    for (;;)
    {
        nb = bytes + 4 + 7;
        if (nb > MINSIZE)
            nb &= ~7u;
        else
            nb = MINSIZE;

        if (nb <= max_fast)
        {
            mfastbinptr *fb = &fastbins[fastbin_index(nb)];
            if ((victim = *fb) != 0)
            {
                victim->size &= 0x7ffffffb;
                *fb = victim->fd;
                return chunk2mem(victim);
            }
        }

        if (in_smallbin_range(nb))
        {
            idx = smallbin_index(nb);
            bin = bin_at(this, idx);
            if ((victim = last(bin)) != bin)
            {
                set_inuse_bit_at_offset(victim, nb);
                unlink(victim, bck, fwd);
                return chunk2mem(victim);
            }
        }
        else
        {
            idx = largebin_index(nb);
            if (have_fastchunks(this))
                ((Rva00034C90 *)this)->rva00033930();
        }

        unsorted = unsorted_chunks(this);
        for (;;)
        {
            while ((victim = unsorted->bk) != unsorted)
            {
                bck = victim->bk;
                size = chunksize(victim);

                if (in_smallbin_range(nb) &&
                    victim == last_remainder &&
                    bck == unsorted &&
                    size > nb + MINSIZE)
                {
                    remainder_size = size - nb;
                    remainder = chunk_at_offset(victim, nb);
                    unsorted->bk = unsorted->fd = remainder;
                    last_remainder = remainder;
                    remainder->bk = remainder->fd = unsorted;
                    set_head(victim, nb | 1);
                    set_head(remainder, remainder_size | 1);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }

                unsorted->bk = bck;
                bck->fd = unsorted;

                if (size == nb)
                {
                    set_inuse_bit_at_offset(victim, size);
                    return chunk2mem(victim);
                }

                if (in_smallbin_range(size))
                {
                    victim_index = smallbin_index(size);
                    bck = bin_at(this, victim_index);
                    fwd = bck->fd;
                }
                else
                {
                    victim_index = largebin_index(size);
                    bck = bin_at(this, victim_index);
                    fwd = bck->fd;

                    if (bck != fwd)
                    {
                        if (size < bck->bk->size)
                        {
                            fwd = bck;
                            bck = bck->bk;
                        }
                        else
                        {
                            while (size < chunksize(fwd))
                                fwd = fwd->fd;
                            bck = fwd->bk;
                        }
                    }
                }

                block = victim_index >> 5;
                binmap[block] |= idx2bit(victim_index);
                victim->bk = bck;
                victim->fd = fwd;
                fwd->bk = victim;
                bck->fd = victim;
            }

            if (!in_smallbin_range(nb))
            {
                bin = bin_at(this, idx);
                for (victim = last(bin); victim != bin; victim = victim->bk)
                {
                    size = chunksize(victim);
                    if (size >= nb)
                    {
                        remainder_size = size - nb;
                        unlink(victim, bck, fwd);
                        if (remainder_size < MINSIZE)
                        {
                            set_inuse_bit_at_offset(victim, size);
                            return chunk2mem(victim);
                        }
                        remainder = chunk_at_offset(victim, nb);
                        unsorted->bk = unsorted->fd = remainder;
                        remainder->bk = remainder->fd = unsorted;
                        set_head(victim, nb | 1);
                        set_head(remainder, remainder_size | 1);
                        set_foot(remainder, remainder_size);
                        return chunk2mem(victim);
                    }
                }
            }

            ++idx;
            bin = bin_at(this, idx);
            block = idx2block(idx);
            map = binmap[block];
            bit = idx2bit(idx);

            for (;;)
            {
                if (bit > map || bit == 0)
                {
                    do
                    {
                        if (++block >= 4)
                            goto use_top;
                    } while ((map = binmap[block]) == 0);
                    bin = bin_at(this, (block << 5));
                    bit = 1;
                }

                while ((bit & map) == 0)
                {
                    bin = next_bin(bin);
                    bit <<= 1;
                }

                victim = last(bin);
                if (victim == bin)
                {
                    binmap[block] = map &= ~bit;
                    bin = next_bin(bin);
                    bit <<= 1;
                }
                else
                {
                    size = chunksize(victim);
                    unlink(victim, bck, fwd);
                    remainder_size = size - nb;
                    if (remainder_size < MINSIZE)
                    {
                        set_inuse_bit_at_offset(victim, size);
                        return chunk2mem(victim);
                    }
                    remainder = chunk_at_offset(victim, nb);
                    unsorted->bk = unsorted->fd = remainder;
                    remainder->bk = remainder->fd = unsorted;
                    if (in_smallbin_range(nb))
                        last_remainder = remainder;
                    set_head(victim, nb | 1);
                    set_head(remainder, remainder_size | 1);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }
            }

        use_top:
            victim = top;
            size = chunksize(victim);
            if (size >= nb + MINSIZE)
            {
                remainder_size = size - nb;
                set_head(victim, nb | 1);
                remainder = chunk_at_offset(victim, nb);
                set_head(remainder, remainder_size | 1);
                top = remainder;
                mchunkptr t = top;
                set_head(t, remainder_size | 1);
                t->bk = t->fd = t;
                set_foot(t, remainder_size);
                return chunk2mem(victim);
            }
            if (!have_fastchunks(this))
                break;
            ((Rva00034C90 *)this)->rva00033930();
            idx = smallbin_index(nb);
        }

        if (m_46d)
        {
            if (nb >= mmap_threshold && n_mmaps < n_mmaps_max)
            {
                result = ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(bytes);
                if (result)
                    return result;
            }
            if (m_46d)
            {
                mchunkptr p = (mchunkptr)((EA::Allocator::GeneralAllocator *)this)->rva000334A0(nb);
                if (p)
                {
                    set_inuse_bit_at_offset(p, chunksize(p));
                    result = chunk2mem(p);
                }
            }
        }
        if (result || !m_grow || ++attempts >= m_4b4)
            break;

        int refs = m_lock->m_ref;
        for (int i = 0; i < refs; ++i)
        {
            Rva00030DD0Lock *lock = m_lock;
            --lock->m_ref;
            LeaveCriticalSection(lock);
        }
        bool ok = m_grow(this, bytes, bytes + 0x40, m_4b0);
        for (int j = 0; j < refs; ++j)
        {
            Rva00030DD0Lock *lock = m_lock;
            EnterCriticalSection(lock);
            ++lock->m_ref;
        }
        if (!ok)
            break;
    }
    return result;
}
