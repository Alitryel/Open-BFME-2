// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0021FFEE..00220105 (279B), vtable BE648C slot0's complete dtor.
// Target offsets and EH states establish the member destruction order below.
// CreateAHeroData's independently rowed provider establishes its 140B extent;
// container spellings follow the existing verified destructor providers.
// Lead: Rva0038454E's many-member destructor in Rva003844D7Dtor.cpp.
#include <vector>
#include <map>
#include "ascii_string.h"

// SubsystemInterface's fourteen-slot BFME2 view, shared with the constructor
// unit so both emit one CreateAHeroManager vftable (0x00BE648C).
typedef bool Bool;
#include "subsystem_interface.h"

class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
private:
	char m_storage04[0x13c];
};

struct BfmePod216 { int a[54]; };


struct Rva0021DA18
{
	~Rva0021DA18();
	char m_storage[12];
};
struct Rva0021DA57
{
	~Rva0021DA57();
	char m_storage[12];
};

// Retain the existing provider's opaque value spelling. This parent observes
// the tree header and cleanup ABI, and supplies no new claim about its payload.
struct Rva0040A603Record { char bytes[1]; };
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva0040A603Record>,
	_STL::_Select1st<_STL::pair<const int, Rva0040A603Record> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva0040A603Record> > > CleanupTree;
template <> CleanupTree::~_Rb_tree();
template <> void CleanupTree::clear();

class Rva0040A59B
{
public:
	void rva0040A59B();
};

// CreateAHeroManager (formerly the Rva0021FFEE placeholder): its constructor
// 0x0021FE49 installs vftable 0x00BE648C, whose slot 0 is this destructor's
// scalar deleting destructor 0x002201B9. Retail slots: 1 init, 2 a `return
// true` loadIniFilesFromLegend (0x0050B5C6), 9 reset and 10 update both the
// folded empty body 0x000B3FD0; the other slots keep the base's.
class CreateAHeroManager : public SubsystemInterface
{
public:
	// The named, independently rowed 00219C1F accessor views the same 32B class
	// record and its 216B subclass range. Keep the existing container spelling.
	class CreateAHeroClass
	{
	public:
		int GetAwardCount(unsigned int subClassIndex);
		CreateAHeroClass(const CreateAHeroClass &);
		~CreateAHeroClass();
		AsciiString m_strings[5];
		_STL::vector<BfmePod216> m_subclasses;
	};

	virtual ~CreateAHeroManager();
	virtual void init();
	// ?loadIniFilesFromLegend@CreateAHeroManager present-unmatched
	virtual Bool loadIniFilesFromLegend() { return true; }
	// ?reset@CreateAHeroManager present-unmatched
	virtual void reset() {}
	// ?update@CreateAHeroManager present-unmatched
	virtual void update() {}
	CreateAHeroClass *rva0022020C(CreateAHeroClass &entry);
private:
	CreateAHeroData m_hero0C;
	_STL::vector<CreateAHeroClass> m_vector14C;
	int m_158;
	Rva0021DA18 m_vector15C;
	Rva0021DA57 m_vector168;
	CleanupTree m_tree174;
	char m_pad180[8];
	AsciiString m_text188, m_text18C, m_text190;
	char m_pad194[0x30];
	AsciiString m_text1C4, m_text1C8, m_text1CC;
	int m_1D0;
	unsigned int m_maxAwards1D4;
	int m_1D8;
	AsciiString m_text1DC;
	int m_state1E0;
	int m_1E4;
	AsciiString m_text1E8, m_text1EC;
};

template <> _STL::vector<CreateAHeroManager::CreateAHeroClass>::~vector();
template <> void _STL::vector<CreateAHeroManager::CreateAHeroClass>::push_back(const CreateAHeroManager::CreateAHeroClass &);

CreateAHeroManager::~CreateAHeroManager()
{
	m_state1E0 = 0;
	reinterpret_cast<Rva0040A59B *>(&m_tree174)->rva0040A59B();
}

// Native 0022020C..002202BF (179B): reuse an existing entry by its fifth
// string, or append a copy and update the maximum subclass award count.
// Binding the name to a reference first is what lets retail's index share
// the dead argument slot (and its strength-reduced offset take [ebp-4]).
CreateAHeroManager::CreateAHeroClass *CreateAHeroManager::rva0022020C(CreateAHeroClass &entry)
{
	const AsciiString &name = entry.m_strings[4];
	for (int i = 0; i < m_vector14C.size(); ++i)
		if (name.compareNoCase(m_vector14C[i].m_strings[4]) == 0)
			return &m_vector14C[i];
	m_vector14C.push_back(entry);
	for (int i = 0; i < entry.m_subclasses.size(); ++i)
	{
		unsigned int count = reinterpret_cast<CreateAHeroManager::CreateAHeroClass *>(&entry)->GetAwardCount(i);
		if (m_maxAwards1D4 < count)
			m_maxAwards1D4 = count;
	}
	return m_vector14C.end() - 1;
}
