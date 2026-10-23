// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?doFXPos@ParticleSystemFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// retail 0x001E19CE, 26 bytes (formerly rowed under the donor's free-function
// spelling ?bfmeGoFHG@@YGXPAX000@Z, the same bytes). Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv897.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// The callee is retail's REL32 at 0x001E19E0 (next-instruction 0x001E19E5
// plus 0x00000003): 0x001E19E8, the rowed ParticleSystemFXNugget::reallyDoFX.
// Target identity (retail evidence, independent of the donor): the
// ParticleSystemFXNugget vtable at VA 0x00BDD908 holds 0x001E10CE (rowed
// deleting dtor), 0x001E19CE (this body) and 0x001E24DC (rowed doFXObj) in
// slots 0..2; CursorParticleSystemFXNugget's table at 0x00BDD91C holds its
// rowed doFXPos(const Coord3D*, const Matrix3D*, Real, const Coord3D*) in slot
// 1. The body leaves ECX untouched and returns RET 0x10, so it is the
// thiscall slot-1 override forwarding `this` to the rowed reallyDoFX 0x001E19E8.
struct Coord3D;
class Matrix3D;
class Object;
typedef float Real;

class ParticleSystemFXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, const Real primarySpeed, const Coord3D *secondary) const;
	void reallyDoFX(const Coord3D *primary, const Matrix3D *mtx, const Object *thingToAttachTo, const Object *secondaryObj) const;
};

void ParticleSystemFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, const Real /*primarySpeed*/, const Coord3D * /*secondary*/) const
{
	if (primary)
		reallyDoFX(primary, primaryMtx, 0, 0);
}
