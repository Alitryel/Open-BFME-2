// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// ??A?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@QAEAAUPristineBoneInfo@@ABW4NameKeyType@@@Z
// retail 0x000BCF68, 80 bytes. PristineBoneInfoMap::operator[]: lower_bound on the key (retail
// shares the int/int _M_lower_bound 0x00382A92), and on a miss insert (hint, pair(key, default
// PristineBoneInfo)) through the rowed insert 0x000BC1A5, the rowed pair constructor 0x000B642A
// and the rowed PristineBoneInfo default constructor 0x000423C5. The unchecked-STL flags
// (/EHs, _STLP_NO_EXCEPTIONS) give retail's ebp frame and register roles. Evidence: target bytes and the
// rowed callees; the callers (doSingleBoneName 0x000BD2BF) use the returned reference.
#include <map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

struct PristineBoneInfo
{
	PristineBoneInfo();
	unsigned char m_data[52];
};

struct Rva000B642A
{
	Rva000B642A(const int *p, const PristineBoneInfo &q);
	int m_0;
	PristineBoneInfo m_4;
};

typedef _STL::map<NameKeyType, PristineBoneInfo> PristineBoneInfoMap;
static __forceinline const PristineBoneInfoMap::value_type &asPair(const Rva000B642A &entry)
{
	return *(const PristineBoneInfoMap::value_type *)&entry;
}
typedef _STL::map<int, int> BoneIntMap;

// Retail shares one out-of-line int/int _M_lower_bound (0x00382A92) across the integer-keyed trees.
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > BoneIntTree;
template<> BoneIntTree::_Link_type BoneIntTree::_M_lower_bound(const int &) const;

template<> PristineBoneInfoMap::iterator PristineBoneInfoMap::insert(PristineBoneInfoMap::iterator, const PristineBoneInfoMap::value_type &);

template<> PristineBoneInfo &PristineBoneInfoMap::operator[](const NameKeyType &key)
{
	BoneIntMap::iterator found = ((BoneIntMap *)this)->lower_bound(*(const int *)&key);
	iterator i = *(iterator *)&found;
	if (i == end() || key < (*i).first)
	{
		i = insert(i, asPair(Rva000B642A((const int *)&key, PristineBoneInfo())));
	}
	return (*i).second;
}

// Keeps the specialization referenced so its (inline) body is emitted.
// ?_bfmePristineSubscriptAnchor@@ absent-from-retail
PristineBoneInfo &_bfmePristineSubscriptAnchor(PristineBoneInfoMap *m, const NameKeyType &k)
{
	return (*m)[k];
}
