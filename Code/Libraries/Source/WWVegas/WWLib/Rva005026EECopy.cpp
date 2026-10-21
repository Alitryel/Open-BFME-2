// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??0Rva00502909Sub@@QAE@ABU0@@Z, retail 0x005026EE 153B.
// Subobject copy ctor: 4 ints then 5 vector<ScienceType> then map<int Rva00501E3FElement>.
// Evidence: rowed vector copy 0x0054878E x5 and rowed rb_tree copy 0x00501E88; element copy 0x00502909 tail-calls it; neighbours share stlport /O1 /EHsc flags.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

struct Rva00501E3FElement
{
	int a[5];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree_node<pair<int const ,Rva00501E3FElement> > * _Rb_tree<int,pair<int const ,Rva00501E3FElement>,_Select1st<pair<int const ,Rva00501E3FElement> >,less<int>,allocator<pair<int const ,Rva00501E3FElement> > >::_M_copy(_Rb_tree_node<pair<int const ,Rva00501E3FElement> > *,_Rb_tree_node<pair<int const ,Rva00501E3FElement> > *); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<pair<int const ,Rva00501E3FElement>,pair<int const ,Rva00501E3FElement> >(pair<int const ,Rva00501E3FElement> *,pair<int const ,Rva00501E3FElement> const &); }

struct Rva00501656
{
	Rva00501656(const Rva00501656 &other);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	_STL::vector<ScienceType> m_10;
	_STL::vector<ScienceType> m_1c;
	_STL::vector<ScienceType> m_28;
	_STL::vector<ScienceType> m_34;
	_STL::vector<ScienceType> m_40;
	_STL::map<int, Rva00501E3FElement> m_4c;
};

Rva00501656::Rva00501656(const Rva00501656 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_1c(other.m_1c)
	, m_28(other.m_28)
	, m_34(other.m_34)
	, m_40(other.m_40)
	, m_4c(other.m_4c)
{
}
