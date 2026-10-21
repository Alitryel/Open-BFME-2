// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
//
// ?rva002829BD@Rva002829BD@@QAEXPBVModuleData@@P6APAXPAX@Z@Z retail 0x002829BD..0x00282B26, 361 B, RET 8.
// Target evidence: the 40-byte group the rowed constructor 0x00281A76 builds (radius +0x04,
// center +0x08, padding +0x14, vector +0x1C) grows its bounding sphere to cover a key's
// position: callers Rva00282B26 (0x00282B26) and the GroupMerge add pass (key, cdecl position
// getter). Retail's body is byte-for-byte the shape of the rowed 0x004DFCE6 sphere merge
// (Rva004DFCE6SphereMerge.cpp, WorldBuilder twin 0x0129CFF0: in-place Coord3D Sub/Scale/Add),
// the same template over a different element type: the containment test is the rowed
// 0x004DFA43 and the append is the four-byte pointer-vector push_back fold at 0x004DFCB0
// (its rowed instance is vector<const ModuleData *>, so the key is spelled const ModuleData *;
// the key's real type stays open).
#include <stl/_alloc.h>
// Use the rowed malloc allocator provider instead of emitting a competing copy.
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
#include <vector>
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
#include <math.h>
// coord3d.cpp's Coord3D::length (0x00003571) and ::normalize (0x000035B6), visible here
// so cl knows they keep no pointer to the direction vector (as AIAttackApproachComputePath.cpp).
__declspec(noinline) inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}
class ModuleData;
typedef void *(__cdecl *Rva00282B26Callback)(void *key);
class Rva004DFA43 { public: bool rva004DFA43(void*,void*); };
class Rva002829BD {
public:
 void rva002829BD(const ModuleData *key, Rva00282B26Callback callback);
 bool active00;
 float radius04;
 Coord3D center08;
 float padding14;
 bool selected18;
 _STL::vector<const ModuleData*> objects1C;
};
void Rva002829BD::rva002829BD(const ModuleData *object, Rva00282B26Callback callback)
{
 float padding=padding14;
 _STL::vector<const ModuleData*> *objects=&objects1C;
 if(objects->empty()) {
  radius04=padding14;
  center08=*static_cast<const Coord3D *>(callback((void *)object));
 } else if(!reinterpret_cast<Rva004DFA43*>(this)->rva004DFA43((void *)object,(void*)callback)) {
  Coord3D old(center08);
  Coord3D position(*static_cast<const Coord3D *>(callback((void *)object)));
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
