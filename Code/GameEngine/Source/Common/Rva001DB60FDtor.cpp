// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1MetaMap@@UAE@XZ retail 0x001DB60F 91B. Dtor storing vtable 0x007DBA7C
// then clearing a MetaMapRec list at +0xC via rowed dtor 0x001DB48E plus rowed
// operator delete then tailing to rowed SubsystemInterface dtor 0x001B4E74.
// Evidence: vtable store plus rowed callees plus deleting-dtor caller 0x001DB66A.
class MetaMapRec
{
public:
	~MetaMapRec();
	MetaMapRec *m_next;
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class MetaMap : public SubsystemInterface
{
public:
	MetaMap();
	virtual ~MetaMap();
private:
	MetaMapRec *m_head;
};

MetaMap::~MetaMap()
{
	while (m_head != 0) {
		MetaMapRec *next = m_head->m_next;
		delete m_head;
		m_head = next;
	}
}

// ??0MetaMap@@QAE@XZ retail 0x001DB3E8 22B, the matching constructor
// (same vtable 0x007DBA7C; caller 0x0022E2E4): the canonical subsystem base,
// then an empty record list.
MetaMap::MetaMap() : m_head(0)
{
}
