// The native 11-byte callback releases the classic locale implementation.
// locale::classic() identifies the handle at DA6214; its loader initializer
// points at the classic storage DDE118. Keep the callback's existing name.
namespace _STL {
class locale;
extern locale _Stl_loc_classic_locale;
class _Locale_impl {
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
};
}

void Rva007B6890()
{
    _STL::_Locale_impl *impl = *reinterpret_cast<_STL::_Locale_impl **>(
        &_STL::_Stl_loc_classic_locale);
    impl->_M_decr();
}
