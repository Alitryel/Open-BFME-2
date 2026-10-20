// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// WaterTracksObj::init, ported from Open-BFME-1 9cbfb551fe20
// GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp and
// guided by Zero Hour's W3DWaterTracks.cpp.
//
// Target facts (native FE379..FE8FC, RET 0x1C, seven arguments from the
// editor callers): bounds +0x08..+0x2C, wave type +0x30, start +0x40,
// initial start/end +0x58/+0x60, time offset +0x68 and the timing block
// +0x6C..+0xAC. BFME 2 adds an optional map-settings object whose values
// override the per-type wave table; its class is unknown, so its getters
// are reached through the providers already rowed at their addresses
// (0x30C934/0x30C8CC/0x30C8E6/0x30C900 address-named float-to-int getters,
// 0x30C8A7 and 0x5508E2 ICF-folded int getters at +0x80/+0x84).
// BFME 2 also computes timeToStop before timeToReachBeach (retail's x87
// load order of the total-time sum needs that statement order).
#include "vector2.h"
#include "vector3.h"
#include "sphere.h"
#include <math.h>
#include "region.h"
#include "ascii_string.h"
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr { public: T *m_ptr; const RefCountPtr &operator=(const RefCountPtr &); ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();} };
class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass> {};
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *,int,int);
};
float GetGameClientRandomValueReal(float,float,char *,int);
class Rva0030C934IntGetter { public: int get()const; };
class Rva0030C8CCIntGetter { public: int get()const; };
class Rva0030C8E6IntGetter { public: int get()const; };
class Rva0030C900IntGetter { public: int get()const; };
class RenderObjClass { public: virtual void *Get_User_Data(); };
class Drawable; class Thing { public: Drawable *getDrawable()const; };
struct waveInfo { float finalWidth,finalHeight,distance,velocity; int fadeMs; float widthFraction,heightFraction; int compressMs,secondOffset; char *textureName,*typeName; };
// Zero Hour's per-type wave table, unchanged in BFME 2: retail 0x009B5C18 holds
// these five 44-byte entries and a zero WaveTypeStationary slot (WaveTypeMax 6),
// both texture pointers on one pooled "wave256.tga" literal.
waveInfo waveTypeInfo[6]= //TODO: Move this into INI
{
	{	28.0f,	18.0f,	25.0f,	0.018f,	900,	0.01f,	0.18f,	1500,	0,		"wave256.tga",	"Pond"},	//pond
	{	28.0f,	18.0f,	40.0f,	0.005f,	2000,	0.5f,	1.0f,	1000,	6267,	"wave256.tga",	"Ocean"},	//ocean
	{	55.0f,	36.0f,	80.0f,	0.015f,	2000,	0.05f,	0.18f,	1000,	6267,	"wave256.tga",	"Close Ocean"},	//close ocean
	{	55.0f,	36.0f,	80.0f,	0.015f,	4000,	0.01f,	0.18f,	2000,	6267,	"wave256.tga",	"Close Ocean Double"},	//close ocean double
	{	55.0f,	27.0f,	80.0f,	0.015f,	2000,	0.01f,	8.0f,	2000,	5367,	"wave256.tga",	"Radial"},	//radial
};
// The bounding sphere is a real SphereClass (its out-of-line copy is what the
// bounds getter calls); init() keeps the inline field-wise Init it was
// matched with.
struct InitSphere : SphereClass { void Init(const Vector3 &v,float r) {Center=v;Radius=r;} };
struct InitBox { Vector3 Center,Extent; };
class WaterTracksObj {
public:
 BFME2ParticleTextureHandle texture;
 InitSphere sphere; InitBox box;
 int type,x,y; bool bound; Vector2 startPos,waveDir,perpDir,initStart,initEnd;
 int initOffset,fadeMs,totalMs,elapsedMs;
 float initialWidth,initialHeight,finalWidth,peakFraction,finalHeight;
 float velocity,distance,timeToBeach,frontAcc,timeToStop,timeToRetreat,backAcc,timeToCompress,flipU;
 WaterTracksObj *next,*previous;
 void init(float,float,Vector2&,Vector2&,char*,int,void*);
 virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &out) const;
 virtual void Get_Obj_Space_Bounding_Box(Region3D &out) const;
};
// Target FE440..FE488 evaluates cos before sin, then Y*cos + X*sin.
// Keep that arithmetic visible locally without changing the shared donor header.
static __forceinline void rotateInit(Vector2 &v,float angle)
{
 float c=WWMath::Cos(angle);float s=WWMath::Sin(angle);
 float x=v.X*c-v.Y*s;float y=v.Y*c+v.X*s;
 v.X=x;v.Y=y;
}
// Retail 0x000FE359 (16 bytes), the vftable slot after the destructor: the
// Zero Hour body, a SphereClass copy of the +0x08 bounds.
void WaterTracksObj::Get_Obj_Space_Bounding_Sphere(SphereClass &out) const
{
 out=sphere;
}
void WaterTracksObj::Get_Obj_Space_Bounding_Box(Region3D &out) const
{
 out.Region3D::Region3D(*(Region3D*)&box);
}
void WaterTracksObj::init(float width,float length,Vector2 &start,Vector2 &end,char *textureName,int timeOffset,void *settings)
{
 initStart=start;initEnd=end;initOffset=timeOffset;
 sphere.Init(Vector3(0,0,0),400);
 box.Center.Set(0,0,0);box.Extent.Set(400,400,1);
 x=2;y=2;elapsedMs=-initOffset;
 startPos=start;perpDir=waveDir=end-start;
 rotateInit(perpDir,-1.57079632679f);perpDir.Normalize();
 waveDir=perpDir;waveDir.Rotate(1.57079632679f);
 char *randomFile="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp";
 distance=settings?reinterpret_cast<Rva0030C934IntGetter*>(settings)->get():waveTypeInfo[type].distance;
 distance*=GetGameClientRandomValueReal(0.9f,1.1f,randomFile,219);
 waveDir*=distance;startPos-=waveDir;
 velocity=settings?reinterpret_cast<Rva0030C8CCIntGetter*>(settings)->get()*0.001f:waveTypeInfo[type].velocity;
 totalMs=distance/velocity;
 fadeMs=settings?reinterpret_cast<Rva0030C8E6IntGetter*>(settings)->get():waveTypeInfo[type].fadeMs;
 fadeMs*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,228);
 initialWidth=settings?reinterpret_cast<int>(reinterpret_cast<RenderObjClass*>(settings)->RenderObjClass::Get_User_Data())*0.01f:waveTypeInfo[type].widthFraction;
 initialWidth*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,231)*length;
 initialHeight=settings?reinterpret_cast<int>(reinterpret_cast<Thing*>(settings)->getDrawable())*0.01f:waveTypeInfo[type].heightFraction;
 initialHeight*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,233)*width;
 finalWidth=length*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,234);
 finalHeight=width*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,235);
 frontAcc=-(velocity*velocity)/(2*finalHeight);
 timeToStop=-velocity/frontAcc;
 timeToBeach=(distance-finalHeight)/velocity;
 timeToRetreat=sqrt(fabs(2.0f*finalHeight/frontAcc));
 totalMs=timeToBeach+timeToStop+timeToRetreat;
 backAcc=(2.0f*initialHeight)/(timeToStop*timeToStop);
 timeToCompress=settings?reinterpret_cast<Rva0030C900IntGetter*>(settings)->get():waveTypeInfo[type].compressMs;
 timeToCompress*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,245);
 if(type==5) {timeToRetreat=1000;totalMs=timeToBeach+timeToStop+fadeMs+timeToRetreat;startPos=start;fadeMs=1000;}
 texture=TextureAsset::Get(textureName,0,0);
}
// Retail 0x000FF5E6, the Zero Hour loadTracks counterpart (WorldBuilder 0x829D80): rebuilds the
// tracks from the map's track areas; findTrack and init stay visible so the endpoints are unaliased.
struct Rva001408C0Target;
namespace _STL
{
template <class T> struct _Identity {};
template <class T> struct less {};
template <class T> class allocator {};
template <class Key, class Value, class Identity, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();
private:
	void *m_storage[3];
};
template <class T, class Compare, class Allocator>
class set
{
	typedef _Rb_tree<T, T, _Identity<T>, Compare, Allocator> Tree;
	Tree m_tree;
public:
	set();
	~set() {}
};
}
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>, _STL::allocator<Rva001408C0Key> > Rva001408C0Set;
struct AssetList00208F90
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList00208F90 &operator<<(const AsciiString &name);
	AssetList00208F90 &operator<<(const char *name);
};
class Rva009EB960;extern Rva009EB960 *Rva0134FAA0;
void bfmeMergeReceiverKeys(int);

