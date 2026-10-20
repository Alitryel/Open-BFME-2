// ?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z
// partial score=0.97 date=2026-10-20
// ?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z
// partial score=0.95 date=2026-10-19
// ?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z
// partial score=0.95 date=2026-10-18
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#define _OPERATOR_NEW_DEFINED_
#include "vector2.h"

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
struct FeNode;
class WaterTracksObj {public:char unknown00[0xac];float flipU;void init(float,float,Vector2&,Vector2&,char*,int,void*);};
enum waveType {WaveTypePond,WaveTypeOcean};
class WaterTracksRenderSystem {public:WaterTracksObj *bindTrack(waveType);void rva000FE188();FeNode*rva000FE207(const float*,const float*,int);};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
class Rva0007E90ECallee {public:char unknown00[0x28];AsciiString file;void rva000FF5E6(int);};
class File {public:enum {READ=0x01,BINARY=0x40};enum seekMode {START,CURRENT,END};
 virtual ~File();virtual void open();virtual void close();virtual int read(void*,int);virtual int write(const void*,int);virtual int seek(int,seekMode);
 virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual File *convertToRAMFile();};
class FileSystem {public:File *openFile(const char*,int,int);};
extern FileSystem *TheFileSystem;
struct WaveInfo {float m_finalWidth;float m_finalHeight;float m_waveDistance;float m_initialVelocity;int m_fadeMs;float m_initialWidthFraction;float m_initialHeightWidthFraction;int m_timeToCompress;int m_secondWaveTimeOffset;char *m_textureName;char *m_waveTypeName;};
extern WaveInfo waveTypeInfo[];
extern "C" char * __cdecl strcpy(char *,const char *);extern "C" unsigned int __cdecl strlen(const char *);
float GetGameClientRandomValueReal(float,float,char*,int);
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
    if(umod) {
     flipU^=1;	//toggle flip state
     umod->init(waveTypeInfo[wtype].m_finalHeight,waveTypeInfo[wtype].m_finalWidth,startPos,endPos,waveTypeInfo[wtype].m_textureName,0,0);
     assetList<<waveTypeInfo[wtype].m_textureName;
     umod->flipU=flipU;
     if(waveTypeInfo[wtype].m_secondWaveTimeOffset) {	//check if we need a second wave to follow
      umod=TheWaterTracksRenderSystem->bindTrack(wtype);
      if(umod) {
       umod->init(waveTypeInfo[wtype].m_finalHeight,waveTypeInfo[wtype].m_finalWidth,startPos,endPos,waveTypeInfo[wtype].m_textureName,waveTypeInfo[wtype].m_secondWaveTimeOffset,0);
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
 struct SegmentEndpoints {Vector2 shifted,midpoint;};
 SegmentEndpoints guide;Vector2 &startPos=guide.midpoint;Vector2 &endPos=guide.shifted;
 int flipU=0;AssetList00208F90 assets;
 if(!W3DGCData00DE2000)
  return;
  TrackCollection *collection=reinterpret_cast<WaterMapView*>(W3DGCData00DE2000)->tracks;
  for(TrackCollection::const_iterator it=(collection?collection:collection)->begin();it!=collection->end();it++) {
   Rva0007E394Element *record=it.getPtr();
   if(reinterpret_cast<Rva0030C94ADwordField*>(record)->get())continue;
   int count=record->end-record->begin;
   if(count<2)continue;
   int segments=count-1;
   for(int i=0;i<segments;++i) {
    int next=i+1;Vector2 *base=record->begin;const Vector2 &a=base[i];const Vector2 &b=base[next];Vector2 start(a.X,a.Y);Vector2 end(b.X,b.Y);
    Vector2 dir(end.X-start.X,end.Y-start.Y);
    Vector2 midpoint=start+dir*0.5f;
    startPos=midpoint;
    Vector2 &perp=dir;perp.Rotate(1.57079632679f);perp.Normalize();
    endPos=midpoint;
    endPos+=perp;
    //Check if this track already exists.
    if(reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE207(&startPos.X,&endPos.X,1))continue;
    WaterTracksObj *track=TheWaterTracksRenderSystem->bindTrack(WaveTypeOcean);
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
