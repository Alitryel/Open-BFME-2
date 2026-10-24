// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Clone owners with complete lifetime providers.
// The unresolved owner contracts live in RvaCloneDeferredValueReturns.cpp.
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

class Rva005CDB8F
{
public:
	__forceinline Rva005CDB8F(const Rva005CDB8F &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	// Inline: retail deleting dtor 0x005FAA31 is an ICF-shared vptr reset
	// plus delete; no out-of-line ~Rva005CDB8F exists.
	virtual ~Rva005CDB8F() {}
	virtual RvaCloneResult<Rva005CDB8F> clone() const;
	struct Payload { int v[5]; };
	Rva005CDB8F(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CDF6C
{
public:
	__forceinline Rva005CDF6C(const Rva005CDF6C &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	virtual ~Rva005CDF6C();
	virtual RvaCloneResult<Rva005CDF6C> clone() const;
	struct Payload { int v[5]; };
	Rva005CDF6C(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};


RvaCloneResult<Rva005CDB8F> Rva005CDB8F::clone() const
{
	return RvaCloneResult<Rva005CDB8F>(new Rva005CDB8F(*this));
}

RvaCloneResult<Rva005CDF6C> Rva005CDF6C::clone() const
{
	return RvaCloneResult<Rva005CDF6C>(new Rva005CDF6C(*this));
}
