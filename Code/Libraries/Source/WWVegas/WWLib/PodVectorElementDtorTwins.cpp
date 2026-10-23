// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Destructors of container elements whose only owning member is a vector of
// 4-byte PODs at +0. Each compiles to the 14-byte free-the-first-pointer body
// that retail folds into vector<int>'s destructor at 0x0007FAB3; the element
// units call them by these names.
#include <vector>

// Element of the STLport sweep at 0x0054FE47: 12 bytes, the vector itself.
struct Rva0054FE47Record
{
	_STL::vector<int> m_00;
	~Rva0054FE47Record();
};

Rva0054FE47Record::~Rva0054FE47Record()
{
}

// List element of the STLport sweep at 0x0042438D; retail destroys it
// through the same fold, so the vector is at +0.
struct Rva0042438DElement
{
	_STL::vector<int> m_00;
	~Rva0042438DElement();
};

Rva0042438DElement::~Rva0042438DElement()
{
}
