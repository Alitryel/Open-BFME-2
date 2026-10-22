// cl: /DNDEBUG /MD /EHsc
//
// The DynamicVectorClass<EnumParameterClass::ENUM_VALUE>::Resize caller at
// 0x0093E700 reaches this shared 8-byte VectorClass body. Retail's constructor
// at 0x0093D1E0 and destructor thunk at 0x000470F5 show a reference-counted
// surface in the record's second word, so this source uses the retail RVA for
// the ICF-shared body name.

class Rva0093E4D0SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class Rva0093E4D0Surface
{
public:
	Rva0093E4D0Surface() : m_surface(0) {}
	~Rva0093E4D0Surface();

	Rva0093E4D0Surface &operator=(const Rva0093E4D0Surface &that)
	{
		if (that.m_surface)
			that.m_surface->addRef();
		if (m_surface)
			m_surface->release();
		m_surface = that.m_surface;
		return *this;
	}

private:
	Rva0093E4D0SurfaceResource *m_surface;
};

class Rva0093E4D0Element
{
public:
	Rva0093E4D0Element();
	~Rva0093E4D0Element();

	Rva0093E4D0Element &operator=(const Rva0093E4D0Element &that);

	void *m_first;
	Rva0093E4D0Surface m_surface;
};

// The rowed body is the element assignment itself; it is defined here
// directly rather than pulled out of the vector's resize, which would also
// reference the element's (unrowed) constructor and destructor.
Rva0093E4D0Element &Rva0093E4D0Element::operator=(const Rva0093E4D0Element &that)
{
	m_first = that.m_first;
	m_surface = that.m_surface;
	return *this;
}
