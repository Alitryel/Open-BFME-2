// cl: /Ireference/shims/moduledata /O1 /GX /arch:SSE /MD /DNDEBUG
// ??1ShareExperienceBehaviorModuleData@@UAE@XZ @ 0x0047FFCE 48B
// Implicit virtual dtor restoring Snapshot base vtable 0x00BBB554 with no
// base call. Member filter at +0x14 via pinned ??1Rva003623E5Filter at
// 0x00360D26. Layout from ctor TU 0x0047FE90 (pad +4 floats +8+C+10 filter
// +14 size 0x18). Vtable 0x008486B0 slot 0 is ??_G 0x0047FFB2.
// DynamicPortalBehaviourModuleDataDtor precedent.
#include "Common/Snapshot.h"
#include <new>

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
class ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleDataBase() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};
class ShareExperienceBehaviorModuleData : public ShareExperienceBehaviorModuleDataBase
{
public:
	ShareExperienceBehaviorModuleData();
// Implicit virtual dtor (never declared, never defined)
private:
	unsigned char m_unk04[4];
	float m_r8;
	float m_rC;
	float m_r10;
	Rva003623E5Filter m_filter;
};
// Same verified76B constructor as the home; select-any emission avoids the
// former strong dummy constructor that conflicted with its actual definition.
// ??0ShareExperienceBehaviorModuleData@@QAE@XZ present-unmatched
inline ShareExperienceBehaviorModuleData::ShareExperienceBehaviorModuleData()
	: m_r8(0.0f), m_rC(0.0f), m_r10(1.0f)
{
}
void deleteShareExperienceBehaviorModuleData(ShareExperienceBehaviorModuleData *p)
{
	delete p;
}

// Force the real inline constructor and its implicit virtual destructor family.
// ?constructShareExperienceBehaviorModuleData absent-from-retail
void constructShareExperienceBehaviorModuleData(void *storage)
{
    ::new (storage) ShareExperienceBehaviorModuleData;
}
