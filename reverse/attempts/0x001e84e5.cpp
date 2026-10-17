// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.686 date=2026-10-17
// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.845 date=2026-10-15
// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.85986 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include
// Locomotor::locoUpdate_maintainCurrentPosition, native 1E84E5..1E86D0:
// 455 bytes of instructions and a nine-entry switch table. WorldBuilder
// AEF4D0 names the method and confirms the transform save/restore, flag clears
// and maintain-position lifecycle. Pinned BFME1 a7c38d3b Locomotor.cpp provides
// the appearance dispatch and wings/height-worker semantics; BFME2 removes
// the Physics argument and changes the appearance enum and model conditions.
#include "Lib/Coord3D.h"
class Matrix3D {public: float m[12];};
class Thing { public: void setTransformMatrix(const Matrix3D *); };
class Object {
public:
 void rva0028AE6D();
 __forceinline bool hasCondition(unsigned bit) const {return (condition[bit>>5]&(1U<<(bit&31)))!=0;}
 __forceinline void clearCondition(unsigned bit) {
  unsigned mask=1U<<(bit&31);
  if(condition[bit>>5]&mask) {condition[bit>>5]&=~mask;rva0028AE6D();}
 }
 char unknown00[8]; Matrix3D transform; Coord3D position;
 char unknown44[0x10C-0x44]; unsigned condition[19];
 char unknown158[0x25C-0x158]; void *physics;
};
class Rva001E6516 {public: void rva001E6516(Object*);};
class Rva001E46E1 {public: bool rva001E7ECA(Object*,const Coord3D*);};
struct MaintainTemplate {char unknown[0x74];int appearance;};
class Locomotor {
public:
 bool locoUpdate_maintainCurrentPosition(Object*);
 __forceinline bool getFlag(unsigned bit) const {return (flags&(1U<<bit))!=0;}
protected:
 void maintainCurrentPositionWings(Object*);
private:
 void *unknown0; MaintainTemplate *parameters; Coord3D maintainPos;
 char unknown14[0x40-0x14]; float speed; unsigned flags;
 char unknown48[0x68-0x48]; Matrix3D savedTransform; bool unknown98;
};
bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
 if(!obj) return false;
 savedTransform.m[0]=obj->transform.m[0]; savedTransform.m[1]=obj->transform.m[1]; savedTransform.m[2]=obj->transform.m[2]; savedTransform.m[3]=obj->transform.m[3]; savedTransform.m[4]=obj->transform.m[4]; savedTransform.m[5]=obj->transform.m[5]; savedTransform.m[6]=obj->transform.m[6]; savedTransform.m[7]=obj->transform.m[7]; savedTransform.m[8]=obj->transform.m[8]; savedTransform.m[9]=obj->transform.m[9]; savedTransform.m[10]=obj->transform.m[10]; savedTransform.m[11]=obj->transform.m[11];
 Matrix3D *dst=&savedTransform;
 dst->m[0]=obj->transform.m[0]; dst->m[1]=obj->transform.m[1]; dst->m[2]=obj->transform.m[2]; dst->m[3]=obj->transform.m[3]; dst->m[4]=obj->transform.m[4]; dst->m[5]=obj->transform.m[5]; dst->m[6]=obj->transform.m[6]; dst->m[7]=obj->transform.m[7]; dst->m[8]=obj->transform.m[8]; dst->m[9]=obj->transform.m[9]; dst->m[10]=obj->transform.m[10]; dst->m[11]=obj->transform.m[11];
 if(!getFlag(2)) {maintainPos=obj->position;flags|=4;}
 if(!obj->hasCondition(61)) {
  obj->clearCondition(133); obj->clearCondition(134);
  obj->clearCondition(137); obj->clearCondition(138);
  obj->clearCondition(135); obj->clearCondition(136);
  obj->clearCondition(131);
 }
 flags&=~1U;
 unknown98=false;
 if(!obj->physics) return true;
 bool requiresConstantCalling=true;
 switch(parameters->appearance) {
 case 0: case 1: case 4: case 6: case 7:
  speed=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 8:
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 2: case 5:
  speed=0.0f; requiresConstantCalling=true;break;
 case 3:
  maintainCurrentPositionWings(obj);requiresConstantCalling=true;break;
 default:
  speed=0.0f;((Rva001E6516*)this)->rva001E6516(obj);requiresConstantCalling=true;break;
 }
 if(((Rva001E46E1*)this)->rva001E7ECA(obj,&maintainPos)) requiresConstantCalling=true;
 ((Thing*)obj)->setTransformMatrix(&savedTransform);
 return requiresConstantCalling;
}
