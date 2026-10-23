// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/reference/shims/asciistring_downloadmanager /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Weapon SparseMatchFinder tree lookup: _M_find at 0x0033AF5F (92 bytes)
// and const find at 0x0033B81C (20 bytes). Native _M_find calls the verified
// 21-bit comparator 0x0033AD5C and reads the key at node +0x10.
// Keep the comparator's read-only body visible and noinline: an opaque
// declaration changes MSVC7.1 purity assumptions and lookup code generation.
// BitFlags<17> retains the established ledger spelling; the native loop bound
// is 21, not an inference about the original template argument.
// STLport 4.5.3 and pinned Zero Hour SparseMatchFinder.h supply the algorithms.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define BitFlags RealBitFlags   // keep the reference header's template out of the way
#include "PreRTS.h"
#include "Common/AsciiString.h"
#undef BitFlags

class WeaponTemplateSet;

template <int Bits>
class BitFlags
{
public:
	unsigned int m_flagWords[(Bits + 31) / 32];
};

template <class Set, class Flags>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		__declspec(noinline) bool operator()(const Flags &a, const Flags &b) const
		{
			for (int i = 0; i < 21; ++i)
			{
				bool aBit = (a.m_flagWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
				bool bBit = (b.m_flagWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
				if (aBit && bBit)
					continue;
				if (!aBit && !bBit)
					continue;
				if (!aBit)
					return true;
				return false;
			}
			return false;
		}
	};
};

typedef BitFlags<17> WeaponSetFlags;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair,
	_STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper,
	_STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;

// The real 24-byte-node creator is verified in Rva002CF86FCreate.cpp.
// Avoid emitting this donor instantiation's different allocation/copy body.
template <> WeaponTemplateSetTree::_Link_type
WeaponTemplateSetTree::_M_create_node(const WeaponTemplateSetPair &);

template WeaponTemplateSetTree::iterator
WeaponTemplateSetTree::insert_unique( WeaponTemplateSetTree::iterator,
	const WeaponTemplateSetPair & );

// The insertion owners at 0x0033C176/0x0033C646 are verified in
// stlport_rb_tree_0033c646_insert.cpp; retain their identical instantiations.
template _STL::pair<WeaponTemplateSetTree::iterator, bool> WeaponTemplateSetTree::insert_unique( const WeaponTemplateSetPair & );
const WeaponTemplateSetPair *bfmeFindAnchorWeaponTemplateSetTree( const WeaponTemplateSetTree &tree, const WeaponSetFlags &key )
{
	WeaponTemplateSetTree::const_iterator it = tree.find( key );
	if ( it == tree.end() )
		return 0;
	return &( *it );
}
