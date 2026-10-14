// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002B91BBElement {Rva002B91BBElement();Rva002B91BBElement(const Rva002B91BBElement&);Rva002B91BBElement&operator=(const Rva002B91BBElement&);~Rva002B91BBElement(){}char bytes[52]; bool operator==(const Rva002B91BBElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva002B91BBElement * _STL::__copy<Rva002B91BBElement *, Rva002B91BBElement *, int>(Rva002B91BBElement *, Rva002B91BBElement *, Rva002B91BBElement *, _STL::random_access_iterator_tag const &, int *);

// ICF twin of ??4BfmeAssignRecord52@@QAEAAU0@ABU0@@Z (0x002B828A,
// BfmeAssignRecord52Assign.cpp): the same 52-byte record assignment, so the
// copy loop above binds a definition. The member vector's assignment is the
// owner's external instantiation, declared here so this unit emits none.
struct Rva0040DC56Element;
namespace _STL {
template <> vector<Rva0040DC56Element> &vector<Rva0040DC56Element>::operator=(const vector<Rva0040DC56Element> &);
}
class Rva002B5558
{
public:
	Rva002B5558 &operator=(const Rva002B5558 &other);
private:
	char m_pad[8];
};

struct Rva002B91BBView
{
	Rva002B5558 m_00;
	char m_pad08[4];
	_STL::vector<Rva0040DC56Element> m_0C;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

Rva002B91BBElement &Rva002B91BBElement::operator=(const Rva002B91BBElement &o)
{
	Rva002B91BBView *self = (Rva002B91BBView *)this;
	const Rva002B91BBView &other = *(const Rva002B91BBView *)&o;
	self->m_00 = other.m_00;
	self->m_0C = other.m_0C;
	self->m_18 = other.m_18;
	self->m_1C = other.m_1C;
	self->m_20 = other.m_20;
	self->m_24 = other.m_24;
	self->m_28 = other.m_28;
	self->m_2C = other.m_2C;
	self->m_30 = other.m_30;
	return *this;
}
