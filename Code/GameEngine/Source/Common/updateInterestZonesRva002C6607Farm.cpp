// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /GX /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// stlport
// Target 0x002C63A1..0x002C64D0, 303 bytes. WB TacticalAI::DoXfer name lead
// is independently retained by its SkirmishAI caller at +0x164. Native reads
// player+8, chooser+C, generator+10 and the interest-zone vector+20.
// Xfer slots and the two serializer providers agree with matched siblings.
// The 32-byte zone's existing serializer retains its address-derived name.
// Its constructor signature follows complete target 0x002C6234..0x002C6354:
// coordinate address, float, player; member initialization proves 32 bytes.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <list>
class AsciiString;
struct Coord3DBase;
// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


struct Coord3DBase
{
public:
    Coord3DBase() { x=0.0f; y=0.0f; z=0.0f; }
    Coord3DBase(const Coord3DBase &v):x(v.x),y(v.y),z(v.z){}
    // Native retains a temporary cleanup state with no destructor instruction.
    ~Coord3DBase() {}
    float x,y,z;
    Coord3DBase &Sub(const Coord3DBase &b) {x-=b.x; y-=b.y; z-=b.z; return *this;}
    float GetLengthSqrd2D() const {return x*x+y*y;}
};
class Player;
class __multiple_inheritance Team;
class Rva002C5EF0
{
public:
    Rva002C5EF0(const Coord3DBase &,float,Player *);
    void rva002C5EF0(Xfer *);
public:
    unsigned int id;
    float position[3];
    unsigned int state;
    float radius,value;
    unsigned int frame;
};
class Rva002C589B;
class AITargetChooser { public: void xfer(Xfer *); void rva00505911(); Rva002C589B *getBestTarget(); };
class AITacticsGenerator
{
public:
    void xfer(Xfer *);
    void rva005059A1(Team *);
    void rva00505A56(Team *);
    void rva005069B4();
    bool rva005069CE(struct Rva00506909Request*,void*);
};
class Rva002C5FE8 { public: void rva002C60A9(unsigned int); };

class Rva00506A52 { public: void rva00506AFA(); };
class TacticalAI
{
public:
    void DoXfer(Xfer *);
    void updateInterestZones();
    void rva002C6779();
    void rva002C64D0(const Coord3DBase *, int);
    __declspec(noinline) void Register(Team *);
    __declspec(noinline) void UnRegister(Team *);
private:
    char prefix00[8];
    Player *player;
    AITargetChooser *chooser;
    AITacticsGenerator *generator;
    Rva002C589B *target;
    Rva002C589B *fallback;
    Rva00506A52 *tail;
    _STL::vector<Rva002C5EF0 *> interestZones;
};
// DoXfer (0x002C63A1), Register/UnRegister (0x002C5FAA/0x002C5FB2) and the
// interest-zone merge rva002C64D0 are rowed in TacticalAI.cpp, and
// rva002C6779 in TacticalAIInterestZones.cpp. This unit only declares them;
// copies here duplicated those definitions at link time.
#include "ObjectDlinkPmf.h"
template<class T> class DLINK_ITERATOR {
public:
 typedef T *(T::*GetNextFunc)() const;
 DLINK_ITERATOR(T *cur,GetNextFunc next):current(cur),next(next) {}
 void advance() {if(current) current=(current->*next)();}
 bool done() const{return current==0;} T*cur()const{return current;}
private: T *current; GetNextFunc next;
};
template<> void DLINK_ITERATOR<Object>::advance();
class Rva002C6607Base0 {}; class Rva002C6607Base1 {};
class Team : public Rva002C6607Base0, public Rva002C6607Base1 { public:
 DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
 Team *dlink_next_TeamInstanceList() const {return *(Team**)((char*)this+0x40); }
};
class TeamPrototype { public: char pad[0x334]; Team *head;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList);}
};
struct Rva002C6607PlayerView { char pad[0x2ec]; Team *excluded; char gap[0x3c]; _STL::list<TeamPrototype *> prototypes; };
class GameLogic; extern GameLogic *TheGameLogic;
struct Rva002C6607LogicView { char pad[0x40]; unsigned frame; };
extern int g_00DFEFCC;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
struct Rva002C6607ObjectView {
 int unknown; char *tmpl; char pad30[0x30]; Coord3DBase position;
 char pad258[0x258-0x44]; AIUpdateInterface *ai;
};
void TacticalAI::updateInterestZones() {
 for(_STL::vector<Rva002C5EF0*>::iterator z=interestZones.begin();z!=interestZones.end();) {
  if(((Rva002C6607LogicView*)TheGameLogic)->frame - (*z)->frame >= (unsigned)g_00DFEFCC) {
   if(*z) delete *z;
   z=interestZones.erase(z);
  } else ++z;
 }
 typedef _STL::list<TeamPrototype *> PrototypeList;
 PrototypeList &prototypes=((Rva002C6607PlayerView*)player)->prototypes;
 PrototypeList::iterator end=prototypes.end();
 PrototypeList::iterator begin=prototypes.begin();
 PrototypeList::iterator p=begin;
 for(;p!=end;++p) {
  for(DLINK_ITERATOR<Team> teams=(*(TeamPrototype * volatile *)&*p)->iterate_TeamInstanceList();!teams.done();(player ? teams.advance() : teams.advance())) {
   Team *team=teams.cur();
   if(team==((Rva002C6607PlayerView*)player)->excluded) continue;
   volatile bool found = false;
   DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();
   Rva002C6607ObjectView *obj;
   for(;(obj=(Rva002C6607ObjectView*)objects.cur())!=0 && !found;objects.advance()) {
    _ReadWriteBarrier();
    if(((unsigned char)obj->tmpl[0x108]&8) || ((unsigned char)obj->tmpl[0x113]&4)) {
    	_ReadWriteBarrier();
     Object *victim=obj->ai ? obj->ai->getCurrentVictim() : 0;
     if(victim) {
      Rva002C6607ObjectView *target=(Rva002C6607ObjectView*)victim;
      if(!((unsigned char)target->tmpl[0x108]&0x80) && *(int*)(target->tmpl+0x520)!=4) {
       Coord3DBase delta=target->position;
       delta.Sub(obj->position);
       if(delta.GetLengthSqrd2D() <= 90000.0f) {
        rva002C64D0(&obj->position,-1); found=true;
       }
      }
     }
    }
   }
  }
 }
}
