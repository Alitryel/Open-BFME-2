// cl: /O2 /MD
// DogmaAllocator.cpp (retail __FILE__ names it; tu_map approved): the
// free-list push called by DogmaPoolFreeBlock.cpp's verified freeBlock.
// Keep that caller and its allocation callbacks in their owning unit;
// defining freeBlock here lets VC7.1 inline this push into a second body.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB090 {
    void **m_table;
    void *m_unk04;
    int m_unk08;
    int m_unk0C;
    union {
        unsigned int m_cfg;
        struct { unsigned char m_nextIdx; unsigned char m_sizeIdx; unsigned char m_prevIdx; unsigned char m_flagsHi; };
    };
    int m_unk14;
    int m_count;
public:
    void rva006DB090(void *pNowFree, unsigned int nSize);
};
// ?rva006DB090@Rva006DB090@@QAEXPAXI@Z @0x006DB090 136B evidence DogmaAllocator.cpp via string_xrefs file plus assert pNowFree NULL Pointer plus caller 0x006DB270 freeBlock same-this
void Rva006DB090::rva006DB090(void *pNowFree, unsigned int nSize)
{
    if (pNowFree == 0) {
        g_bfmeAptAssertAtE17734("pNowFree != NULL && \"Attempting to Deallocate a NULL Pointer!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 590);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    void **slot = &m_table[nSize >> 2];
    void *old = *slot;
    ++m_count;
    *slot = pNowFree;
    ((void **)pNowFree)[m_cfg & 0xff] = old;
    if (m_cfg & 0x10000000)
        ((unsigned int *)pNowFree)[m_sizeIdx] = (unsigned int)nSize;
    if (m_cfg & 0x20000000) {
        if (old != 0)
            ((void **)old)[m_prevIdx] = pNowFree;
        ((void **)pNowFree)[m_prevIdx] = 0;
    }
}

// Native6DAE50..6DAE74 and 6DAE80..6DAEA4: the array allocation pair of
// this file (DogmaAllocator.cpp lines 0x5E / 0x63, retail text): each fires
// the unconditional "never created in Arrays" assert, then forwards to the
// Apt allocation callbacks E17728 (gAptFuncs.pfnMemAlloc) and E1772C
// (gAptFuncs.pfnMemFree). Which class owns these operators is not
// established; the names are address-derived.
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
extern void (__cdecl *g_aptFreeCallback)(void *);
void *Rva006DAE50ArrayAlloc(unsigned int nSize)
{
    g_bfmeAptAssertAtE17734("false && \"Garbage collected Objects should never be created in Arrays!!!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 0x5e);
    if (g_bfmeAptBreakOnAssertAtDDC01C)
        __debugbreak();
    return g_bfmeAptAllocAtE17728(nSize);
}
void Rva006DAE80ArrayFree(void *p)
{
    g_bfmeAptAssertAtE17734("false && \"Garbage collected Objects should never be created in Arrays!!!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 0x63);
    if (g_bfmeAptBreakOnAssertAtDDC01C)
        __debugbreak();
    g_aptFreeCallback(p);
}
