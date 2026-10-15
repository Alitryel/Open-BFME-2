// cl: /DNDEBUG /MD /EHs
// ??1Rva000AADC1@@UAE@XZ retail 0x000AADC1 124B
// Own vftable 0x00BC942C. Global-deletes every
// owned polymorphic entry of the void* vector at +0x04, clears it through the
// rowed erase 0x0031BD55, frees its storage, then the inline base dtor restores vftable
// 0x00BC93C8.
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
		// The rowed erase is the void* instantiation (0x0031BD55); every
		// pointer vector clears through it.
		void clear()
		{
			((vector<void *, allocator<void *> > *)this)->erase((void **)begin(), (void **)end());
		}
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva000AADC1Entry
{
public:
	virtual ~Rva000AADC1Entry();
};

class Rva000AADC1Base
{
public:
	virtual ~Rva000AADC1Base() {}
};

class Rva000AADC1 : public Rva000AADC1Base
{
public:
	virtual ~Rva000AADC1();
private:
	_STL::vector<Rva000AADC1Entry *, _STL::allocator<Rva000AADC1Entry *> > m_entries; // +0x04
};

Rva000AADC1::~Rva000AADC1()
{
	for (Rva000AADC1Entry **it = m_entries.begin(); it != m_entries.end(); ++it)
		::delete *it;
	m_entries.clear();
}
