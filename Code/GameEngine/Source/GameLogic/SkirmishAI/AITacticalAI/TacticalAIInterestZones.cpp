// cl: /O1 /G7 /arch:SSE /GX /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from TacticalAI.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Target 0x002C63A1..0x002C64D0, 303 bytes. WB TacticalAI::DoXfer name lead
// is independently retained by its SkirmishAI caller at +0x164. Native reads
// player+8, chooser+C, generator+10 and the interest-zone vector+20.
// Xfer slots and the two serializer providers agree with matched siblings.
// The 32-byte zone's existing serializer retains its address-derived name.
// Its constructor signature follows complete target 0x002C6234..0x002C6354:
// coordinate address, float, player; member initialization proves 32 bytes.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
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
    // Native retains a temporary cleanup state with no destructor instruction.
    ~Coord3DBase() {}
    float x,y,z;
};
class Object;
class Player;
class Team;
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
class Rva00506909
{
public:
    void DoXfer(Xfer *);
    void Register(Team *);
    void UnRegister(Team *);
    void rva005069B4();
    bool activateTactic(struct Rva00506909Request*,void*);
};
class Rva002C5FE8 { public: void rva002C60A9(unsigned int); };

class Rva00506A52 { public: void rva00506AFA(); };
class TacticalAI
{
public:
    bool checkEnemyForAttackMove(Object *,Object *);
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
    Rva00506909 *generator;
    Rva002C589B *target;
    Rva002C589B *fallback;
    Rva00506A52 *tail;
    _STL::vector<Rva002C5EF0 *> interestZones;
};





// Native73B RET0 and WB E88F20 ordered callgraph use the established
// TacticalAI chooser/generator fields. The final dispatcher1C is independent
// of whether a request is chosen. Original update-method name unresolved.
void TacticalAI::rva002C6779() {
 updateInterestZones();
 if(chooser) chooser->rva00505911();
 generator->rva005069B4();
 Rva002C589B *request;
 if(chooser) target=request=chooser->getBestTarget();
 else request=fallback;
 if(request) generator->activateTactic((Rva00506909Request*)request,player);
 tail->rva00506AFA();
}

// Native 2C600A..2C60A9 and the named WB/filter caller establish predicate identity.

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad0[4];
	void *m_ptr4;
	char m_pad1[0x6C];
	int m_74;
	char m_pad2[0x1E0];
	class AIUpdateInterface *m_ai258;
};

struct Rva002A8AB1Record
{
public:
	void *rva002C6ACB();
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

// Native DFEEF8 is the existing single datum owned by Rva005EEA20Find.cpp.
extern Rva002A8F24 *g_00DFEEF8;

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

struct Rva002C600AFlag
{
	char m_pad[0x120];
	unsigned char m_flag120;
};

struct Rva002C600AArg1
{
	char m_pad[0x74];
	int m_74;
};

