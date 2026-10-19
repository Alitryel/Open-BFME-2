// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.311 date=2026-10-17
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.2 date=2026-10-15
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.562 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
// partial score=0.561548 date=2026-10-14
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAVCoord3D@@@Z
template<class T> inline volatile T &__vref(T &x)
{
 return *(volatile T *)&x;
 
}
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
class Vector2 

{
 public: Real X, Y;
 
}
;
class Vector3 

{
 public: Real X, Y, Z;
 
}
;
class Coord3D

{
 public:
 Real x, y, z;
 Real Normalize();
// 0x00005A70
 
}
;
class RenderObjClass

{
 public:
 Vector3 Get_Position() const;
// 0x0013B8A0
 private:
 char m_pad[0x14];
 
}
;
class CameraClass : public RenderObjClass

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
 
}
;
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
 
}
;
extern DisplayClass *TheDisplay;
class Rva0009BF33Point

{
 public:
 Int m_x;
 Int m_y;
 
}
;
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
 Int m_1b0;
// +0x1B0
 Int m_1b4;
// +0x1B4
 Int m_1b8;
// +0x1B8
 Int m_1bc;
// +0x1BC
 
}
;
void Rva0009BF33::rva0009BF33(Rva0009BF33Point *screen, Vector3 *rayStart, Coord3D *rayEnd)

{
	_ReadWriteBarrier();
 CameraClass *cam = m_camera;
 cam->slot20();
 Vector2 min, max;
 cam->Get_View_Plane(min, max);
 Real dx = max.X - min.X;
 Real dy = max.Y - min.Y;
 Int px;
 Int py;
 Real width;
 Real height;
 Int sx = screen->m_x;
 Int sy = screen->m_y;
 if (!(m_19)) {
  px = sx;
  py = sy;
  width = (Real)(unsigned int)TheDisplay->getWidth();
  height = (Real)(unsigned int)TheDisplay->getHeight();
  
 } else {
  px = sx - m_1b0;
  py = sy - m_1b4;
  width = (Real)m_1b8;
  height = (Real)m_1bc;
  
 }
 Real t0 = ((Real)px / width - 0.5f) * dx;
 Real t2 = ((Real)py / height - 0.5f) * dy;
 Real t1 = 0.0f - t2;
 Real w = 1.0f;
 rayEnd->x = cam->m_18 * t0 + cam->m_1c * t1 - cam->m_20 * w;
 rayEnd->y = cam->m_28 * t0 + cam->m_2c * t1 - cam->m_30 * w;
 rayEnd->z = cam->m_38 * t0 + cam->m_3c * t1 - cam->m_40 * w;
 rayEnd->Normalize();
 *rayStart = cam->Get_Position();
 
}
