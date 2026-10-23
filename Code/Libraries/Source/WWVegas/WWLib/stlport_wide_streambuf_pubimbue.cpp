// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide basic_streambuf instantiation. The upstream class-template
// body is specialized here because VC7.1 rejects explicit instantiation of the
// library's wchar_t specialization while emitting the same member definition.

#include <streambuf>

template <> inline
_STL::locale
_STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >::pubimbue(const _STL::locale &loc)
{
	this->imbue(loc);
	_STL::locale previous = _M_locale;
	_M_locale = loc;
	return previous;
}

#pragma inline_depth(0)
// ?bfmeEmitstlport_wide_streambuf_pubimbue@@YAXPAV?$basic_streambuf@GV?$char_traits@G@_STL@@@_STL@@ABVlocale@2@@Z present-unmatched
void bfmeEmitstlport_wide_streambuf_pubimbue(_STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> > *p, const _STL::locale &loc)
{
	p->pubimbue(loc);
}
#pragma inline_depth()
