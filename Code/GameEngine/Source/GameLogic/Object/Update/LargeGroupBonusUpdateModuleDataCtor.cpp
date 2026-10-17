// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ow
// stlport
// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ, retail 0x004901BD, 104 bytes.
//
// Constructor of the module data (companion of the dtor TU
// LargeGroupBonusUpdateModuleDataDtor.cpp, which keeps the dtor-ful member
// declarations; this TU keeps dtor-less ones for retail's single-state frame).
// /Ow (assume no aliasing across calls) lets the update-rate global load
// (0x00A03994, frame-rate init) float above the vtable and state stores as in
// retail; the barrier at the end keeps the EH-chain restore behind the last
// member store.
#include <vector>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
// bfme link decl-only end
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
class UpdateModuleData
{
public:
	UpdateModuleData() {}
	virtual ~UpdateModuleData();
};
extern int g_00E03994;	// owned by Rva007ABC6FFrameRateInits.cpp (frame-rate inits)
class LargeGroupBonusUpdateModuleData : public UpdateModuleData
{
public:
	LargeGroupBonusUpdateModuleData();
	virtual ~LargeGroupBonusUpdateModuleData();
private:
	int m_unused04;
	int m_updateRate;
	Rva003623E5Filter m_hordeMemberFilter;
	int m_count;
	float m_radius;
	bool m_alliesOnly;
	float m_rubOffRadius;
	_STL::vector<AsciiString> m_flagSubObjectNames;
	AsciiString m_attributeModifier;
};
// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ @0x004901BD
LargeGroupBonusUpdateModuleData::LargeGroupBonusUpdateModuleData() :
	m_updateRate(g_00E03994),
	m_count(0),
	m_radius(0.0f),
	m_alliesOnly(true),
	m_rubOffRadius(20.0f)
{
	_ReadWriteBarrier();
}
