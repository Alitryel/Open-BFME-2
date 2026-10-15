// ?rva002F07F5@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.9741068869019179 date=2026-10-15
// ?rva002F07F5@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// W7-D1 r11: native2F07F5..2F0A72 RET8; whole637B/frame4C EXACT.
// Raw/normalized16 vs r10's42 and first r11's27/frame48.
// Group the existing layers[2] and origin ICoord2D in a local16B CoordStorage;
// their member types and original real-definition order are unchanged.
// This is an implementation storage adapter, not a target type/layout claim.
// Keep destination phase scope and shared lastX/lastY; no old equal-arm calls.
// Remaining16 are home displacements: above/mainlayer; both Ybase temps;
// destination cell; firstcell.y/destY and below/maincell phase reuse.
// First origin/layer/query homes now exactly match retail.
// Preserve actual owner declarations and visible whole Cell/Split providers.
// This is a bank; do not port the standalone context as a new Code TU.
// Proven41B query ctor visibility leaves the parent unchanged; not included.
// Proven32B prvalue factory, guarded bounds/union phases, placement storage,
// early cell initialization and rank injections were worse; no new pin used.
// No new asm, address globals, private canonical copies or escape hatches.
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /I.
// stlport


namespace _STL {
  const unsigned int &max(const unsigned int &a, const unsigned int &b);
}
#include <vector>
#include <new>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;

class LocomotorSet
{
public:
	LocomotorSurfaceTypeMask getValidSurfaces() const
	{
		return m_validLocomotorSurfaces;
	}
private:
	char m_pad[0x10];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
	Bool m_downhillOnly;
	Bool m_scalesWalls;
};

class Player
{
public:
	char m_pad00[0x5c];
	Int m_playerType;		
};

class AIUpdateInterface;
struct PathfinderTemplateView {
    char pad[0x64];
    char *nameBuffer;
    char pad68[0x108-0x68];
    unsigned char kinds[24];
    char pad120[0x56c-0x120];Int priority;char pad570[0x634-0x570];Bool flag;
    __forceinline bool hasKind(int bit) const { return (kinds[bit/8] & (1<<(bit%8)))!=0; }
    
    __forceinline unsigned int testKindWord(unsigned int bit) const { return ((const unsigned int *)kinds)[bit>>5] & (1u<<(bit&31)); }
    __forceinline const char *name() const { return nameBuffer ? nameBuffer+8 : ""; }
};
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
enum ObjectStatusTypes { QuickStatus49=49 };
enum NameKeyType { NAMEKEY_INVALID=0 };
class Module;
struct Coord3D;
class Object
{
friend class Rva002F23A6;
public:
	Player *getControllingPlayer() const;
 Bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
    int rva0028B511() const;
    Object *rva002931F5(Bool);
void rva0028C2DD(Coord3D*)const;
const Coord3D *getPosition()const{return (const Coord3D*)position;}
protected:Module *findModule(NameKeyType)const;
public:
    bool rva002E6B89();
	bool IsAtGoalPosition() const;
	Bool canCrushOrSquishNoAlly(Object *other, Int test);
	bool rva0028AFBB() const;
	float GetGoalAngle() const;
    __forceinline int getID() const { return *(const int *)((const char *)this+0x74); }
	AIUpdateInterface *getAI() const { return reinterpret_cast<AIUpdateInterface *>(m_258); }
	void *m_vtable;
	PathfinderTemplateView *m_template;
	char m_pad08[0x38-8];
	float position[3];
	float m_orientation;				
	char m_pad48[0x258 - 0x48];
	char *m_258;						
	char m_pad25C[0x274-0x25C];
	Object *container;
};
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
void getUnitDirectionVector2D(Coord3D&)const;
};
struct Rva002E7ED6Info;
class Pathfinder;

class PathNode {
public:
    PathNode(const Coord3D *,PathfindLayerEnum) throw();
    PathNode *next,*previous,*nextOptimized;
    Coord3D position;
    PathfindLayerEnum layer;
    Bool canOptimize;
    Int portalID;
    const Coord3D *getPosition() const { return &position; }
    PathNode *getNextOptimized() const { return nextOptimized; }
};
struct Rva002EDEABArg;
struct Rva002E93A7Info
{
	Pathfinder *m_00;
	Int m_04;
};
class Waypoint { public: Int word0,id;void *name;Coord3D location;char pad18[0x44-0x18];Waypoint *chainNext;Int word48,linkCount; };
class PathfindCell;
class Path
{
 friend class Pathfinder;
public:
 void rva00265596(const Coord3D *,PathfindLayerEnum,Int);
	Path();										

	void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
	void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, Int portal);
	void SetLastNodePortal(Int portal);
private:
	void *word0;PathNode *firstNode;PathNode *lastNode;char wordC;Bool blockedByAlly;char padE[0x28-0xe];
};

struct Rva002E8C23Pair { Int x,y; };
void rva002E79A8(int,unsigned char,int,int,int);

