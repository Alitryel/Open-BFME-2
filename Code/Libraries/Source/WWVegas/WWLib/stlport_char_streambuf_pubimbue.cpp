// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: STLport 4.5.3 char basic_streambuf::pubimbue at 0x0083FC10.
// The char specialization is declared as a concrete class in _streambuf.h,
// so its member is defined without the primary-template specialization tag.

#include <iosfwd>
#include <stdio.h>

// This TU-local facade uses the mutable-return locale assignment row at
// 0x00007160; the vendor header's const-return spelling asks for an alias.
// It reproduces the char streambuf's FILE-backed layout and virtual slot order
// needed by this body: imbue is slot 0x34 and _M_locale is at +0x4c. The other
// virtual signatures are unused here; no streambuf vtable is emitted.
namespace _STL
{
class locale
{
public:
	locale(const locale &);
	~locale();
	locale &operator=(const locale &);

private:
	void *_M_impl;
};

template <>
class basic_streambuf<char, char_traits<char> >
{
public:
	virtual ~basic_streambuf();
	virtual basic_streambuf *setbuf(char *, int);
	virtual int seekoff(int, int, int);
	virtual int seekpos(int, int);
	virtual int sync();
	virtual int showmanyc();
	virtual int xsgetn(char *, int);
	virtual int underflow();
	virtual int uflow();
	virtual int pbackfail(int);
	virtual int xsputn(const char *, int);
	virtual int _M_xsputnc(char, int);
	virtual int overflow(int);
	virtual void imbue(const locale &);

	locale pubimbue(const locale &);

private:
	FILE *_M_get;
	FILE *_M_put;
	FILE _M_default_get;
	FILE _M_default_put;
	locale _M_locale;
};
}

_STL::locale
_STL::basic_streambuf<char, _STL::char_traits<char> >::pubimbue(const _STL::locale &loc)
{
	this->imbue(loc);
	_STL::locale previous = _M_locale;
	_M_locale = loc;
	return previous;
}
