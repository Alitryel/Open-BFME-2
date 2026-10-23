// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0053ED1A@@UAE@XZ @0x0053ED78 90B dtor installs vtables plus frees vector buffer plus secondary plus base via caller ??_G 0x0053EF12. Evidence: pin plus vtable slots plus rowed base SubsystemInterface plus twin-pinned secondary Rva005C6D4D at 0x005C6C7B plus rowed _free.
#include <vector>

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// The secondary base (ctor 0x005C6D4D, Rva0053ED1ACtor.cpp's Rva005C6D4D)
// under its destructor's rowed name: ??1Rva005C6C7B@@UAE@XZ at 0x005C6C7B.
class Rva005C6C7B
{
public:
	virtual ~Rva005C6C7B();
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public SubsystemInterface, public Rva005C6C7B
{
public:
	Rva0053ED1A();
	virtual ~Rva0053ED1A();
	// Slots as Rva0053ED1ACtor.cpp lists them, so both units emit one vtable.
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void rva0053EDD2();
private:
	_STL::vector<int> m_at48;
	int m_at54;
	int m_at58;
};

Rva0053ED1A::~Rva0053ED1A()
{
}