int __cdecl Rva002E8C4DCall(int a1, unsigned char a2, Rva002E8C23Pair *a3, int a4);
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
extern "C" double __cdecl fabs(double);
struct PathfinderCostCellInfo { Int x,y; };
struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x28-0x14];ObjectID obstacleID;unsigned int flags; };
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
private:
	char m_pad[0x48];
	void *m_48;
};

void ji_00629952();
struct Rva002F35AFCell;
class Rva002E6C79
{
public:
	Int rva002E6C79();
	Rva002F35AFCell *m_00;
	Rva002E6C79 *next() { return (Rva002E6C79 *)rva002E6C79(); }
};
class PathfindCell
{
 friend class Pathfinder;
public:
	
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_OBSTACLE = 4,
		CELL_IMPASSABLE = 5
	};
	enum { LAYER_GROUND = 1 };

 Bool IsObstaclePresent(ObjectID) const;
 Bool StartPathfind(Int);void ReleaseInfo();void SetParentCell(Int *);void PutOnClosedList(MixFileInfoBuffer **);Int CalcCostSoFar(const Rva002E6C79 *);
 __forceinline void allocateInfo(In002E6BA1 *pos) {
  if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
  else m_pathInfo->parentWaypoint=0;
 }
	void SetOpen(Bool open);
	unsigned short quickZone()const {return (unsigned short)word8;}
 Int getXIndex() const { return m_pathInfo->position.x; }
	Int getYIndex() const { return m_pathInfo->position.y; }

	float rva0052DD75(float facing, Int count, float weight);
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }
	Int getConnectLayer() const { return (m_info >> 10) & 0x3f; }
	Bool rvaBit16() const { return (Bool)((m_info >> 16) & 1); }
 PathfindCell *getParentCell(){return (PathfindCell *)((Rva002E6C79 *)this)->rva002E6C79();}
 Waypoint *getParentWaypoint()const {return m_pathInfo?m_pathInfo->parentWaypoint:0;}

private:
	PathfinderGroundInfo *m_pathInfo;
	Waypoint *waypoint;Int word8;
	unsigned int m_info;			
};

struct LocomotorTemplate
{
	char m_pad00[0x14];
	LocomotorSurfaceTypeMask m_surfaces;	
};

class Locomotor
{
public:
	float getMaxSpeed(Object *obj) const;
	__declspec(dllimport) __forceinline LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
	void *m_vtbl;
	const LocomotorTemplate *m_template;	
};

unsigned int g_00DBD33C[16] = {
	0x00000009, 0x0000000A, 0x0000000C, 0x00000018,
	0x00000028, 0x00000048, 0x00000048, 0x00000088,
	0x00000000, 0x3E490FDB, 0x41A00000, 0x41A00000,
	0x00000000, 0x00000001, 0x00000000, 0xFFFFFFFF
};

extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);

  Int realToIntFloor(float f);

class Rva002F3738
{
public:
	void rva002F3738(void **entry);
};

struct _Rva002E7B02Cell
{
	Int x;
	Int y;
	Int z;
};

class Rva002E7B02
{
public:
	Rva002E7B02(Int a, Int b, const _Rva002E7B02Cell &cell);
private:
	Int m_00;
	Int m_04;
	Int m_08;
	Int m_0C;
	Int m_10;
};

struct Rva002E7B29Info;

template<int N> class PathfinderNativeSlots : public PathfinderNativeSlots<N-1> { public: virtual void unusedSlot(PathfinderNativeSlots<N> *); };
template<> class PathfinderNativeSlots<0> {};
class TerrainLogicCheckDestination : public PathfinderNativeSlots<50> { public: virtual bool slotC8(const Coord3D *); };
class PathfinderContain28 : public PathfinderNativeSlots<28> { public: virtual int slot70(); };
class PathfinderContain31 : public PathfinderNativeSlots<31> { public: virtual void *slot7C(); };
class PathfinderContain69 : public PathfinderNativeSlots<69> { public: virtual unsigned int slot114(int); };
class TerrainLogicWaterQuery : public PathfinderNativeSlots<19> { public: virtual bool slot4C(float,float,float *,void *,void *); };
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
	virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D *,Bool);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;

  void zeroCoord3D(Coord3D *dst);
  void copyCoord3D(Coord3D *dst, const Coord3D *src);

class Pathfinder_FuncTightenPath
{
public:
	Pathfinder_FuncTightenPath(Pathfinder *pathfinder, Object *obj,
		const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
		const Coord3D &goal);

	Pathfinder *m_pathfinder;				
	Object *m_obj;							
	const LocomotorSet *m_locomotorSet;		
	Int m_radius;							
	unsigned char m_center;					
	PathfindLayerEnum m_layer;				
	Bool m_foundDest;						
	Coord3D m_goal;							
	Coord3D m_destPos;						
};

