// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001539BC@Rva00153729@@QAEAAU1@ABU1@@Z retail 0x001539BC 48 bytes.
// Copies int at +0 then 6 vector<Rva005F8F96> at +4 via rowed assign 0x001537D8.
// Callers 0x001539EC 0x00153A7B 0x00153A98; unblocks 3.
// Identity honest address method __thiscall returns *this.
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
struct Rva00153729 &Rva00153729::rva001539BC(const struct Rva00153729 &other)
{
	m_00 = other.m_00;
	for (int i = 0; i < 6; i++)
		m_vec[i] = other.m_vec[i];
	return *this;
}
