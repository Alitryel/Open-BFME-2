// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ICF twin of ??4ProductionPrerequisite@@QAEAAV0@ABV0@@Z (0x0042816E,
// ThingFactory.cpp): the element of the STLport sweep at 0x0042830D is the
// same record (Zero Hour's prerequisite units and sciences vectors), and its
// assignment is that body. The member vectors' assignments stay out of line.
#include <vector>

class ProductionPrerequisite { public: struct PrereqUnitRec; };
typedef ProductionPrerequisite::PrereqUnitRec PrereqUnitRec;
enum ScienceType { SCIENCE_INVALID = -1 };

namespace _STL {
template<> vector<PrereqUnitRec, allocator<PrereqUnitRec> > &vector<PrereqUnitRec, allocator<PrereqUnitRec> >::operator=(const vector<PrereqUnitRec, allocator<PrereqUnitRec> > &);
template<> vector<ScienceType, allocator<ScienceType> > &vector<ScienceType, allocator<ScienceType> >::operator=(const vector<ScienceType, allocator<ScienceType> > &);
}

struct Rva0042830DElement
{
	_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > m_prereqUnits;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_prereqSciences;
	Rva0042830DElement &operator=(const Rva0042830DElement &other);
};

Rva0042830DElement &Rva0042830DElement::operator=(const Rva0042830DElement &other)
{
	m_prereqUnits = other.m_prereqUnits;
	m_prereqSciences = other.m_prereqSciences;
	return *this;
}