class Pathfinder_IsCheckForAdjust
{
public:
	Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, const Coord3D *layerPos, float range,
		Int arg6);

	Pathfinder *m_pathfinder;				
	Object *m_obj;							
	void *m_08;								
	Bool m_isHuman;							
	unsigned char m_center;					
	Int m_radius;							
	const Coord3D *m_layerPos;				
	PathfindLayerEnum m_layer;				
	float m_range;							
	Rva002E8C23Pair fallback;
	Int m_28;								
	Int m_2C;								
	Coord3D m_goal;							
};

class Pathfinder_IsCheckForMeleeHordeAdjust
{
public:
	Pathfinder_IsCheckForMeleeHordeAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, float range);

	Pathfinder *m_pathfinder;				
	Object *m_obj;							
	void *m_08;								
	Bool m_isHuman;							
	unsigned char m_center;					
	Int m_radius;							
	PathfindLayerEnum m_layer;				
	float m_range;							
	Rva002E8C23Pair m_1C;
	Int m_24;								
	Coord3D m_goal;							
};

void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	bool isWithinAttackRange(Object*,const Coord3D*,Object*,const Coord3D*,float,bool);
};
class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *a, float b);
	void *m_00;
	Rva002C9400ByteField *m_04;				
};

struct Rva002E8BCFSrc;
struct Rva002F4D8BInfo;
class Rva002E9ACC
{
public:
	Rva002E9ACC(void *a1, Object *obj, Rva002E8BCFSrc const *src,
		unsigned char a4, unsigned char a5);
	char m_pad00[0x1C];
	Bool m_found;							
	unsigned char m_1D;						
	unsigned char m_1E;						
	unsigned char m_1F;						
	unsigned char m_20;						
};

struct Rva002F35AFZone
{
	Int m_00;
	Int m_04;
};
struct Rva002F35AFCell
{
	Int x;
	Int y;
	Int m_08;
	Rva002F35AFZone *m_0C;
};

struct Rva002F35AFHop
{
	Int m_zone;
	PathfinderCostCellInfo m_position;
};

class Rva005348AD
{
public:
	Rva005348AD();
	void rva00534557(Rva002F35AFCell *cell);
	void rva00534AAE();
private:
	char m_pad[0x14];
};

class Rva0036666B
{
public:
	bool rva0036666B();
};

class PathfindLayer
{
public:
	bool setDestroyed(bool destroyed);
    __declspec(noinline) void rva000B3FD0();
private:
	char m_pad[0x40];
};

class PathfindZoneManager
{
public:
	void rva00531300();
	void rva00531481();
	void rva005314C6(Int x, Int y, unsigned char flag);
};

struct Rva002EBC7FPair { int x,y; };
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
class AIUpdateInterface {
public:
    bool findNearestLabeledContactPointOnTarget(Object *,Coord3D *,const Coord3D *,bool);
    bool isAircraftThatAdjustsDestination() const;
    int rva0026417F(bool);
    Object *getCurrentVictim() const;
    char gap[0x1f0];
    Locomotor *locomotor;
};

struct PathCollisionNode { PathCollisionNode *next; void *word4; Object *object; };
struct PathCollisionInfo {
    int x,y;
    char gap08[0x14-8];
    PathCollisionNode *occupants;
    PathCollisionNode *hordeGoalNodes; 
    char gap1C[4];
    PathCollisionNode *goals;
    PathCollisionNode *reservations;
    ObjectID fallbackID; 
};
struct PathCollisionCell { PathCollisionInfo *info; };

class Bridge {
public:
    bool isPointOnBridge(const Coord3D *pos);
    float getBridgeHeight(const Coord3D *pos, Coord3D *normal);
    void *m_00;
    Bridge *m_next;
};
struct Rva002ED236Pos {
    float x, y, z;
    Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
    ~Rva002ED236Pos() {}
};
int Rva002E6E8AGet(int layer);
class Rva002E7482 { public: float rva002E7482(int layer); };

#include "ascii_string.h"
struct GeometryShape {
    int type; float height,major,minor;
    float offsetX,offsetY,offsetZ;
    AsciiString name;
    bool enabled,opaque21;
    __forceinline GeometryShape() : type(0),height(1),major(1),minor(1),offsetX(0),offsetY(0),offsetZ(0),enabled(true),opaque21(true) {}
};
class GeometryInfo { public: void rva006BD9C0(GeometryShape &) const; };
struct ICoord2DBase { int x,y; };
class Rva002E9D09 { public: int rva002E9D09(Object *,int,int); };
class Rva002E7C99 {
public:
    void *rva002E7C99(int,int,int,unsigned char,int,unsigned char,int);
    char fields[28];
};
class Rva0006E009DwordField { public: int get() const; };
class Rva0052DB4D { public: bool rva0052DB4D(int); };
void rva002E79A8(int,unsigned char,int,int,int);

