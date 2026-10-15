// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??1Rva003ED1FC@@UAE@XZ @0x003ED1FC 77B
// Dtor: vtable 0x00C36100 store then ArmorTemplateMap clear plus hashtable
// dtor plus SubsystemInterface dtor. Evidence: caller ??_GRva003ED1FC
// at 0x003ED249 in OpaqueScalarDeletingDtorsB07 plus vtable 0x00C36100 slot 0
// plus callees clear 0x001DBCDC plus dup_003ed1be 0x003ED1BE plus base
// 0x001B4E74; ledger notes ThreatFinderManager identity for this copy vs
// ArmorStore 0x00360A45 but no VTABLE line proves a real name so honest Rva
// name keeps the pin.

#include <hash_map>
#include <cstddef>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	unsigned char m_pad04[8];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

// Use the existing table destructor and clear providers. This unit's /O1
// instantiation otherwise emits a different clear/delete-node pair.
namespace _STL
{
typedef pair<const NameKeyType, ArmorTemplate> ManagerMapValue;
typedef hashtable<ManagerMapValue, NameKeyType, rts::hash<NameKeyType>,
	_Select1st<ManagerMapValue>, equal_to<NameKeyType>,
	allocator<ManagerMapValue> > ManagerMapTable;
template <> void ManagerMapTable::clear();
template <> ManagerMapTable::~hashtable();
}
// Existing neutral owner of the complete 72-byte bucket/node cleanup at
// 0x001DBCDC; it touches no payload fields (Rva004E013BOwnedResources.cpp).
class Rva004DFC20 { public: void clear(); };

// Native parent FuncInfo 0x0092F5C0 state 1 uses cleanup 0x007836A4:
// load this, add 0x0C, jump to the 5-byte destructor at 0x003ED1F7.
// That wrapper tail-calls the same table destructor as the normal path.
// Keep its address-derived identity separate from the existing Armor map
// spelling. The map implementation is inherited from this verified unit;
// its original target payload type and source-level wrapper name are unknown.
class Rva003ED1F7
{
	ArmorTemplateMap table;
public:
	void clear() { reinterpret_cast<Rva004DFC20 *>(&table)->clear(); }
};

class Rva003ED1FC : public SubsystemInterface
{
public:
	virtual ~Rva003ED1FC();
private:
	Rva003ED1F7 m_map;
};

// ??1Rva003ED1FC@@UAE@XZ
Rva003ED1FC::~Rva003ED1FC()
{
	m_map.clear();
}
