// ?doParticles@ButterflyDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// partial score=0.99 date=2026-10-20
// Native560B11..561375 Butterfly renderer, 2148 B, two wing quads per particle (WB 0x1424D50).
// 5 instructions left: row-0 schedule of the view loop (X*m00 vs m02*Z first).
// Levers found: WB axis pointer local (const Vector3*axis=&p->axis), and the view loop binding
// Vector4&v=vertices[j] (or view*(vertices[j]+=translation)), each a large drop.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include
#include "ascii_string.h"
class RenderInfoClass;
class RefCountClass;
#include "matrix4.h"
float Rva001333F0Atan2(float y, float x);
class Matrix4 : public Matrix4x4 {
public:
 __forceinline void identity() {Make_Identity();}
 __forceinline void transposeFrom(const Matrix4 &m) {*(Matrix4x4*)this=m.Transpose();}
};
class Rva0007671F:public Matrix4 {public:Rva0007671F();};
struct D3DXMATRIX {float m[4][4];};
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationZ(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationX(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationY(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationAxis(D3DXMATRIX*,const Vector3*,float);
template<class T>class ShareBufferClass {public:T*Get_Array(){return Array;}private:char pad[12];T*Array;};
extern ShareBufferClass<Vector3>*g_00E065C8;
extern ShareBufferClass<Vector4>*g_00E065CC;
class ShaderClass {public:__declspec(dllimport) __forceinline ShaderClass(const ShaderClass&s){ShaderBits=s.ShaderBits;}__declspec(dllimport) __forceinline ShaderClass&operator=(const ShaderClass&s){ShaderBits=s.ShaderBits;return *this;}unsigned ShaderBits;static ShaderClass _PresetAdditive2DShader,_PresetAlpha2DShader,_PresetAdditiveSpriteShader,_PresetAlphaSpriteShader,_PresetATestSpriteShader,_PresetMultiplicativeSpriteShader;void Enable_Fog(const char*);};
extern unsigned int BfmeParticleType2ShaderBits;
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}TextureClass*Ptr;};
class TextureAsset {public:static BFME2ParticleTextureHandle Get(const char*,int,int);};
template<class T>class RefCountPtr {public:const RefCountPtr&operator=(const RefCountPtr&);T*Ptr;};
class Rva0090F8C0Holder {public:void set(int,RefCountClass*,RefCountClass*,RefCountClass*,RefCountClass*);};
class Rva00177860 {public:void rva00177F82(RenderInfoClass&);void*refs[4];int count;RefCountPtr<TextureClass> texture;unsigned shader;float tail[4];};
extern Rva00177860*g_00E06254;
enum D3DTRANSFORMSTATETYPE {D3DTS_VIEW=2,D3DTS_PROJECTION=3,D3DTS_WORLD=256,D3DTS_FORCE_DWORD=0x7fffffff};
struct RenderStateStruct {char pad[0x1EC];Matrix4x4 world;Matrix4x4 view;};
class DX8Wrapper {public:enum {WORLD_IDENTITY=1<<18,VIEW_IDENTITY=1<<19};static bool Get_Fog_Enable(){return FogEnable;}
 // BFME 2 DX8Wrapper::Get_Transform (WB 0x009C1560)
 static __forceinline void Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m)
{
	switch ((int)transform) {
	case D3DTS_WORLD:
		if (render_state_changed&WORLD_IDENTITY) m.Make_Identity();
		else m=render_state.world.Transpose();
		break;
	case D3DTS_VIEW:
		if (render_state_changed&VIEW_IDENTITY) m.Make_Identity();
		else m=render_state.view.Transpose();
		break;
	case D3DTS_PROJECTION:
		m=DeviceProjectionMatrix.Transpose();
		break;
	default:
		m.Make_Identity();
		break;
	}
}
protected:static bool FogEnable;static unsigned render_state_changed;static RenderStateStruct render_state;static Matrix4 DeviceProjectionMatrix;};
namespace FXParticleSystem {class ButterflyDrawModule;}
class WW3D {friend class FXParticleSystem::ButterflyDrawModule;static bool IsCurrentlyRenderingShadowMap;};
class Rva001F4E2D {public:bool rva001F4E2D();};
class Rva001F4D2D {public:float rva001F4D2D();};
class Rva001F4DC4 {public:float rva001F4DC4();};
class Rva001F4DE6 {public:int rva001F4DE6();};
#include "Lib/RGBColor.h"
class Rva001F4E1BSlot {public:const RGBColor*get()const;};
class Rva001F4DF9 {public:float rva001F4DF9();};
struct ButterflyParticle {char prefix[16];Vector3 axis;Vector3 position;char gap[0x3c];ButterflyParticle*next;};
class ButterflyParticleStorage {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual ButterflyParticle*getFirstParticle();};
class Rva0004CABDSevenEight {public:int get()const;};
class ParticleSystem {public:char p0[8];int shader;char pC[4];AsciiString texture;char p14[0x90];ButterflyParticleStorage*storage;};
ParticleSystem*Make001FCBD7();
struct ButterflyBox {Vector3 center,extent;};
__forceinline float quadFabs(float x){unsigned n=*(unsigned*)&x;n&=0x7fffffff;return *(float*)&n;}
namespace FXParticleSystem {
class ButterflyDrawModule {public:virtual int doParticles(RenderInfoClass&,void*,int*);private:ParticleSystem*system;__forceinline ParticleSystem*getSystem(){return system?system:Make001FCBD7();}};
int ButterflyDrawModule::doParticles(RenderInfoClass&rinfo,void*bounds,int*particleCount){
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int count=0;Vector3*positions=g_00E065C8->Get_Array();Vector4*colors=g_00E065CC->Get_Array();
 Vector4 vertices[8];
 const ButterflyBox*box=(const ButterflyBox*)bounds;
 float cx=box->center.X,cy=box->center.Y,cz=box->center.Z;
 float ex=box->extent.X,ey=box->extent.Y,ez=box->extent.Z;
 Rva0007671F view;Vector4 transformed;Rva0007671F matrixB,matrixC,matrixD,matrixA;
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 ButterflyParticle*p=0;if(!((unsigned char)((Rva0004CABDSevenEight*)getSystem())->get()))
 p=getSystem()->storage->getFirstParticle();{
 for(;p;p=p->next){
  if(((Rva001F4E2D*)p)->rva001F4E2D())continue;
  const Vector3*pos=&p->position;const Vector3*axis=&p->axis;float size=((Rva001F4D2D*)p)->rva001F4D2D();float angle=((Rva001F4DC4*)p)->rva001F4DC4();
  if(quadFabs(pos->X-cx)>ex+size)continue;
  if(quadFabs(pos->Y-cy)>ey+size)continue;
  if(quadFabs(pos->Z-cz)>ez+size)continue;
  float height=WWMath::Cos(angle)*size*2.0f;
  if(height<-size)height=-size;
  float width=WWMath::Sin(angle)*size*2.0f;
  float s=size;
  vertices[0].X=0;vertices[0].Y=s;vertices[0].Z=0;vertices[0].W=1;
  vertices[1].X=width;vertices[1].Y=s;vertices[1].Z=height;vertices[1].W=1;
  vertices[2].X=0;vertices[2].Y=-s;vertices[2].Z=0;vertices[2].W=1;
  vertices[3].X=width;vertices[3].Y=-s;vertices[3].Z=height;vertices[3].W=1;
  vertices[4].X=0;vertices[4].Y=s;vertices[4].Z=0;vertices[4].W=1;
  vertices[5].X=-width;vertices[5].Y=s;vertices[5].Z=height;vertices[5].W=1;
  vertices[6].X=0;vertices[6].Y=-s;vertices[6].Z=0;vertices[6].W=1;
  vertices[7].X=-width;vertices[7].Y=-s;vertices[7].Z=height;vertices[7].W=1;
  if(fabs(axis->X)>0.0001f){
   Rva0007671F rotation;
   float facing=(float)(Rva001333F0Atan2(-axis->Y,axis->X)-1.5707963267948966);
   D3DXMatrixRotationZ((D3DXMATRIX*)&rotation,facing);
   for(int i=0;i<8;++i){transformed=rotation*vertices[i];vertices[i]=transformed;}
  }
  int start=count*4;Vector4 translation(pos->X,pos->Y,pos->Z,0);
  for(int j=0;j<8;++j){Vector4&v=vertices[j];v+=translation;transformed=view*v;
   positions[start+j].X=transformed.X;positions[start+j].Y=transformed.Y;positions[start+j].Z=transformed.Z;
  }
  const RGBColor*color=((Rva001F4E1BSlot*)p)->get();float alpha=((Rva001F4DF9*)p)->rva001F4DF9();
  if(color){for(int k=0;k<8;++k){colors[start+k].X=color->red;colors[start+k].Y=color->green;colors[start+k].Z=color->blue;colors[start+k].W=alpha;}}else{for(int k=0;k<8;++k)colors[start+k].Set(0,0,0,alpha);}
  count+=2;if(count>=512)break;
 }
 }
 if(count>0){BFME2ParticleTextureHandle texture=TextureAsset::Get(getSystem()->texture.str(),0,0);
  if(g_00E06254){RefCountPtr<TextureClass>&slot=g_00E06254->texture;slot=*(RefCountPtr<TextureClass>*)&texture;
   ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
   switch(getSystem()->shader){case 2:shader=*reinterpret_cast<const ShaderClass*>(&BfmeParticleType2ShaderBits);break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;}
   if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");g_00E06254->shader=shader.ShaderBits;
   ((Rva0090F8C0Holder*)g_00E06254)->set(count,(RefCountClass*)g_00E065C8,(RefCountClass*)g_00E065CC,0,0);g_00E06254->rva00177F82(rinfo);
  }
 }
 return count;
}
}
