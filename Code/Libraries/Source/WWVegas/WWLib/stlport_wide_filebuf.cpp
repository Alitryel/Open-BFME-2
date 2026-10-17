// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_output_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_underflow_aux(); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(char const *, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekpos(fpos<int>, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekoff(long, int, int); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::underflow(); }
// bfme link decl-only end

template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;

// seekoff and underflow are rowed in stlport_create_filebuf.cpp and
// stlport_wide_filebuf_underflow.cpp (declared above). Their copies here were
// what emitted these rowed helpers; instantiate / anchor them directly.
template class _STL::_Underflow<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::_Filebuf_Tmp_Buf<wchar_t>;
template bool _STL::equal(wchar_t *, wchar_t *, wchar_t *, _STL::_Eq_traits<_STL::char_traits<wchar_t> >);
extern ptrdiff_t (*const _bfmeAnchorCountChar)(char *, char *, const char &) = &_STL::count<char *, char>;
extern _STL::codecvt_base::result (_STL::codecvt<wchar_t, char, mbstate_t>::*const _bfmeInlineAnchorWideCodecvtIn)(
	mbstate_t, const char *, const char *, const char *&, wchar_t *, wchar_t *, wchar_t *&) const =
	&_STL::codecvt<wchar_t, char, mbstate_t>::in;
extern _STL::streamoff (_STL::_Filebuf_base::*const _bfmeInlineAnchorFilebufGetOffset)(char *, char *) =
	&_STL::_Filebuf_base::_M_get_offset;
extern bool (_STL::_Filebuf_base::*const _bfmeInlineAnchorFilebufInBinaryMode)() const =
	&_STL::_Filebuf_base::_M_in_binary_mode;
