// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ob0
// stlport
//
// The narrow twin of stlport_wide_filebuf_underflow.cpp - same instantiation as
// stlport_narrow_filebuf.cpp built without inline expansion, because retail's
// underflow is a plain forwarder to _Underflow::_M_doit and cl folds _M_doit
// into it at the default level.

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_input_error(); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_underflow_aux(); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::open(char const *, int); }
// overflow is stlport_narrow_filebuf_overflow.cpp's retail body (0x00015AB0);
// this /Ob0 copy differs and calls pptr and _FILE_O_next out of line, and
// this unit is first in link order for both, so their out-of-line copies
// beat every inlined-shape copy in the stream units.
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::overflow(int); }
// bfme link decl-only end

// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}


template class _STL::basic_filebuf<char, _STL::char_traits<char> >;

// The /Ob0 overflow copy was the only reference to the rowed out-of-line
// codecvt<char,char,mbstate_t>::out (0x0001D140); this anchor keeps cl
// emitting it.
// ?bfmeAnchorCodecvtCharOut absent-from-retail
int bfmeAnchorCodecvtCharOut(const _STL::codecvt<char, char, _STL::mbstate_t> &cvt, const char *from,
    const char *&fromNext, char *to, char *&toNext)
{
	return cvt.out(0, from, from, fromNext, to, to, toNext);
}
