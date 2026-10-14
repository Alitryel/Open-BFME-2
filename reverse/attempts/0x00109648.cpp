// ?updateBounds@W3DShadowTexture@@QAEXAAVVector3@@PAVRenderObjClass@@@Z
// partial score=0.576725269048644 date=2026-10-14
// ?updateBounds@W3DShadowTexture@@QAEXAAVVector3@@PAVRenderObjClass@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/wwmath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// BFME1 cee35b7d8 donor: game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowUpdateTexture.cpp.
// Zero Hour W3DTextureShadow.cpp supplies the decal update purpose and UV arithmetic.
// BFME2 caller update() at 0x001094E2 calls 0x0010930F with the current light position.
// Target layout and calls independently show mask +0x34, texture +0x68, render object +0x70;
// box slot +0x110 and sphere slot +0x10C differ from the BFME1 donor view.
// The target copies the six-float box storage with the existing Region3D copy constructor
// at 0x0009AC04. Its storage view is retained without claiming donor center/extent field names.
// The scalar constants and local uvData initializer remain exactly the donor values.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

#include "Vector2.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h
#include <math.h>
#pragma intrinsic(sqrt)
#pragma function(fabs)

class Vector3
{
public:
	Vector3(void) {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator = (const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = X;
		float tmp_y = Y;

		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}

	Vector3 &operator += (const Vector3 &v) { X+=v.X; Y+=v.Y; Z+=v.Z; return *this; }
	Vector3 &operator -= (const Vector3 &v) { X-=v.X; Y-=v.Y; Z-=v.Z; return *this; }
	Vector3 &operator *= (float v) { X*=v; Y*=v; Z*=v; return *this; }
	float Length2() const { return X*X + Y*Y + Z*Z; }
	float Length() const { float squared = Length2(); volatile float root = (float)sqrt(squared); return root; }
	friend Vector3 operator + (const Vector3 &a,const Vector3 &b) { return Vector3(a.X+b.X,a.Y+b.Y,a.Z+b.Z); }
	friend Vector3 operator - (const Vector3 &a,const Vector3 &b) { return Vector3(a.X-b.X,a.Y-b.Y,a.Z-b.Z); }
	friend Vector3 operator - (const Vector3 &a) { return Vector3(-a.X,-a.Y,-a.Z); }
	friend Vector3 operator * (const Vector3 &a, float k);
	friend Vector3 operator / (const Vector3 &a, float k);

	float X;
	float Y;
	float Z;
};

inline Vector3 operator * (const Vector3 &a, float k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

inline Vector3 operator / (const Vector3 &a, float k)
{
	float ook = 1.0f / k;
	return Vector3((a.X * ook), (a.Y * ook), (a.Z * ook));
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	SphereClass(void) {}

	void Init(const Vector3 &c,float r) { Center=c; Radius=r; }
	Vector3 Center;
	float Radius;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
struct Region3D
{
public:
	Region3D(void) {}
	Region3D(const Region3D &) throw();

	float x_min,y_min,z_min,x_max,y_max,z_max;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned int Format;
		unsigned int Width;
		unsigned int Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
};

// Retail 0x00176CB0 destroys the by-value surface 0x00132D70 returns.
class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface(void);

private:
	void *m_surface;
};

class CursorTextureSlot
{
public:
	W3DRadarResetSurface Get_Surface_Level(void);

	TextureBaseClass *m_texture;
};

// The AssetReference returned at 0x001085B4 is the one-pointer texture
// holder passed to CursorTextureSlot::Get_Surface_Level at 0x00132D70.
class AssetReference : public CursorTextureSlot
{
public:
	~AssetReference(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

// Retail 0x001085B4 reads the AssetReference at shadow-texture +0x30.
class Rva001085B4
{
public:
	AssetReference rva001085B4(void);
};

// Offsets witnessed by this body and the landed destructor at 0x007AF4E0;
// the order matches the Zero Hour W3DShadowTexture.
// Donor AABoxClass semantics; target box is the six-word storage at +0x64.
typedef float Real;
struct ShadowProjectionBox {
 Vector3 Center,Extent;
 __forceinline void Init(Vector3 *points,int num) {
  Vector3 Min=points[0],Max=points[0];
  for(int i=1;i<num;++i) {
   if(Min.X>points[i].X) Min.X=points[i].X;
   if(Min.Y>points[i].Y) Min.Y=points[i].Y;
   if(Min.Z>points[i].Z) Min.Z=points[i].Z;
   if(Max.X<points[i].X) Max.X=points[i].X;
   if(Max.Y<points[i].Y) Max.Y=points[i].Y;
   if(Max.Z<points[i].Z) Max.Z=points[i].Z;
  }
  Center=(Max+Min)*0.5f;
  Extent=(Max-Min)*0.5f;
 }
 void Translate(const Vector3 &v) { Center+=v; }
};

class RenderObjClass;
class W3DShadowTexture
{
public:
	void updateBounds(Vector3 &lightPos,RenderObjClass *robj);
	void setLightPosHistory(Vector3 &pos) { m_lastLightPosition = pos; }
	void setBoundingSphere(SphereClass &sphere) { m_areaEffectSphere = sphere; }
	void setBoundingBox(Region3D &box) { ((Region3D *)&m_areaEffectBox)->Region3D::Region3D(box); }
	// Reuse the rowed 0x00108603 provider; its field-copy body cannot throw.
	void setDecalUVAxis(Vector3 &u, Vector3 &v) throw();

private:
	char m_unmodelled00[0x34];
	Vector3 m_lastLightPosition;		// +0x34
	char m_unmodelled40[0x24];
	ShadowProjectionBox m_areaEffectBox;			// +0x64
	SphereClass m_areaEffectSphere;		// +0x7C
	Vector3 m_shadowUV[2];				// +0x8C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void v27(void);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual const Region3D &Get_Bounding_Box(void) const;
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const; // +0x10C
	virtual void Get_Obj_Space_Bounding_Box(Region3D &box) const; // +0x110

	Vector3 Get_Position(void) const;
};

#define DECAL_TEXELS_PER_WORLD_UNIT	(64.0f/20.0f)	//64 texels per 2 terrain cells (20 units)

class W3DProjectedShadow
{
public:
	void updateTexture(Vector3 &lightPos);

private:
	char m_unmodelled00[0x34];
	unsigned int m_unmodelled34;			// +0x34 decal-kind mask test 0x2C61
	char m_unmodelled38[0x30];
	W3DShadowTexture *m_shadowTexture[1];	// +0x68
	void *m_unmodelled6C;
	RenderObjClass *m_robj;					// +0x70
};

void W3DProjectedShadow::updateTexture(Vector3 &lightPos)
{
	//default uv coordinates before rotation starting at top/left going clockwise
	static Vector2 uvData[4]={Vector2(-0.5,-0.5f),Vector2(-0.5,0.5f),Vector2(0.5f,0.5f),Vector2(-0.5f,0.5f)};

	if (m_unmodelled34 & 0x2C61)
	{	//decal shadows use artist supplied textures.  We just need to tweak the uv coordinates to match
		//the light direction.
		Vector3 objPos=m_robj->Get_Position();
		Vector3 objectToLight;
		objectToLight.Set(1.0f,0.0f,0.0f);

		SurfaceClass::SurfaceDescription surface_desc;
		((Rva001085B4 *)m_shadowTexture[0])->rva001085B4().Get_Surface_Level().Get_Description(surface_desc);
		//default shadow texture points along world -x axis (west).  Rotate uv coordinates to fit actual light direction
		Vector3 uVec = objectToLight * DECAL_TEXELS_PER_WORLD_UNIT / (float)surface_desc.Width;
		objectToLight.Rotate_Z(-1.0f,0.0f);	//rotate u vector by -90 degress to get v vector.
		Vector3 vVec = objectToLight * DECAL_TEXELS_PER_WORLD_UNIT / (float)surface_desc.Height;

		m_shadowTexture[0]->setDecalUVAxis(uVec, vVec);

		Region3D	box;
		SphereClass	sphere;
		m_robj->Get_Obj_Space_Bounding_Box(box);	//shadow uses same bounding box as object
		m_robj->Get_Obj_Space_Bounding_Sphere(sphere);

		m_shadowTexture[0]->setBoundingSphere(sphere);
		m_shadowTexture[0]->setBoundingBox(box);
	}

	m_shadowTexture[0]->setLightPosHistory(lightPos);	//store position of light at time of texture update.
}

void W3DShadowTexture::updateBounds(Vector3 &lightPos, RenderObjClass *robj)
{
		ShadowProjectionBox &box=m_areaEffectBox;	///@todo: fix for multiple lights
		Vector3			objPos;
		Vector3 Corners[8];
		Vector3 lightRay;
		Real floorZ;
		Real vectorScale,vectorScaleTemp, vectorScaleMax,length;
		
		//calculate local bounding box of shadow projection
		objPos=robj->Get_Position();
		((Region3D *)&m_areaEffectBox)->Region3D::Region3D(robj->Get_Bounding_Box());
		floorZ = objPos.Z - 2.0f;	//lower slightly so shadows go under ground.

		//project each box corner to base of object to determine rough extent of shadow
		//Get vertices of top of bounding box
		Corners[0]=box.Center+box.Extent;	//top right corner
		Corners[1]=Corners[0];
		Corners[1].X -= 2.0f*box.Extent.X;		//top left corner
		Corners[2]=Corners[1];
		Corners[2].Y -= 2.0f*box.Extent.Y;		//bottom left corner
		Corners[3]=Corners[2];
		Corners[3].X += 2.0f*box.Extent.X;		//bottom right corner

		//Project top volume corners onto ground plane
		lightRay = Corners[0] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleMax=vectorScale=(Real)fabs((Corners[0].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[4]=Corners[0]+lightRay*vectorScale;
		vectorScaleMax *= length;

		lightRay = Corners[1] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[1].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[5]=Corners[1]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		lightRay = Corners[2] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScale=(Real)fabs((Corners[2].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[6]=Corners[2]+lightRay*vectorScale;
		vectorScale *= length;

		if (vectorScale > vectorScaleMax)
			vectorScaleMax=vectorScale;	//keep track of maximum required extrusion length.

		lightRay = Corners[3] - lightPos;	//vector light to corner
		length= 1.0f/lightRay.Length();
		lightRay *= length;
		vectorScaleTemp=(Real)fabs((Corners[3].Z-floorZ)/lightRay.Z);	//length of vector from top corner to ground.
		Corners[7]=Corners[3]+lightRay*vectorScaleTemp;
		vectorScaleTemp *= length;

		if (vectorScaleTemp > vectorScaleMax)
			vectorScaleMax=vectorScaleTemp;	//keep track of maximum required extrusion length.

		box.Init(Corners, 8);	//generate a new bounding box to fit the shadow projection
		m_areaEffectSphere.Init(box.Center,box.Extent.Length());

		m_areaEffectSphere.Center -= objPos;	//translate sphere to object space.
		box.Translate(-objPos);	//translate box to object space.
}

