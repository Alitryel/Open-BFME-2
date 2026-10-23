// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00153A7BFill@@YAXPAURva00153729@@0ABU1@@Z retail 0x00153A7B 29 bytes.
// Fill range with value via rowed 0x001539BC rva assign.
// Callers 0x00153DE5 0x00153E25 in 0x00153D5E.
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
void __cdecl Rva00153A7BFill(struct Rva00153729 *first, struct Rva00153729 *last, const struct Rva00153729 &value)
{
	for (; first != last; ++first)
		first->rva001539BC(value);
}
