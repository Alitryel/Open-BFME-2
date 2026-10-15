// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// stlport
//
// ??1GeometryUpgradeModuleData@@UAE@XZ, retail 0x004B6F81, 114 bytes.
// ModuleData dtor: destroys the three AsciiStrings at +0x138 (state 4) then
// +0x134 (state 3) then +0x130 (state 2) through the folded StringBase<char>
// teardown at 0x00036410 then the two AsciiString vectors at +0x124 (state 1)
// then +0x118 (state 0) through the rowed 0x2CC70 body then restores the
// canonical Snapshot base vtable 0x00BBB554. Empty derived body with no
// out-of-line base call; the inherited 0x118-byte state has no cleanup here.
// Layout from the rowed ctor 0x004B6EE2
// (base 0x118 via OpenContain 0x253487, vectors at +0x118/+0x124, strings at
// +0x130/+0x134/+0x138, size 0x13C via factory 0x00250642) and table 0x858918.
// Caller is the slot-0 ??_G at 0x004B6F65 (vtable 0x008589F0). Shape follows
// RemoveUpgradeUpgradeModuleDataDtor (inline Snapshot teardown, novtable
// derived, empty body, vectors via 0x2CC70). Canonical Snapshot also makes
// the EH cleanup bind the existing 0x0049B47C destructor provider.
#include "Common/Snapshot.h"

#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

class __declspec(novtable) GeometryUpgradeModuleData : public Snapshot
{
public:
	virtual ~GeometryUpgradeModuleData();

private:
	// The inherited ModuleData state is opaque here; members still start at +0x118.
	unsigned char m_moduleDataState[0x118 - sizeof(Snapshot)];
	_STL::vector<AsciiString> m_showGeometry; // +0x118
	_STL::vector<AsciiString> m_hideGeometry; // +0x124
	AsciiString m_wallBoundsMesh; // +0x130
	AsciiString m_rampMesh1; // +0x134
	AsciiString m_rampMesh2; // +0x138
};

GeometryUpgradeModuleData::~GeometryUpgradeModuleData()
{
}