class Rva0030C94ADwordField {public:int get()const;};
class Rva0030C91AIntGetter {public:int get()const;};
class Rva0030C890IntGetter {public:int get()const;};
class Rva0030C896DwordField {public:int get()const;};
class Rva000B28F2LeaGetter {public:void *get()const;};
struct Rva0007E394Element {char unknown00[0x38];Vector2 *begin,*end,*capacity;};
struct TrackCollection;
// Native cursor storage is an owner pointer followed by a record ordinal.
// Retail's two-dword cursor equality at 0x7E394, defined here so the caller sees it keeps no cursor address.
extern "C" inline __declspec(noinline) bool __cdecl rva0007E394CursorEqual(const void*a,const void*b){return ((const unsigned*)a)[0]==((const unsigned*)b)[0]&&((const unsigned*)a)[1]==((const unsigned*)b)[1];}
struct MapEntry {unsigned key;Rva0007E394Element *value;};
struct TrackCollection {
 class const_iterator {
 public:
  const_iterator(TrackCollection *set,int index):m_set(set),m_index(index){}
  Rva0007E394Element *getPtr()const{return m_set->m_begin[m_index].value;}
  const_iterator &operator++(){++m_index;return *this;}
  const_iterator operator++(int){const_iterator old=*this;++*this;return old;}
  bool operator!=(const const_iterator &it)const{return !(*this==it);}
  friend bool operator==(const const_iterator &a,const const_iterator &b){return rva0007E394CursorEqual(&a,&b);}
  TrackCollection *m_set;int m_index;
 };
 char unknown00[0x14];MapEntry *m_begin,*m_end,*m_capacity;
 const_iterator begin(){return const_iterator(this,0);}
 const_iterator end(){return const_iterator(this,m_end-m_begin);}
};
struct WaterMapView {char unknown00[0x124];TrackCollection *tracks;};
extern void *W3DGCData00DE2000;
struct FeNode {unsigned char m_pad0[0x30];int m_30;unsigned char m_pad1[0x3c-0x34];unsigned char m_flag3c;unsigned char m_pad2[0x58-0x3d];float m_58;float m_5c;float m_60;float m_64;unsigned char m_pad3[0xb0-0x68];FeNode *m_next;FeNode *m_prev;};
enum waveType {WaveTypePond,WaveTypeOcean};
class WaterTracksRenderSystem {public:WaterTracksObj *bindTrack(waveType);void rva000FE188();__declspec(noinline) FeNode*rva000FE207(const float*,const float*,int);unsigned char m_pad[0x10];FeNode *m_tail10;FeNode *m_head14;};
// Retail 0x000FE207, rowed in Rva000FE207Find.cpp; this select-any copy shows loadTracks
// that the search keeps no endpoint address.
inline FeNode *WaterTracksRenderSystem::rva000FE207(const float *a, const float *b, int c)
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		unsigned char d1 = (node->m_60 == b[0]) ? 1 : 0;
		unsigned char a1 = (node->m_64 == b[1]) ? 1 : 0;
		if ((d1 & a1) != 0)
		{
			unsigned char d2 = (node->m_58 == a[0]) ? 1 : 0;
			unsigned char a2 = (node->m_5c == a[1]) ? 1 : 0;
			if ((d2 & a2) != 0)
			{
				if (node->m_30 == c)
					return node;
			}
		}
		node = node->m_next;
	}
	return 0;
}
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
class Rva0007E90ECallee {public:char unknown00[0x28];AsciiString file;void rva000FF5E6(int);};
class File {public:enum {READ=0x01,BINARY=0x40};enum seekMode {START,CURRENT,END};
 virtual ~File();virtual void open();virtual void close();virtual int read(void*,int);virtual int write(const void*,int);virtual int seek(int,seekMode);
 virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual File *convertToRAMFile();};
