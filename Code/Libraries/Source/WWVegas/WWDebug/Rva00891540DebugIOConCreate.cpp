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

class DebugIOInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
// (only the size and the two members this factory uses).
class DebugIOCon
{
public:
    DebugIOCon(void);
    static DebugIOInterface *Create(void);

private:
    char m_body[0x110];
};

// ?Create@DebugIOCon@@SAPAVDebugIOInterface@@XZ @0x00040E50 89B: the "con"
// factory DebugPostStaticInit (0x0003A250) registers, as ZH Debug::PostStaticInit
// does with DebugIOCon::Create.
DebugIOInterface *DebugIOCon::Create(void)
{
    return (DebugIOInterface *)new (DebugAllocMemory(sizeof(DebugIOCon))) DebugIOCon();
}
