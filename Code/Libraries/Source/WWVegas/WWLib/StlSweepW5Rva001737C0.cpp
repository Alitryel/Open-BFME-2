// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001737C0Element {Rva001737C0Element();Rva001737C0Element(const Rva001737C0Element&);Rva001737C0Element&operator=(const Rva001737C0Element&);~Rva001737C0Element(){}char bytes[32]; bool operator==(const Rva001737C0Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva001737C0Element * _STL::__copy<Rva001737C0Element *, Rva001737C0Element *, int>(Rva001737C0Element *, Rva001737C0Element *, Rva001737C0Element *, _STL::random_access_iterator_tag const &, int *);

// ICF twin of ??4BfmeAssignRecord32@@QAEAAU0@ABU0@@Z (0x00173499,
// BfmeAssignRecord32Assign.cpp): the same 32-byte record assignment, so the
// copy loop above binds a definition.
class Rva00072A94
{
	unsigned char m_data[4];
public:
	Rva00072A94 &operator=(const Rva00072A94 &o);
};

struct Rva001737C0View
{
	Rva00072A94 m_00;
	unsigned int m_04;
	Rva00072A94 m_08[6];
};

Rva001737C0Element &Rva001737C0Element::operator=(const Rva001737C0Element &other)
{
	Rva001737C0View *self = (Rva001737C0View *)this;
	const Rva001737C0View &o = *(const Rva001737C0View *)&other;
	self->m_00 = o.m_00;
	self->m_04 = o.m_04;
	for (int i = 0; i < 6; ++i)
		self->m_08[i] = o.m_08[i];
	return *this;
}