union PathfinderCheckCoordinates {
    Coord3D point;
    struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;

#include "Code/Libraries/Include/Lib/ICoord2D.h"

struct PathfinderCellIndex : ICoord2D {
	__forceinline PathfinderCellIndex() {}
	__forceinline PathfinderCellIndex(const PathfinderCellIndex &o) { x = o.x; y = o.y; }
};
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 {
public:
    Rva002E7440(Pathfinder *owner) : pf(owner) {}
    Bool rva002E7440(Int,Int);
private:
    Pathfinder *pf;
};
class Rva002E7414 {
public:
    Rva002E7414(Pathfinder *owner) : pf(owner) {}
    Int rva002E7414(Int,Int);
private:
    Pathfinder *pf;
};
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderOpenQueue {PathfindCell **first,**last;Bool empty()const{return first==last;}PathfindCell *front()const{return *first;}};
struct ICoord2D;
struct Rva002E7261Info;
struct PathfinderMineshaft { Int m_00; Int m_portal; Int m_08; Coord3D m_position; };
struct TCheckMovementInfo;
class HierarchicalPath;
class Rva002E7E26;
class Rva002E7DF5;
class Pathfinder
{
public:
 Bool rva002F07F5(Object *,const Coord3D *);
 Bool IsValidHordeMemberRegularMovement(Object *,const Coord3D *,const Coord3D *,const Coord3D *);
 Bool AdjustToNearestValidCell(Coord3D *);
 Bool AdjustToNearestGroundCell(Coord3D *);
bool rva002ED313(Object*);
void AdjustMeleeOffset(Object*,Object*,Coord3D*);
Bool rva002EEA8A(const ICoord2D*,Int,ICoord2D*,void*,Int);
 Bool adjustToMeleeDestination(Object*,const LocomotorSet&,Coord3D*);
 Bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);
 void SnapClosestGoalPosition(Object *,Coord3D *);
 Bool CheckForAdjust(Object *,const LocomotorSet &,Bool,Int,Int,PathfindLayerEnum,Int,Bool,Coord3D *,const Coord3D *,float,Int *,Int);
 Bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,Int);
 Bool IsValidMovementPositionForObject(const Coord3D *,Int,Int,const Object *);
 Bool rva002F4115(Object *,Int,Int,LocomotorSet *);
 Bool rva002F4AC1(const ICoord2D *,Int,Int,Object *,PathfindLayerEnum,Int,Rva002E7261Info *,void *,void *);
 PathfindCell *rva002F068F();
 Path *FindSafePath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,const Coord3D *,float);
 Path *PatchPath(Object *,const LocomotorSet &,Path *,Bool);
 Path *GetHordeUnitPath(Object *,const Coord3D *);
    Path *GetAircraftPath(const Object *,const Coord3D *);
    int _GetOverlapUnits(Object *,const Coord3D *,int *);
    int GetOverlapGoalUnits(Object *,const Coord3D *,int *);
    int CountOverlapHordeGoalUnits(Object *,const Coord3D *);
    int _GetAdjacentUnits(Object *,const Coord3D *,int *);
    Bool CircleClipsTallBuilding(const Coord3D *,const Coord3D *,float,unsigned,Coord3D *);
    Bool rva002F3392(PathNode *,PathNode *,unsigned,Coord3D *,Coord3D *,Coord3D *);
    void SetDebugPath(Rva002EDEABArg *);
	Bool rva002EAE5F(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002EB11B(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F379E(ICoord2D *,Int,void *);
	Bool AdjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
	Bool AdjustHordeMeleeDestination(Object *,void *,Coord3D *);
	Int CheckPathCost(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *);
	Bool rva002F8E2D(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F90E9(ICoord2D *,Int,void *);
	Bool rva002F92BC(const ICoord2D *,Int,ICoord2D *,void *);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
 PathfindCell *rva002F36E5();Int rva002F40E7();void CheckChangeLayers(PathfindCell *,Object *);
	Path *InternalFindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,HierarchicalPath *,Bool *);
	Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Path *GetMoveAwayFromPath(Object *,Object *,Path *,Object *,Path *);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,const ICoord2D *,Int,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Bool checkForMovement(Object *,TCheckMovementInfo &);
	Bool rva002EDFF9(Object *,Coord3D *);
	void rva002E75A3(Coord3D *,Coord3D *);
	Int rva002F0A72(PathfindCell *,PathfindCell *);
	float GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
	void *rva001E3647Pos(int layer, const Coord3D *pos);
	bool IsPointOnRamp(const Coord3D *pos);
	PathfindLayerEnum rva002ED236(Object *obj, Rva002ED236Pos pos);
	Bool CheckDestination(Object *,Int,Int,PathfindLayerEnum,Int,Bool,Int *,Bool);
    Int rva002EED80(const ICoord2DBase *,const ICoord2DBase *,float,int,Rva002E9D09 *);
	void SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired);
	void ForceMapRecalculation();
	void Rva0052F2EC();
	int rva002EADE1(const Coord3D *a, const Coord3D *b,
		PathfindLayerEnum layer, Rva002E7ED6Info *info);
	int rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E93A7Info *info);
	int rva002EB3D7(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E7B29Info *info);
	Bool IsGroundLineOnly(const Coord3D *startWorld,
		const Coord3D *endWorld);
	Bool IsGroundPathPassable(const Coord3D *startWorld,
		PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter);
	void AddToOpenList(PathfindCell *cell);
	int CalcExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,int,int,bool);
	int CalcCollisionFreeExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,PathfindLayerEnum,int,int,bool);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);	
	PathfinderCellIndex Rva002E7917(bool center, const Coord3D *pos);	
	Bool IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos);
	Int AdjustGroundPathPosition(const Coord3D &source, Coord3D &destination);
	unsigned char bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
	Bool CheckForTarget(void *obj, void *a2, void *a3, Rva002CB35CObj *weapon,
		void *a5, void *a6, void *a7, void *a8, Coord3D *out);
	Path *BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
		const Coord3D *fromPos, PathfindCell *goalCell, Bool center,
		Bool blocked, Bool faceDirection);
	
	void PrependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);
	Rva005348AD *MakeHierarchicalPathPassable(void *unused, Rva002E6C79 *path, Bool expand);
	void TightenPath(Object *obj, const LocomotorSet &locomotorSet, Coord3D *from, const Coord3D *to);
	int rva002F95B7(const Coord3D *from, const Coord3D *to, PathfindLayerEnum layer, Rva002F600CInfo *info);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
