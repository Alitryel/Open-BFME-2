// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.99 date=2026-10-20
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.9296820699597845 date=2026-10-19
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.9296820699597845 date=2026-10-19
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.9588173627150627 date=2026-10-16
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.9578922598050313 date=2026-10-14
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.9588 date=2026-10-13
// W7-MP6 r10: first-line symbol corrected to the emitted body (the old name passed the wrong stack bytes for this RVA)
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.993 date=2026-10-13
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.993 date=2026-10-13 (W7-S4: whole normal path wrapped in a block)
// ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// partial score=0.98 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include /Oi- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
//
// NEAR DRAFT (not landable as is): replacement for
// Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsPositionHorde.cpp
// adding ?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z
// retail 0x001E756D (1726 bytes, ret 0x10; WB twin 0x00AE6C40). 0x001E3FFD and
// 0x001E7389 stay exact in this draft. 0x001E756D compiles to 1726 bytes, normalized
// instruction ratio 0.986: (1) the type-2 portal vector sits at [ebp-0x4c]
// (retail [ebp-0x3c]) and shares its slot with the type-8 vector (retail
// [ebp-0x48]) so cl tail-merges the type-2 destroy-and-return into the type-8
// one (retail keeps a separate copy after the loop); (2) retail hoists the
// LocomotorTemplate +0xD8 load between the goal copy stores in the normal path.
//
// Locomotor's horde portal movement, retail 0x001E7389 (484 bytes), with the
// path getter it calls.
//
// ?Rva001E3FFDGet@@YAPAXPAURva001E3FFDOuter@@@Z, retail 0x001E3FFD (24 bytes):
// the Object's +0x258 AI and that AI's +0x140 path, else null. Defined here,
// ahead of its Locomotor callers, because retail cleans up the calls to it
// with `add esp,4` after moving the result out of eax; cl 7.1 emits that
// shape (rather than `pop ecx`) only when the callee body is in the same
// unit and known to leave ecx alone. Callers: 0x001E6007 0x001E7389
// 0x001E756D 0x001E9083 (all Locomotor).
//
// ?moveTowardsPositionHordeOnClimbPortal@Locomotor@@QAE_NPAVObject@@PAVWaypoint@@@Z,
// retail 0x001E7389 (484 bytes, ret 8). Name from the WorldBuilder twin
// 0x00AE58F0 (Locomotor.cpp asserts 1963..2010); called from 0x001E764E in
// 0x001E756D (WB moveTowardsPositionHorde) when the path's next waypoint
// (TheTerrainLogic slot 35, type at +0x60) is type 3. Requires the
// waypoint's +0xB0 object to exist and the Object's +0x250 contain to hand
// out a horde contain interface (slot +0x7C). Peeks the climb position past
// the portal and takes the 16-byte path point (0x00364521); while the Object
// is farther than 10 from the climb position it is moved there (rowed
// Thing::setPosition), the transform matrix at +0x68 gets the translation,
// the layer is applied (rowed Object 0x0028B4CE), the horde interface slot
// +0x1BC gets the goal, the point's position, waypoint and layer, the frame
// deadline at +0x64 becomes TheGameLogic's frame plus 12 times the global
// 0x009BA4E4, and the result is true. Otherwise it stays true until the
// members reached the end of their path (slot +0x1CC) or the deadline
// passed, then advances the path past the portal (rowed 0x0036617B) with a
// temporary vector and returns false.
// Retail evidence: EH frame for the vector only, SSE distance test against
// 100.0f (0x00BC292C), the waypoint argument slot reused for the path.
// Callee rows: 0x00049DC5 0x00363DF9 0x00364521 0x0030AA80 0x001E34FA
// 0x0028B4CE 0x001E3511 0x001E34B2 (Rva001E34B2.cpp) 0x0036617B; the vector's
// base ctor is the ICF-folded 0x00211E58.
// Facts from retail: offsets slots and types; names of the method and the
// waypoint come from the WorldBuilder twin; the point and node views are
// address-named because their real types are unproven.
#include <vector>
#define COORD3D_VIEW_INLINE
#include "Lib/Coord3DCtorView.h"
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "../../../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
typedef float Real;
enum PathfindLayerEnum

{
 LAYER_INVALID = 0
 
}
;
enum ScienceType

{
 SCIENCE_INVALID = -1
 
}
;
// The float triple 0x001E34B2 returns by value (see Rva001E34B2.cpp).
struct Rva001E34B2Point

{
 Real x;
 Real y;
 Real z;
 Rva001E34B2Point(Real ax, Real ay, Real az) 
 {
  x = ax;
  y = ay;
  z = az;
  
 }
 Rva001E34B2Point(const Rva001E34B2Point &o) 
 {
  x = o.x;
  y = o.y;
  z = o.z;
  
 }
 
}
;
// What 0x00364521 returns by value (16 bytes): a node and a position.
struct Rva003642DFNode;
struct Rva003642DFResult

{
 Rva003642DFNode *m_node;
// +0x00
 Coord3D m_pos;
// +0x04
 
}
;
class Rva001E34FA

