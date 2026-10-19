// ?rva0007F0FB@Rva0007F0FBOwner@@QAEXPAVCameraClass@@_N@Z
// partial score=0.45 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// ?rva0007F0FB@Rva0007F0FB@@QAEXXZ
// partial score=0.05 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 donor 0bef414b52a39a3ab1ec98dca60d8a214de4260e; native BFME2 7EF35..7F0F9.
 // ?rva0007F0FB@Rva0007F0FB@@QAEXXZ
// Native camera preparation uses CameraClass* and bool, with the counted camera pointer at owner+0xFC.
// The donor provenance note above describes the preceding loadSetting body; reflection is only a donor algorithm lead.
// Native-derived reconstruction; remaining code generation and declaration-binding evidence is in reverse/attempt_support/0007f0fb-20261019.md.
#include <float.h>
#include "vector3.h"
#include "vector4.h"

class Matrix3D;
struct Matrix4 {
 float m[4][4];
 Matrix4(){}
 __forceinline Matrix4(const Matrix3D &s);
};
class Matrix3D {
public:
 float m[3][4];
 Matrix3D() {}
 __forceinline Matrix3D(
  const Vector3 &x, // x-axis unit vector
  const Vector3 &y, // y-axis unit vector
  const Vector3 &z, // z-axis unit vector
  const Vector3 &pos) // position
 {
  m[0][0]=x.X; m[0][1]=y.X; m[0][2]=z.X; m[0][3]=pos.X;
  m[1][0]=x.Y; m[1][1]=y.Y; m[1][2]=z.Y; m[1][3]=pos.Y;
  m[2][0]=x.Z; m[2][1]=y.Z; m[2][2]=z.Z; m[2][3]=pos.Z;
 }
 __forceinline Matrix3D(const Matrix3D &s) {
  m[0][0]=s.m[0][0]; m[0][1]=s.m[0][1]; m[0][2]=s.m[0][2]; m[0][3]=s.m[0][3];
  m[1][0]=s.m[1][0]; m[1][1]=s.m[1][1]; m[1][2]=s.m[1][2]; m[1][3]=s.m[1][3];
  m[2][0]=s.m[2][0]; m[2][1]=s.m[2][1]; m[2][2]=s.m[2][2]; m[2][3]=s.m[2][3];
 }
};
__forceinline Matrix4::Matrix4(const Matrix3D &s) {
 m[0][0]=s.m[0][0];
 m[0][1]=s.m[0][1];
 m[0][2]=s.m[0][2];
 m[0][3]=s.m[0][3];
 m[1][0]=s.m[1][0];
 m[1][1]=s.m[1][1];
 m[1][2]=s.m[1][2];
 m[1][3]=s.m[1][3];
 m[2][0]=s.m[2][0];
 m[2][1]=s.m[2][1];
 m[2][2]=s.m[2][2];
 m[2][3]=s.m[2][3];
 m[3][0]=0.0f; m[3][1]=0.0f; m[3][2]=0.0f; m[3][3]=1.0f;
}
class Vector2 { public: float X,Y; };
class CameraClass {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
 virtual void Validate_Transform() const;
 virtual void Set_Transform(const Matrix3D &);
 char gap[0x14];
 Matrix3D transform;
 CameraClass &operator=(const CameraClass &);
 void Set_Viewport(const Vector2 &,const Vector2 &);
 void Apply();
 void Set_Reflected_Projection_Matrix(const Matrix4 &);
 const Matrix3D &Get_Transform() const { Validate_Transform();return transform; }
};
class Overridable {
public:
 void *vtable;
 Overridable *next;
 Overridable *friend_getFinalOverride();
};
// recursively ask if there is a next override, and if not, return this.
static __forceinline Overridable *finalSetting(Overridable *setting) {
 if(!setting)return 0;
 if(setting->next)return setting->next->friend_getFinalOverride();
 return setting;
}
class WaterTransparencySetting;
template<class T> class OVERRIDE {public:T *ptr;};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class StringClass {
 char *buffer;
public:
 StringClass(int,bool);
 ~StringClass(){Free_String();}
private:
 void Free_String();
};
struct IDirect3DDevice8;
struct RenderStateStruct { char gap[0x22c]; Matrix4 view; };
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass &,unsigned long,unsigned);
 static Matrix4 Projection() { return DeviceProjectionMatrix; }
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static unsigned RenderStates[256];
 static IDirect3DDevice8 *D3DDevice;
 static unsigned render_state_changes;
 static Matrix4 DeviceProjectionMatrix;
 friend class Rva0007F0FBOwner;
};
class WW3D {
 static bool SnapshotActivated;
 friend class Rva0007F0FBOwner;
};
extern unsigned number_of_DX8_calls;
extern bool bfmeCameraProjectionOverride;
extern "C" Matrix4 *__stdcall D3DXMatrixInverse(Matrix4 *,float *,const Matrix4 *);
extern "C" Matrix4 *__stdcall D3DXMatrixTranspose(Matrix4 *,const Matrix4 *);
extern "C" Vector4 *__stdcall rva0062AF4AD3DXVec4Transform(Vector4 *,const Vector4 *,const Matrix4 *);
void BFME_DX8_Thread_Lock();
void BFME_DX8_Thread_Assert();
struct DeviceLock {
 DeviceLock(){BFME_DX8_Thread_Lock();}
 ~DeviceLock(){BFME_DX8_Thread_Assert();}
};
class Rva0007F0FBOwner {
 char gap[0xfc];
 CameraClass *camera;
public:
 void rva0007F0FB(CameraClass *,bool);
};

