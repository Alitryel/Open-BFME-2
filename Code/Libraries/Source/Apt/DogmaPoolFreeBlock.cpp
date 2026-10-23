// cl: /O2 /MD
// ?freeBlock@Rva006DB270@@QAEXPAXH@Z @0x006DB270 207B evidence DogmaAllocator.cpp file plus two asserts plus pool range matching DOGMA_PoolManager plus callee 0x006DB090 row
#include <string.h>
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
// g_bfmeAptAllocAtE17728: VA 0xe17728 (zero-filled .data tail).
void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int) = 0;
// g_bfmeAptFreeSizeAtE17730: VA 0xe17730 (zero-filled .data tail).
void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *, unsigned int) = 0;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct _DOGMA_MemPool {
    _DOGMA_MemPool *mpNextPool;
    unsigned int mnPoolSize;
    unsigned int mnPoolFree;
};
class Rva006DB090 {
public:
    void rva006DB090(void *pNowFree, unsigned int nSize);
};
class Rva006DB270 {
    void **m_table;
    _DOGMA_MemPool *m_firstPool;
    int m_unk08;
    unsigned int m_maxSize;
    union {
        unsigned int m_cfg;
        struct { unsigned char m_nextIdx; unsigned char m_sizeIdx; unsigned char m_prevIdx; unsigned char m_minByte; };
    };
    int m_used;
    int m_count;
public:
    void freeBlock(void *pNowFree, int nSize);
};
void Rva006DB270::freeBlock(void *pNowFree, int nSize)
{
    if (pNowFree == 0) {
        g_bfmeAptAssertAtE17734("pNowFree != NULL && \"Attempting to Deallocate NULL pointer!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 471);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    int aligned = nSize;
    if ((aligned & 3) != 0)
        aligned = (aligned & ~3) + 4;
    unsigned int low = (unsigned int)m_minByte & 0xf;
    if ((unsigned int)aligned < low)
        aligned = (int)low;
    if ((unsigned int)aligned > m_maxSize) {
        g_bfmeAptFreeSizeAtE17730(pNowFree, (unsigned int)nSize);
        return;
    }
    _DOGMA_MemPool *pool = m_firstPool;
    for (;;) {
        unsigned char *start = (unsigned char *)pool + 12;
        if ((unsigned char *)pNowFree >= start) {
            unsigned int used = pool->mnPoolSize - pool->mnPoolFree;
            unsigned char *end = (unsigned char *)pool + 12 + used;
            if ((unsigned char *)pNowFree < end)
                break;
        }
        pool = pool->mpNextPool;
        if (pool == 0) {
            g_bfmeAptAssertAtE17734("bFound && \"Error! Deallocate recieved pointer to object that was not allocated here!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 496);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
            break;
        }
    }
    --m_used;
    memset(pNowFree, 0xcd, (unsigned int)aligned);
    ((Rva006DB090 *)this)->rva006DB090(pNowFree, (unsigned int)aligned);
}
