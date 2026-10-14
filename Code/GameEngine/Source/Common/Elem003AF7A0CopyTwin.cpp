// cl: /DNDEBUG /MD /EHsc
//
// ICF twin of ??0Rva005DBCD1@@QAE@ABV0@@Z (0x005DBCD1, V3PolyCopyCtors.cpp):
// the vector element of PAVectorEraseRange003AF7A0.cpp is the same vptr plus
// two words record, and its copy constructor is that body.
typedef short Short;

struct Elem003AF7A0
{
	Elem003AF7A0(const Elem003AF7A0 &other);
	virtual ~Elem003AF7A0();

	Short m_field04;
	Short m_field06;
};

Elem003AF7A0::Elem003AF7A0(const Elem003AF7A0 &other)
{
	m_field04 = other.m_field04;
	m_field06 = other.m_field06;
}
