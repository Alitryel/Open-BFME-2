// cl: /O1 /EHsc /MD /Ireference/shims/moduledata
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
class Rva004ABFB2
{
public:
	void rva004ABFB2(int key);
};
extern Rva004ABFB2 g_00E03CE0;
class Rva003ED94FDtor
{
public:
	~Rva003ED94FDtor();
};
class LargeGroupAudioUpdateModuleData : public Snapshot
{
public:
	virtual ~LargeGroupAudioUpdateModuleData();
private:
	char m_pad04[4];
	Rva003ED94FDtor m_08;
};
LargeGroupAudioUpdateModuleData::~LargeGroupAudioUpdateModuleData()
{
	g_00E03CE0.rva004ABFB2((int)this);
}
