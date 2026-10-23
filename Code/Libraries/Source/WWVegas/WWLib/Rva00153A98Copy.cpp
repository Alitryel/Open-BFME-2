// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PAURva00153729@@PAU1@H@_STL@@YAPAURva00153729@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z retail 0x00153A98 50 bytes.
// Forward copy of Rva00153729 array via rowed 0x001539BC rva assign.
// Caller 0x00153BAC.
// Identity honest address free function.
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
namespace _STL
{
struct random_access_iterator_tag;
template <class Input, class Output, class Distance>
Output __copy(Input, Input, Output, const random_access_iterator_tag &, Distance *);
}

template <>
Rva00153729 *_STL::__copy<Rva00153729 *, Rva00153729 *, int>(
    Rva00153729 *first, Rva00153729 *last, Rva00153729 *result,
    const _STL::random_access_iterator_tag &, int *)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		result->rva001539BC(*first);
		++first;
		++result;
	}
	return result;
}