{
 public:
 int rva001E34FA();
// 0x001E34FA, the node's layer
 
}
;
class Rva001E3511

{
 public:
 int rva001E3511();
// 0x001E3511, the node's waypoint (0x7FFFFFFF without one)
 
}
;
class Rva001E34B2

{
 public:
 Rva001E34B2Point rva001E34B2();
// 0x001E34B2, the node's position
 
}
;
class Rva0008BB38FloatField;
class Path

{
 public:
 Coord3D *PeekPastClimbPortal(Coord3D *out);
 Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);
 void AdvancePastPortal(ScienceType st, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *vec);
 Rva003642DFResult rva003642DF(Real dist);
 bool DoAdvanceAlongPath(const Coord3D *pos, bool flag);
 int GetNextPortalID();
 unsigned m_count;
 
}
;
class Rva00363D20

{
 public:
 double rva00363D20();
// 0x00363D20, on the 16-byte path point
 
}
;
struct Rva001E3FFDInner

{
 char m_pad00[0x140];
 void *m_p140;
// +0x140
 
}
;
struct Rva001E3FFDOuter

{
 char m_pad00[0x258];
 Rva001E3FFDInner *m_p258;
// +0x258
 
}
;
void *__cdecl Rva001E3FFDGet(Rva001E3FFDOuter *p)

{
 Rva001E3FFDInner *q = p->m_p258;
 return q ? q->m_p140 : 0;
 
}
// The horde interface getHordeContainInterface hands out (retail vtable
// 0x00C44C58: +0x1BC is 0x0046ECDE, +0x1CC is 0x0046A677).
class HordeContainInterface

{
 public:
 virtual void s000();
 virtual void s001();
 virtual void s002();
 virtual void s003();
 virtual void s004();
 virtual void s005();
 virtual void s006();
 virtual void s007();
 virtual void s008();
 virtual void s009();
 virtual void s010();
 virtual void s011();
 virtual void s012();
 virtual void s013();
 virtual void s014();
 virtual void slot15();
// +0x3C
 virtual void slot16();
// +0x40
 virtual void s017();
 virtual void s018();
 virtual void s019();
 virtual void s020();
 virtual void s021();
 virtual void s022();
 virtual void s023();
 virtual void s024();
 virtual void s025();
 virtual void s026();
 virtual void s027();
 virtual void s028();
 virtual void s029();
 virtual void s030();
 virtual void s031();
 virtual void s032();
 virtual void s033();
 virtual void s034();
 virtual void s035();
 virtual void s036();
 virtual void s037();
 virtual void s038();
 virtual void s039();
 virtual void s040();
 virtual void s041();
 virtual void s042();
 virtual void s043();
 virtual void s044();
 virtual void s045();
 virtual void s046();
 virtual void s047();
 virtual void s048();
 virtual void s049();
 virtual void s050();
 virtual void s051();
 virtual void s052();
 virtual void s053();
 virtual void s054();
 virtual void s055();
 virtual void s056();
 virtual void s057();
 virtual void s058();
 virtual void s059();
 virtual void s060();
 virtual void s061();
 virtual void s062();
 virtual void s063();
 virtual void s064();
 virtual void s065();
 virtual void s066();
 virtual void s067();
 virtual void s068();
 virtual void s069();
 virtual void s070();
 virtual void s071();
 virtual void s072();
 virtual void s073();
 virtual void s074();
 virtual void s075();
 virtual void s076();
 virtual void s077();
 virtual void s078();
 virtual void s079();
 virtual void s080();
 virtual void s081();
 virtual void s082();
 virtual void s083();
 virtual void s084();
 virtual void s085();
 virtual void s086();
 virtual void s087();
 virtual void s088();
 virtual void s089();
 virtual void s090();
 virtual void s091();
 virtual void s092();
 virtual void s093();
 virtual void s094();
 virtual void s095();
 virtual void s096();
 virtual void s097();
 virtual void s098();
 virtual void s099();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void s104();
 virtual void s105();
 virtual void s106();
 virtual void s107();
 virtual void s108();
 virtual void s109();
 virtual void s110();
 virtual void slot111(const Coord3D *goal, const Rva001E34B2Point *pos, int waypointID, int layer);
// +0x1BC
 virtual bool slot112(Real angle);
// +0x1C0
 virtual void s113();
 virtual void s114();
 virtual bool haveMembersReachedEndOfPath();
// +0x1CC (WB assert text)
 virtual void s116();
 virtual void slot117(const Coord3D *pos, int waypointID);
// +0x1D4
 virtual void s118();
 virtual void s119();
 virtual void s120();
 virtual void s121();
 virtual void s122();
 virtual void s123();
 virtual void s124();
 virtual void s125();
 virtual void s126();
 virtual void s127();
 virtual void s128();
 virtual void s129();
 virtual void s130();
 virtual void s131();
 virtual void s132();
 virtual void s133();
 virtual void s134();
 virtual void s135();
 virtual void s136();
 virtual void s137();
 virtual void s138();
 virtual void s139();
 virtual void s140();
 virtual void s141();
 virtual void s142();
 virtual void s143();
 virtual Real slot144(Real speed);
// +0x240
 virtual void s145();
 virtual void s146();
 virtual void s147();
 virtual void s148();
 virtual void s149();
 virtual void s150();
 virtual void s151();
 virtual void s152();
 virtual void s153();
 virtual void slot154();
// +0x268
 
}
;
class ContainModuleInterface

