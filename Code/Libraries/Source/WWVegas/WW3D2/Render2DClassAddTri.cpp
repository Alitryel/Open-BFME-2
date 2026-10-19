// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME1 donor revision 0bef414; readable body of ?Add_Tri@Render2DClass@@: game/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME1 semantic donor triangle overload at 0x006EB070; BFME2 target0x00045708, 293B.
//
// Sibling of Render2DClassAddQuad.cpp (Add_Quad, retail 0x006E7210): same
// active-batch vertex layout, allocateGeometry006e helper, coordinate
// conversion and color-converter global, just for three vertices instead of
// four, one shared color instead of per-vertex colors, and 16-bit indices
// written individually instead of packed as dword pairs.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../../reference/shims/wwmath/Vector2.h"
#include <math.h>

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32(__cdecl *BfmeColorConverter)(BfmeUInt32 color);

// Native DEC49C already defined by Rva00118B50State.cpp.
extern float g_Va00DEC49C;

// BFME1 converter storage was 0x012D7198; BFME2 binds the existing 0x00DB5FC8 owner.
// Existing BFME2 global g_Va00DB5FC8 is defined by GlobalGetterSingles.cpp.
// (game/GameEngine/Source/Common/TinyGlobalStores.cpp).  That file has no
// header, so its class definition is repeated here verbatim.  Retail keeps a
// function pointer in the slot the setter writes as an int, so the call is made
// through the address of the member rather than through a pointer variable.
extern int g_Va00DB5FC8;

// Retail calls the pointer stored in the slot, so the call goes through the
// memory at the member's address rather than through a register copy of it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	void set00(unsigned v) { m_state = v; }
	void set48(bool b) { m_active48 = b; }
private:
	unsigned int m_state;
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;
	unsigned char m_unmodelled_14[0x34];
	bool m_active48;
	unsigned char m_unmodelled_49[0x0B];
	unsigned char m_texturingEnabled;

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
        vertex.z = g_Va00DEC49C;
	}

	void convertFirstPosition(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
        // Preserve the native v0 Y-store before loading the next position.
        // The intrinsic emits no instruction and keeps the three writes ordered.
        _ReadWriteBarrier();
        vertex.z = g_Va00DEC49C;
	}

public:
	void Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
		const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
		BfmeUInt32 color);
};

// ?Add_Tri@Render2DClass@@QAEXABVVector2@@00000K@Z
void Render2DClass::Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
	const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
	BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(
		3, 3, &indices, &baseVertexPair);

	convertFirstPosition(vertices[0], v0);
	
	convertPosition006e(vertices[1], v1);
	
	convertPosition006e(vertices[2], v2);
	

	vertices[0].u = uv0.X;
	vertices[0].v = uv0.Y;
	vertices[1].u = uv1.X;
	vertices[1].v = uv1.Y;
	vertices[2].u = uv2.X;
	vertices[2].v = uv2.Y;

	BfmeUInt32 convertedColor = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	vertices[2].color = convertedColor;
	vertices[1].color = convertedColor;
	vertices[0].color = convertedColor;

	reinterpret_cast<unsigned short *>(indices)[0] = (unsigned short)baseVertexPair;
	reinterpret_cast<unsigned short *>(indices)[1] = (unsigned short)baseVertexPair + 1;
	reinterpret_cast<unsigned short *>(indices)[2] = (unsigned short)baseVertexPair + 2;
}

// --- W3DDisplay radial image clock (0x000471AD) and its file-static texture
// getter (0x000470D5), retail neighbours of Add_Tri 0x00045708 in the
// W3DDisplay code range. VC7.1 shares the clock's stack slots like retail
// (handle temporary in its own -0x28 slot, width's x87 transfer packed into
// endUV.Y at -0x2C, frame 0x4C) only when Add_Tri, which receives the
// addresses of the six Vector2 locals, has its body visible in the TU; here it
// is the unit's own rowed definition. Getter is exact only as a TU static
// beside its caller (hidden result loaded into EDI once at entry).
#include "ascii_string.h"
float atan2(float, float);

class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};

template<class T> class RefCountPtr
{
public:
	~RefCountPtr();
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			++other.Referent->m_refCount;
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	T *Referent;
};
template<class T> bool operator!=(RefCountPtr<T> const &a, RefCountPtr<T> const &b) { return a.Referent != b.Referent; }

class ShroudFilter { public: int m_00, m_04, m_08, m_0C, m_10; };
class ShroudTexture { public: ShroudFilter *getFilter(void); };
class BFME2ParticleTextureHandle;
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char*,int,int);
	void rva00132FE9(bool flag);
};
class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
	~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
	ShroudFilter *getFilter() { return ((ShroudTexture *)this)->getFilter(); }
	void setQuality(bool b) { ((TextureAsset *)this)->rva00132FE9(b); }
};

