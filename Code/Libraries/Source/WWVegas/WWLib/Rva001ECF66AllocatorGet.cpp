// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Provider unit for the empty-allocator getter the 96-byte range copy ctor in
// Rva001ECF66Finish.cpp calls at 0x001ECF82. That call decodes to 0x0021983A,
// where the ledger rows a 7-byte leaf (8b442404c20400: return the hidden
// return slot, write nothing) - the ICF fold every empty STLport allocator
// getter lands on. The copy ctor compiles to retail's 96 bytes only while its
// TU sees a declaration, not the 7-byte body, so the definition lives here and
// the linker folds this COMDAT onto the same address.
//
// GeometryShape's allocator is empty, so its copy construct is elided here and
// the getter emits exactly retail's 7 bytes with no relocations.

struct GeometryShape;

namespace _STL
{
template <class _Tp> class allocator
{
public:
	allocator()
	{
	}
	allocator(const allocator<_Tp> &);
};
template <class _Tp, class _Alloc> class vector;
template <> class vector<GeometryShape, allocator<GeometryShape> >
{
public:
	allocator<GeometryShape> get_allocator() const;
};
}

__declspec(noinline) _STL::allocator<GeometryShape>
_STL::vector<GeometryShape, _STL::allocator<GeometryShape> >::get_allocator() const
{
	return _STL::allocator<GeometryShape>();
}