{
 public:
 virtual void s00();
 virtual void s01();
 virtual void s02();
 virtual void s03();
 virtual void s04();
 virtual void s05();
 virtual void s06();
 virtual void s07();
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual HordeContainInterface *getHordeContainInterface();
// +0x7C
 
}
;
class Matrix3D;
class ThingTemplate

{
 public:
 bool isKindOf9() const 
 {
  return (m_kindOf[1] & 2) != 0;
  
 }
 private:
 char m_pad000[0x108];
 unsigned char m_kindOf[4];
// +0x108
 
}
;
enum KindOfType

{
 KINDOF_INVALID = -1
 
}
;
class Thing

{
 public:
 void setPosition(const Coord3D *pos);
 const Coord3D *getPosition() const 
 {
  return &m_pos;
  
 }
 Real getOrientation() const 
 {
  return m_orientation;
  
 }
 const ThingTemplate *getTemplate() const 
 {
  return m_template;
  
 }
 float getHeightAboveTerrainOrWater()const; void setOrientation(float); const Coord3D *getUnitDirectionVector2D()const; void setPositionZ(float);
 public:
 void *m_vtbl;
 const ThingTemplate *m_template;
// +0x04
 Matrix3D m_matrix08;
 Coord3D m_pos;
// +0x38
 Real m_orientation;
// +0x44
 
}
;
class Rva0030A3E4

{
 public:
 void _setTransformMatrix(const Matrix3D *mtx);
// 0x0030A3E4
 
}
;
struct Obj254V { virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07(); virtual int s08(); };
class Rva00368C7A { public: unsigned char rva00368271(); };
struct Obj258Holder
{
#define V(n) virtual void q##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
 V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
 V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97)
 virtual Rva00368C7A *query001E546B();
 V(99) V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109) V(110) V(111) V(112) V(113) V(114) V(115) V(116) V(117) V(118) V(119)
 V(120) V(121) V(122) V(123) V(124) V(125) V(126) V(127) V(128) V(129) V(130) V(131) V(132) V(133) V(134) V(135) V(136) V(137)
#undef V
 virtual bool queryTurnSlow();
 char m_pad[0x1F8-4];
 float m_1F8;
};
struct Rva001E546BFlags {
    unsigned m_bits[19];
    __forceinline unsigned test(unsigned i)const {return m_bits[i>>5] & (1u<<(i&31));}
    __forceinline void set(unsigned i){m_bits[i>>5]|=1u<<(i&31);}
    __forceinline void reset(unsigned i){m_bits[i>>5]&=~(1u<<(i&31));}
};
class Object : public Thing
{
 public:
 void rva0028B4CE(PathfindLayerEnum layer);
 bool isKindOf(KindOfType t) const;
 ContainModuleInterface *getContain() const { return m_contain; }
 void rva0028AE6D();
 void rva0028CFB2(const int*,const int*);
 bool rva0006F039(int)const;
 char m_pad48[0x74-0x48];
 int m_id74;
 char m_pad78[0xB8-0x78]; float m_B8;
 float m_BC;
 char m_padC0[0x10C-0xC0];
 Rva001E546BFlags m_flags10C;
 char m_pad158[0x198-0x158];
 Coord3D m_198;
 char m_pad1A4[2]; bool m_1A6;
 char m_pad1A7[0x250-0x1A7];
 ContainModuleInterface *m_contain;
 Obj254V *m_254;
 Obj258Holder *m_258;
};
class Waypoint

{
 public:
 ObjectID getClimbObjectID() const 
 {
  return m_climbObjectID;
  
 }
 int getID() const 
 {
  return m_id;
  
 }
 const Coord3D *getLocation() const 
 {
  return &m_location;
  
 }
 int getType() const 
 {
  return m_type;
  
 }
 private:
 void *m_vtbl;
 int m_id;
// +0x04
 char m_pad08[4];
 Coord3D m_location;
// +0x0C
 char m_pad18[0x60 - 0x18];
 int m_type;
// +0x60
 char m_pad64[0xB0 - 0x64];
 ObjectID m_climbObjectID;
// +0xB0
 
}
;
class TerrainLogic

{
 public:
#define V(n) virtual void r##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34)
#undef V
 virtual Waypoint *getWaypointByID(int id);
// +0x8C
 
}
;
extern TerrainLogic *TheTerrainLogic;
class AIGroup

{
 public:
 void add(Object *obj);
 void rva00372BB9(const void *target, int mode);
 
}
;
class AI

