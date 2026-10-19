// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAUCoord3D@@@Z
// partial score=0.990909 date=2026-10-19
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.311 date=2026-10-17
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.2 date=2026-10-15
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.562 date=2026-10-15
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.561548 date=2026-10-14
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.559752 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// retail 0x0009BF33..0x0009C0EB (440B, RET 12). Screen ray: takes the current
// camera's view-plane corners and the screen point, maps it through the
// camera basis, normalises the direction into the third argument and returns
// the camera position in the second. Callees rowed: Coord3D::Normalize
// 0x00005A70, CameraClass::Get_View_Plane 0x00134080, RenderObjClass::
// Get_Position 0x0013B8A0; singleton TheDisplay 0x00DFE9D8 slot +0x40/+0x44.
typedef float Real;
typedef int Int;
typedef bool Bool;
#include "../../reference/shims/wwmath/Vector2.h"
class Vector3
{
 public: Real X, Y, Z;

};
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
// 0x00005A70
class RenderObjClass
{
 public:
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void slot20();
// +0x50
 Vector3 Get_Position() const;
// 0x0013B8A0
 private:
 char m_pad[0x14];

};
class CameraClass : public RenderObjClass
{
 public:
 void Get_View_Plane(Vector2 &min, Vector2 &max) const;
// 0x00134080
 private:
 public:
 Real m_18, m_1c, m_20, m_24;
// +0x18 basis row 0
 Real m_28, m_2c, m_30, m_34;
// +0x28 basis row 1
 Real m_38, m_3c, m_40, m_44;
// +0x38 basis row 2

};
class DisplayClass
{
 public:
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual Int getWidth();
// +0x40
 virtual Int getHeight();
// +0x44

};
extern DisplayClass *TheDisplay;
class Rva0009BF33Point
{
 public:
 Int m_x;
 Int m_y;
 Rva0009BF33Point operator-(const Rva0009BF33Point &v) const {
  Rva0009BF33Point r;
  r.m_x = m_x - v.m_x;
  r.m_y = m_y - v.m_y;
  return r;
 }

};
class Rva0009BF33
{
 public:
 void rva0009BF33(Rva0009BF33Point *screen, Vector3 *rayStart, Coord3D *rayEnd);
 private:
 char m_pad00[0x19];
 Bool m_19;
// +0x19
 char m_pad1a[0xC0 - 0x1A];
 CameraClass *m_camera;
// +0xC0
 char m_padC4[0x1B0 - 0xC4];
 Rva0009BF33Point m_origin;
// +0x1B0
// +0x1B4
 Int m_1b8;
// +0x1B8
 Int m_1bc;
// +0x1BC

};
void Rva0009BF33::rva0009BF33(Rva0009BF33Point *screen, Vector3 *rayStart, Coord3D *rayEnd)
{

 CameraClass *cam = m_camera;
 cam->slot20();
 Vector2 min, max;
 m_camera->Get_View_Plane(min, max);
 Vector2 delta = max - min;
 Int px;
 Int py;
 Real width;
 Real height;
 if (!(m_19)) {
  width = (Real)(unsigned int)TheDisplay->getWidth();
  height = (Real)(unsigned int)TheDisplay->getHeight();
  px = screen->m_x;
  py = screen->m_y;

 } else {
  width = (Real)m_1b8;
  height = (Real)m_1bc;
  Rva0009BF33Point point = *screen - m_origin;
  px = point.m_x;
  py = point.m_y;

 }
 Real t0 = ((Real)px / width - 0.5f) * delta.X;
 Real t2 = ((Real)py / height - 0.5f) * delta.Y;
 Real t1 = -t2;
 Real w = -1.0f;
 Real rx = cam->m_18 * t0 + cam->m_1c * t1 + cam->m_20 * w;
 Real ry = cam->m_28 * t0 + cam->m_2c * t1 + cam->m_30 * w;
 Real rz = cam->m_38 * t0 + cam->m_3c * t1 + cam->m_40 * w;
 rayEnd->x = rx;
 rayEnd->y = ry;
 rayEnd->z = rz;
 rayEnd->Normalize();
 Vector3 position = m_camera->Get_Position();
 rayStart->X = position.X;
 rayStart->Y = position.Y;
 rayStart->Z = position.Z;

}
// Retail 440-byte extent and canonical Coord3D declaration are verified; the old metadata above is retained evidence.
// Camera reloads, screen access timing, base adjustment and output aliasing follow retail; two delta reloads remain reversed.
