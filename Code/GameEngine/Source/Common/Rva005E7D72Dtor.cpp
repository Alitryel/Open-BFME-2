// cl: /O1 /MD /EHsc
//
// ??1Rva005E7D72@@UAE@XZ retail 0x005E7D72 5 bytes.
// A 5-byte jmp to the rowed Rva005E7C19 destructor at 0x005E7C19, `this` unchanged: the
// destructor of a class over that base that adds nothing needing teardown and
// stores no vptr (novtable, the HordeGarrisonContain 0x0047A147 shape). Its
// deleting destructor 0x005E7F94 (rowed in Rva005E7C19Dtor.cpp) and the owned-pointer resets in
// OwnedPointerResets.cpp call it. Owner identity unrecovered (address name).

namespace StrategicHUD { class BuildQueueIconSlot; }
namespace StrategicInGameUI { class BuildQueueDetailsPanel { public: class Impl; }; class BuildQueueDetailsPanel::Impl { public: class Icon; }; }
class StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon
{
public:
	~Icon();
  virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *);
  virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *);
  virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *);
  virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *);
  virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *);
  virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *);
};

class __declspec(novtable) Rva005E7D72 : public StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon
{
public:
	virtual ~Rva005E7D72();
};

Rva005E7D72::~Rva005E7D72()
{
}
