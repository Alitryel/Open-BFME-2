// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002A8D08Create@@YGPAXPAX@Z @0x002A8D08 37B alloc 12 via rowed 0x000307F0 zero +4 via typed copy owner 0x002A8C17 return ptr arg src caller 0x002A9059
#include <memory>
struct TreeKey00242F5E;
void Rva002A8C17Construct(TreeKey00242F5E *, const TreeKey00242F5E &);

void *__stdcall Rva002A8D08Create(void *src)
{
    void *p = _STL::allocator<char>::allocate(12, 0);
    *(int *)p &= 0;
    Rva002A8C17Construct((TreeKey00242F5E *)((char *)p + 4),
        *(const TreeKey00242F5E *)src);
    return p;
}
