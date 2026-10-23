// cl: /DNDEBUG /MD /EHs-c-
// BFME1 donor: 4367fc698990427e26cc1c399989d074d8ee9bbe,
// game/GameEngine/Source/Common/System/Rva00881D70CrtShims.cpp,
// RVA 0x00881D20 (29 bytes) and 0x00881D40 (35 bytes).
// BFME2 proves cdecl pointer adapters at RVA 0x0002FC10/0x0002FC30,
// a shared sentinel at VA 0x00E23310, and the free slot at VA 0x00DE03FC.
// Original adapter names remain unproven. Native crtexew.obj identifies the
// sentinel as __onexitbegin; atonexit.obj retains its four-byte COMMON definition.

typedef void (__cdecl *GameFreeFunction)(void *, int);
extern "C" GameFreeFunction __gameMemFreePtr;
typedef int (__cdecl *CrtExitProc)();
extern "C" CrtExitProc *__onexitbegin;

void rva0002FC10(void *block)
{
    if (block != 0 && block != __onexitbegin)
        __gameMemFreePtr(block, 0);
}

void rva0002FC30(void *block, int blockType)
{
    if (block != 0 && block != __onexitbegin)
        __gameMemFreePtr(block, 0);
}
