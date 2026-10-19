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
struct Rva000FF5E6Cursor {
 TrackCollection *first;int second;
 Rva000FF5E6Cursor(TrackCollection *owner,int index):first(owner),second(index){}
};
extern "C" bool __cdecl rva0007E394CursorEqual(const Rva000FF5E6Cursor &,const Rva000FF5E6Cursor &);
struct MapEntry {unsigned key;Rva0007E394Element *value;};
struct TrackCollection {
 char unknown00[0x14];MapEntry *m_begin,*m_end,*m_capacity;
 int size()const {return m_end-m_begin;}
 Rva000FF5E6Cursor begin(){return Rva000FF5E6Cursor(this,0);}
 Rva000FF5E6Cursor end(){return Rva000FF5E6Cursor(this,size());}
 Rva0007E394Element *at(const Rva000FF5E6Cursor &it)const {return m_begin[it.second].value;}
};
inline bool operator!=(const Rva000FF5E6Cursor &a,const Rva000FF5E6Cursor &b){return !rva0007E394CursorEqual(a,b);}
inline void advance(Rva000FF5E6Cursor &it){++it.second;}
struct WaterMapView {char unknown00[0x124];TrackCollection *tracks;};
extern void *W3DGCData00DE2000;
struct FeNode;
class WaterTracksObj {public:char unknown00[0xac];float flipU;void init(float,float,Vector2&,Vector2&,char*,int,void*);};
enum waveType {WaveTypePond,WaveTypeOcean};
class WaterTracksRenderSystem {public:WaterTracksObj *bindTrack(waveType);void rva000FE188();FeNode*rva000FE207(const float*,const float*,int);};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
class Rva0007E90ECallee {public:char unknown00[0x28];AsciiString file;void rva000FF5E6(int);};
struct TrackPoint : Vector2 {
 TrackPoint(){}
 ~TrackPoint(){}
};
struct EliminatedLifetime { ~EliminatedLifetime(); };
void eliminatedSink(const void *, const void *);
float GetGameClientRandomValueReal(float,float,char*,int);
void Rva0007E90ECallee::rva000FF5E6(int filename)
{
 file=*reinterpret_cast<const AsciiString*>(filename);
 reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE188();
 if(0){EliminatedLifetime e0;EliminatedLifetime e1;eliminatedSink(&e0,&e1);}
 struct SegmentEndpoints {Vector2 midpoint,shifted;};
 SegmentEndpoints guide;Vector2 &endPos=guide.midpoint;Vector2 &startPos=guide.shifted;
 int flipU=0;AssetList00208F90 assets;
 if(W3DGCData00DE2000) {
  TrackCollection *collection=reinterpret_cast<WaterMapView*>(W3DGCData00DE2000)->tracks;
  for(Rva000FF5E6Cursor it=collection->begin(),last=collection->end();it!=last;advance(it),last.second=collection->size()) {
   last.first=collection;
   Rva0007E394Element *record=collection->at(it);
   if(reinterpret_cast<Rva0030C94ADwordField*>(record)->get())continue;
   int count=record->end-record->begin;
   if(count<2)continue;
   int segments=count-1;
   for(int i=0;i<segments;++i) {
    int next=i+1;Vector2 *base=record->begin;const Vector2 &a=base[i];const Vector2 &b=base[next];Vector2 start(a.X,a.Y);Vector2 end(b.X,b.Y);
    Vector2 dir(end.X-start.X,end.Y-start.Y);
    Vector2 midpoint=start+dir*0.5f;
    endPos=midpoint;
    Vector2 &perp=dir;perp.Rotate(1.57079632679f);perp.Normalize();
    startPos=midpoint;
    startPos+=perp;
    //Check if this track already exists.
    if(reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE207(&endPos.X,&startPos.X,1))continue;
    WaterTracksObj *track=TheWaterTracksRenderSystem->bindTrack(WaveTypeOcean);
    if(track) {
     float fraction=GetGameClientRandomValueReal(0.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp",1141);
     int offset=fraction*reinterpret_cast<Rva0030C91AIntGetter*>(record)->get();
     flipU^=1;	//toggle flip state
     // Retail uses the same midpoint and shifted midpoint order as findTrack.
     track->init(float(reinterpret_cast<Rva0030C896DwordField*>(record)->get()),float(reinterpret_cast<Rva0030C890IntGetter*>(record)->get()),endPos,startPos,const_cast<char*>(static_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get())->str()),offset,record);
     assets<<*static_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get());
     track->flipU=flipU;
    }
   }
  }
  if(Rva0134FAA0)bfmeMergeReceiverKeys(reinterpret_cast<int>(&assets));
 }
}
