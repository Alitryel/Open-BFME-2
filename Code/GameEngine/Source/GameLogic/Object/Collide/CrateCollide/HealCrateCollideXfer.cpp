// cl: /DNDEBUG /MD
//
// ?xfer@HealCrateCollide@@MAEXPAVXfer@@@Z @0x004BD2F9 27B: slot 3 (offset 0x0C)
// of vtable 0x0085A868 (class of ??0HealCrateCollide at 0x004BC80F) and five
// ICF-twin vtables 0x0085A8A0/0x0085A8D8/0x0085A914/0x0085A954/0x0085A9C0
// (Money/Shroud/Unit/Veterancy/Salvage CrateCollide). Version1 via rowed
// 0x000053EE then base CrateCollide xfer via rowed 0x004BC617; no extra
// members. Donor is ZH CrateCollide::xfer pattern; BFME2 derived empties
// fold to this Version1-plus-base shape.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
#include "../../../../../Include/Common/BfmeXfer.h"
class BehaviorModule
{
public:
    BehaviorModule(Thing *thing, const ModuleData *moduleData);
    virtual void behaviorModuleAnchor();
private:
    unsigned char m_data[8];
};
class InlineCollideModuleInterface
{
public:
    virtual void collideModuleInterfaceAnchor();
};
class ModuleInterface
{
public:
    virtual void moduleInterfaceAnchor();
};
class CollideModule : public BehaviorModule,
    public InlineCollideModuleInterface,
    public ModuleInterface
{
public:
    CollideModule(Thing *thing, const ModuleData *moduleData);
    void xfer(Xfer *xfer);
};
class CrateCollide : public CollideModule
{
public:
    CrateCollide(Thing *thing, const ModuleData *moduleData);
protected:
    virtual void xfer(Xfer *xfer);
private:
    bool m_everExecuted;
};
class HealCrateCollide : public CrateCollide
{
public:
    HealCrateCollide(Thing *thing, const ModuleData *moduleData);
protected:
    virtual void xfer(Xfer *xfer);
};
void HealCrateCollide::xfer(Xfer *xfer)
{
    xfer->Version1();
    CrateCollide::xfer(xfer);
}
