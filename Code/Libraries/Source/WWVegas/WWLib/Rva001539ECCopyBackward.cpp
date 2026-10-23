// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva001539ECCopyBackward@@YAPAURva00153729@@PAU1@00@Z retail 0x001539EC 50 bytes.
// Backward copy of Rva00153729 array via rowed 0x001539BC rva assign.
// Caller 0x00153A71 in 0x00153A5E; prev 0x001539BC assign next 0x00153A7B fill.
// Identity honest address free function __cdecl 3-pointer copy_backward shape.
struct Rva005F8F96;
namespace _STL
{
template <class T> class allocator;
template <class T, class Alloc> class vector
{
public:
	vector &operator=(const vector &x);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
struct Rva00153729
{
public:
	struct Rva00153729 &rva001539BC(const struct Rva00153729 &other);
private:
	int m_00;
	_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > m_vec[6];
};
struct Rva00153729 *__cdecl Rva001539ECCopyBackward(struct Rva00153729 *first, struct Rva00153729 *last, struct Rva00153729 *result)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		--last;
		--result;
		result->rva001539BC(*last);
	}
	return result;
}
