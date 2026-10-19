// cl: /O1 /EHsc /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common
// Class identity recovered from factory 0x24F362 and ctor 0x4ABED8 sharing
// vtable 0xC549F8; the address-derived owner is now LargeGroupAudioUpdateModuleData.
// ??1LargeGroupAudioUpdateModuleData@@UAE@XZ @0x004ABFD9 72B.
// Dtor with EH prolog removing itself from global Rva004ABFB2 registry then
// member at +8 then Snapshot base BBB554 restore. Evidence: vptr 0x00C549F8
// then global 0x00E03CE0 as this plus this as int key rowed 0x004ABFB2;
// lea member pin 0x003ED94F; second vptr 0x00BBB554 (??_7Snapshot) shared by 12 TUs;
// deleting dtor 0x004AC021 calls here; slot 0 vtable 0x008549F8 class ctor.
class Xfer;
#include "Common/Snapshot.h"
#include "BfmeModuleData.h"
// Native table has the shared 31-slot ModuleData interface, ending at 0xC54A74.
// Native teardown then restores Snapshot table 0xBBB554; original intermediate
// inheritance and the meaning of the word at +4 remain unrecovered.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
class Rva004ABFB2
{
public:
	void rva004ABFB2(int key);
};
struct Rva00E03CE0;
// Existing data-ledger owner; use typed views of the one registry datum.
extern unsigned g_Va00E03CE0;
class Rva003ED94FDtor
{
public:
	~Rva003ED94FDtor();
    unsigned char m_payload[12];
};
class LargeGroupAudioUpdateModuleData : public ModuleData
{
public:
	virtual __declspec(noinline) ~LargeGroupAudioUpdateModuleData();
private:
	char m_pad04[4];
	Rva003ED94FDtor m_08;
    int m_min; int m_variance; unsigned short m_weight;
};
LargeGroupAudioUpdateModuleData::~LargeGroupAudioUpdateModuleData()
{
	reinterpret_cast<Rva004ABFB2 *>(&g_Va00E03CE0)->rva004ABFB2((int)this);
}
