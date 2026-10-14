// ?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXI@Z
// partial score=0.85 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG

// --- 0x005839E6 (15B) and 0x005839F5 (15B): resize with a zero fill value
// through the rowed by-value vector<ObjectID>::resize 0x005839A7. The first
// is the one-argument overload itself; the second resizes the +8 vector of
// the class whose retail table 0x0086FC30 holds it in slots 1 and 2 (slot 3
// is the rowed Rva00583794::rva00583933). WorldBuilder's twin (0x0147CBB0)
// pushes a by-value 0 into the same two-argument resize.
enum ObjectID
{
	INVALID_ID = 0
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
class vector<ObjectID, allocator<ObjectID> >
{
public:
	void resize(unsigned int newSize, ObjectID value);		// 0x005839A7
	void resize(unsigned int newSize);
private:
	ObjectID *_M_start;
	ObjectID *_M_finish;
	ObjectID *_M_end_of_storage;
};
}

void _STL::vector<ObjectID, _STL::allocator<ObjectID> >::resize(unsigned int newSize)
{
	const ObjectID &value = ObjectID();
	resize(newSize, value);
}

class Rva00583794
{
public:
	void rva005839F5(int count);
private:
	void *m_vtable;
	void *m_member04;
	_STL::vector<ObjectID, _STL::allocator<ObjectID> > m_08;
};

void Rva00583794::rva005839F5(int count)
{
	ObjectID value = ObjectID();
	m_08.resize(count, value);
}
