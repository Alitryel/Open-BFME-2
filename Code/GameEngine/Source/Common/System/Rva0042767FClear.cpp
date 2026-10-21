// cl: /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reset@Rva00427611@@QAEXXZ @0x0042767F 55B.
// Frees every owned element of the malloc-config pointer vector at +0x10 of the
// Rva00427611 object (the vector its dtor at 0x00427611 releases), then erases the
// whole range. The element type is open: only a virtual first slot is witnessed
// (called with 0, so the destructor runs without deleting), followed by the
// scalar operator delete 0x0002FD60 on the returned pointer.
#include <vector>

// vector<void*> begin/end/clear are expanded inline here; their out-of-line copies
// would differ from retail's. Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
}

class Rva00427611Element
{
public:
	virtual void *destroy(int flags);
};

class Rva00427611
{
public:
	void reset();
private:
	char m_pad00[0x10];
	_STL::vector<void *> m_elements;
};

void Rva00427611::reset()
{
	for (void **it = m_elements.begin(); it != m_elements.end(); ++it)
	{
		if (*it)
		{
			::operator delete(static_cast<Rva00427611Element *>(*it)->destroy(0));
		}
	}
	m_elements.clear();
}
