// cl: /DNDEBUG /MD /EHs
// ??1Rva00421242@@MAE@XZ retail 0x00421312 128B
// Own vftable 0x00C3BE00 (slot-0 ??_G at 0x004214A7). Global-deletes every
// non-null owned polymorphic entry of the void* vector at +0x0C, clears it through the
// rowed erase 0x0031BD55, frees its storage, then runs the rowed base dtor
// ??1SubsystemInterface@@UAE@XZ 0x001B4E74.
extern "C" void __cdecl free(void *);

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A> class vector
	{
	public:
		__forceinline ~vector()
		{
			if (m_start)
				free(m_start);
		}
		T *begin() { return m_start; }
		T *end() { return m_finish; }
		T *erase(T *first, T *last);
		void clear()
		{
			erase(begin(), end());
		}
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
	// Keep these accesses inline without competing with the STLport providers.
	template <> __declspec(dllimport) __forceinline
	void **vector<void *, allocator<void *> >::begin() { return m_start; }
	template <> __declspec(dllimport) __forceinline
	void **vector<void *, allocator<void *> >::end() { return m_finish; }
	template <> __declspec(dllimport) __forceinline
	void vector<void *, allocator<void *> >::clear() { erase(begin(), end()); }
}

class Rva00421242Entry
{
public:
	virtual ~Rva00421242Entry();
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva00421242 : public SubsystemInterface
{
protected:
	virtual ~Rva00421242();
private:
	_STL::vector<void *, _STL::allocator<void *> > m_entries; // +0x0C
};

Rva00421242::~Rva00421242()
{
	for (void **it = m_entries.begin(); it != m_entries.end(); ++it)
		if (*it)
			::delete static_cast<Rva00421242Entry *>(*it);
	m_entries.clear();
}