{
 public:
 AIGroup *createGroup();
 void destroyGroup(AIGroup *group);
 
}
;
extern AI *TheAI;
class MineshaftPortalBehaviour

{
 public:
 void addArrivingObject(void *obj);
 
}
;
void *Rva00372D3AFind(void *obj);
Real normalizeAngle(Real angle);
Real Cos(Real angle);
extern "C" float atan2f(float y, float x);
float atan2(float y, float x);
struct Rva001E46E1Data
{
	char m_pad00[0x18];
	float m_18;
	char m_pad1C[0x24-0x1C];
	float m_24;
	float m_28; char m_pad2C[0x3C-0x2C]; float m_3C;
	char m_pad40[4];
	unsigned int m_44;
	float m_48;
	float m_4C;
	unsigned int m_50;
	char m_pad54[0x74-0x54]; int m_74;
	char m_pad78[4]; float m_7C, m_80; char m_pad84[0xBC-0x84]; float m_BC;
	char m_padC0[0xEC-0xC0];
	unsigned char m_ec;
	char m_padED[0x104 - 0xED];
	float m_104;
	unsigned char m_108;
	unsigned char m_109;
	unsigned char m_10A;
	char m_pad10B[0x14C-0x10B];
	float m_14C;
};
class Rva001E46E1
{
public:
	void rva001E56DC(Object*,const Coord3D*,float,float*);
	void rva001E6007(Object*,const Coord3D*,float,float);
	bool getFlag(int bit)const{return (m_flags44>>bit)&1;}
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
	bool rva001E543F(Object *obj);
	void *m_00;
	const Rva001E46E1Data *m_data;
	char m_pad08[0x24 - 8];
	float m_24;
	float m_28;
	float m_2c;
	float m_30;
	float m_34;
	char m_pad38[0x40 - 0x38];
	float m_40;
	unsigned m_flags44;
	float m_48;
	char m_pad4C[0x5C - 0x4C];
	float m_5C;
	unsigned int m_60;
	char m_pad64[4];
	Matrix3D m_matrix68;
	unsigned char m_98,m_99; char m_pad9A[6];
	float m_A0,m_A4;
	int m_A8;
};
class Rva001E6007

{
 public:
 void rva001e6007(Object *obj, const Coord3D *goal, Real onPathDistToGoal, Real desiredSpeed);
 
}
;
class Rva001E685F

{
 public:
 void rva001E685F(Object *obj, const Coord3D *pos, float *angle);
 char prefix[0x68];
 struct MatrixRow{unsigned int a,b,c,d;__forceinline void set(const MatrixRow&r){a=r.a;b=r.b;c=r.c;d=r.d;}} matrix[3];
 
}
;
class Rva001E702E

{
 public:
 void rva001E702E(Thing *obj, int goal, int flag);
 
}
;
struct Rva001E756DCoord

{
 static void scale(Coord3D *c, Real s) 
 {
  c->x *= s;
  c->y *= s;
  c->z *= s;
  
 }
 static void sub(Coord3D *c, const Coord3D *p) 
 {
  c->x -= p->x;
  c->y -= p->y;
  c->z -= p->z;
  
 }
 
}
;
struct Rva001E756DTemplate

{
 char m_pad000[0x84];
 Real m_84;
// +0x84
 char m_pad088[0xD8 - 0x88];
 int m_D8;
// +0xD8
 char m_pad0DC[0x150 - 0xDC];
 bool m_150;
// +0x150
 bool m_151;
// +0x151
 
}
;
// The transform at Locomotor +0x68; only the translation column is touched.
struct Rva001E7389Transform

{
 float Row[3][4];
 void setTranslation(const Coord3D *p) 
 {
  Row[0][3] = p->x;
  Row[1][3] = p->y;
  Row[2][3] = p->z;
  
 }
 
}
;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
class Locomotor

{
 public:
 enum LocoFlag
 
