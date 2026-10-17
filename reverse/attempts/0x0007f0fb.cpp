// ?rva0007F0FB@Rva0007F0FB@@QAEXXZ
// partial score=0.05 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// BFME1 donor 0bef414b52a39a3ab1ec98dca60d8a214de4260e; native BFME2 7EF35..7F0F9.
#include <float.h>
#define __thiscall __stdcall
struct Matrix4;
Matrix4 *__stdcall D3DXMatrixInverse(Matrix4 *, unsigned *, Matrix4 *);
float *__stdcall D3DXVec4Transform(float *, float *, Matrix4 *);
struct Matrix4 *__stdcall D3DXMatrixTranspose(struct Matrix4 *, struct Matrix4 *);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class WaterSetting;
extern WaterSetting WaterSettings[];

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class BFME2ParticleTextureHandle {
public:
 TextureBaseClass *Ptr;
 ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *,int,int);
};
class W3DRadarResetSurface;
class CursorTextureSlot {
public:
 TextureBaseClass *Ptr;
 ~CursorTextureSlot() { if (Ptr) reinterpret_cast<TextureClass *>(Ptr)->Release_Ref(); }
 void operator=(const BFME2ParticleTextureHandle &);
 W3DRadarResetSurface Get_Surface_Level();
};

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		UnsignedInt Format;
		UnsignedInt Width;
		UnsignedInt Height;
	};
	void Get_Description(SurfaceDescription &surfaceDesc);
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual unsigned long __stdcall addRef(void);
	virtual unsigned long __stdcall release(void);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	W3DRadarResetSurface(void) : m_surface(0) {}
	W3DRadarResetSurface(SurfaceResource *surface);
	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) :
		m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}
	~W3DRadarResetSurface(void);
private:
	SurfaceResource *m_surface;
};

class WaterSettingColorView
{
public:
	UnsignedInt red;
	UnsignedInt green;
	UnsignedInt blue;
	UnsignedInt alpha;
};

class WaterSettingLoadView
{
public:
	virtual ~WaterSettingLoadView(void);
	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	Int m_waterRepeatCount;
	Real m_skyTexelsPerUnit;
	WaterSettingColorView m_vertex00Diffuse;
	WaterSettingColorView m_vertex10Diffuse;
	WaterSettingColorView m_vertex11Diffuse;
	WaterSettingColorView m_vertex01Diffuse;
	WaterSettingColorView m_waterDiffuseColor;
	WaterSettingColorView m_transparentWaterDiffuse;
	Real m_uScrollPerMs;
	Real m_vScrollPerMs;
};

enum TimeOfDay;

class WaterRenderObjClass
{
public:
	struct Setting
	{
		Setting();
		~Setting();
		CursorTextureSlot skyTexture;
		CursorTextureSlot waterTexture;
		Int waterRepeatCount;
		Real skyTexelsPerUnit;
		UnsignedInt vertex00Diffuse;
		UnsignedInt vertex10Diffuse;
		UnsignedInt vertex11Diffuse;
		UnsignedInt vertex01Diffuse;
		UnsignedInt waterDiffuse;
		UnsignedInt transparentWaterDiffuse;
		Real uScrollPerMs;
		Real vScrollPerMs;
	};
protected:
	void loadSetting(Setting *setting, TimeOfDay timeOfDay);
};

void WaterRenderObjClass::loadSetting(
	Setting *setting, TimeOfDay timeOfDay)
{
 setting->skyTexture = TextureAsset::Get(((WaterSettingLoadView *)WaterSettings)[(unsigned)timeOfDay].m_skyTextureFile.str(),0,0);
 setting->waterTexture = TextureAsset::Get(((WaterSettingLoadView *)WaterSettings)[(unsigned)timeOfDay].m_waterTextureFile.str(),0,0);
	setting->skyTexelsPerUnit = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_skyTexelsPerUnit;
	SurfaceClass::SurfaceDescription surfaceDesc;
	setting->waterTexture.Get_Surface_Level().Get_Description(surfaceDesc);
	setting->skyTexelsPerUnit /= (Real)surfaceDesc.Width;
	setting->waterRepeatCount = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterRepeatCount;
	setting->uScrollPerMs = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_uScrollPerMs;
	setting->vScrollPerMs = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vScrollPerMs;
	setting->vertex00Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.blue;
	setting->vertex01Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.blue;
	setting->vertex10Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.blue;
	setting->vertex11Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.blue;
	setting->waterDiffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.alpha << 24) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.blue;
	setting->transparentWaterDiffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.alpha << 24) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.blue;
}

