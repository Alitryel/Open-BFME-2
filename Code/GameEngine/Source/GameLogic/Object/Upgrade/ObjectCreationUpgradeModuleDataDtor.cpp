// cl: /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1ObjectCreationUpgradeModuleData@@UAE@XZ, retail 0x004B45E8, 84 bytes.
// ModuleData dtor: destroys the three AsciiStrings at +0x128 (state 2) then
// +0x124 (state 1) then +0x120 (state 0) through the folded StringBase<char>
// teardown at 0x00036410 then restores the Snapshot base vtable 0x00BBB554.
// Empty derived body with inline canonical base teardown; the inherited
// 0x120-byte state has no cleanup here. Layout from the rowed ctor 0x004B425B (base 0x120 via OpenContain
// 0x25342C, strings at +0x120/+0x124/+0x128, size 0x154 via factory
// 0x0024FFAC) and own vtable 0x00C577C8. Caller is the slot-0 ??_G at
// 0x004B45CC (vtable 0x00C577C8). Shape follows GeometryUpgradeModuleDataDtor
// (canonical inline Snapshot teardown, novtable derived, empty body, strings
// via 0x36410). The shared base also supplies the native EH cleanup target.

#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) ObjectCreationUpgradeModuleData : public Snapshot
{
public:
	virtual ~ObjectCreationUpgradeModuleData();

private:
	// Opaque inherited state; the first owned string remains at +0x120.
	unsigned char m_moduleDataState[0x120 - sizeof(Snapshot)];
	AsciiString m_removeUpgrade; // +0x120
	AsciiString m_grantUpgrade; // +0x124
	AsciiString m_thingToSpawn; // +0x128
	unsigned char m_tail[0x154 - 0x12C]; // +0x12C..+0x153 trivial tail
};

ObjectCreationUpgradeModuleData::~ObjectCreationUpgradeModuleData()
{
}