 {
  LOCO_FLAG_7 = 7
  
 }
 ;
 Real getMaxSpeed(Object *) const;
 bool moveTowardsPositionHordeOnClimbPortal(Object *obj, Waypoint *way);
 void moveTowardsPositionHorde(Object *obj, const Coord3D &goalPos, Real onPathDistToGoal, Real desiredSpeed);
 Real getMaxTurnRate(Object *obj) const;
 void rva001E41FA(Real angle);
 private:
 void setFlag(LocoFlag f, bool set);
 bool getFlag7() const 
 {
  return (m_flags >> 7) & 1;
  
 }
 void *m_vtbl;
 const Rva001E756DTemplate *m_template;
// +0x04
 char m_pad08[0x40 - 8];
 Real m_40;
// +0x40
 unsigned int m_flags;
// +0x44
 char m_pad48[0x64 - 0x48];
 unsigned int m_hordeClimbFrame;
// +0x64
 Rva001E7389Transform m_transform;
// +0x68
 unsigned char m_98;
// +0x98
 unsigned char m_99;
 unsigned char m_9A;
// +0x9A
 
}
;
class Rva001E43CF {public: void rva001E43CF(void*);};
class Rva001E4912 { public:
    Rva001E4912 *rva001E4912(int,unsigned,unsigned);
    unsigned m_bits[19];
};
// Native 0x001E56DC..0x001E5F1D (RET16): the locomotor receiver and Object
// layouts are shared with the verified neighbouring movement/vertical bodies.
// BFME1 Locomotor::rotateObjAroundLocoPivot (9cbfb551) and the ZH locomotor
// turn logic supply the pivot semantics; the original method name is uncertain.
// Target data offsets 3C/74/BC/10A, Object transform08 and radiusB8, AI slot228,
// mover transform68/flags98-99/turn directionA8 and flags133/134/137/138 are
// read from this retail body. WWMath is the unchanged shared donor at2f243e26d.
// The local union records two successive stages: optional angle output, then
// returned speed. Reading that speed through a volatile float view keeps the
// native FSTP float rounding before SSE halving. The flag starts after the call
// and before halving; the special pivot's constant offset is a const reference.
static __forceinline void preRotateZ(Matrix3D&m,float s,float c){m.In_Place_Pre_Rotate_Z(s,c);}
void Rva001E46E1::rva001E56DC(Object *obj,const Coord3D *goal,float maxTurnRate,float *relAngle)
{
    union PivotValue {float *output;float speed;};PivotValue value;value.output=relAngle;
    float angle=obj->m_orientation;
    float offset=m_data->m_BC;
    float turnRate=m_data->m_3C;
    if(m_99) turnRate*=0.0625f;
    Obj258Holder *ai=obj->m_258;
    bool slow=ai && ai->queryTurnSlow();
    m_A8=0;
    if(m_data->m_74==5) {
        const float &turnPointOffset=offset*obj->m_B8;
        Coord3D turnPos;
        turnPos.x=obj->m_pos.x; turnPos.y=obj->m_pos.y;
        const Coord3D *dir=obj->getUnitDirectionVector2D();
        turnPos.x+=dir->x*turnPointOffset;
        turnPos.y+=dir->y*turnPointOffset;
        float dx=goal->x-turnPos.x,dy=goal->y-turnPos.y;
        if(fabs(dx)<0.1f && fabs(dy)<0.1f)return;
        float amount=normalizeAngle(atan2(dy,dx)-angle);
        if(value.output)*value.output=amount;
        if(amount>0.0f) {
            if(amount>m_data->m_3C)m_A8=1;
            if(amount>maxTurnRate)amount=maxTurnRate;
        } else {
            if(amount< -m_data->m_3C)m_A8=-1;
            if(amount< -maxTurnRate)amount=-maxTurnRate;
        }
        Matrix3D mtx,tmp(true);
        tmp.Translate(turnPos.x,turnPos.y,0.0f);
        tmp.In_Place_Pre_Rotate_Z(amount);
        tmp.Translate(-turnPos.x,-turnPos.y,0.0f);
        mtx.mul(tmp,obj->m_matrix08);
        ((Rva001E43CF*)this)->rva001E43CF(&mtx);
    } else {
        float turnPointOffset=offset*obj->m_B8;
        Coord3D turnPos;
        turnPos.x=obj->m_pos.x;turnPos.y=obj->m_pos.y;
        const Coord3D *dir=obj->getUnitDirectionVector2D();
        turnPos.x+=dir->x*turnPointOffset;turnPos.y+=dir->y*turnPointOffset;
        float dx=goal->x-turnPos.x,dy=goal->y-turnPos.y;
        if(fabs(dx)<0.1f && fabs(dy)<0.1f)return;
        float amount=normalizeAngle(atan2(dy,dx)-angle);
        if(value.output)*value.output=amount;
        if(amount>0.0f){if(amount>turnRate)m_A8=1;if(amount>maxTurnRate)amount=maxTurnRate;}
        else {if(amount< -turnRate)m_A8=-1;if(amount< -maxTurnRate)amount=-maxTurnRate;}
        if(slow)amount*=0.5f;
        float c=cosf(amount),s=sinf(amount);preRotateZ(m_matrix68,s,c);
    }
    float speed=m_40;
    value.speed=((const Locomotor *)this)->getMaxSpeed(obj);bool animate=true;float half=reinterpret_cast<const volatile float&>(value.speed)*0.5f;
    if(speed>half && !m_data->m_10A)animate=false;
    if(slow)animate=false;
    if(!m_99) {
        if(obj->m_flags10C.test(133)){obj->m_flags10C.reset(133);obj->rva0028AE6D();}
        if(obj->m_flags10C.test(134)){obj->m_flags10C.reset(134);obj->rva0028AE6D();}
        if(obj->m_flags10C.test(137)){obj->m_flags10C.reset(137);obj->rva0028AE6D();}
        if(obj->m_flags10C.test(138)){obj->m_flags10C.reset(138);obj->rva0028AE6D();}
    }
    if(animate) {
        if(m_A8==-1) {
            if(speed>half) {
                Rva001E4912 clear,set;
                obj->rva0028CFB2((int*)clear.rva001E4912(0,137,133),(int*)set.rva001E4912(0,138,134));
            } else if(obj->m_flags10C.test(133)||!obj->m_flags10C.test(134)){
                obj->m_flags10C.reset(133);obj->m_flags10C.set(134);obj->rva0028AE6D();
            }
        } else if(m_A8==1) {
            if(speed>half) {
                Rva001E4912 clear,set;
                obj->rva0028CFB2((int*)clear.rva001E4912(0,138,134),(int*)set.rva001E4912(0,137,133));
            } else if(obj->m_flags10C.test(134)||!obj->m_flags10C.test(133)){
                obj->m_flags10C.reset(134);obj->m_flags10C.set(133);obj->rva0028AE6D();
            }
        }
    }
}


