// ?Rva000471AD@W3DDisplay@@UAEXPBVImage@@MMMMMK@Z
// partial score=0.994 date=2026-10-19
// ?Rva000471AD@W3DDisplay@@UAEXPBVImage@@MMMMMK@Z
// partial score=0.99 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /ICode/GameEngineDevice/Source/W3DDevice/GameClient
// Bank state (size-exact 1474 B, 9 diff lines): <math.h> float tan overload
// with tanf at the first site gives retail's pop placement and done flag
// order; in-class render setters (+0 and +0x48, as in the BFME 1 twin
// 0x006F1AC0) give retail's image=edx / const2=ecx / render=eax registers;
// RectClass Width()/Height() inline readers restore the halfU-first SSE
// block the setters otherwise reshuffle. Residue: retail keeps the 0x470D5
// handle temp in its own slot (-0x28) and packs width's x87 transfer temp
// into endUV.Y (-0x2c); the dead-throw lever puts the handle temp in
// percent's dead home (+0x1c) instead. Without the lever the frame is 0x50;
// any nested block for the triangle locals packs both (frame 0x48). Callee
// 0x000470D5 is still unmatched and unpinned.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// (inlined from the scratch hcopy.h: handle view with the inline copy ctor)
// BFME 2 one-pointer texture ownership views, established by the matched
// particle texture loader, fallback getters and native release/copy providers.
#ifndef BFME2_PARTICLE_TEXTURE_HANDLES_H
#define BFME2_PARTICLE_TEXTURE_HANDLES_H
class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};

// Inline acquisition has its own overload because this /O1 caller uses INC;
// the ordinary out-of-line copy provider at 0x001494F0 uses ADD. Keep that
// provider declaration while reproducing the verified inline caller expansion.
template<class T> class RefCountPtr
{
public:
    RefCountPtr() : Ptr(0) {}
    RefCountPtr(const RefCountPtr &other);
    enum InlineCopy { COPY_INLINE };
    __forceinline RefCountPtr(const RefCountPtr &other, InlineCopy)
        : Ptr(other.Ptr)
    {
        if (Ptr)
            ++Ptr->m_refCount;
    }
    ~RefCountPtr();
    T *Ptr;
};

class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle() : Ptr(0) {}
	BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
	BFME2ParticleTextureHandle(TextureClass *ptr);
	enum InlineAcquire { ACQUIRE_INLINE };
	__forceinline BFME2ParticleTextureHandle(TextureClass *ptr, InlineAcquire) : Ptr(ptr)
	{
		if (Ptr)
			++Ptr->m_refCount;
	}
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};

#endif

#include <math.h>
#include "ascii_string.h"
class ShroudFilter { public: int m_00, m_04, m_08, m_0C, m_10; };
class ShroudTexture { public: ShroudFilter *getFilter(void); };
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *, int, int);
	void rva00132FE9(bool flag);
};
const float ClockPi=3.14159265358979323846f;
class Vector2{public:float X,Y;Vector2&operator=(const Vector2&v){X=v.X;Y=v.Y;return *this;}};
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
	unsigned int getStatus() const { return m_status; }
	const AsciiString &getFilename() const { return m_filename; }
};
static BFME2ParticleTextureHandle Rva000470D5(const Image *image)
{
	if (image->getStatus() & 2) {
		BFME2ParticleTextureHandle texture(*image->m_rawTextureData);
		((ShroudTexture *)&texture)->getFilter()->m_10 = 1;
		((ShroudTexture *)&texture)->getFilter()->m_0C = 1;
		return texture;
	} else {
		BFME2ParticleTextureHandle texture(TextureAsset::Get(image->getFilename().str(), 1, 0));
		((ShroudTexture *)&texture)->getFilter()->m_10 = 1;
		((ShroudTexture *)&texture)->getFilter()->m_0C = 1;
		((TextureAsset *)&texture)->rva00132FE9(true);
		return texture;
	}
}
class Rva000456C9{public:void rva000456C9(const RefCountPtr<TextureClass>*);};
class Render2DClass{public:void set00(unsigned v){state=v;}void set48(bool b){active=b;}void Add_Tri(const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,unsigned long) throw();unsigned state;char gap04[0x44];bool active;};
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
 ((Rva000456C9*)render)->rva000456C9((const RefCountPtr<TextureClass>*)&Rva000470D5(image));
 float height=bottom-top;
 float halfHeight=height*0.5f;
 float width=right-left;
 float halfWidth=width*0.5f;
 Vector2 center={left+halfWidth,top+halfHeight};
 float widthHeight=width/height;
 float heightWidth=height/width;
 float halfU=uv->Width()*0.5f;
 float halfV=uv->Height()*0.5f;
 Vector2 centerUV={uv->Left+halfU,uv->Top+halfV};
 float corner=atan2f(width,height);
 Vector2 end={left,top};
 Vector2 endUV={uv->Left,uv->Top};
 Vector2 start={center.X,top};
 Vector2 startUV={centerUV.X,uv->Top};
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
