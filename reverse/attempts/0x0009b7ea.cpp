// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z
// partial score=0.94 date=2026-10-17
// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z
// partial score=0.9769963871932229 date=2026-10-14
// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z
// partial score=0.9731624517254267 date=2026-10-14
// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z
// partial score=0.9731624517254267 date=2026-10-14
// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z
// Native9B7EA..9BAA4, 698B, RET4. Four camera-frustum corner rays projected at z=0.
// Native this+C0, Camera Get_View_Plane134080, virtual Validate_Transform50,
// RenderObjClass Get_Position13B8A0, WWMath Inv_Sqrt4233A prove the operations.
// Neutral class name follows existing9C134/9C18A caller view; original name unknown.
// Served WB6537E0 is a different screen-point projection and cannot name this body.
// Matrix3D/Vector3 semantic helpers from BFME1 a7c38d3b (WWMath); target operations
// and offsets are independently established above. Real Find_X/Y_At_Z and scalar
// direction-constructor shape close all instructions; frameA0 and698B exact.
// Remaining14 bytes are only homes: native height38,forward3C,width48,len4C,x50;
// current height48,forward38,width4C,len50,x44 (EBP uses biased frame +74).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "matrix3d.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
class RenderObjClass {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
virtual void Validate_Transform()const;
Vector3 Get_Position()const;
const Matrix3D&Get_Transform()const {Validate_Transform();return transform;}
char pad[0x18-4];Matrix3D transform;
};
class CameraClass:public RenderObjClass {public:
void Get_View_Plane(Vector2&,Vector2&)const;
float offsetX()const{return *(const float*)((const char*)this+0xc8);}
float offsetY()const{return *(const float*)((const char*)this+0xcc);}
};
class Rva0009C134Host {public:void rva0009B7EA(Coord3D*);char pad[0xc0];CameraClass*camera;};
void Rva0009C134Host::rva0009B7EA(Coord3D*out){
CameraClass *cam=camera;
Vector2 lo,hi;
cam->Get_View_Plane(lo,hi);
Matrix3D tm=camera->Get_Transform();
int i=0;
Vector2 extent(hi.X-lo.X,hi.Y-lo.Y);
Vector3 forward=tm.Get_Z_Vector()*-1.0f;
for(;i<4;++i){
int x,y;
switch(i){case 0:x=0;y=1;break;case 1:x=1;y=1;break;case 2:x=0;y=0;break;case 3:x=1;y=0;break;default:x=0;y=0;break;}
float dx=(x-0.5-cam->offsetX())*extent.Y;
float dy=(y-0.5-cam->offsetY())*extent.X;
Vector3 dir(tm[0][0]*dx+tm[0][1]*dy+forward.X,tm[1][0]*dx+tm[1][1]*dy+forward.Y,tm[2][0]*dx+tm[2][1]*dy+forward.Z);
dir.Normalize();
Vector3 p=camera->Get_Position()+dir;
const float &xx=Vector3::Find_X_At_Z(0.0f,camera->Get_Position(),p);
float yy=Vector3::Find_Y_At_Z(0.0f,camera->Get_Position(),p);
out[i].x=xx;out[i].y=yy;out[i].z=0.0f;
}
}
