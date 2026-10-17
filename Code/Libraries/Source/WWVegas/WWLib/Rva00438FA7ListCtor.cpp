// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004393D6@@QAE@XZ, 0x00438FA7, 30B. Default ctor of the
// InvisibilityManager record whose map<int, Rva004393D6> subscript is
// 0x00439C73: it calls the STLport list<BfmePod196> base ctor (allocator
// temporary at [esp+7]) and clears the three trailing words at +4 +8 +0xc.
// The record's copy ctor 0x004393D6, assignment 0x004393FD and the other
// per-unit views live in Rva004393D6Copy.cpp, Rva00439C73MapSubscript.cpp and
// the InvisibilityManager units; its destructor is 0x00438FC5 in
// stlport_list_int_dtor.cpp. Renamed from the address placeholder Rva00438FA7
// so the units that spell the record Rva004393D6 resolve this body -- that is
// what retired their /alternatename. Bytes unchanged under the rename.
#include <list>

struct BfmePod196 { int a[49]; };

class Rva004393D6 : public _STL::list<BfmePod196>
{
public:
	Rva004393D6();
	~Rva004393D6();
private:
	int m_04;
	int m_08;
	int m_0c;
};

Rva004393D6::Rva004393D6()
	: _STL::list<BfmePod196>(_STL::allocator<BfmePod196>())
{
	m_04 = 0;
	m_08 = 0;
	m_0c = 0;
}
