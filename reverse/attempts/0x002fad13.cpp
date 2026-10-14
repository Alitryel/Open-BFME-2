// ?FindAttackPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@02PAVRva002C9B80Owner@@_NPA_N@Z
// partial score=0.9796863056641045 date=2026-10-14
// ?FindAttackPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@02PAVRva002C9B80Owner@@_NPA_N@Z
// partial score=0.97969 date=2026-10-14
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport

namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <new>
#include <math.h>
#include "Common/GameLogicObjectLookupView.h"
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
 Bool isDownhillOnly()const{return m_downhillOnly;}
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
struct Coord3D;
struct AttackGeometry{char gap[0x10];float radial;float getRadial()const{return radial;}};
class Object
{
public:
 __forceinline const AttackGeometry& getAttackGeometry()const{return (*reinterpret_cast<const AttackGeometry *>((const char*)this+0xa8));}
 char rva00294815();
 void rva0028C2DD(Coord3D*) const;
 bool isSignificantlyAboveTerrain() const;
	Player *getControllingPlayer() const;
 Bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
    int rva0028B511() const;
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
#include "Lib/Coord3D.h"
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
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
	void rva0052DAE9(Bool open);
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
static __forceinline Int realToIntFloor(float f)
{return (Int)(float)floor((double)f);}
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
static __forceinline void zeroCoord3D(Coord3D *dst);
static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src);
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
class Rva002C9B80Owner
{
public:
 Bool isWithinAttackRange(Object *,const Coord3D *,Object *,const Coord3D *,float,Bool);
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
 Bool IsPassable(Int,Int);
 void rva005312BE();
	void rva00531300();
	void rva00531481();
	void rva005314C6(Int x, Int y, unsigned char flag);
};
struct Rva002EBC7FPair { int x,y; };
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
class Rva001E46E1 { public: float rva001E46E1(Object *); };
class AIUpdateInterface {
public:
    bool isAircraftThatAdjustsDestination() const;
    int rva0026417F(bool);
    Object *getCurrentVictim() const;
    char gap[0x1f0];
    Rva001E46E1 *locomotor;
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
#include "Lib/ICoord2D.h"
struct PathfinderCellIndex : ICoord2D {
	__forceinline PathfinderCellIndex() {}
	__forceinline PathfinderCellIndex(const PathfinderCellIndex &o) { x = o.x; y = o.y; }
};
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 { public: Bool rva002E7440(Int,Int); };
class Rva002E7414 { public: Int rva002E7414(Int,Int); };
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderOpenQueue {PathfindCell **first,**last;Bool empty()const{return first==last;}PathfindCell *front()const{return *first;}};
struct ICoord2D;
struct Rva002E7261Info;
struct PathfinderMineshaft { Int m_00; Int m_portal; Int m_08; Coord3D m_position; };
struct TCheckMovementInfo;
struct Rva002F5925Info;
class HierarchicalPath;
class Pathfinder
{
public:
 Bool rva002EA658(Object*,TCheckMovementInfo&,const ICoord2D*);
private:
 Int iterateCellsAlongLine(const ICoord2D*,const ICoord2D*,PathfindLayerEnum,Rva002F5925Info*);
public:
 Path *FindAttackPath(Object *,const LocomotorSet &,const Coord3D *,Object *,const Coord3D *,Rva002C9B80Owner *,Bool,Bool *);
 Bool isAttackViewBlockedByObstacle(const Object *,const Coord3D *,const Object *,const Coord3D *);
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
void Pathfinder::AddToOpenList(PathfindCell *cell)
{
	((PathfindCell *)cell)->rva0052DAE9(true);
	((Rva002F3738 *)((char *)this + 0x1d1f0))->rva002F3738((void **)&cell);
}
Path *Pathfinder::FindClosestHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher, Coord3D *adjustedTo)
{
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, true, adjustedTo);
}
Path *Pathfinder::BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
	const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked,
	Bool faceDirection)
{
	Path *path = new Path;
	PrependCells(path, fromPos, goalCell, center);
	float facing[2];
	facing[0] = 0.0f;
	facing[1] = 0.0f;
	if (m_1BEB6)
	{
		float orientation = obj->m_orientation;
		float angle = goalCell->rva0052DD75(orientation, 10, 0.5f);
		facing[0] = Cos(angle);
		facing[1] = Sin(angle);
	}
	path->rva00364551(obj, surfaces, blocked, m_1BEB6 ? facing : 0);
	if (faceDirection)
	{
		Coord3D dir = *((const Thing *)obj)->getUnitDirectionVector2D();
		path->rva00365E98(obj, &dir, surfaces, blocked);
	}
	return path;
}
int Pathfinder::CalcExtraCosts(Object *object,PathfindCell *oldCell,Rva002EBC7FPair *destination,int lower,int upper,bool ignoreEnemies)
{
    if (!oldCell) return 0;
    Rva002EBC7FPair minimum,maximum;
    minimum.x=destination->x-lower; minimum.y=destination->y-lower;
    maximum.x=destination->x+upper; maximum.y=destination->y+upper;
    int &reduction=upper;
    reduction=0;
    if (lower>=4) reduction=2;
    else if (lower>1) reduction=1;
    float ourArrival=-1.0f;
    int &cost=lower;
    cost=0;
    for (int x=minimum.x;x<maximum.x;++x) {
        for (int y=minimum.y;y<maximum.y;++y) {
            PathCollisionCell *cell=reinterpret_cast<PathCollisionCell *>(getCell(static_cast<PathfindLayerEnum>(oldCell->getLayer()),x,y));
            if (!cell || !cell->info) continue;
            for (PathCollisionNode *node=cell->info->occupants;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (enemies && ignoreEnemies) continue;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))>static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) continue;
                int amount;
                if (other->IsAtGoalPosition() || !object->getAI()->locomotor || !other->getAI()->locomotor) amount=8;
                else {
                    Coord3D target;
                    rva002EBC7F(&target,object,destination,1);
                    if (ourArrival<0.0f) {
                        float dx=object->position[0]-target.x;
                        float dy=object->position[1]-target.y;
                        Rva001E46E1 *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->rva001E46E1(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Rva001E46E1 *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->rva001E46E1(other);
                    if (!(otherArrival<ourArrival)) continue;
                    amount=4;
                }
                cost+=amount>>reduction;
            }
        }
    }
    return cost;
}
Bool Pathfinder::CheckDestination(Object *obj,Int cellX,Int cellY,PathfindLayerEnum layer,
    Int radius,Bool center,Int *out,Bool flag)
{
    PathfinderCheckCoordinates coordinates;
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,
            "          Pathfinder::CheckDestination called with: obj=%s(%d), cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s",
            obj->m_template->name(), obj->getID(), cellX,cellY,layer,radius,center?"TRUE":"FALSE");
    }
    if (obj->m_template->hasKind(109)) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          horde");
        if (layer==PATHFIND_LAYER_GROUND && !flag) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer is LAYER_GROUND");
            rva002E79A8((int)&coordinates.point,1,cellX,cellY,1);
            if (((TerrainLogicCheckDestination *)TheTerrainLogic)->slotC8(&coordinates.point)) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          narrow passage area");
                radius=1; center=true;
            }
        } else {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer != LAYER_GROUND, layer=%d",layer);
            radius=1; center=true;
        }
    }
    if (obj->m_template->hasKind(90) && obj->m_template->hasKind(8) && layer!=PATHFIND_LAYER_GROUND) {
        radius=1; center=false;
    }
    Int upper=radius;
    if (center) ++upper;
    if (obj->rva0028AFBB()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          human controlled");
        if (cellX-radius<m_extentLowX || cellX+upper>m_extentHighX || cellY-radius<m_extentLowY || cellY+upper>m_extentHighY) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"            returning false");
            return false;
        }
    }
    Bool aircraft=false;
    Int ignored=0, objectId=0;
    const LocomotorSet *locomotors=0;
    if (obj->getAI()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          I have an AI");
        ignored=((const Rva0006E009DwordField *)obj->getAI())->get();
        aircraft=obj->getAI()->isAircraftThatAdjustsDestination();
        objectId=obj->getID();
        locomotors=(const LocomotorSet *)((char *)obj->getAI()+0x1cc);
    }
    *out=0;
    Rva002E7C99 info;
    info.rva002E7C99((int)this,(int)obj,(int)out,0,ignored,flag,(int)locomotors);
    if (!aircraft && obj->m_template->hasKind(186)) {
        ICoord2DBase &position=coordinates.cells.position;
        position.x=cellX;position.y=cellY;
        GeometryShape shape;
        ((const GeometryInfo *)((char *)obj+0xa8))->rva006BD9C0(shape);
        ICoord2DBase &size=coordinates.cells.size;
        size.x=(int)((shape.major*2.0f+4.0f)*0.1f);
        size.y=(int)((shape.minor*2.0f+4.0f)*0.1f);
        void *contain=*(void **)((char *)obj+0x250);
        if (contain && ((PathfinderContain31 *)contain)->slot7C()) {
            Int count=((PathfinderContain28 *)contain)->slot70();
            if (count>0) {
                float fraction=(float)((PathfinderContain69 *)contain)->slot114(0)/count;
                size.x=(int)((size.x-2.0f)*fraction+2.0f);
                size.y=(int)((size.y-2.0f)*fraction+2.0f);
            }
        }
        return !rva002EED80(&position,&size,obj->GetGoalAngle(),layer,(Rva002E9D09 *)&info);
    }
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,"          BEGIN cell iteration (deep innards), i from %d to %d, j from %d to %d",
            cellX-radius,cellX+upper,cellY-radius,cellY+upper);
    }
    for (Int i=cellX-radius;i<cellX+upper;++i) {
        for (Int j=cellY-radius;j<cellY+upper;++j) {
            PathfindCell *cell=getCell(layer,i,j);
            if (!cell) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          OFF THE MAP, return false: i=%d, j=%d",i,j);
                return false;
            }
            if (aircraft) {
                if (((Rva0052DB4D *)cell)->rva0052DB4D(objectId)) {
                    if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          checkForAircraft=TRUE, return false: i=%d, j=%d",i,j);
                    return false;
                }
            } else if (((Rva002E9D09 *)&info)->rva002E9D09((Object *)cell,0,0)) return false;
        }
    }
    return true;
}
struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };
struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);
Int Pathfinder::rva002F0A72(PathfindCell *cell, PathfindCell *goal)
{
    unsigned int cost = 0;
    Int x = cell->getXIndex(), y = cell->getYIndex();
    for (_STL::vector<Rva002F35AFHop>::iterator it = m_1C1CC.end();
         it != m_1C1CC.begin(); --it)
    {
        PathfinderCostCellInfo point = (it - 1)->m_position;
        Int nx = point.x, ny = point.y;
        Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - nx);
        Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - ny);
        if (dx > dy)
            cost = (cost + 14 * dy) + (cost + 10 * (dx - dy));
        else
            cost = (cost + 14 * dx) + (cost + 10 * (dy - dx));
        cost += 1400;
        x = nx;
        y = ny;
    }
    Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - goal->getXIndex());
    Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - goal->getYIndex());
    if (dx > dy)
        return 14 * dy + cost + 10 * (dx - dy);
    return 14 * dx + cost + 10 * (dy - dx);
}
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
void Rva002E6BA1::rva002E6BA1(int a, In002E6BA1 *b)
{
	m_30 = a;
	m_00 = b->x;
	m_04 = b->y;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
	++TheMixFileInfoCount;
}
class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);
};
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(a, in);
	return node;
}
inline bool ICoord2D::operator==(const ICoord2DBase &that) const
{
	return x == that.x && y == that.y;
}
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct PathfinderSearchRadiusView { char pad[0x11F0]; Int searchRadius; };
static __forceinline Coord3D adjustCellCenter(bool center,Rva002E8C23Pair *cell,PathfindLayerEnum layer);
static __forceinline Bool findAdjustedCell(Pathfinder *finder,ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForAdjust *info);
extern float g_00BC7838;
struct PathfinderCellPoint : Coord3D {
	__forceinline PathfinderCellPoint() {}
	__forceinline PathfinderCellPoint(const PathfinderCellPoint &o) { x = o.x; y = o.y; z = o.z; }
	__forceinline ~PathfinderCellPoint() {}
};
PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer)
{
	PathfinderCellPoint pos;
	if (centerInCell) {
		pos.x = ((float)cellX + 0.5f) * 10.0f;
		pos.y = ((float)cellY + 0.5f) * 10.0f;
	} else {
		pos.x = ((float)cellX + g_00BC7838) * 10.0f;
		pos.y = ((float)cellY + g_00BC7838) * 10.0f;
	}
	if (layer != PATHFIND_LAYER_GROUND || !((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(pos.x, pos.y, &pos.z, 0, 0))
		pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
	return pos;
}
PathfinderCellPoint Rva002E8C23Call(Bool centerInCell, PathfindCell *cell)
{
	return rva002E79A8(centerInCell, cell->getXIndex(), cell->getYIndex(), (PathfindLayerEnum)cell->getLayer());
}
void Pathfinder::PrependCells(Path *path,const Coord3D *fromPos,PathfindCell *goalCell,Bool center)
{
 Coord3D pos;
 PathfindCell *cell,*prevCell=0;
 Bool goalCellNull=(goalCell->getParentCell()==0);
 for(cell=goalCell;cell->getParentCell();cell=cell->getParentCell()) {
  pos=Rva002E8C23Call(center,cell);
  if(prevCell && cell->getXIndex()==prevCell->getXIndex() && cell->getYIndex()==prevCell->getYIndex()) {
   PathfindLayerEnum layer=(PathfindLayerEnum)cell->getLayer();
   if(layer==PATHFIND_LAYER_GROUND)layer=(PathfindLayerEnum)prevCell->getLayer();
   path->firstNode->layer=layer;continue;
  }
  Bool canOptimize=true;
  if(cell->getType()==2) {
   if(prevCell && prevCell->getType()!=2) {if(path->firstNode)path->firstNode->canOptimize=false;}
  } else {if(prevCell && prevCell->getType()==2)canOptimize=false;}
  if(cell->getParentWaypoint()) {
   Waypoint *parent=cell->getParentWaypoint();
   Int id=parent->id;pos=parent->location;
   if(id!=0x7fffffff) {
    if(cell->waypoint) {
     if(path->firstNode){path->firstNode->portalID=cell->waypoint->id;path->firstNode->canOptimize=false;}
     path->rva00265596(&cell->waypoint->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
    }
    Waypoint *link=cell->getParentWaypoint()->chainNext;
    while(link) {
     if(path->firstNode){path->firstNode->portalID=link->id;path->firstNode->canOptimize=false;}
     path->rva00265596(&link->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
     if(link->linkCount!=0)break;
     link=link->chainNext;
    }
    if(path->firstNode){path->firstNode->portalID=id;path->firstNode->canOptimize=false;}
   }
  }
  path->rva00265596(&pos,TheTerrainLogic->getLayerForDestination(0,&pos),0x7fffffff);
  path->firstNode->canOptimize=canOptimize;
  if(cell->m_pathInfo->flags&1)path->blockedByAlly=true;
  if(prevCell)prevCell->m_pathInfo->parent=0;
  prevCell=cell;
 }
 if(cell && cell->m_pathInfo) {
  if(goalCellNull) {pos=Rva002E8C23Call(center,cell);path->rva00265596(&pos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);}
  if(fromPos->x!=path->firstNode->position.x || fromPos->y!=path->firstNode->position.y)
   path->rva00265596(fromPos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
 }
}
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
static __forceinline PathNode *makeAircraftNode(const Coord3D *p);
static __forceinline void appendAircraftNode(PathNode *current,PathNode *node);
class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
int Rva002E6E6CGet(int);
extern int g_Va00DFECD0;
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva002EBCD6Split(void *,int *,int *);
static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
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
__declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos);
int __cdecl Rva002E9B31Get(void *p);
__declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest);
extern GameLogic *TheGameLogic;
struct Rva002CECAETarget;
void Rva002CECAEAppend(Rva002CECAETarget *,const char *,...);
class Rva0028B984ByteField {public:unsigned char get()const;};
struct PathfinderHordeMeleeRadiusView { char pad[0x11F4]; Int searchRadius; };
static __forceinline Bool findHordeMeleeCell(Pathfinder *finder,const ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForMeleeHordeAdjust *info);
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
static __forceinline Coord3D *cellPointArg(const PathfinderCellPoint &p);
static __forceinline void *boolArg(const Bool &value);
static __forceinline Bool pathfinderLogOn();
static __forceinline void pathfinderLog(const char *text);
static __forceinline void rotateOffset(float &x, float &y, float angle);
static __forceinline void setInfoCell(TCheckMovementInfo &info, ICoord2D c);
static __forceinline void setInfoCellYX(TCheckMovementInfo &info, ICoord2D c);
#include "Lib/IRegion2D.h"
bool __cdecl ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);
extern float g_00BC7838;
static __forceinline float clipCellFloor(float f);
static __forceinline long clipCellRound(float f);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Rva002E6FDF *Rva002E6FDF::rva002E6FDF()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_11 = 0;
	m_14 = 0;
	m_18 = 0;
	_ReadWriteBarrier();
	m_24 = -1;
	m_1C = 0;
	m_20 = 0;
	m_21 = 0;
	m_28 = 0;
	m_2C = 0;
	m_31 = 0;
	m_32 = 0;
	m_30 = 0;
	m_34 = 0;
	return this;
}
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
static __forceinline void checkCellFlags(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info);
static __forceinline Bool checkCellUnits(Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID);
static __forceinline Bool checkCell(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID);
static __forceinline void readMoverInfo(TCheckMovementInfo &info, Object *obj);
struct Gen_p12pod {Int a[3];};
class Rva002E7964 {
public:
 void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);
 char pad[0x14];IRegion2D extent;
};
struct PathfinderPatchLimitView { char pad[0x120C]; unsigned int maxCells; };
PathfinderCellIndex Pathfinder::Rva002E7917(bool center, const Coord3D *pos)
{
	PathfinderCellIndex tmp;
	Rva002E7875WorldToCell(&tmp, center, pos);
	if (tmp.x < m_clampLo.x)
		tmp.x = m_clampLo.x;
	if (tmp.y < m_clampLo.y)
		tmp.y = m_clampLo.y;
	if (tmp.x > m_clampHi.x)
		tmp.x = m_clampHi.x;
	if (tmp.y > m_clampHi.y)
		tmp.y = m_clampHi.y;
	return tmp;
}
PathfindCell *Pathfinder::rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos)
{
	PathfinderCellIndex cell = Rva002E7917(true, pos);
	return getCell(layer, cell.x, cell.y);
}
class MathCoord2D
{
public:
	MathCoord2D() {}
	MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float ix, float iy) : x(ix), y(iy) {}
	MathCoord2D(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~MathCoord2D() {}
	float dot(const MathCoord2D &c) const { return y * c.y + x * c.x; }
	MathCoord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	MathCoord2D &operator-=(const MathCoord2D &c) { x -= c.x; y -= c.y; return *this; }
	MathCoord2D &operator+=(const MathCoord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthEstimate() const { return fabs(x) > fabs(y) ? fabs(x) + fabs(y) * 0.25f : fabs(y) + fabs(x) * 0.25f; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + y * y); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};
inline MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right)
{
	left -= right;
	return left;
}
inline MathCoord2D operator+(MathCoord2D left, const MathCoord2D &right)
{
	left += right;
	return left;
}
class Rva0053476A{public:~Rva0053476A();};
class Rva002EAD62{public:void rva002EAD62();Rva0053476A *m_ptr;};
void Rva002EAD62::rva002EAD62(){delete m_ptr;}

