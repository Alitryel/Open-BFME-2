// ?rva0010473F@Rva001040D5@@QAEXHHHH@Z
// partial score=0.97 date=2026-10-16
// ?rva0010473F@Rva001040D5@@QAEXHHHH@Z
// W9-O2 (2026-10-16): size-exact 535 B, nd 8 (was 49): frame 0x40 exact once the matrix, the display
// scale and the viewport corners each sit in their own { } block (retail packs scale/low/high and the
// Rotate_X s/c locals into the 16 bytes above the matrix). Residue: Rotate_X's first fld -pi/2 and the
// fst c are scheduled one slot earlier than retail (the two leading _ReadWriteBarrier() calls are still
// needed for the rest), and retail's scale float/int-temp homes are -0xC/-4 where ours are -4/-0xC.
// ?rva0010473F@Rva001040D5@@QAEXHHHH@Z
// partial score=0.878 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0010473F@Rva001040D5@@QAEXHHHH@Z
// partial score=0.8591948238677211 date=2026-10-13
// ?rva0010473F@Rva001040D5@@QAEXHHHH@Z
// partial score=0.8591948238677211 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
class Vector2 {public:Vector2(float x,float y):X(x),Y(y){} float X,Y;};
struct Matrix3D {float Row[3][4]; Matrix3D(bool){Row[0][0]=1;Row[0][1]=0;Row[0][2]=0;Row[0][3]=0;Row[1][0]=0;Row[1][1]=1;Row[1][2]=0;Row[1][3]=0;Row[2][0]=0;Row[2][1]=0;Row[2][2]=1;Row[2][3]=0;}
__forceinline void Rotate_X(float theta){float tmp1,tmp2;float s,c;s=(float)sin(theta);c=(float)cos(theta);
 tmp1=Row[0][1];tmp2=Row[0][2];Row[0][1]=(float)(c*tmp1+s*tmp2);Row[0][2]=(float)(-s*tmp1+c*tmp2);
 tmp1=Row[1][1];tmp2=Row[1][2];Row[1][1]=(float)(c*tmp1+s*tmp2);Row[1][2]=(float)(-s*tmp1+c*tmp2);
 tmp1=Row[2][1];tmp2=Row[2][2];Row[2][1]=(float)(c*tmp1+s*tmp2);Row[2][2]=(float)(-s*tmp1+c*tmp2);}
__forceinline void Translate_Z(float z){Row[0][3]+=(float)(Row[0][2]*z);Row[1][3]+=(float)(Row[1][2]*z);Row[2][3]+=(float)(Row[2][2]*z);}
};
class CameraClass {public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void Set_Transform(const Matrix3D&);void Set_Viewport(const Vector2&,const Vector2&);void Set_View_Plane(float,float);};
class Display {public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual unsigned getWidth();virtual unsigned getHeight();};
extern Display*TheDisplay;
extern float g_cameraDistance;
bool __cdecl Rva00118660Call(void*,void*);
class Rva001040D5 {public:void rva0010473F(int x,int y,int width,int height);private:char unknown[0x14];void*render;CameraClass*camera;unsigned active;};
void Rva001040D5::rva0010473F(int x,int y,int width,int height){if(active){
	_ReadWriteBarrier();
	_ReadWriteBarrier();
 {Matrix3D transform(true);transform.Rotate_X(-1.5707963705062866f);transform.Translate_Z(g_cameraDistance);camera->Set_Transform(transform);}
 float iw,ih;{Vector2 scale(0,0);scale.Y=(float)TheDisplay->getHeight();scale.X=(float)TheDisplay->getWidth();iw=1.0f/scale.X;ih=1.0f/scale.Y;}{Vector2 low((float)x*iw,(float)y*ih);Vector2 high((float)width*iw+low.X,(float)height*ih+low.Y);
 camera->Set_Viewport(low,high);}camera->Set_View_Plane(0.87266463f,-1.0f);Rva00118660Call(render,camera);
}}