class Rva001E434A {public:void *rva001E434A();};
static __forceinline void rva6007Clear(Object *obj,unsigned bit)
{
 if(obj->m_flags10C.test(bit)){obj->m_flags10C.reset(bit);obj->rva0028AE6D();}
}
static __forceinline void rva6007Set(Object *obj,unsigned bit)
{
 if(!obj->m_flags10C.test(bit)){obj->m_flags10C.set(bit);obj->rva0028AE6D();}
}
static __forceinline float rva6007SlowDown(float speed,float minSpeed,float braking)
{
 float delta=speed-minSpeed;
 if(delta<=0.0f)return 0.0f;
 float frames=delta/braking;
 frames+=1.0f;
 float dist=(delta*0.5f+minSpeed)*frames;
 const float fudge=1.05f;
 return dist*fudge;
}
static __forceinline void rva6007SetNextPosition(Object *obj,const Coord3D *pos){obj->m_1A6=true;obj->m_198=*pos;}
void Rva001E46E1::rva001E6007(Object *obj,const Coord3D *goal,float distance,float desiredSpeed)
{
 float maxSpeed=((const Locomotor*)this)->getMaxSpeed(obj);
 if(desiredSpeed>maxSpeed)desiredSpeed=maxSpeed;
 float goalSpeed=desiredSpeed;
 float actualSpeed=m_40;
 float braking=rva001E488A(obj);
 float minSpeed=m_data->m_28;
 float slowDownDist=rva6007SlowDown(actualSpeed,minSpeed,braking);
 if(distance>slowDownDist*3.0f)m_flags44&=~1u;
 float next=m_40-braking;
 if(next>desiredSpeed){goalSpeed=next;if(goalSpeed<braking)goalSpeed=braking;}
 if(slowDownDist>distance && !getFlag(4)){
  m_flags44|=1;
  goalSpeed=m_40-rva001E488A(obj);
  if(goalSpeed<braking)goalSpeed=braking;
 }
 Rva003642DFResult result;
 const Coord3D *objPos=obj->getPosition();
 Coord3D goalCopy(*goal);
 if(goalSpeed>m_40 && !getFlag(0))m_40+=rva001E4845(obj);
 if(m_40>goalSpeed){m_40-=braking;if(m_40<goalSpeed)m_40=goalSpeed;}
 Coord3D pos(*goal);
 float speed=m_40;
 Path *path=(Path*)Rva001E3FFDGet((Rva001E3FFDOuter*)obj);
 if(path){
  ++path->m_count;
  result=path->rva00364521((const Rva0008BB38FloatField*)this);
  pos=result.m_pos;
  path->DoAdvanceAlongPath(&pos,true);
  result=path->rva00364521((const Rva0008BB38FloatField*)this);
  if(path->m_count)--path->m_count;
  Coord3D nextPos(result.m_pos);
  rva6007SetNextPosition(obj,&nextPos);
 } else {
  Coord3D delta(goalCopy);
  delta.sub(objPos);
  pos=*objPos;
  delta.z=0.0f;
  float len=delta.length();
  if(speed<10.0f/BfmeLogicFramesPerSecond)speed=10.0f/BfmeLogicFramesPerSecond;
  if(speed>len)speed=len;
  if(len>0.001f){delta.normalize();delta.scale(speed);pos.x=delta.x+pos.x;pos.y=delta.y+pos.y;pos.z=delta.z+pos.z;}
 }
 pos.z=objPos->z;
 Coord3D dest(*(const Coord3D*)((Rva001E434A*)obj)->rva001E434A());
 dest.z=objPos->z;
 rva6007SetNextPosition(obj,&dest);
 m_matrix68.Set_Translation(Vector3(pos.x,pos.y,pos.z));
 float acceleration=m_40-actualSpeed;
 float threshold=m_data->m_7C*maxSpeed;
 if(acceleration>rva001E4845(obj)*0.4f && actualSpeed<threshold){
  rva6007Clear(obj,136);
  if(m_data->m_80>distance)rva6007Clear(obj,135);
  else {rva6007Clear(obj,131);rva6007Set(obj,135);}
 } else if(getFlag(0) && threshold>m_40){
  rva6007Clear(obj,135);
  if(m_98){rva6007Clear(obj,131);rva6007Set(obj,136);}
  else {rva6007Clear(obj,136);rva6007Set(obj,131);}
 } else {
  rva6007Clear(obj,135);rva6007Clear(obj,136);
  if(actualSpeed>threshold){
   if(distance>m_data->m_80 && obj->rva0006F039(131))rva6007Clear(obj,131);
   if(!obj->rva0006F039(131))m_98=true;
  }
 }
}