WaterRenderObjClass::Setting::~Setting() {}

template <class T>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
};

class Vector3;

class Rva0007E7DD
{
public:
	void rva0007E7DD();
};

struct Matrix4 { float M[4][4]; };
struct Vector2 { float X,Y; };
class CameraClass {
public:
	CameraClass & operator=(const CameraClass &);
	void Set_Viewport(const Vector2 &, const Vector2 &);
	void Apply();
	void Set_Reflected_Projection_Matrix(const Matrix4 &);
	void Get_Clip_Planes(Matrix4 *,Matrix4 *,Matrix4 *,Matrix4 *) const;
};
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class Overridable { public: Overridable *friend_getFinalOverride(); };
class DX8Wrapper {
public:
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(AsciiString &,UnsignedInt,Int);
};

class Rva0007F0FB {
public:
	void rva0007F0FB();
};

 // ?rva0007F0FB@Rva0007F0FB@@QAEXXZ
void Rva0007F0FB::rva0007F0FB()
{
	BFME_DX8_Thread_Lock();
	CameraClass *src = *(CameraClass **)((char *)&src + 4);
	CameraClass *srcCopy = (1 ? src : src);
	int flag = *(int *)((char *)&srcCopy + 8);
	((void(__thiscall *)(void *,unsigned))(*(unsigned **)srcCopy)[0x50/4])((void *)srcCopy, 0);
	if (!_finite((double)*(float *)((char *)src + 0x18)))
		return;
	CameraClass *cam = (CameraClass *)((char *)this + 0xfc);
	{
		float *d = (float *)cam;
		float *s = (float *)src;
		d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4]; d[5]=s[5]; d[6]=s[6]; d[7]=s[7];
		d[8]=s[8]; d[9]=s[9]; d[10]=s[10]; d[11]=s[11]; d[12]=s[12]; d[13]=s[13]; d[14]=s[14]; d[15]=s[15];
	}
	Matrix4 a,b,c,d;
	{
	W3DRadarResetSurface tmp1;
	W3DRadarResetSurface tmp2;
	cam->Get_Clip_Planes(&a,&b,&c,&d);
	}
	Overridable *ov = *(Overridable **)0xdff488;
	float over = 0.0f;
	if (ov) {
		if (*(int *)((char *)ov + 4))
			ov = ov->friend_getFinalOverride();
		over = *(float *)((char *)ov + 0x4c);
	}
	float k1 = *(float *)0xbc28f4;
	float k2 = *(float *)0xbbb8d8;
	float m00 = a.M[0][0]+b.M[0][0];
	float m10 = a.M[1][0]+b.M[1][0];
	float m20 = a.M[2][0]+b.M[2][0];
	float m30 = a.M[3][0]+b.M[3][0];
	float t0 = (m00*0.0f+m30)*k1;
	float r0x = t0*0.0f;
	float cx = m00-r0x;
	float wx = m30-t0;
	float qx = b.M[0][0]-r0x;
	float m01 = a.M[0][1]+b.M[0][1];
	float m11 = m10;
	float m31 = b.M[3][1]+a.M[3][1];
	(void)m11;
	float t1 = (m01*0.0f+m31)*k1;
	float r1 = t1*0.0f;
	float cy = b.M[0][1]-r1;
	float t1b = m10-r1;
	float wy = m31-t1;
	float qy = m01-t1;
	float m02 = a.M[0][2]+b.M[0][2];
	float m32 = a.M[3][2]+c.M[3][2];
	float t2 = (m02*0.0f+m32)*k1;
	float w2 = m32-t2;
	float r2 = t2*0.0f;
	float cz = m02-r2;
	float qz = w2;
	float m03 = a.M[0][3]+b.M[0][3];
	float m33 = d.M[3][3]+c.M[3][3];
	float t3 = ((m03*0.0f+m33)-over)*k1;
	float w3 = m33-t3;
	float r3 = t3*0.0f;
	float cw = m03-r3;
	float qw = w3;
	Matrix4 clip;
	clip.M[0][0]=cx; clip.M[0][1]=cy; clip.M[0][2]=cz; clip.M[0][3]=cw;
	clip.M[1][0]=qx; clip.M[1][1]=qy; clip.M[1][2]=qz; clip.M[1][3]=qw;
	clip.M[2][0]=wx; clip.M[2][1]=wy; clip.M[2][2]=w2; clip.M[2][3]=w3;
	clip.M[3][0]=0.0f; clip.M[3][1]=0.0f; clip.M[3][2]=0.0f; clip.M[3][3]=0.0f;
	((void(__thiscall *)(void *,void *))(*(unsigned **)cam)[0x54/4])((void *)cam,(void *)&clip);
	Vector2 v0; Vector2 v1;
	v0.X=v0.Y=v1.X=v1.Y=k2;
	v1.X=0.0f; v1.Y=0.0f;
	cam->Set_Viewport(v0,v1);
	cam->Apply();
	DX8Wrapper::Apply_Render_State_Changes();
	Matrix4 inv;
	if (*(unsigned char *)0xdec4f6 & 8) {
		inv.M[0][0]=k2; inv.M[0][1]=0; inv.M[0][2]=0; inv.M[0][3]=0;
		inv.M[1][0]=0; inv.M[1][1]=k2; inv.M[1][2]=0; inv.M[1][3]=0;
		inv.M[2][0]=0; inv.M[2][1]=0; inv.M[2][2]=k2; inv.M[2][3]=0;
		inv.M[3][0]=0; inv.M[3][1]=0; inv.M[3][2]=0; inv.M[3][3]=k2;
	} else {
		inv = *(Matrix4 *)0xdee804;
	}
	Matrix4 tmp;
	D3DXMatrixInverse((Matrix4 *)&tmp,0,(Matrix4 *)&inv);
	float v[4]; v[0]=0; v[1]=0; v[2]=k2; v[3]=0.0f-over;
	float out[4];
	D3DXVec4Transform((float *)&out,(float *)&v,(Matrix4 *)&tmp);
	Matrix4 src2 = *(Matrix4 *)0xdedbf0;
	Matrix4 tr;
	D3DXMatrixTranspose(&tr,&src2);
	float px = out[0];
	float py = out[1];
	float pz = out[2];
	float pw = out[3];
	float sx = px>=0.0f ? k2 : (0.0f>px ? 0.0f : *(float *)0xbbb9ac);
	float sy = py>=0.0f ? k2 : (0.0f>py ? 0.0f : *(float *)0xbbb9ac);
	float szx = 0.0f;
	float inv2 = 1.0f/(px*sx+py*sy+pz*szx+pw);
	(void)inv2;
	cam->Set_Reflected_Projection_Matrix(tr);
	if (*(int *)0xded858) {
		if (!*(unsigned char *)0xdec3fd) {
			AsciiString s((const char *)0x98,false);
			DX8Wrapper::Get_DX8_Render_State_Value_Name(s,0x98,0);
		}
		unsigned *p = *(unsigned **)0xdeda34;
		*(int *)0xded858 = 0;
		((void(__thiscall *)(void *,int,int))(*(unsigned **)p)[0xe4/4])((void *)p,0,0x98);
		(*(int *)0xdeda98)++;
		(*(int *)0xdeda64)++;
	}
	*(unsigned char *)0xdeda05 = 1;
	cam->Apply();
	if (flag)
		*(unsigned char *)0xdeda05 = 0;
	BFME_DX8_Thread_Assert();
}
