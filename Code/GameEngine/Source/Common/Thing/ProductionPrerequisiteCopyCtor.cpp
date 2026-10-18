// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ProductionPrerequisite copy ctor, retail 0x002D08DA.
//
// Layout evidence, all retail-measured: the ctor copies member vectors at
// +0x00 (PrereqUnitRec, 12-byte elements: the callee divides the byte count
// by 0x0C), +0x0C (4-byte elements: the callee shifts the byte count right
// by 2) and +0x18 (calls the matched vector<uint> copy at 0x002CFAB9).
// This mirrors the Zero Hour header carried in
// reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/
// ProductionPrerequisiteCopyCtor.cpp (PrereqUnitRec vector, ScienceType
// vector, third vector), 0x24 bytes total like the push_back TU's replica.

#include <vector>

struct PrereqUnitRec
{
	unsigned int m_data[3];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<PrereqUnitRec,allocator<PrereqUnitRec> >::vector(vector<PrereqUnitRec,allocator<PrereqUnitRec> > const &); }

enum ScienceType
{
	SCIENCE_NONE = 0
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite(const ProductionPrerequisite &other);

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<unsigned int> m_unused;
};

typedef char ProductionPrerequisiteCopySizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

inline ProductionPrerequisite::ProductionPrerequisite(const ProductionPrerequisite &other)
	: m_prereqUnits(other.m_prereqUnits)
	, m_prereqSciences(other.m_prereqSciences)
	, m_unused(other.m_unused)
{
}

#pragma inline_depth(0)
// ?bfmeEmitProductionPrerequisiteCopyCtor@@YAXPAVProductionPrerequisite@@ABV1@@Z present-unmatched
void bfmeEmitProductionPrerequisiteCopyCtor(ProductionPrerequisite *p, const ProductionPrerequisite &other)
{
	p->ProductionPrerequisite::ProductionPrerequisite(other);
}
#pragma inline_depth()
