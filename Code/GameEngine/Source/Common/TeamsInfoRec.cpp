// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail TeamsInfoRec owns the pair-keyed team index and a 12-byte vector.
// Constructor and cleanup declarations bind to their existing rowed owners.

// stlport
#include <map>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Rva00196D90Element;
typedef _STL::pair<AsciiString, AsciiString> TeamKey;
typedef _STL::map<TeamKey, int> TeamIndex;
namespace _STL {
template <> map<TeamKey, int>::map();
template <> _Rb_tree<TeamKey, pair<const TeamKey, int>, _Select1st<pair<const TeamKey, int> >, less<TeamKey>, allocator<pair<const TeamKey, int> > >::~_Rb_tree();
template <class Type, class Alloc> class vector
{
public:
	explicit vector(unsigned int);
private:
	Type *m_begin;
	Type *m_end;
	Type *m_storage;
};
}

class TeamsInfoRec
{
public:
	TeamsInfoRec();

private:
	TeamIndex m_tree;
	_STL::vector<Rva00196D90Element, _STL::allocator<Rva00196D90Element> > m_member;
	short m_a;
	short m_b;
};

TeamsInfoRec::TeamsInfoRec()
	: m_member(1)
{
	m_a = 0;
	m_b = 0;
}
