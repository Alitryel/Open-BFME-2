// cl: /O1 /DNDEBUG /MD
//
// ?rva004B15E6@EmotionTrackerUpdate@@UAEXXZ @0x004B15E6 77B.
// EmotionTrackerUpdate's override of slot 0 of its +0x20 interface (the
// derived table's slot, ctor 0x004B21B9 / dtor 0x004B1322), so its this is
// that subobject: +0x70/+0x7C here are the object's +0x90 emotion vector
// and +0x9C current emotion. When the current one is live, call 0x004DD2C0
// on it and clear it. Then destroy each non-null element of the vector
// through the rowed destructor 0x004DCE8E and operator delete 0x0002FD60,
// and erase the whole range through the rowed vector erase 0x0031BD55.

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *erase(T *first, T *last);
};
}

class EmotionNugget
{
public:
	void OnDeactivation();
};

class Rva004DCE8E
{
public:
	~Rva004DCE8E();
};

// The UpdateModule part (primary vftable, 0x20 bytes) and the one-slot
// interface at +0x20.
class EmotionTrackerUpdatePrimaryView
{
public:
	virtual ~EmotionTrackerUpdatePrimaryView();
private:
	char m_pad04[0x20 - 0x04];
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void rva004B15E6() = 0;
};

class EmotionTrackerUpdate : public EmotionTrackerUpdatePrimaryView, public EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void rva004B15E6();

private:
	char m_pad24[0x90 - 0x24];
	_STL::vector<void *, _STL::allocator<void *> > m_vec;	// +0x90
	EmotionNugget *m_slot;	// +0x9C
};

void EmotionTrackerUpdate::rva004B15E6()
{
	EmotionNugget *slot = m_slot;
	if (slot != 0)
	{
		slot->OnDeactivation();
		m_slot = 0;
	}
	_STL::vector<void *, _STL::allocator<void *> > *vec = &m_vec;
	for (void **it = vec->m_start; it != m_vec.m_finish; ++it)
	{
		Rva004DCE8E *elem = (Rva004DCE8E *)*it;
		if (elem != 0)
		{
			elem->~Rva004DCE8E();
			::operator delete(elem);
		}
	}
	vec->erase(vec->m_start, vec->m_finish);
}