protected:
	Path *FindHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher);
	Path *FindClosestHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher, Coord3D *adjustedTo);
	Path *internal_findHierarchicalPath(Bool isHuman,
		LocomotorSurfaceTypeMask locomotorSurface, Object *obj,
		const Coord3D *from, const Coord3D *to, Bool crusher, Bool closestOK,
		Coord3D *adjustedTo);
private:
	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002E7261Info *);
	char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
	int m_unknown10;
	ICoord2D m_clampLo, m_clampHi;	
    Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
    MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x48-0x39];
	ObjectID m_ignoreObstacleID;	
	char m_pad04C[0x5c-0x4c];
	Bridge *m_bridges;
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
	char m_pad461[0x1BEB6 - 0x461];
	Bool m_1BEB6;		
	char m_pad1BEB7[5];
	float m_wallLayerHeights[48];
	char m_pad1BF7C[0x1C1CC - 0x1BF7C];
	_STL::vector<Rva002F35AFHop> m_1C1CC;	

 PathfinderMineshaft *m_srcMineshaft,*m_destMineshaft;
 char pad1c1e0[0x1d1f0-0x1c1e0];PathfinderOpenQueue m_openCells;
public:
	Bool getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out);
	Int rva002EB4DF(const ICoord2DBase *center, const ICoord2DBase *diameter, float angle, int layer, Rva002E7E26 *visitor);
	Int rva002E8773(Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor);
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *, unsigned short);
	unsigned short rva00531FD4(void *, unsigned short);
};

struct Rva002E7261Info
{
	Pathfinder *m_pathfinder;
	Int m_arg;
	Int m_key;
	ICoord2D m_position;
	Int cellCallback(PathfindCell *, PathfindCell *, Int, Int);
};

struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };

struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
extern int TheMixFileInfoCount;

class Rva002E6BA1
{
public:
	void rva002E6BA1(int a, In002E6BA1 *b);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned short m_10;
	unsigned short m_12;
	int m_14[5];
	int m_28;
	int m_2C;
	int m_30;
};

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);
};

 __declspec(noinline) MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct PathfinderSearchRadiusView { char pad[0x11F0]; Int searchRadius; };
  Coord3D adjustCellCenter(bool center,Rva002E8C23Pair *cell,PathfindLayerEnum layer);
  Bool findAdjustedCell(Pathfinder *finder,ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForAdjust *info);

extern float g_00BC7838;
struct PathfinderCellPoint : Coord3D {
	__forceinline PathfinderCellPoint() {}
	__forceinline PathfinderCellPoint(const PathfinderCellPoint &o) { x = o.x; y = o.y; z = o.z; }
	__forceinline ~PathfinderCellPoint() {}
};

PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer);

PathfinderCellPoint Rva002E8C23Call(Bool centerInCell, PathfindCell *cell);

