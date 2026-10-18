// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The vector<bool> member at CreateAHeroData+0x5C is established by the
// matched copy/destructor source and its 0x388F9B/0x3890D5 bit helpers.
// This explicit STLport instantiation recovers its complete assignment body.
#include <vector>

// Keep STLport's deallocation inlined without emitting a competing helper.
// The external helper has no retail address and differs across allocator TUs.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Bvector_base<allocator<bool> >::_M_deallocate()
{
    if (_M_start._M_p)
        _M_end_of_storage.deallocate(_M_start._M_p,
            _M_end_of_storage._M_data - _M_start._M_p);
}
}

// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
// bfme link decl-only end
template _STL::vector<bool> &_STL::vector<bool>::operator=(const _STL::vector<bool> &);
