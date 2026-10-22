// cl: -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// Retail's caller at 0x00451E60 supplies the bidirectional iterator tag and
// reaches this __partition body through the ILT at 0x00043004. The earlier
// synthetic __uninitialized_copy pin cannot describe the in-place pointer
// swaps; the three byte fields and six mask bits are all directly observable.
#include <algorithm>

struct Rva00450B90Item
{
	char m_beforeFlags[0x24];
	bool m_flag24;
	bool m_flag25;
	bool m_flag26;
};

class Rva00450B90Predicate
{
public:
	bool operator()(const Rva00450B90Item *item) const
	{
		if (!(((m_mask & 1) && item->m_flag26) ||
		      ((m_mask & 2) && !item->m_flag26)))
			return false;

		return !((item->m_flag24 && (m_mask & 4)) ||
		         (!item->m_flag24 && (m_mask & 8)) ||
		         (item->m_flag25 && (m_mask & 0x10)) ||
		         (!item->m_flag25 && (m_mask & 0x20)));
	}

	unsigned int m_mask;
};

typedef Rva00450B90Item **(*Rva00450B90PartitionFn)(
	Rva00450B90Item **, Rva00450B90Item **, Rva00450B90Predicate);

Rva00450B90PartitionFn Rva00450B90PartitionAnchor =
	&_STL::partition<Rva00450B90Item **, Rva00450B90Predicate>;