class Rva00065964ObjectPool { public: void *rva002635C2() throw(); };
extern Rva00065964ObjectPool g_pathNodePool;
template<int N> class AircraftSlots:public AircraftSlots<N-1>{public:virtual void slot(AircraftSlots<N>*);};
template<> class AircraftSlots<0>{};
struct AircraftLocomotorTemplate { char prefix[0x74];int appearance; };
struct AircraftLocomotor { void *vtable; AircraftLocomotorTemplate *data; };
class AircraftAIView:public AircraftSlots<109>{
public:
 virtual unsigned avoidObject();
 char prefix04[0x1f0-4]; AircraftLocomotor *locomotor;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class AI;
extern AI *TheAI;
struct PathfinderAircraftAIView { char prefix[0x10]; Pathfinder *pathfinder; };
  PathNode *makeAircraftNode(const Coord3D *p);
  void appendAircraftNode(PathNode *current,PathNode *node);

class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
int Rva002E6E6CGet(int);
extern int g_Va00DFECD0;
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva002EBCD6Split(void *,int *,int *);

static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
inline __declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV);
	} else {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV + 0.5f);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

struct ICoord2D;
struct Coord3D;
struct ICoord2D *__cdecl Rva002E7875WorldToCell(struct ICoord2D *out, bool center, const struct Coord3D *pos);
bool __cdecl Rva002EBBFBIsOdd(void *p);

inline __declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
	Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
	return out;
}

int __cdecl Rva002E9B31Get(void *p);
__declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}

extern GameLogic *TheGameLogic;

struct Rva002CECAETarget;
void Rva002CECAEAppend(Rva002CECAETarget *,const char *,...);
class Rva0028B984ByteField {public:unsigned char get()const;};

struct PathfinderHordeMeleeRadiusView { char pad[0x11F4]; Int searchRadius; };
  Bool findHordeMeleeCell(Pathfinder *finder,const ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForMeleeHordeAdjust *info);

struct TCheckMovementInfo
{
	ICoord2D cell;					
	PathfindLayerEnum layer;		
	Int radius;						
	Bool centerInCell;				
	Bool m_11;
	unsigned char m_pad12[2];
	unsigned int m_14;				
	ObjectID m_18;					
	unsigned char m_1C[0x10];		
	Int m_2C;
	Bool m_30,m_31,m_32;
	unsigned char m_pad33;
	Int m_34;
};
class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	char m_pad12[2];
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[2];
	int m_24;
	unsigned char m_28;
	char m_pad29[3];
	int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
	char m_pad33[1];
	int m_34;
};
class HierarchicalPath { public: Int lookUpPositionOnPath(const Coord3D *); };
struct PathfinderCellLimitView { char pad[0x1210]; unsigned int maxCells; };
extern Int PathfinderSearchCellsVisited;	

  Coord3D *cellPointArg(const PathfinderCellPoint &p);

  void *boolArg(const Bool &value);
  Bool pathfinderLogOn();
  void pathfinderLog(const char *text);

  void rotateOffset(float &x, float &y, float angle);
  void setInfoCell(TCheckMovementInfo &info, ICoord2D c);
  void setInfoCellYX(TCheckMovementInfo &info, ICoord2D c);

#include "Code/Libraries/Include/Lib/IRegion2D.h"
bool __cdecl ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);
extern float g_00BC7838;

  float clipCellFloor(float f);
  long clipCellRound(float f);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva002E6DC4_P1
{
	unsigned int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
struct Rva002E6DC4_P2Inner
{
	char m_pad[0x28];
	void *m_28;
};
struct Rva002E6DC4_P2
{
	Rva002E6DC4_P2Inner *m_0;
	char m_pad4[8];
	unsigned int m_C;
};
bool Rva002E6DC4::rva002E6DC4(void *a_raw, void *b_raw)
{
	Rva002E6DC4_P1 *a = (Rva002E6DC4_P1 *)a_raw;
	Rva002E6DC4_P2 *b = (Rva002E6DC4_P2 *)b_raw;
	if (!b)
		return false;
	unsigned int flags = b->m_C;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0 && a->m_5 != 0)
		return false;
	unsigned int low = flags & 0xF;
	switch (low) {
	case 3:
		if ((flags & 0x3F0) != 0x10)
			return false;
		break;
	case 4: {
		void *chase = b->m_0 ? b->m_0->m_28 : 0;
		if (chase == m_48)
			return true;
		break;
	}
	default:
		break;
	}
	if ((a->m_0 & g_00DBD33C[low]) == 0)
		return false;
	unsigned char b17 = (unsigned char)(flags >> 17);
	if (a->m_4 != 0 && (b17 & 1) != 0)
		return false;
	if (a->m_C != 0) {
		unsigned char b22 = (unsigned char)(flags >> 22);
		if (((b22 & 1) == 0) && low == 4)
			return false;
	}
	int v = a->m_8;
	if (v < 0 || (int)((flags >> 19) & 3) <= v)
		return true;
	return false;
}

