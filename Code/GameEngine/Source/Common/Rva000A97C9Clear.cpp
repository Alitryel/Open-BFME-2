// cl: /MD /EHsc /DNDEBUG
// ?rva000A97C9@@YAXAAU?$pair@$$CBHUGen_t_00786db0_p12cd@@@_STL@@@Z @0x000A97C9 35B:
// explicit destroy-and-clear of one hash_map entry. ~Rva00787C20 (0x000AAE59)
// passes it to for_each over its first hash_map<int, 12-byte value> (+0x08),
// so it takes the map's pair by reference. Runs the value's object slot0 probe
// (or null) through the rowed operator delete, then clears the slot. Honest
// address-derived names; boundary verified (frameless at 0xA97C9, ret at end).
void operator delete(void *p);
class Rva000A97C9Sub {
public:
	virtual void *vslot0(int v);
};
struct Gen_t_00786db0_p12cd {
	Rva000A97C9Sub *m_object;
	int m_unknown[2];
};
namespace _STL {
template <class T1, class T2> struct pair { T1 first; T2 second; };
}
void rva000A97C9(_STL::pair<const int, Gen_t_00786db0_p12cd> &entry)
{
	Rva000A97C9Sub *p = entry.second.m_object;
	::operator delete(p ? p->vslot0(0) : 0);
	entry.second.m_object = 0;
}
