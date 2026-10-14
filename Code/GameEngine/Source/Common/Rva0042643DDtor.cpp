// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??1Rva0042643D@@UAE@XZ @0x0042643D 183B evidence: vtable 0x0083C350 plus base GameEngineDeletingBase 0x001B4E74 plus Entry dtor 0x004DC9ED plus loops over +0x0C +0x18 plus frees +0x24 +0x18 +0x0C
#include <vector>

// Retain the bfmealloc primary bodies inline without competing external copies.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* p, size_t n) const {
 _STLP_ASSERT( (p == 0) == (n == 0) )
 if(p != 0) ::free((void*)p);
}
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int* p, size_t n) {
 __stl_alloc_rebind(static_cast<allocator<int>&>(*this),(int*)0).deallocate(p,n);
}
}


class Rva004DC9EDEntry
{
public:
	~Rva004DC9EDEntry();
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Base dtor at 0x001B4E74 by its row name ??1SubsystemInterface@@UAE@XZ (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva0042643D : public SubsystemInterface
{
public:
	virtual ~Rva0042643D();
private:
	_STL::vector<Rva004DC9EDEntry *> m_vec0C;
	_STL::vector<Rva004DC9EDEntry *> m_vec18;
	_STL::vector<int> m_vec24;
};

Rva0042643D::~Rva0042643D()
{
	for (Rva004DC9EDEntry **p = m_vec0C.begin(); p != m_vec0C.end(); ++p)
	{
		if (*p)
			delete *p;
	}
	for (Rva004DC9EDEntry **p = m_vec18.begin(); p != m_vec18.end(); ++p)
	{
		if (*p)
			delete *p;
	}
}
