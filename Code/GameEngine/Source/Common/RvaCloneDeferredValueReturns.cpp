// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Clone owners whose destructor/vtable contracts remain unresolved.
// Split from RvaCloneValueReturns.cpp without changing the native clone bodies.
// Native RET4 returns a hidden one-pointer object: allocate a payload, zero
// its reference count at +4, then increment it when constructing the result.
// The nontrivial result destructor establishes this ABI; release is external.

template <class T> class RvaCloneResult
{
public:
	RvaCloneResult(T *p) : pointer(p)
	{
		if (p) ++p->m_ref;
	}
	~RvaCloneResult();
private:
	T *pointer;
};

class Rva005CE259
{
public:
	__forceinline Rva005CE259(const Rva005CE259 &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	virtual ~Rva005CE259();
	virtual RvaCloneResult<Rva005CE259> clone() const;
	struct Payload { int v[2]; };
	Rva005CE259(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005677B9
{
public:
 __forceinline Rva005677B9(const Rva005677B9 &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva005677B9();
 virtual RvaCloneResult<Rva005677B9> clone() const;
 struct Payload { int v[2]; };
 Rva005677B9(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};

class Rva00574ABB
{
public:
 __forceinline Rva00574ABB(const Rva00574ABB &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva00574ABB();
 virtual RvaCloneResult<Rva00574ABB> clone() const;
 struct Payload { int v[2]; };
 Rva00574ABB(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};

class Rva005E9742
{
public:
 __forceinline Rva005E9742(const Rva005E9742 &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva005E9742();
 virtual RvaCloneResult<Rva005E9742> clone() const;
 struct Payload { int v[6]; };
 Rva005E9742(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};


RvaCloneResult<Rva005CE259> Rva005CE259::clone() const
{
	return RvaCloneResult<Rva005CE259>(new Rva005CE259(*this));
}

RvaCloneResult<Rva005677B9> Rva005677B9::clone() const
{
 return RvaCloneResult<Rva005677B9>(new Rva005677B9(*this));
}

RvaCloneResult<Rva00574ABB> Rva00574ABB::clone() const
{
 return RvaCloneResult<Rva00574ABB>(new Rva00574ABB(*this));
}

RvaCloneResult<Rva005E9742> Rva005E9742::clone() const
{
 return RvaCloneResult<Rva005E9742>(new Rva005E9742(*this));
}
