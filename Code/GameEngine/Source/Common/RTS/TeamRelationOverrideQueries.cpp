// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x003A10C0 and 0x003A10DF (31 bytes each, RET 4), between the rowed
// Team::getTeamTargetObject 0x003A105B and Team::deleteTeam 0x003A10FE: each
// asks whether one of the team's relation maps (+0x118, then +0x11C; Zero
// Hour's Team keeps m_teamRelations then m_playerRelations) holds an entry
// for the id, through the shared hash_map<int, Relationship> _M_find
// 0x002888D4, as Player::getRelationship (PlayerGetRelationship.cpp) does on
// the player's maps. The relation map keeps its vtable at +0 and the
// hash_map at +4. Which override query each one is in BFME 2 is not
// established; the names are address-derived.
#include <hash_map>

// The hash table's bucket-vector begin()/size() const copies here differed
// from retail's; declared imported and force-inlined they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> > TeamRelationMapType;

struct RetailTeamRelationMap
{
	void *m_vtbl;
	TeamRelationMapType m_map;
};

class Team
{
public:
	bool rva003A10C0(int id) const;
	bool rva003A10DF(int id) const;
private:
	char m_pad00[0x118];
	RetailTeamRelationMap *m_teamRelations;		// +0x118
	RetailTeamRelationMap *m_playerRelations;	// +0x11C
};

bool Team::rva003A10C0(int id) const
{
	return m_teamRelations->m_map.find(id) != m_teamRelations->m_map.end();
}

bool Team::rva003A10DF(int id) const
{
	return m_playerRelations->m_map.find(id) != m_playerRelations->m_map.end();
}
