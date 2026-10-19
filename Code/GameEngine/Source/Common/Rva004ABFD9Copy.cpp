// cl: /EHsc /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common
#include "Common/Snapshot.h"
#include "BfmeModuleData.h"
// Native table has the shared 31-slot ModuleData interface, ending at 0xC54A74.
// Native teardown then restores Snapshot table 0xBBB554; original intermediate
// inheritance and the meaning of the word at +4 remain unrecovered.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
// Class identity recovered from factory 0x24F362 and ctor 0x4ABED8 sharing
// vtable 0xC549F8; the address-derived owner is now LargeGroupAudioUpdateModuleData.
//
// ??0LargeGroupAudioUpdateModuleData@@QAE@ABV0@@Z @0x004ABF47 102B: copy constructor of the class
// whose destructor is the rowed ??1LargeGroupAudioUpdateModuleData (0x004ABFD9, vtable 0x00C549F8
// slot 0 via ??_GLargeGroupAudioUpdateModuleData 0x004AC021). It copies the polymorphic base
// through the rowed address-derived base copy constructor 0x004ABCE6
// (the original base identity is still unknown), installs vtable
// 0x00C549F8, copies the member at +8 (rowed Rva003ED658 copy 0x003ED658) and
// three plain fields, then inserts itself into the global registry 0x00E03CE0
// (rowed Rva00E03CE0::Rva004ABEAE 0x004ABEAE). Identities are address-derived.

struct __declspec(novtable) Rva001408C0Target : public ModuleData
{
	Rva001408C0Target(const Rva001408C0Target &other);
	virtual ~Rva001408C0Target();

	int m_04;
};

struct Rva00E03CE0
{
	void Rva004ABEAE(Rva001408C0Target *key);
};

// Existing data-ledger owner; use typed views of the one registry datum.
extern unsigned g_Va00E03CE0;

class Rva003ED658
{
public:
	Rva003ED658(const Rva003ED658 &other);
	~Rva003ED658();

private:
	char m_pad[0xC];
};

class LargeGroupAudioUpdateModuleData : public Rva001408C0Target
{
public:
	LargeGroupAudioUpdateModuleData(const LargeGroupAudioUpdateModuleData &other);
	virtual __declspec(noinline) ~LargeGroupAudioUpdateModuleData();

private:
	Rva003ED658 m_08;
	int m_14;
	int m_18;
	short m_1C;
};

LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData(const LargeGroupAudioUpdateModuleData &other) :
	Rva001408C0Target(other),
	m_08(other.m_08),
	m_14(other.m_14),
	m_18(other.m_18),
	m_1C(other.m_1C)
{
	reinterpret_cast<Rva00E03CE0 *>(&g_Va00E03CE0)->Rva004ABEAE(this);
}

inline Rva001408C0Target::~Rva001408C0Target() {}