class StateMachine
{
public:
	Object *getGoalObject();
};
struct CheckMovementAIView
{
	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine;	
};
struct CheckMovementObjectNode
{
	CheckMovementObjectNode *m_next;
	int m_04;
	Object *m_object;	
};
struct CheckMovementCellInfo
{
	unsigned char m_pad00[0x14];
	int m_14;
	unsigned char m_pad18[0x20 - 0x18];
	CheckMovementObjectNode *m_objects;	
};
struct CheckMovementCell
{
	Int getType() const { return m_flags & 0xf; }
	Int getLayer() const { return (m_flags >> 4) & 0x3f; }
	Bool rvaBit18() const { return (Bool)((m_flags >> 18) & 1); }
	Bool rvaInfo14() const { return m_info ? m_info->m_14 != 0 : false; }
	Bool hasObjects() const { return m_info ? m_info->m_objects != 0 : false; }
	CheckMovementObjectNode *getObjects() const { return m_info ? m_info->m_objects : 0; }

	CheckMovementCellInfo *m_info;
	unsigned char m_pad04[0x0C - 0x04];
	unsigned int m_flags;	
};
  void checkCellFlags(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info);
  Bool checkCellUnits(Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID);
  Bool checkCell(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID);

  void readMoverInfo(TCheckMovementInfo &info, Object *obj);
struct Gen_p12pod {Int a[3];};

namespace _STL {
template <> Gen_p12pod *vector<Gen_p12pod, allocator<Gen_p12pod> >::erase(Gen_p12pod *, Gen_p12pod *);
}

class Rva002E7964 {
public:
 void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);
 char pad[0x14];IRegion2D extent;
};

struct PathfinderPatchLimitView { char pad[0x120C]; unsigned int maxCells; };

#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "Code/Libraries/Include/Lib/Region2D.h"
Bool LineInRegion(const Coord2D *,const Coord2D *,const Region2D *);
int Rva002E9B31Get(void *);

void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd);

struct Rva002ED7F7Budget{char pad[0x1200];int maxSteps;};
class Rva002EC3CEProbes{public:bool rva002EAA41(int,int,int,int,int,bool);bool rva002E7BF0(int,int,bool,int,int,int,void*,bool);};
  void subtractMelee(Coord3D &a,const Coord3D&b);
  float distanceMelee(const Coord3D&a);

class BfmeTripleRC;
class Gen_003D5670 {public:Gen_003D5670(int,int,int,int,int,int,unsigned char,unsigned char,int,int,BfmeTripleRC*,unsigned char);unsigned char storage[0x3c];};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object*);};
class Rva004C5772CmpBoolField {public:bool get()const;};

class Rva002EC3CE {public: Bool rva002EC3CE(Int,Int);};
struct Rva002E8D74Pt
{
	char m_pad00[0x38];
	float m_38;
	float m_3C;
};

class Rva002E8D74
{
public:
	float rva002E8D74(int a, int b);
private:
	char m_pad00[0x28];
	Rva002E8D74Pt *m_28;
};

struct MeleeSearchLimit {char pad[0x11ec];int searchLimit;};
struct SearchCoordinate:Coord3D {
 SearchCoordinate(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
 SearchCoordinate(const SearchCoordinate &p){x=p.x;y=p.y;z=p.z;}
 void zero(){x=0;y=0;z=0;}
 void scale(float f){x*=f;y*=f;z*=f;}
 void add(const Coord3D &p){x+=p.x;y+=p.y;z+=p.z;}
};
class Rva002F23A6 {public:bool rva002F23A6(Object *,int,int,Coord3D *,Object *);};
typedef unsigned char (Pathfinder::*ProbeCall)(Object*,int,int,PathfindLayerEnum,int,bool);

  bool possibleFootprint(Pathfinder *p,Object *object,int x,int y,int layer,int radius,bool center);

class Rva0052DB73 { public: bool rva0052DB73(int); };
class Rva0052DB11 { public: bool rva0052DB11(int); };
  bool snapDestination(Pathfinder *p,Object *obj,int x,int y,int layer,int radius,bool center);

struct PathMeleeCoord : Coord3D
{
    PathMeleeCoord(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
    ~PathMeleeCoord() {}
    PathMeleeCoord &Scale(float scale)
    {
        x*=scale; y*=scale; z*=scale;
        return *this;
    }
    void Add(const Coord3D &p) { x+=p.x; y+=p.y; z+=p.z; }
};

  void scaleMeleeOffset(Coord3D &p,float scale);

struct _Rva002E7DF5Cell 
{
 int x, y, z;
 
}
;
class Rva002E7DF5

{
 public:
 Rva002E7DF5(int, const _Rva002E7DF5Cell &) throw();
 int owner;
 int sourceWords[3];
 Coord3D closest;
 float cost;
 bool found;
 
}
;
class Rva002E7E26 
{
 public:int rva002E7E26(Object*,int,int);
 int owner;
 Coord3D source,closest;
 float cost;
 bool found;
 
}
;
enum LandCellKind 
{
 LandClear=0, LandWater=1, LandSolid=7 
}
;
struct LandWordView 
{
 int a,b,c;
 unsigned packed;
 __forceinline LandCellKind getKind() const 
 {
  return (LandCellKind)(packed&15);
  
 }
 
}
;
struct LandLocalPoint : Coord3D 
{
 __forceinline void set(const float *p) 
 {
  x=p[0];
  y=p[1];
  z=p[2];
  
 }
 __forceinline void set(float a,float b,float c) 
 {
  x=a;
  y=b;
  z=c;
  
 }
 __forceinline void sub(const float *p) 
 {
  x-=p[0];
  y-=p[1];
  z-=p[2];
  
 }
 __forceinline float squared() const 
 {
  return x*x+y*y+z*z;
  
 }
 
}
;

class Rva002E6CFE

{
 public:
 int m_00;

