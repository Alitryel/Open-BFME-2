// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z
// partial score=0.96 date=2026-10-19
// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z
// partial score=0.588 date=2026-10-17
// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z
// partial score=0.5 date=2026-10-14
// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
// 2026-10-19 seat12 (member-mutator lever, reverse/attempt_support/coord3d-member-mutator-lever-20261019.md):
// rebuilt in the WB 0x0129CFF0 shape: copy-constructed old/position/direction (Coord3DCtorView),
// direction -= position (WB 0x420D30), length, normalize, opposite copied then negated,
// direction *= radius04 and opposite *= newRadius (WB 0x421230), edge(old += direction),
// center08 = (edge += opposite) (WB 0x420830 returns *this). 361/361 B, 3 differing lines:
// retail loads old.x ([ebp-0x14]) between position.x and position.y/.z; ours loads position
// x,y,z first. Inert: sub body spellings, set() inits, a block around the sub; worse: position
// as reference/pointer (364 B), direction declared before position (376 B), `*= -1` (357 B).
#include <vector>
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
class Object;
struct SpherePointValue { float x,y,z; SpherePointValue(const Coord3D &p):x(p.x),y(p.y),z(p.z){} };
class Rva004DFA43 { public: bool rva004DFA43(void*,void*); };
class Rva004DFCE6 {
public:
 void rva004DFCE6(Object*,void*);
 bool active00;
 float radius04;
 Coord3D center08;
 float padding14;
 bool selected18;
 _STL::vector<Object*> objects1C;
};
void Rva004DFCE6::rva004DFCE6(Object *object,void *callback)
{
 float padding=padding14;
 _STL::vector<Object*> *objects=&objects1C;
 if(objects->empty()) {
  radius04=padding14;
  center08=*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object);
 } else if(!reinterpret_cast<Rva004DFA43*>(this)->rva004DFA43(object,callback)) {
  Coord3D old(center08);
  Coord3D position(*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object));
  Coord3D direction(old);
  direction -= position;
  float distance=direction.length();
  direction.normalize();
  Coord3D opposite(direction);
  opposite.x=-opposite.x;opposite.y=-opposite.y;opposite.z=-opposite.z;
  direction *= radius04;
  float radius=(padding+radius04+distance)*0.5f;
  opposite *= radius;
  Coord3D edge(old += direction);
  center08=(edge += opposite);
  radius04=radius;
 }
 objects->push_back(object);
}
