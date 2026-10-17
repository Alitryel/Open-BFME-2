// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva004393D6@@QAE@XZ, retail 0x00438FC5, 47 bytes.
// Non-virtual destructor of the InvisibilityManager record whose default ctor
// is 0x00438FA7 (Rva00438FA7ListCtor.cpp) and whose map<int, Rva004393D6>
// subscript is 0x00439C73: the body explicitly clears the list<BfmePod196> base
// and then runs the base destructor, with the EH frame those two destructible
// steps need. The element type is fixed by the record's copy ctor 0x004393D6
// (list copy 0x004392CD plus the three ints at +4 +8 +0xc), by the map's value
// type, and by the published STLport list<BfmePod196> bodies in
// stlport_pod_list_bodies.cpp. Renamed from the address placeholder Rva00438FC5
// so the units that spell the record Rva004393D6 resolve this body -- that is
// what retired their /alternatename. Bytes unchanged under the rename: the
// clear/base-dtor pair is the same code for any element type (ICF-folded) and
// is what the EH graph rows 0x00788160/0x00788168 describe.
#include <list>

struct BfmePod196 { int a[49]; };

class Rva004393D6 : public _STL::list<BfmePod196>
{
public:
	~Rva004393D6();
private:
	int m_04;
	int m_08;
	int m_0c;
};

Rva004393D6::~Rva004393D6()
{
	clear();
}
