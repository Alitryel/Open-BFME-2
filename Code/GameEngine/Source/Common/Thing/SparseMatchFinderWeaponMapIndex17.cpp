// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??A?$map@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@UMapHelper@... @0x0033D19B 88B
// STLport 4.5.3 map::operator[] for the weapon SparseMatchFinder map. Retail calls the
// rowed _M_lower_bound 0x0033B7D0 and comparator 0x0033AD5C, copies the key through the
// rowed out-of-line fixed-storage copy 0x002CF0F0, and inserts through the shared hint
// insert wrapper 0x0033CBAD whose ledger name is the int-keyed instantiation (ICF).
#define _STLP_NO_EXCEPTIONS
#include <map>
class WeaponTemplateSet;

class BfmeFixedStorage002CF0F0 {
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};

template <int BitCount>
class BitFlags
{
public:
	unsigned int m_flagWords[(BitCount + 31) / 32];
	__forceinline BitFlags(const BitFlags &that)
	{
		new (this) BfmeFixedStorage002CF0F0(*reinterpret_cast<const BfmeFixedStorage002CF0F0 *>(&that));
	}
};
template <class MatchableType, class FlagSet>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		// ?MapHelper::operator() present-unmatched
		bool operator()(const FlagSet &a, const FlagSet &b) const
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
typedef BitFlags<17> WeaponFlags17;
typedef _STL::pair<const WeaponFlags17, const WeaponTemplateSet *> WeaponPair17;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags17>::MapHelper WeaponMapHelper17;
typedef _STL::map<const WeaponFlags17, const WeaponTemplateSet *, WeaponMapHelper17,
	_STL::allocator<WeaponPair17> > WeaponMap17;

struct Rva0033CBADRecord { char bytes[1]; };
typedef _STL::map<int, Rva0033CBADRecord, _STL::less<int>,
	_STL::allocator<_STL::pair<const int, Rva0033CBADRecord> > > Rva0033CBADMap;
namespace _STL {
template <> __forceinline WeaponPair17::pair(const WeaponFlags17 &k, const WeaponTemplateSet *const &v) : first(k), second(v) {}
template <> Rva0033CBADMap::iterator Rva0033CBADMap::insert(iterator, const value_type &);
typedef Rva0033CBADMap::iterator (Rva0033CBADMap::*IntInsertFn)(Rva0033CBADMap::iterator, const Rva0033CBADMap::value_type &);
typedef WeaponMap17::iterator (Rva0033CBADMap::*WeaponInsertFn)(WeaponMap17::iterator, const WeaponMap17::value_type &);
template <> __forceinline WeaponMap17::iterator WeaponMap17::insert(iterator pos, const value_type &value)
{
	IntInsertFn real = &Rva0033CBADMap::insert;
	return (reinterpret_cast<Rva0033CBADMap *>(this)->*reinterpret_cast<WeaponInsertFn &>(real))(pos, value);
}
}
template const WeaponTemplateSet *&WeaponMap17::operator[](const WeaponFlags17 &);