class FileSystem {public:File *openFile(const char*,int,int);};
extern FileSystem *TheFileSystem;
extern "C" char * __cdecl strcpy(char *,const char *);extern "C" unsigned int __cdecl strlen(const char *);
void Rva0007E90ECallee::rva000FF5E6(int filename)
{
 file=*reinterpret_cast<const AsciiString*>(filename);
 bool loadFromFile=false;
 if(loadFromFile) {
  AsciiString fileName=file;
  char path[256];
  strcpy(path,fileName.str());
  int len=strlen(path);
  strcpy(path+len-4,".wak");
  File *wakFile=TheFileSystem->openFile(path,File::READ|File::BINARY,0);
  int trackCount=0;
  int flipU=0;
  Vector2 startPos,endPos;
  waveType wtype;
  AssetList00208F90 assetList;
  if(wakFile) {
   wakFile=wakFile->convertToRAMFile();
   wakFile->seek(-4,File::END);
   wakFile->read(&trackCount,sizeof(trackCount));
   wakFile->seek(0,File::START);
   for(int i=0;i<trackCount;i++) {
   tryagain:
    wakFile->read(&startPos,sizeof(startPos));
    wakFile->read(&endPos,sizeof(endPos));
    wakFile->read(&wtype,sizeof(wtype));
    //Check if this track already exists.
    if(reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE207(&startPos.X,&endPos.X,wtype)) {
     i++;
     goto tryagain;
    }
    WaterTracksObj *umod=TheWaterTracksRenderSystem->bindTrack(wtype);
    if(umod) {	//umod->init(1.5f*MAP_XY_FACTOR,Vector2(0,0),Vector2(1,1),"wave256.tga");
     flipU^=1;	//toggle flip state
     umod->init(waveTypeInfo[wtype].finalHeight,waveTypeInfo[wtype].finalWidth,startPos,endPos,waveTypeInfo[wtype].textureName,0,0);
     assetList<<waveTypeInfo[wtype].textureName;
     umod->flipU=flipU;
     if(waveTypeInfo[wtype].secondOffset) {	//check if we need a second wave to follow
      umod=TheWaterTracksRenderSystem->bindTrack(wtype);
      if(umod) {
       umod->init(waveTypeInfo[wtype].finalHeight,waveTypeInfo[wtype].finalWidth,startPos,endPos,waveTypeInfo[wtype].textureName,waveTypeInfo[wtype].secondOffset,0);
       umod->flipU=!flipU;
      }
     }
    }
   }
   wakFile->close();
  }
  if(Rva0134FAA0)bfmeMergeReceiverKeys(reinterpret_cast<int>(&assetList));
 } else {
 reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE188();
 int trackCount=0;
 int flipU=0;
 Vector2 startPos,endPos;
 waveType wtype;
 AssetList00208F90 assets;
 if(!W3DGCData00DE2000)
  return;
  TrackCollection *collection=reinterpret_cast<WaterMapView*>(W3DGCData00DE2000)->tracks;
  for(TrackCollection::const_iterator it=(collection?collection:collection)->begin();it!=collection->end();it++) {
   Rva0007E394Element *record=it.getPtr();
   if(reinterpret_cast<Rva0030C94ADwordField*>(record)->get())continue;
   int numPoints=record->end-record->begin;
   if(numPoints<2)continue;
   trackCount=numPoints-1;
   for(int i=0;i<trackCount;i++) {
    int next=i+1;Vector2 *base=record->begin;const Vector2 &a=base[i];const Vector2 &b=base[next];Vector2 start(a.X,a.Y);Vector2 end(b.X,b.Y);
    Vector2 dir(end.X-start.X,end.Y-start.Y);
    Vector2 midpoint=start+dir*0.5f;
    startPos=midpoint;
    Vector2 &perp=dir;perp.Rotate(1.57079632679f);perp.Normalize();
    endPos=midpoint;
    endPos+=perp;
    wtype=WaveTypeOcean;
    //Check if this track already exists.
    if(reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE207(&startPos.X,&endPos.X,wtype))continue;
    WaterTracksObj *track=TheWaterTracksRenderSystem->bindTrack(wtype);
    if(track) {
     float fraction=GetGameClientRandomValueReal(0.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp",1141);
     int offset=fraction*reinterpret_cast<Rva0030C91AIntGetter*>(record)->get();
     flipU^=1;	//toggle flip state
     // Retail uses the same midpoint and shifted midpoint order as findTrack.
     track->init(float(reinterpret_cast<Rva0030C896DwordField*>(record)->get()),float(reinterpret_cast<Rva0030C890IntGetter*>(record)->get()),startPos,endPos,const_cast<char*>(static_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get())->str()),offset,record);
     assets<<*static_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get());
     track->flipU=flipU;
    }
   }
  }
  if(Rva0134FAA0)bfmeMergeReceiverKeys(reinterpret_cast<int>(&assets));
 }
}
