// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Isolated unresolved range-erase wrapper; retain its existing typed callee.
// Retail 0x00056B0A, 42 bytes. See damagefx-erase-link-20261023-codex5.md.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class DamageFX
{
public:
	int m_valueWords[0x1E0];
};

inline bool operator==(const DamageFX &x, const DamageFX &y)
{
	return x.m_valueWords[0] == y.m_valueWords[0];
}

namespace rts
{

template <class _Key>
struct hash
{
};

template <>
struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const
	{
		const unsigned int *words = (const unsigned int *)&key;
		return (words[1] << 16) + words[0];
	}
};

template <class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}

typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > DamageFXMap;

// Instantiate the owned operations, avoiding unused whole-map definitions.
typedef _STL::pair<const NameKeyType, DamageFX> DamageFXPair;
typedef _STL::hashtable<DamageFXPair, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<DamageFXPair>, rts::equal_to<NameKeyType>,
    _STL::allocator<DamageFXPair> > DamageFXTable;
namespace _STL {
template <> void DamageFXTable::erase(DamageFXTable::const_iterator, DamageFXTable::const_iterator);
}
template void DamageFXMap::erase(DamageFXMap::iterator, DamageFXMap::iterator);
