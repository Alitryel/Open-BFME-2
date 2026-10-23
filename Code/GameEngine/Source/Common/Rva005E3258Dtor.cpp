// cl: /MD
// ??1RegionDetailsMovieClip@StrategicHUD@@UAE@XZ @0x005E3258 14B
// Virtual dtor storing vtable 0x00877BB4 then tail-jmping to member clear
// 0x005E30CE at +4. Layout from retail add ecx 4: Rva005E30CE subobject at +4.
// Caller 0x005E3271 plus chain from 0x005E30CE. Precedent SubtitleEntry 14B tail-jmp.
// Identity: it installs vtable 0x00877BB4, which the rowed RegionDetailsMovieClip
// ctor 0x005E3463 stores (slots: deleting dtor 0x005E326E, __purecall, 0x0047A69C).
class Rva005E30CE
{
public:
	void rva005E30CE();
};

class AsciiString;
struct TreeHintRef00217D4C;

// All three slots, so this unit's vtable copy equals the ctor unit's.
namespace StrategicHUD {
class RegionDetailsMovieClip
{
public:
	virtual ~RegionDetailsMovieClip();
	virtual TreeHintRef00217D4C CreatePage(int slot, int level, const AsciiString &name) = 0;
	virtual void v2(int page) {}
private:
	Rva005E30CE m_04;
};
}

StrategicHUD::RegionDetailsMovieClip::~RegionDetailsMovieClip()
{
	m_04.rva005E30CE();
}
