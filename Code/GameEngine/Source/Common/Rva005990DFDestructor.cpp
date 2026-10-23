// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva005990DF@@UAE@XZ, retail 0x005990DF..0x00599151 (114 bytes, EH). The
// skirmish AI unit upgrader wrapper (vtable 0x00C70D44 and, at +0x0C, the
// AIUnitUpgrader object with its own vtable 0x00C70D38): the destructor shuts
// the upgrader down (rowed shutdown 0x0059904A), frees its two vectors at
// +0x14 / +0x20, restores the builder base (0x00506B28) and the first base's
// vftable (0x004EA016 for unwinding). Same shape as Rva00597BD4Destructor.cpp.
#include <vector>

enum ObjectID { INVALID_ID = 0 };

class Gen_uwm_004ea016
{
public:
	// Retail vtable 0x00862888 holds __purecall here.
	virtual void slot00() = 0;
	~Gen_uwm_004ea016() {}
private:
	char m_pad[8];
};

// The base is Rva00506B1B (ctor 0x00506B1B, vtable 0x00863F9C); its
// destructor is the 7-byte vptr store at 0x00506B28.
class Rva00506B1B
{
public:
	virtual ~Rva00506B1B();
};

class AIUnitUpgrader
{
public:
	void shutdown();
};

class Rva005990DF : public Gen_uwm_004ea016, public Rva00506B1B
{
public:
	virtual ~Rva005990DF();
private:
	char m_pad10[0x14 - 0x10];
	_STL::vector<ObjectID> m_vec14;
	_STL::vector<ObjectID> m_vec20;
};

Rva005990DF::~Rva005990DF()
{
	((AIUnitUpgrader *)static_cast<Rva00506B1B *>(this))->shutdown();
}