// Retail next-position flag order and named speed callee are reproduced by this bank.
// Remaining coordinate-copy evidence: reverse/attempt_support/001e6007-20261019-w5.md.

void Rva001E685F::rva001E685F(Object *obj,const Coord3D *a,float *b){
const MatrixRow *src=(const MatrixRow *)&obj->m_matrix08;
matrix[0].set(src[0]);
matrix[1].set(src[1]);
matrix[2].set(src[2]);
float turn=((const Locomotor*)this)->getMaxTurnRate(obj);((Rva001E46E1*)this)->rva001E56DC(obj,a,turn,b);}
bool Locomotor::moveTowardsPositionHordeOnClimbPortal(Object *obj, Waypoint *way)

{
 if (!way->getClimbObjectID())
 return false;
 Object *climbObj = TheGameLogic->findObjectByID(way->getClimbObjectID());
 if (!climbObj)
 return false;
 ContainModuleInterface *contain = obj->getContain();
 if (!contain || !contain->getHordeContainInterface())
 return false;
 HordeContainInterface *hordeContain = contain->getHordeContainInterface();
 Path *aPath = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
 if (!aPath)
 return false;
 Coord3D climbPos;
 aPath->PeekPastClimbPortal(&climbPos);
 Rva003642DFResult result = aPath->rva00364521((const Rva0008BB38FloatField *)this);
 Coord3D goalPos;
 goalPos.x = result.m_pos.x;
 goalPos.y = result.m_pos.y;
 goalPos.z = result.m_pos.z;
 const Coord3D *pos = obj->getPosition();
 Coord3D delta;
 delta.x = pos->x - climbPos.x;
 delta.y = pos->y - climbPos.y;
 delta.z = pos->z - climbPos.z;
 if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > 10.0f * 10.0f)
 
 {
  obj->setPosition(&climbPos);
  m_transform.setTranslation(&climbPos);
  obj->rva0028B4CE((PathfindLayerEnum)((Rva001E34FA *)&result)->rva001E34FA());
  hordeContain->slot111(&goalPos, &((Rva001E34B2 *)&result)->rva001E34B2(),
  ((Rva001E3511 *)&result)->rva001E3511(), ((Rva001E34FA *)&result)->rva001E34FA());
  m_hordeClimbFrame = TheGameLogic->getFrame() + BfmeLogicFramesPerSecond * 12;
  return true;
  
 }
 if (!hordeContain->haveMembersReachedEndOfPath() && TheGameLogic->getFrame() <= m_hordeClimbFrame)
 return true;
 aPath = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
 if (!aPath)
 return false;
 _STL::vector<ScienceType> portals;
 aPath->AdvancePastPortal((ScienceType)((Rva001E3511 *)&result)->rva001E3511(), &portals);
 return false;
 
}
void Locomotor::moveTowardsPositionHorde(Object *obj, const Coord3D &goalPos, Real onPathDistToGoal, Real desiredSpeed)