struct PathfinderAttackHandle {
 Path *path;
 __forceinline PathfinderAttackHandle(Path*p):path(p){}
 __forceinline ~PathfinderAttackHandle(){((Rva002EAD62*)this)->rva002EAD62();}
};
class PartitionManager{public:float rva002C9C37(const Object*,const Object*,void*);};
struct PathfinderAttackNode{PathfinderAttackNode*next,*previous,*optimized;};
struct PathfinderAttackPathView{void*vptr;PathfinderAttackNode*first;};
struct AttackLimitView{char gap[0x9b8];Int debugAI;char pad[0x1214-0x9bc];unsigned int attackLimit;};
class Rva002EAB6F {public:Rva002EAB6F(Int,const Rva002E8BCFSrc *,unsigned char,Int,Object *,unsigned char,Int,Int);char fields[0x34];};
struct Rva002F5925Info;
struct BurningCell {char pad[6];unsigned short count;char pad8[12];};
struct BurningGrid {char pad[0x70];BurningCell **cells;char word74[4];Int width,height;};
class Rva002872BA;extern Rva002872BA *TheTriggerManager;
Int Rva002E6E6CGet(Int);
__declspec(noinline) Int Pathfinder::rva002F83F5(PathfindCell *parentCell,PathfindCell *goalCell,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackMode)
{
if(obj->m_template->hasKind(109)||obj->m_template->hasKind(191)){radius=1;centerInCell=true;}
Bool canPathThroughUnits=false;
if(obj->getAI())canPathThroughUnits=*(Bool *)((char *)obj->getAI()+0x3ba);
if(!m_isTunneling && !locomotorSet.isDownhillOnly() && goalCell && !(parentCell->getXIndex()&3) && !(parentCell->getYIndex()&3)) {
ICoord2D end;const ICoord2D *endPtr;
if(m_1C1CC.empty()){endPtr=(ICoord2D *)goalCell->m_pathInfo;}
else {endPtr=(ICoord2D *)&m_1C1CC.back().m_position;}
end=*endPtr;PathfindLayerEnum layer=(PathfindLayerEnum)parentCell->getLayer();Rva002EAB6F query((Int)this,(const Rva002E8BCFSrc *)&locomotorSet,centerInCell,radius,obj,isHuman,(Int)goalCell,m_1C1CC.empty()?attackMode:0);
iterateCellsAlongLine((const ICoord2D *)parentCell->m_pathInfo,&end,layer,(Rva002F5925Info *)&query);
}
Int cellCount=0;
TCheckMovementInfo info;((Rva002E6FDF *)&info)->rva002E6FDF();
info.layer=(PathfindLayerEnum)parentCell->getLayer();info.radius=radius;info.centerInCell=centerInCell;
info.m_14=12;if(!obj->m_template->hasKind(90))info.m_14=28;
info.m_18=(ObjectID)(obj->getAI()?((Rva0006E009DwordField *)obj->getAI())->get():0);
Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;info.m_11=true;
*(Rva002E8BCF *)info.m_1C=Rva002E8BCF((const Rva002E8BCFSrc *)&locomotorSet,!flag,priority-1,obj->rva0028AFBB());
static Int deltaX[]={1,0,-1,0,1,-1,-1,1};static Int deltaY[]={0,1,0,-1,1,1,-1,-1};
Bool neighborFlags[8];
for(Int i=0;i<8;++i) {
neighborFlags[i]=false;
Int x=parentCell->getXIndex()+deltaX[i],y=parentCell->getYIndex()+deltaY[i];ICoord2D coords={x,y};
PathfindCell *newCell=getCell((PathfindLayerEnum)parentCell->getLayer(),x,y);
if(!newCell)continue;
if((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06() || (unsigned char)((Rva002E6AF3 *)newCell)->get())continue;
if(newCell->getLayer()!=parentCell->getLayer() && !(((Rva002E8BCF *)info.m_1C)->surfaces&64) && newCell->getLayer()!=((parentCell->m_info>>10)&63) && ((newCell->m_info>>10)&63)!=parentCell->getLayer() && (((parentCell->m_info>>10)&63)!=16 || ((newCell->m_info>>10)&63)!=((parentCell->m_info>>10)&63)))continue;
if(isHuman){if(x<m_extentLowX)continue;if(y<m_extentLowY)continue;if(x>m_extentHighX)continue;if(y>m_extentHighY)continue;}
if(i>=4 && !neighborFlags[i&3] && !neighborFlags[(i+1)&3])continue;
if(locomotorSet.isDownhillOnly()) {
float oldZ=TheTerrainLogic->getGroundHeight((float)(parentCell->getXIndex()*10),(float)(parentCell->getYIndex()*10),0);
float newZ=TheTerrainLogic->getGroundHeight((float)(x*10),(float)(y*10),0);
if(oldZ<newZ)continue;
}
Bool movementValid=((Rva002E6DC4 *)this)->rva002E6DC4(info.m_1C,newCell);
Bool tunnelingValid=false;
if(m_isTunneling)tunnelingValid=(newCell->getLayer()==parentCell->getLayer());
if(!movementValid && !tunnelingValid){newCell->allocateInfo((In002E6BA1 *)&coords);newCell->PutOnClosedList(&m_closedList);continue;}
neighborFlags[i]=true;
info.cell.x=x;info.cell.y=y;
if(!rva002EA658(obj,info,(const ICoord2D *)parentCell->m_pathInfo)) {
if(!tunnelingValid){newCell->allocateInfo((In002E6BA1 *)&coords);newCell->PutOnClosedList(&m_closedList);continue;}
++info.m_34;
} else {if(movementValid)m_isTunneling=false;}
if(!newCell->m_pathInfo)++cellCount;
newCell->allocateInfo((In002E6BA1 *)&coords);
unsigned int newCostSoFar=0;
Int dx=goalCell?abs(x-goalCell->getXIndex()):3;
Int dy=goalCell?abs(y-goalCell->getYIndex()):3;
if(newCell->getType()==2 && !(unsigned char)(newCell->m_info>>16&1)) {
float oldZ=TheTerrainLogic->getGroundHeight((float)(parentCell->getXIndex()*10),(float)(parentCell->getYIndex()*10),0);
float newZ=TheTerrainLogic->getGroundHeight((float)(x*10),(float)(y*10),0);
if(fabs(oldZ-newZ)<10.0f)newCostSoFar=98;
} else if((unsigned char)(newCell->m_info>>16)&1 || (unsigned char)(newCell->m_info>>23)&1){if(dx+dy>3)newCostSoFar=10;}
newCell->m_pathInfo->flags&=~1U;
if(info.m_2C){newCostSoFar+=14;if(!canPathThroughUnits)newCell->m_pathInfo->flags|=1;}
Int remaining=0;
if(goalCell){remaining=rva002F0A72(newCell,goalCell);if(attackMode && info.m_32)newCostSoFar+=30;}
if((unsigned char)Rva002E6E6CGet(newCell->getLayer()) && !m_zoneManager.IsPassable(x,y) && !((unsigned char)(newCell->m_info>>21)&1))newCostSoFar+=1000;
if(newCell->getType()==4){Int obstacle=newCell->m_pathInfo?newCell->m_pathInfo->obstacleID:0;if(obstacle!=m_ignoreObstacleID)newCostSoFar+=1000;}
newCostSoFar+=info.m_34*10;
if(m_isTunneling && !((Rva002E6DC4 *)this)->rva002E6DC4(info.m_1C,newCell))newCostSoFar+=100;
if((unsigned char)(newCell->m_info>>21)&1)newCostSoFar>>=1;
newCostSoFar+=newCell->CalcCostSoFar((const Rva002E6C79 *)parentCell);
newCostSoFar+=CalcExtraCosts(obj,parentCell,(Rva002EBC7FPair *)&coords,info.radius,info.radius+(info.centerInCell?1:0),true);
Int fireX=realToIntFloor(((float)(x*10)+0.5f)*0.1f);
Int fireY=realToIntFloor(((float)(y*10)+0.5f)*0.1f);
BurningGrid *grid=(BurningGrid *)TheTriggerManager;
Bool burning=false;
if(fireX>=0 && fireX<grid->width && fireY>=0 && fireY<grid->height)burning=grid->cells[fireX][fireY].count>0;
if(burning)newCostSoFar+=10;
newCell->m_pathInfo->costSoFar=(unsigned short)newCostSoFar;
newCell->SetParentCell((Int *)parentCell);
if(m_isTunneling)remaining=0;
newCell->m_pathInfo->totalCost=(unsigned short)(newCell->m_pathInfo->costSoFar+remaining);
AddToOpenList(newCell);
}
return cellCount;
}
__declspec(noinline) inline float Coord3D::length()const {return (float)sqrt(x*x+y*y+z*z);}
__declspec(noinline) inline void Coord3D::normalize(){float len=length();if(len!=0.0f){float s=1.0f/len;x*=s;y*=s;z*=s;}}
struct Rva002E8BCFSrc{char pad[0x10];Int m10;char m14;Bool m15;};
__declspec(noinline) Rva002E8BCF::Rva002E8BCF(const Rva002E8BCFSrc*src,Bool a,Int b,Bool c){surfaces=src->m10;field4=a;field5=c;maxLayer=b;fieldC=src->m15;}
struct PathfinderAttackCoord : Coord3D {
    __forceinline PathfinderAttackCoord() {}
    __forceinline PathfinderAttackCoord(const Coord3D &v) { x=v.x;y=v.y;z=v.z; }
    __forceinline PathfinderAttackCoord(const PathfinderAttackCoord &v) { x=v.x;y=v.y;z=v.z; }
    __forceinline ~PathfinderAttackCoord(){}
    void set(float xx,float yy,float zz){x=xx;y=yy;z=zz;}
    void sub(const Coord3D&p){x-=p.x;y-=p.y;z-=p.z;}
    void scale(float f){x*=f;y*=f;z*=f;}
    void add(const Coord3D&p){x+=p.x;y+=p.y;z+=p.z;}
};
Path *Pathfinder::FindAttackPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,
 Object *victim,const Coord3D *victimPos,Rva002C9B80Owner *weapon,Bool skipQuick,Bool *partial)
{
    if (!m_isMapReady) return 0;
    if (partial) *partial=false;
    m_srcMineshaft=0; m_destMineshaft=0;
    Bool crusher=obj->rva00294815()>0;
    Int radius; Bool center;
    Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
    Int priority=obj->m_template->priority;
    Bool flag=obj->m_template->flag;
    Rva002E8BCF movement((const Rva002E8BCFSrc *)&locos,!flag,priority-1,obj->rva0028AFBB());
    Bool human=true;
    if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1) human=false;
    if(!skipQuick){
        PathfinderAttackCoord curPos(*(const Coord3D *)obj->position);
        PathfinderAttackCoord quickGoal(victim?*(const Coord3D *)victim->position:*victimPos);
        struct {float x,y;} step;
        {PathfinderAttackCoord delta;delta.set(quickGoal.x-curPos.x,quickGoal.y-curPos.y,0);
        delta.normalize();step.x=(*(const volatile float*)&delta.x)*10.0f;step.y=(*(const volatile float*)&delta.y)*10.0f;}
        for(Int i=1;i<10;++i){
            PathfinderAttackCoord test(curPos);
            test.x+=step.x*i*0.5f;test.y+=step.y*i*0.5f;
            ICoord2D index;Rva002E7875WorldToCell(&index,true,&test);
            if(human && (index.x<m_extentLowX || index.y<m_extentLowY || index.x>m_extentHighX || index.y>m_extentHighY))break;
            PathfindCell *cell=getCell((PathfindLayerEnum)obj->rva0028B511(),index.x,index.y);
            if(!cell || !((Rva002E6DC4 *)this)->rva002E6DC4(&movement,cell))break;
            if(!bfmeWrapE6E90(obj,(void *)index.x,(void *)index.y,(void *)obj->rva0028B511(),(void *)radius,*(void **)&center))break;
            if(weapon->isWithinAttackRange(obj,&test,victim,victimPos,10.0f,true) &&
               !isAttackViewBlockedByObstacle(obj,&test,victim,victimPos)){
                Path *path=new Path;
                path->rva00265596(&test,(PathfindLayerEnum)obj->rva0028B511(),0x7fffffff);
                path->rva00265596(&curPos,(PathfindLayerEnum)obj->rva0028B511(),0x7fffffff);
                PathfinderAttackNode *first=((PathfinderAttackPathView *)path)->first;
                first->optimized=first->next;
                if(((AttackLimitView*)TheWritableGlobalData)->debugAI==1)SetDebugPath((Rva002EDEABArg *)path);
                return path;
            }
        }
    }
    PathfinderAttackCoord goal(*victimPos);
    if(victim){
        if(victim->m_template->hasKind(150))victim->rva0028C2DD(&goal);
        if(!weapon->m_04->get()){
            PathfinderAttackCoord delta(*(Coord3D*)obj->position);delta.sub(*(Coord3D*)victim->position);delta.z=0;
            delta.Normalize();
            delta.scale(victim->getAttackGeometry().getRadial()+10.0f);goal.add(delta);
        }
    }
    reinterpret_cast<_STL::vector<Gen_p12pod> &>(m_1C1CC).clear();
    m_zoneManager.rva005312BE();
    PathfinderAttackHandle hierarchical(FindClosestHierarchicalPath(human,locos,obj,from,&goal,crusher,&goal));
    if(!hierarchical.path)m_zoneManager.rva00531300();
    unsigned int count=0;
    Int attackDistance=(Int)((PartitionManager *)weapon)->rva002C9C37(obj,victim,(void *)victimPos)+30;
    PathfinderAttackCoord objectPos(*(const Coord3D *)obj->position);
    if(center){objectPos.x+=5.0f;objectPos.y+=5.0f;}
    ICoord2D startIndex;
    { ICoord2D scratch; startIndex=*Rva002E7875WorldToCell(&scratch,true,&objectPos); }
    PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),&objectPos);
    if(!parent)return 0;
    if(!obj->getAI())return 0;
    const PathfindCell *start=parent;
    parent->allocateInfo((In002E6BA1 *)&startIndex);
    parent->StartPathfind(0);
    ICoord2D victimIndex;
    Rva002E7875WorldToCell(&victimIndex,true,victim?(const Coord3D *)victim->position:victimPos);
    PathfindCell *goalCell=getCell(PATHFIND_LAYER_GROUND,victimIndex.x,victimIndex.y);
    if(!goalCell)return 0;
    goalCell->allocateInfo((In002E6BA1 *)&victimIndex);
    AddToOpenList(parent);
    PathfindCell *acceptable=0,*closest=0;
    Int acceptableDistance=9999999;
    Int closestOrder=0;
    Int dx=goalCell->getXIndex()-parent->getXIndex();
    Int dy=goalCell->getYIndex()-parent->getYIndex();
    float closestDistance=(float)(dx*dx+dy*dy)*0.9f;
    Bool checkLOS=false;
    if(!victim)checkLOS=true;
    if(victim && !victim->isSignificantlyAboveTerrain())checkLOS=true;
    PathfinderSearchCellsVisited=0;
    while((parent=rva002F36E5())!=0){
        PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
        if(hierarchical.path){
            Int order=((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
            Int dx=goalCell->getXIndex()-parent->getXIndex(),dy=goalCell->getYIndex()-parent->getYIndex();
            float distance=(float)(dx*dx+dy*dy);
            if(order>closestOrder || (order==closestOrder && distance<closestDistance)){
                closest=parent;closestOrder=order;closestDistance=distance;
            }
        }
        Int cellState=parent->m_pathInfo?(Int)parent->m_pathInfo->parentWaypoint:0;
        if(!cellState && weapon->isWithinAttackRange(obj,&cellCenter,victim,victimPos,0.0f,true)){
            Int destinationDistance;
            if(CheckDestination(obj,parent->getXIndex(),parent->getYIndex(),(PathfindLayerEnum)parent->getLayer(),radius,center,&destinationDistance,false)){
                Bool blocked=checkLOS?isAttackViewBlockedByObstacle(obj,&cellCenter,victim,victimPos):false;
                if(start==parent)blocked=true;
                else {
                    PathfinderCellPoint pos=Rva002E8C23Call(center,parent);
                    float dx=pos.x-objectPos.x,dy=pos.y-objectPos.y;
                    if(dx*dx+dy*dy<25.0f)blocked=true;
                }
                if(!blocked && destinationDistance>1){
                    blocked=true;
                    if(destinationDistance<acceptableDistance){acceptable=parent;acceptableDistance=destinationDistance;partial=0;}
                }
                if(!blocked){
                    parent->PutOnClosedList(&m_closedList);
                    Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,parent,center,false,true);
                    if(goalCell->m_pathInfo && !static_cast<unsigned char>(((Rva002E6B06 *)goalCell)->rva002E6B06()) && !static_cast<unsigned char>(((const Rva002E6AF3 *)goalCell)->get()))goalCell->ReleaseInfo();
                    rva002F40E7();return path;
                }
            }
        }
        parent->PutOnClosedList(&m_closedList);
        if(count<((AttackLimitView*)TheWritableGlobalData)->attackLimit){
            if(!skipQuick)CheckChangeLayers(parent,obj);
            count+=rva002F83F5(parent,goalCell,locos,human,center,radius,&startIndex,obj,attackDistance);
        }
    }
    if(acceptable){
        Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,acceptable,center,false,true);
        rva002F40E7();return path;
    }
    if(closest){
        if(partial)*partial=true;
        Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,closest,center,false,true);
        rva002F40E7();return path;
    }
    rva002F40E7();m_isTunneling=false;goalCell->ReleaseInfo();return 0;
}
