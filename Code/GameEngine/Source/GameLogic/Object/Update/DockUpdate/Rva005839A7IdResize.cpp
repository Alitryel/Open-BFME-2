// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Retail 0x005839E6 (15 B) and 0x005839F5 (15 B): one-argument resize wrappers
// over the two-argument by-value resize at 0x005839A7. Target evidence: both
// materialise the fill value as xor eax,eax / push eax, which cl 7.1 emits for
// a 4-byte class element with an inline zeroing default constructor
// (resize(n) { resize(n, T()); }); an enum or integer element pushes 0. The
// second resizes the +8 vector of the class whose retail table 0x0086FC30
// holds both in slots 1 and 2 (slot 3 is the rowed Rva00583794::rva00583933).
// The element class is address-named: its original identity (an ID wrapper)
// is not established, so these spellings disclaim the ledger's ObjectID guess.
struct Rva005839A7Id
{
	int m_value;
	Rva005839A7Id() : m_value(0) {}
};

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector;

template <>
class vector<Rva005839A7Id, allocator<Rva005839A7Id> >
{
public:
	void resize(unsigned int newSize, Rva005839A7Id value);	// 0x005839A7
	void resize(unsigned int newSize);
private:
	Rva005839A7Id *_M_start;
	Rva005839A7Id *_M_finish;
	Rva005839A7Id *_M_end_of_storage;
};
}

void _STL::vector<Rva005839A7Id, _STL::allocator<Rva005839A7Id> >::resize(unsigned int newSize)
{
	resize(newSize, Rva005839A7Id());
}

class Rva00583794
{
public:
	void rva005839F5(int count);
private:
	void *m_vtable;
	void *m_member04;
	_STL::vector<Rva005839A7Id, _STL::allocator<Rva005839A7Id> > m_08;
};

void Rva00583794::rva005839F5(int count)
{
	m_08.resize(count, Rva005839A7Id());
}

// The retail call in this body reads 0x005839A7, an address the ledger already
// carries as ?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXIW4ObjectID@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?resize@?$vector@URva005839A7Id@@V?$allocator@URva005839A7Id@@@_STL@@@_STL@@QAEXIURva005839A7Id@@@Z=?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXIW4ObjectID@@@Z")
