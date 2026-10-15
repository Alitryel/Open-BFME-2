// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /Oy-

// Keep the standard placement operations visible for construction and unwind,
// while suppressing the unused competing external placement-new copy.
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

class Rva00891540DebugIOCon
{
private:
    char m_body[0x110];
};

class DebugIOCon
{
public:
    DebugIOCon(void);

private:
    char m_body[0x110];
};

class Rva00891540DebugIOConFactory
{
public:
    static Rva00891540DebugIOCon *Create(void);
};

// ?Create@Rva00891540DebugIOConFactory@@SAPAVRva00891540DebugIOCon@@XZ
Rva00891540DebugIOCon *Rva00891540DebugIOConFactory::Create(void)
{
    return (Rva00891540DebugIOCon *)new (DebugAllocMemory(sizeof(Rva00891540DebugIOCon)))
        DebugIOCon();
}
