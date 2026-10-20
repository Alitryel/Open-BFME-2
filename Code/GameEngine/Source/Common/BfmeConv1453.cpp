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


char *bfmeFillV14(char *p, unsigned n, char v);
class BfmeStrV14
{
public:
	BfmeStrV14 *bfmeAssignV14(char *first, char *last, unsigned n, char v);
	void bfmeEraseV14(char *first, char *last);
};

BfmeStrV14 *BfmeStrV14::bfmeAssignV14(char *first, char *last, unsigned n, char v)
{
	char unused[8];
	unsigned dist = (unsigned)(last - first);

	if (dist >= n)
	{
		bfmeFillV14(first, n, v);
		bfmeEraseV14(first + n, last);
	}
	else
	{
		bfmeFillV14(first, dist, v);
		((NativeFillString *)this)->insert(last, n - dist, v);
	}
	return this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFillInsV38@BfmeStrV38@@QAEPAV1@PAD0ID@Z=?bfmeAssignV14@BfmeStrV14@@QAEPAV1@PAD0ID@Z")