 int m_04;

 int m_08;

 int m_0C;

 void rva002E6CFE(int a, int b, int c);
 bool rva002E6D2F();
 
}
;

#define nextIndex(i,n) ((i)+1==(n)?0:(i)+1)
#define prevIndex(i,n) ((i)!=0?(i)-1:(n)-1)

#undef nextIndex
#undef prevIndex

extern float g_Va00BBB8E0;

  int landCells(const float & radius,const float & padding);

struct Rva002F07F5ObjectView {void *vtable;PathfinderTemplateView *templ;char pad08[0x38-8];Coord3D pos;char pad44[0x258-0x44];AIUpdateInterface *ai;};
struct Rva002F07F5Node {Rva002F07F5Node *next;void *prev;Object *obj;};
struct Rva002F07F5CellInfo {char pad00[0x14];Rva002F07F5Node *items;};
struct Rva002F07F5CellView {Rva002F07F5CellInfo *info;char pad04[8];unsigned int flags;};
struct CoordStorage {Int layers[2];ICoord2D origin;};
Bool Pathfinder::rva002F07F5(Object *obj,const Coord3D *dest)
{
 Rva002F07F5ObjectView *view=(Rva002F07F5ObjectView *)obj;
 const Coord3D *from=&view->pos;
 if(!IsValidHordeMemberRegularMovement(obj,from,dest,from))return false;
 Int lastX; Int lastY;
 Int newCount=0;
 Int below; Int above;Rva002EBCD6Split(obj,&below,&above);
 CoordStorage coords;coords.layers[0]=obj->rva0028B511();Int layerCount=1;
 if(!(unsigned char)Rva002E6E6CGet(coords.layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(obj,coords.layers[0])) {
  coords.layers[1]=1;layerCount=2;
 }
 Int oldCount=0;
 {
  Rva002EBC14Cell(&coords.origin,obj,from);
  Int x=coords.origin.x-below; lastX=coords.origin.x+above;
  for(;x<lastX;++x) {
   Int y=coords.origin.y-below; lastY=coords.origin.y+above;
   for(;y<lastY;++y)
    for(Int l=0;l<layerCount;++l) {
     PathfindCell *c=getCell((PathfindLayerEnum)coords.layers[l],x,y);
     if(c && ((Rva002F07F5CellView *)c)->info)for(Rva002F07F5Node *n=((Rva002F07F5CellView *)c)->info->items;n;n=n->next)if(n->obj!=obj)++oldCount;
    }
  }
 }
 {
 ICoord2D cell;ICoord2D *found=Rva002EBC14Cell(&cell,obj,dest);Int destX=found->x,destY=found->y;
 Int priority=view->templ->priority;Bool flag=view->templ->flag;AIUpdateInterface *ai=view->ai;
 Rva002E8BCF query((const Rva002E8BCFSrc *)((char *)ai+0x1CC),!flag,priority-1,obj->rva0028AFBB());
 Int x=destX-below; lastX=destX+above;
 for(;x<lastX;++x) {
  Int y=destY-below; lastY=destY+above;
  for(;y<lastY;++y)
   for(Int l=0;l<layerCount;++l) {
    Int layer=coords.layers[l];PathfindCell *c=getCell((PathfindLayerEnum)layer,x,y);
    if(!c)continue;
    if(c->m_info & 0x10000) {
     static Int deltaX[]={-1,1,0,0};static Int deltaY[]={0,0,-1,1};
     for(Int i=0;i<4;++i) {
      PathfindCell *neighbor=getCell((PathfindLayerEnum)layer,x+deltaX[i],y+deltaY[i]);
      if(neighbor && ((neighbor->m_info>>4)&0x3F)!=layer)return false;
     }
    }
    Rva002F07F5CellInfo *info=((Rva002F07F5CellView *)c)->info;
    if(info) {
     if(!((Rva002E6DC4 *)this)->rva002E6DC4(&query,c))return false;
     for(Rva002F07F5Node *n=info->items;n;n=n->next) {
      if(n->obj==obj)continue;
      ++newCount;
      if(newCount>=oldCount)return false;
      Object *effective=n->obj->rva002931F5(true);if(!effective)effective=n->obj;
      AIUpdateInterface *other=((Rva002F07F5ObjectView *)effective)->ai;
      if(other && *(Int *)((char *)other+0x16C)>0)return false;
     }
    }
   }
 }
 return true;
 }
}
