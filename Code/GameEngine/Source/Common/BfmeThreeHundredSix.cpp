// cl: /Od

// Native 0x29530 is the recovered STLport insertion owner. This declaration
// binds the existing wrapper call without introducing another implementation.
namespace _STL {
template<class T> class allocator;
template<class T> class char_traits;
template<class T, class Traits, class Alloc> class basic_string {
public:
 void insert(T *, unsigned int, T);
};
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NativeFillString;

// A stretch of one byte put into the run at a given place, after the place has
// been checked against the length and the new length against the limit. The
// record is handed back. Built without optimisation; all three callees are
// pinned by address.

struct BfmeThingQX
{
	BfmeThingQX *bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what);

	void bfmeRangeErrorQX(void);

	void bfmeLengthErrorQX(void);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

BfmeThingQX *BfmeThingQX::bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what)
{
	if (where > (unsigned int)(m_bfmeEnd - m_bfmeAt))
		bfmeRangeErrorQX();

	if ((unsigned int)(m_bfmeEnd - m_bfmeAt) > 0xfffffffe - many)
		bfmeLengthErrorQX();

	char *at = m_bfmeAt;

	((NativeFillString *)this)->insert(at + where, many, (char)what);

	return this;
}
