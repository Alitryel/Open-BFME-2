// cl: /MD
// ??1ArmyUnitSwapperMovieClip@StrategicHUD@@UAE@XZ @0x005FD9FF 14B
// Virtual dtor storing its vtable then tail-jumping to the +4 holder's rowed
// clear 0x005FD95E (OwnedPointerResets.cpp). Called by the scalar deleting
// dtor 0x005FDA1D, slot 0 of vtable 0x00C7A2E8, the table
// StrategicHUD::ArmyUnitSwapperMovieClip's ctor 0x005FDE24 stores (slots 1..5
// are its notify* handlers). Prev/next share /O1.
class Rva005FD95E
{
public:
	void clear();
};

namespace StrategicHUD {
class ArmyUnitSwapperMovieClip
{
public:
	virtual ~ArmyUnitSwapperMovieClip();
	virtual void notifyClosed();
	virtual void notifyExit();
	virtual void notifyMoveDown();
	virtual void notifyMoveUp();
	virtual void notifySwap();
private:
	Rva005FD95E m_holder; // +0x04 (vptr at +0x00): the owned Impl pointer
};
}

StrategicHUD::ArmyUnitSwapperMovieClip::~ArmyUnitSwapperMovieClip()
{
	m_holder.clear();
}