class RectClass{public:float Left,Top,Right,Bottom;float Width()const{return Right-Left;}float Height()const{return Bottom-Top;}};
class Image
{
public:
	char gap[0x8];
	AsciiString m_filename;
	char gap0C[0x8];
	RectClass uv;
	char gap24[0x8];
	BFME2ParticleTextureHandle *m_rawTextureData;
	unsigned int m_status;
};
struct Rva000470D5Source
{
	int m_00;
	int m_04;
	AsciiString m_name08;
	char m_pad0C[0x2C - 0x0C];
	BFME2ParticleTextureHandle *m_texture2C;
	unsigned int m_flags30;
	unsigned int getStatus() const { return m_flags30; }
	const AsciiString &getFilename() const { return m_name08; }
};
static BFME2ParticleTextureHandle Rva000470D5GetTexture(const Rva000470D5Source *src)
{
	if (src->getStatus() & 2) {
		BFME2ParticleTextureHandle tex(*src->m_texture2C);
		tex.getFilter()->m_10 = 1;
		tex.getFilter()->m_0C = 1;
		return tex;
	} else {
		BFME2ParticleTextureHandle tex(TextureAsset::Get(src->getFilename().str(), 1, 0));
		tex.getFilter()->m_10 = 1;
		tex.getFilter()->m_0C = 1;
		tex.setQuality(true);
		return tex;
	}
}

class Rva000456C9{public:void rva000456C9(const RefCountPtr<TextureClass>*);};
class W3DDisplay{public:virtual void Rva000471AD(const Image*,float,float,float,float,float,unsigned long);char gap04[0x164];Render2DClass*render;};
inline float clockPi(){return 3.14159265358979323846f;}
void W3DDisplay::Rva000471AD(const Image*image,float left,float top,float right,float bottom,float percent,unsigned long color)
{
 if(!image)return;
 const RectClass*uv=&image->uv;
 if(!uv)return;
 static float halfPi=clockPi()/2.0f;
 static float threeHalfPi=clockPi()*1.5f;
 static float twoPi=clockPi()*2.0f;
 float angle=twoPi-(twoPi*percent)*0.01f;
 if(angle<=0.0f)return;
 if(angle>twoPi)angle=twoPi;
 render->set00(2);
 render->set48(true);
 ((Rva000456C9*)render)->rva000456C9((const RefCountPtr<TextureClass>*)&Rva000470D5GetTexture((const Rva000470D5Source*)image));
 float height=bottom-top;
 float halfHeight=height*0.5f;
 float width=right-left;
 float halfWidth=width*0.5f;
 Vector2 center(left+halfWidth,top+halfHeight);
 float widthHeight=width/height;
 float heightWidth=height/width;
 float halfU=uv->Width()*0.5f;
 float halfV=uv->Height()*0.5f;
 Vector2 centerUV(uv->Left+halfU,uv->Top+halfV);
 float corner=atan2(width,height);
 Vector2 end(left,top);
 Vector2 endUV(uv->Left,uv->Top);
 Vector2 start(center.X,top);
 Vector2 startUV(centerUV.X,uv->Top);
 bool done=false;
 if(angle<=corner){
  float t=tanf(angle);
  end.X=(float)(center.X-halfHeight*t);
  endUV.X=(float)(centerUV.X-t*halfU*heightWidth);
  done=true;
 }
 render->Add_Tri(center,end,start,centerUV,endUV,startUV,color);
 if(done)return;
 float boundary2=3.14159265358979323846f-corner;
 start.X=end.X;start.Y=top;startUV=endUV;
 end.Y=bottom;endUV.Y=uv->Bottom;
 if(angle<=boundary2){
  if(angle>halfPi){
   float t=(float)tan(angle-halfPi);
   end.Y=(float)(center.Y+halfWidth*t);
   endUV.Y=(float)(centerUV.Y+t*halfV*widthHeight);
  }else{
   float t=(float)tan(halfPi-angle);
   end.Y=(float)(center.Y-halfWidth*t);
   endUV.Y=(float)(centerUV.Y-t*halfV*widthHeight);
  }
  done=true;
 }
 render->Add_Tri(center,end,start,centerUV,endUV,startUV,color);
 if(done)return;
 float boundary3=corner+3.14159265358979323846f;
 start=end;startUV=endUV;
 end.X=right;endUV.X=uv->Right;
 if(angle<=boundary3){
  if(angle>3.14159265358979323846f){
   float t=(float)tan(angle-3.14159265358979323846f);
   end.X=(float)(center.X+halfHeight*t);
   endUV.X=(float)(centerUV.X+t*halfU*heightWidth);
  }else{
   float t=(float)tan(3.14159265358979323846f-angle);
   end.X=(float)(center.X-halfHeight*t);
   endUV.X=(float)(centerUV.X-t*halfU*heightWidth);
  }
  done=true;
 }
 render->Add_Tri(center,end,start,centerUV,endUV,startUV,color);
 if(done)return;
 float boundary4=twoPi-corner;
 start=end;startUV=endUV;
 end.Y=top;endUV.Y=uv->Top;
 if(angle<=boundary4){
  if(angle>threeHalfPi){
   float t=(float)tan(angle-threeHalfPi);
   end.Y=(float)(center.Y-halfWidth*t);
   endUV.Y=(float)(centerUV.Y-t*halfV*widthHeight);
  }else{
   float t=(float)tan(threeHalfPi-angle);
   end.Y=(float)(center.Y+halfWidth*t);
   endUV.Y=(float)(centerUV.Y+t*halfV*widthHeight);
  }
  done=true;
 }
 render->Add_Tri(center,end,start,centerUV,endUV,startUV,color);
 if(done)return;
 start=end;startUV=endUV;
 end.X=center.X;endUV.X=centerUV.X;
 float remaining=twoPi-angle;
 if(remaining>0.0001f){
  float t=(float)tan(remaining);
  end.X=(float)(center.X+halfHeight*t);
  endUV.X=(float)(centerUV.X+t*halfU*heightWidth);
 }
 render->Add_Tri(center,end,start,centerUV,endUV,startUV,color);

}