void Rva0007F0FBOwner::rva0007F0FB(CameraClass *source,bool clearOverride)
{
 DeviceLock guard;
 Vector2 minimum,maximum;
 Matrix4 inverse,projection;
 Vector4 clip;
 if (!_finite(source->Get_Transform().m[0][0]))return;
 *camera=*source;
 Matrix4 old(source->Get_Transform());
 Overridable *setting=(Overridable*)TheWaterTransparency.ptr;
 setting=finalSetting(setting);
 float level=*(float*)((char*)setting+0x4c);

 Matrix4 full;
 full.m[0][0]=old.m[0][0];
 full.m[0][1]=old.m[1][0];
 full.m[0][2]=old.m[2][0];
 full.m[1][0]=old.m[0][1];
 full.m[1][1]=old.m[1][1];
 full.m[1][2]=old.m[2][1];
 full.m[2][0]=old.m[0][2];
 full.m[2][1]=old.m[1][2];
 full.m[2][2]=old.m[2][2];
 full.m[3][0]=old.m[0][3];
 full.m[3][1]=old.m[1][3];
 full.m[3][2]=old.m[2][3];
 Vector3 waterNormal(0,0,1);
 Vector3 rRight,rUp,rN,rPos;
 float axis_distance=Vector3::Dot_Product((Vector3&)full.m[0],waterNormal);
 rRight=(Vector3&)full.m[0]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[1],waterNormal);
 rUp=(Vector3&)full.m[1]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[2],waterNormal);
 rN=(Vector3&)full.m[2]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[3],waterNormal);
 axis_distance-=level;
 rPos=(Vector3&)full.m[3]-(2.0f*axis_distance*waterNormal);
 Matrix3D reflected(rRight,-rUp,rN,rPos);
 camera->Set_Transform(reflected);
 maximum.X=maximum.Y=1.0f;
 minimum.X=minimum.Y=0.0f;
 camera->Set_Viewport(minimum,maximum);
 camera->Apply();
 DX8Wrapper::Apply_Render_State_Changes();
 if(DX8Wrapper::render_state_changed&0x80000) {
  inverse.m[0][0]=1.0f; inverse.m[0][1]=0.0f; inverse.m[0][2]=0.0f; inverse.m[0][3]=0.0f;
  inverse.m[1][0]=0.0f; inverse.m[1][1]=1.0f; inverse.m[1][2]=0.0f; inverse.m[1][3]=0.0f;
  inverse.m[2][0]=0.0f; inverse.m[2][1]=0.0f; inverse.m[2][2]=1.0f; inverse.m[2][3]=0.0f;
  inverse.m[3][0]=0.0f; inverse.m[3][1]=0.0f; inverse.m[3][2]=0.0f; inverse.m[3][3]=1.0f;
 } else {
  inverse.m[0][0]=DX8Wrapper::render_state.view.m[0][0]; inverse.m[0][1]=DX8Wrapper::render_state.view.m[1][0]; inverse.m[0][2]=DX8Wrapper::render_state.view.m[2][0]; inverse.m[0][3]=DX8Wrapper::render_state.view.m[3][0];
  inverse.m[1][0]=DX8Wrapper::render_state.view.m[0][1]; inverse.m[1][1]=DX8Wrapper::render_state.view.m[1][1]; inverse.m[1][2]=DX8Wrapper::render_state.view.m[2][1]; inverse.m[1][3]=DX8Wrapper::render_state.view.m[3][1];
  inverse.m[2][0]=DX8Wrapper::render_state.view.m[0][2]; inverse.m[2][1]=DX8Wrapper::render_state.view.m[1][2]; inverse.m[2][2]=DX8Wrapper::render_state.view.m[2][2]; inverse.m[2][3]=DX8Wrapper::render_state.view.m[3][2];
  inverse.m[3][0]=DX8Wrapper::render_state.view.m[0][3]; inverse.m[3][1]=DX8Wrapper::render_state.view.m[1][3]; inverse.m[3][2]=DX8Wrapper::render_state.view.m[2][3]; inverse.m[3][3]=DX8Wrapper::render_state.view.m[3][3];
 }
 D3DXMatrixInverse(&inverse,0,&inverse);
 Vector4 plane(0.0f,0.0f,1.0f,0.0f-level);
 rva0062AF4AD3DXVec4Transform(&clip,&plane,&inverse);
 projection.m[0][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][0]; projection.m[0][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][0]; projection.m[0][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][0]; projection.m[0][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][0];
 projection.m[1][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][1]; projection.m[1][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][1]; projection.m[1][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][1]; projection.m[1][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][1];
 projection.m[2][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][2]; projection.m[2][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][2]; projection.m[2][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][2]; projection.m[2][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][2];
 projection.m[3][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][3]; projection.m[3][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][3]; projection.m[3][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][3]; projection.m[3][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][3];
 D3DXMatrixTranspose(&projection,&projection);
 Vector4 q;
 q.X=((clip.X>0.0f ? 1.0f : (clip.X<0.0f ? -1.0f : 0.0f))-projection.m[2][0])/projection.m[0][0];
 q.Y=((clip.Y>0.0f ? 1.0f : (clip.Y<0.0f ? -1.0f : 0.0f))-projection.m[2][1])/projection.m[1][1];
 q.Z=1.0f;
 q.W=(1.0f-projection.m[2][2])/projection.m[3][2];
 Vector4 c=clip*(1.0f/Vector4::Dot_Product(clip,q));
 projection.m[0][2]=c.X;
 projection.m[1][2]=c.Y;
 projection.m[2][2]=c.Z;
 projection.m[3][2]=c.W;
 camera->Set_Reflected_Projection_Matrix(projection);
 if(DX8Wrapper::RenderStates[152]!=0) {
  if(WW3D::SnapshotActivated) {
   StringClass value(0,true);
   DX8Wrapper::Get_DX8_Render_State_Value_Name(value,152,0);
  }
  DX8Wrapper::RenderStates[152]=0;
  typedef long (__stdcall *SetRenderState)(IDirect3DDevice8*,unsigned long,unsigned long);
  ((SetRenderState*)*(void**)DX8Wrapper::D3DDevice)[0xe4/4](DX8Wrapper::D3DDevice,152,0);
  ++number_of_DX8_calls;
  ++DX8Wrapper::render_state_changes;
 }
 bfmeCameraProjectionOverride=true;
 camera->Apply();
 if(clearOverride)bfmeCameraProjectionOverride=false;
}
