// cl: /DNDEBUG /MD /EHsc /Od
// STLport's unoptimized allocation helpers retain stack locals in retail.

// The vendored header declares _S_oom_malloc public (SAPAXI); this unit's row
// keeps the private spelling (CAPAXI) it compiled to. Same function, same
// address: bind the header spelling to the row.
#pragma comment(linker, "/alternatename:?_S_oom_malloc@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z=?_S_oom_malloc@?$__malloc_alloc@$0A@@_STL@@CAPAXI@Z")

extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int);
extern "C" __declspec(dllimport) int __cdecl puts(const char *);
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl exit(int);

namespace _STL
{
typedef void (__cdecl *__oom_handler_type)();

template <int Instance>
class __malloc_alloc
{
private:
    static void *__cdecl _S_oom_malloc(unsigned int bytes);
    static __oom_handler_type __oom_handler;
};

// Algorithm from STLport 4.5.2 stl/_alloc.c; its no-exception branch is in _alloc.h.
template <int Instance>
void *__cdecl __malloc_alloc<Instance>::_S_oom_malloc(unsigned int bytes)
{
    __oom_handler_type __my_malloc_handler;
    void *__result;

    for (;;) {
        __my_malloc_handler = __oom_handler;
        if (__my_malloc_handler == 0) {
            puts("out of memory\n");
            exit(1);
        }
        (*__my_malloc_handler)();
        __result = malloc(bytes);
        if (__result) return __result;
    }
}

template void *__malloc_alloc<0>::_S_oom_malloc(unsigned int);

// The handler slot: _S_oom_malloc's matched DIR32 read at +0x7 resolves to VA
// 0x00DDF4CC in the .data zero-fill tail, so retail starts it null.
template <int Instance>
__oom_handler_type __malloc_alloc<Instance>::__oom_handler = 0;
template __oom_handler_type __malloc_alloc<0>::__oom_handler;
}