{
 ContainModuleInterface *contain = obj->getContain();
 HordeContainInterface *hordeContain = contain ? contain->getHordeContainInterface() : 0;
 Real dist = onPathDistToGoal;
 bool onPortal = false;
 Path *aPath = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
 if (aPath)
 
 {
  Rva003642DFResult result = aPath->rva00364521((const Rva0008BB38FloatField *)this);
  dist = (Real)((Rva00363D20 *)&result)->rva00363D20();
  if (m_9A)
  
  {
   if (hordeContain && !hordeContain->haveMembersReachedEndOfPath())
   
   {
    ((Rva001E702E *)this)->rva001E702E(obj, (int)&goalPos, 0);
    return;
    
   }
   m_9A = 0;
   
  }
  if (((Rva001E3511 *)&result)->rva001E3511() != 0x7fffffff)
  
  {
   Waypoint *way = TheTerrainLogic->getWaypointByID(((Rva001E3511 *)&result)->rva001E3511());
   if (way)
   
   {
    onPortal = true;
    int type = way->getType();
    if (type == 3)
    
    {
     if (moveTowardsPositionHordeOnClimbPortal(obj, way))
     return;
     
    }
    else if (type == 4)
    
    {
     
    }
    else if (type == 2)
    
    {
     if (hordeContain)
     
     {
      if (!hordeContain->haveMembersReachedEndOfPath())
      return;
      Path *path = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
      if (!path)
      return;
      _STL::vector<ScienceType> portals;
      path->AdvancePastPortal((ScienceType)way->getID(), &portals);
      int lastID = 0x7fffffff;
      for (ScienceType *it = portals.begin(); it != portals.end(); ++it)
      
      {
       Waypoint *portal = TheTerrainLogic->getWaypointByID(*it);
       if (portal)
       
       {
        hordeContain->slot117(portal->getLocation(), portal->getID());
        lastID = portal->getID();
        
       }
       
      }
      path = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
      if (!path)
      return;
      result = path->rva00364521((const Rva0008BB38FloatField *)this);
      ((Rva001E685F *)this)->rva001E685F(obj, &result.m_pos, 0);
      Coord3D goal;
      goal.x = result.m_pos.x;
      goal.y = result.m_pos.y;
      goal.z = result.m_pos.z;
      path = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
      if (!path)
      return;
      result = path->rva003642DF(getMaxSpeed(obj) * 3.0f);
      m_transform.setTranslation(&result.m_pos);
      path->DoAdvanceAlongPath(&result.m_pos, true);
      m_9A = 1;
      hordeContain->slot117(&goal, lastID);
      return;
      
     }
     
    }
    else if (type == 7)
    
    {
     if (hordeContain)
     
     {
      hordeContain->slot154();
      return;
      
     }
     
    }
    else if (type == 8)
    
    {
     if (hordeContain)
     
     {
      Path *path = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
      if (path)
      
      {
       _STL::vector<ScienceType> portals;
       path->AdvancePastPortal((ScienceType)way->getID(), &portals);
       path = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
       if (!path)
       return;
       if (!portals.empty())
       
       {
        Waypoint *destWay = TheTerrainLogic->getWaypointByID(path->GetNextPortalID());
        if (destWay)
        
        {
         Object *destination = TheGameLogic->findObjectByID(destWay->getClimbObjectID());
         MineshaftPortalBehaviour *mpb = (MineshaftPortalBehaviour *)Rva00372D3AFind(destination);
         mpb->addArrivingObject(obj);
         hordeContain->slot154();
         int id = !result.m_node ? 0x7fffffff : ((int *)result.m_node)[8];
         Waypoint *w = TheTerrainLogic->getWaypointByID(id);
         if (w && w->getType() == 8)
         way = w;
         Object *garrison = TheGameLogic->findObjectByID(way->getClimbObjectID());
         AIGroup *group = TheAI->createGroup();
         group->add(obj);
         group->rva00372BB9(garrison, 2);
         TheAI->destroyGroup(group);
         
        }
        else
        hordeContain->slot154();
        return;
        
       }
       
      }
      
     }
     
    }
    
   }
   
  }
  
 }
 
  Real maxSpeed = getMaxSpeed(obj);
  Real maxTurnRate = getMaxTurnRate(obj);
  if (desiredSpeed > maxSpeed)
  desiredSpeed = maxSpeed;
  if (m_template->m_150 && hordeContain)
  desiredSpeed = hordeContain->slot144(desiredSpeed);
  Real angle = obj->getOrientation();
  Real desiredAngle = atan2(goalPos.y - obj->getPosition()->y, goalPos.x - obj->getPosition()->x);
  Real relAngle = normalizeAngle(desiredAngle - angle);
  Coord3D goal;
  goal.x = goalPos.x;
  goal.y = goalPos.y;
  goal.z = goalPos.z;
  bool reverse = false;
  if (m_template->m_D8 && obj->isKindOf((KindOfType)0x41))
  reverse = true;
  if (m_40 == 0.0f)
  
  {
   setFlag(LOCO_FLAG_7, reverse);
   m_98 = 0;
   
  }
  if (getFlag7())
  
  {
   if (!reverse)
   m_flags &= ~0x80;
   else
   
   {
    desiredAngle = normalizeAngle(desiredAngle - 3.14159265359f);
    relAngle = normalizeAngle(desiredAngle - angle);
    goal = *obj->getPosition();
    Rva001E756DCoord::scale(&goal, 2.0f);
    Rva001E756DCoord::sub(&goal, &goalPos);
    
   }
   
  }
  Real limit = m_template->m_84;
  if (Cos(relAngle) < Cos(limit) && !onPortal && dist > 20.0f && hordeContain)
  
  {
   hordeContain->slot15();
   rva001E41FA(desiredAngle);
   ((Rva0030A3E4 *)obj)->_setTransformMatrix((const Matrix3D *)&m_transform);
   hordeContain->slot16();
   
  }
  if (onPortal)
  goal.z = obj->getPosition()->z;
  if (m_template->m_151)
  ((Rva001E46E1 *)this)->rva001E56DC(obj, &goal, maxTurnRate, &relAngle);
  if (!((Rva001E46E1 *)this)->rva001E543F(obj) && obj->getTemplate()->isKindOf9() && hordeContain && !hordeContain->slot112(desiredAngle))
  desiredSpeed *= 0.1f;
  ((Rva001E46E1 *)this)->rva001E6007(obj, &goal, onPathDistToGoal, desiredSpeed);
}

// Aligned nonvolatile-portal comparison: reverse/attempt_support/horde-1e756d-w1-20261019.md.
