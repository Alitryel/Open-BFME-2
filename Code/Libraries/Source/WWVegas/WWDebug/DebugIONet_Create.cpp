// cl: /DNDEBUG /MD /EHa /Oy-

// Preserve placement construction and unwind without an unused competing
// external placement-new copy (the established WWDebug factory spelling).
#define __PLACEMENT_NEW_INLINE
#include <new>
__declspec(dllimport) __forceinline void *__cdecl operator new(size_t, void *memory) throw()
{
    return memory;
}
inline void __cdecl operator delete(void *, void *) throw()
{
}

extern void *DebugAllocMemory(unsigned size);

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    DebugIOInterface(void) {}
};

class DebugIONet : public DebugIOInterface
{
public:
    DebugIONet(void) {}
    virtual ~DebugIONet(void);
    static DebugIOInterface *Create(void);

private:
    void *m_pipe;
};

// ?Create@DebugIONet@@SAPAVDebugIOInterface@@XZ
DebugIOInterface *DebugIONet::Create(void)
{
    return new (DebugAllocMemory(sizeof(DebugIONet))) DebugIONet();
}
