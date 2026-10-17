// ?notifyOfMemberDeath@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.9734 date=2026-10-17
// ?notifyOfMemberDeath@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.8211008385075881 date=2026-10-16
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /Ireference/shims/bfmelist /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// Rebase merge 2026-10-17 (opus): a parallel bank (refreshDeathDrawable(Object*) helper taking the owner,
// `UpdateModule *update` local, HordeDeathBody* body local, deathData local) compiles to the IDENTICAL 567 B
// as this body: same lone residual (slot-96 call via lea ecx,[ebx+0x11c] instead of esi). Neither spelling helps.
// stlport
#include "ascii_string.h"
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}
#include <map>
#include <set>
#include <vector>
#include <math.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../Common/PartitionRangeQueryCallView.h"
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
struct Rva00470041Less : public _STL::less<unsigned short> {};
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
class Rva0055A627Difference
{
public:
	float x, y, z;
	float length() const;
};
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum WeaponSetType
{
	WEAPONSET_18 = 0x18,
	WEAPONSET_19 = 0x19,
	WEAPONSET_1A = 0x1A
};
enum ObjectID
{
	INVALID_ID = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
extern int BfmeLogicFramesPerSecond;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class Object;
class UpgradeTemplate;
class Rva004708BCBehavior;
class AttributeModifierPoolUpdate
{
public:
	bool addModifierToPool(const AsciiString &name, int a2);
	void rva00403744(const AsciiString &name);
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
struct Rva0046DB6DCategory
{
	unsigned char m_pad00[0x0C];
	int m_index;
};
class AttributeModifierStore
{
public:
	int rva00214713(int key);
	void *GetCategoryContainer(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int a1, CommandSourceType cmdSource);
	void rva0026C2D9(Object *obj, int a2, CommandSourceType cmdSource);
	void rva0026C347(Object *obj, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
struct Rva002A8AB1Record
{
	void rva002C6AA8(int value, Object *obj);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;
class LocomotorSet;
class Pathfinder
{
public:
	bool IsPointOnWall(int pos, bool flag);
	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
	bool IsPointOnRamp(const Coord3D *pos);
	void RemoveObjectFromPathfindMap(Object *object);
	void RemoveObjectGoalFromPathfindMap(Object *object);
	bool IsValidMovementPositionForObject(const Coord3D *pos, int layer, int surfaces, const Object *obj);
};
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};
class AIGroup
{
public:
	void add(Object *obj);
	void rva00372571(Rva00372571Params *params, int source);
};
class AttackPriorityInfo;
class PartitionFilter;
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers, const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int a6);
	static bool rva002FE193(Object *obj, Object *victim);
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
	Pathfinder *pathfinder() { return m_pathfinder; }
};
extern AI *TheAI;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class Team;
struct Vector4
{
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}
	float X;
	float Y;
	float Z;
	float W;
};
class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}
	Vector4 Row[3];
};
class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};
class Drawable : public Rva00276470Drawable
{
public:
	void rva00272BE7();
	void rva00272BAB(int a1, int a2);
	void rva00274176(bool a1);
	void rva00272945(int a);
	void rva0027541E(const RGBColor *color, unsigned int a2, unsigned int a3, unsigned int a4);
};
class Thing
{
public:
 void setPositionZ(float);
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
	const Coord3D *getUnitDirectionVector2D() const;
	Drawable *getDrawable() const;
};
class GlobalData
{
public:
	unsigned char m_pad000[0x9A6];
	bool m_9A6;
	unsigned char m_pad9A7[0x1230 - 0x9A7];
	int m_1230;
	int m_1234;
};
extern GlobalData *TheWritableGlobalData;
class Player;
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local;
};
extern PlayerList *ThePlayerList;
class BfmeThingTFB
{
public:
	void bfmeTwoTFB(int a1, int a2);
};
struct Rva003642DFNode;
struct Rva003642DFResult;
struct Rva00468C37Holder;
class Rva003638BA
{
public:
	bool rva003638BA();
	bool rva00363AD7();
	Rva003642DFResult rva00364521(Rva00468C37Holder *holder);
};
struct Rva003642DFResult
{
	Rva003642DFNode *m_node;
	Coord3D m_pos;
};
struct Rva003642DFNode
{
	unsigned char m_pad00[0x08];
	int m_08;
};
class Rva001E3511
{
public:
	int rva001E3511();
};
struct Rva00468C37Template
{
	unsigned char m_pad000[0x150];
	unsigned char m_150;
};
struct Rva00468C37Holder
{
	unsigned char m_pad0[0x4];
	const Rva00468C37Template *m_4;
};
template <int N> class Rva00468D11Slots : public Rva00468D11Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00468D11Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
class TerrainLogic : public Rva00468D11Slots<35>
{
public:
	virtual int slot35(int level) = 0;
};
extern TerrainLogic *TheTerrainLogic;
class AIUpdateInterfaceSlots : public Rva00468D11Slots<110>
{
public:
	virtual bool rva0047306ESlot110() = 0;
	virtual bool rva0046A46FSlot111() = 0;
	virtual void gap112() = 0;
	virtual bool rva0047306ESlot113() = 0;
	virtual bool rva00468D11Slot114() = 0;
	virtual bool rva00468D2CSlot115() = 0;
	virtual void gap116() = 0; virtual void gap117() = 0; virtual void gap118() = 0; virtual void gap119() = 0;
	virtual void gap120() = 0; virtual void gap121() = 0; virtual void gap122() = 0; virtual void gap123() = 0;
	virtual void gap124() = 0; virtual void gap125() = 0; virtual void gap126() = 0; virtual void gap127() = 0;
	virtual void gap128() = 0; virtual void gap129() = 0; virtual void gap130() = 0; virtual void gap131() = 0;
	virtual void gap132() = 0; virtual void gap133() = 0;
	virtual void rva0046DDC5Slot134(int a1, int a2) = 0;
	virtual void gap135() = 0; virtual void gap136() = 0; virtual void gap137() = 0; virtual void gap138() = 0;
	virtual void gap139() = 0; virtual void gap140() = 0; virtual void gap141() = 0;
	virtual void slot142(int value) = 0;
};
class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
	bool isMoving() const;
	void rva00262D2D();
	Object *getCurrentVictim() const;
	int rva00260DED() const;
	unsigned char m_pad004[0x20 - 0x04];
	AICommandInterface m_command;
	void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }
	unsigned char m_pad024[0x140 - 0x24];
	Rva003638BA *m_140;
	unsigned char m_pad144[0x1CC - 0x144];
	unsigned char m_1CC[0x1F0 - 0x1CC];
	Rva00468C37Holder *m_1F0;
	__declspec(dllimport) __forceinline const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_1CC; }
	void rva0026594F(const Coord3D *a1, const Coord3D *a2, int a3, int layer, const Coord3D *a5, const Coord3D *a6);
	void moveThroughPortalWithMicropath(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer, const Coord3D *a5, const Coord3D *a6);
	unsigned char m_pad1F4[0x1FC - 0x1F4];
	int m_1FC;
};
class ModuleData;
class ModuleInfo
{
public:
	struct Entry
	{
		unsigned char m_pad[0x14];
	};
	int getCount() const { return m_end - m_begin; }
	const ModuleData *getNthData(int i) const;
	Entry *m_begin;
	Entry *m_end;
	Entry *m_cap;
};
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
	int rva000456AC(int bit) const;
	__forceinline unsigned int hordeKindMask(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x64];
	AsciiString m_64;
	unsigned char m_pad068[0x109 - 0x68];
	unsigned char m_109;
	unsigned char m_pad10A[0x114 - 0x10A];
	unsigned int m_kindOf[4];
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo;
	unsigned char m_pad2F0[0x528 - 0x2F0];
	float m_528;
	unsigned char m_pad52C[0x5D8 - 0x52C];
	short m_5D8;
};
class Rva0028C197Slot149 : public Rva00468D11Slots<149>
{
public:
	virtual bool slot149() = 0;
};
float Sin(float x);
float Cos(float x);
class Rva003BD306Target
{
public:
	void rva0039B3D1(float value, bool flag);
};
class ExperienceTracker : public Rva003BD306Target
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2);
	unsigned char m_pad00[0x10];
	float m_10;
	unsigned char m_pad14[0x24 - 0x14];
	int m_24;
};
class Rva0046B850Module : public Rva00468D11Slots<5>
{
public:
	virtual float slot5() = 0;
	virtual void m254gap6() = 0; virtual void m254gap7() = 0; virtual void m254gap8() = 0; virtual void m254gap9() = 0;
	virtual void m254gap10() = 0; virtual void m254gap11() = 0; virtual void m254gap12() = 0; virtual void m254gap13() = 0;
	virtual void m254gap14() = 0; virtual void m254gap15() = 0; virtual void m254gap16() = 0; virtual void m254gap17() = 0;
	virtual ObjectID slot18() = 0;
};
class Rva0046A2ECContain : public Rva00468D11Slots<58>
{
public:
	virtual bool slot58(Object *other) = 0;
};
class Rva0046A2ECSlot39 : public Rva00468D11Slots<39>
{
public:
	virtual void slot39(Object *obj) = 0;
};
class Object;
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *victim, float rangeBonus = 0.0f, int useAimPos = 1) const;
	float getAttackRange(const Object *source) const;
	unsigned char m_pad00[0x04];
	const Rva002C9400ByteField *m_04;
};
class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *obj, float bonus);
};
enum WeaponSlotType;
class Module;
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
	unsigned int m_words[19];
};
struct Rva00469F3AFlags
{
	unsigned int m_words[19];
	__forceinline void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 31);
	}
	__forceinline void intersect(const unsigned int *words)
	{
		for (unsigned int i = 0; i < 19; ++i)
			m_words[i] &= words[i];
	}
	__forceinline void flip()
	{
		for (unsigned int i = 0; i < 19; ++i)
			m_words[i] = ~m_words[i];
	}
};
enum KindOfType { KINDOF_HORDE_DEATH=0x1bb };
class Object
{
public:
 bool isKindOf(KindOfType) const;
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	void rva00293077(const void *upgrade);
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	int getID() const { return m_74; }
	void setProducer(Object *);
	__forceinline unsigned int testCondition(int bit) const
	{
		return m_conditionWords[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void clearCondition(int bit)
	{
		m_conditionWords[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	bool test110(int bit) const { return ((m_110 >> bit) & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	bool isEquivalentTemplate(const ThingTemplate *t) const { return m_template->isEquivalentTo(t); }
	__forceinline unsigned int hordeKindMask(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	float m_orientation;
	unsigned char m_pad048[0x74 - 0x48];
	int m_74;
	unsigned char m_pad078[0xB8 - 0x78];
	float m_B8;
	unsigned char m_padBC[0x10C - 0xBC];
	union
	{
		unsigned int m_conditionWords[2];
		struct
		{
			unsigned int m_10C;
			unsigned int m_110;
		};
	};
	unsigned char m_pad114[0x244 - 0x114];
	Rva004708BCBehavior **m_244;
	unsigned char m_pad248[0x250 - 0x248];
	Rva0046A2ECContain *m_250;
	Rva0046B850Module *m_254;
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_264;
	unsigned char m_pad268[0x274 - 0x268];
	Object *m_274;
	unsigned char m_pad278[0x284 - 0x278];
	int m_284;
	unsigned char m_pad288[0x304 - 0x288];
	int m_304;
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_438;
	unsigned char m_pad439[0x44C - 0x439];
	int m_44C;
	unsigned char m_pad450[0x45C - 0x450];
	int m_45C;
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	void rva0028AD32();
	Object *rva002931F5(bool flag);
	bool rva0028D9E5(int a1) const;
	void setTeam(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void clearModelConditionStateForHorde(ModelConditionFlagType flag);
	void setModelConditionStateForHorde(ModelConditionFlagType flag);
	void rva001E42F2(const int *value);
	void rva0028B95F();
	unsigned char rva00290FBB() const;
	int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	void rva0028AE6D();
	void rva0029A12B();
	void rva00298979(Object *source, bool flag);
	void bfmeTransferReplacementState(Object *replacement);
	void setWeaponSetFlag(WeaponSetType flag);
	void rva0028CFB2(const int *a, const int *b);
	void setTransformMatrix(const Matrix3D *mtx);
	float GetRelativeAngle(const Coord3D *pos) const;
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
	float getVisionRange() const;
	bool GetGoalPosition(Coord3D *pos) const;
	float GetGoalAngle() const;
	int GetGoalLayer() const;
	void rva0028ACEE(int a1, int a2);
	void rva00295F05(bool flag);
	void *rva0028C197() const;
protected:
	friend class HordeContain;
	Module *findModule(NameKeyType key) const;
public:
	bool addAttributeModifierToPool(const AsciiString &name, int a2);
	void rva0029041B(Player *player);
	bool isLocallyControlled() const;
	void removeAttributeModifierFromPool(const AsciiString &name);
private:
	friend class HordeContain;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *);
	void rva0023D0C2(Object *obj, int value);
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern class ThingFactory *TheThingFactory;
struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};
struct Rva00462D35Mapped
{
	unsigned int m_bits;
};
class Rva00469294
{
public:
	void *rva00469294(int key);
	char *findEntry(int key) { return (char *)rva00469294(key); }
};
struct Rva00472329Record
{
	int m_key;
	float m_04;
	float m_08;
	unsigned char m_pad0C[0x1C - 0x0C];
};
struct Rva004693ADFlag109
{
	unsigned char m_pad[0x109];
	unsigned char m_flags;
};
struct Rva004693ADArg
{
	char m_pad00[4];
	Rva004693ADFlag109 *m_04;
	char m_pad08[0x6C];
	int m_74;
};
class Rva004693AD
{
public:
	bool rva004693AD(Rva004693ADArg *arg);
private:
	char m_pad[0x264];
	int m_264;
	int m_pad268;
	int m_26C;
};
class Rva0046ACF6
{
public:
	int rva0046ACF6(int key);
private:
	char m_pad[0x17C];
	_STL::map<int, int> m_map;
};
class Rva002390CB
{
	void *m_00;
	void *m_04;
public:
	Rva002390CB();
	__declspec(nothrow) Rva002390CB(const Rva002390CB &other);
	~Rva002390CB();
};
struct Rva0046D158Record
{
	AsciiString m_name;
	unsigned char m_pad04[0x08 - 0x04];
	Rva002390CB m_08;
};
class Rva0046247D
{
public:
	__declspec(noinline) void *rva0046247D(Rva0046247DPair &p)
	{
		void *base = this;
		char *field = (char *)base + 0x20;
		p.m00 = base ? field : 0;
		p.m04 = (const _STL::list<Object *> *)((char *)base + 0x54);
		return &p;
	}
};
class Rva0046E740
{
public:
	void rva0046E740(int a1);
};
class Rva00291793
{
public:
	int rva00291793();
};
class Rva00468FDCHelper : public Rva00468D11Slots<3>
{
public:
	virtual void slot3(Object *target) = 0;
	virtual void rva00468FDCSlot4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0;
	virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0; virtual void gap12() = 0;
	virtual void gap13() = 0;
	virtual bool rva00468DCDSlot14(Object *obj) = 0;
};
struct Rva00468CA3Arg
{
	unsigned char m_pad00[0x38];
	void *m_38;
};
class HordeContainModuleData
{
public:
	unsigned char m_pad[0xA4];
	_STL::list<AsciiString> m_A4;
};
struct Rva004698BCVector
{
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	void **m_begin;
	void **m_end;
	void **m_cap;
};
struct Rva00469851Names
{
	const AsciiString *begin() const { return m_begin; }
	const AsciiString *end() const { return m_end; }
	const AsciiString *m_begin;
	const AsciiString *m_end;
	const AsciiString *m_cap;
};
struct HordeContainModuleDataFields
{
	unsigned char m_pad000[0x98];
	int m_98;
	unsigned char m_pad09C[0x18C - 0x9C];
	unsigned char m_18C[0x0C];
	_STL::vector<Rva0046D158Record *> m_198;
	Rva004698BCVector m_1A4;
	AsciiString m_1B0;
	unsigned char m_pad1B4[0x1B8 - 0x1B4];
	_STL::map<int, int> m_1B8;
	unsigned char m_pad1C4[0x1D8 - 0x1C4];
	bool m_1D8;
	unsigned char m_pad1D9[0x224 - 0x1D9];
	union
	{
		struct
		{
			const AsciiString *m_224Begin;
			const AsciiString *m_224End;
			const AsciiString *m_224Cap;
		};
		Rva00469851Names m_224;
	};
	bool m_230;
	unsigned char m_pad231[0x234 - 0x231];
	int m_234;
	unsigned char m_pad238[0x254 - 0x238];
	bool m_254;
	unsigned char m_pad255[0x25C - 0x255];
	float m_25C;
	unsigned char m_pad260[0x264 - 0x260];
	unsigned int m_264;
	unsigned int m_268;
	float m_26C;
	float m_270;
};
class Rva00469B73
{
public:
	void rva00469B73(void *obj);
};
class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;
};
class Rva0040334B
{
public:
	void rva0040334B(Object *obj);
};
class LifetimeUpdate
{
public:
	void setLifetimeRange(unsigned int minFrames, unsigned int maxFrames);
	unsigned char m_pad00[0x20];
	unsigned int m_20;
};
class Rva004708BCSlot5Iface : public Rva00468D11Slots<1>
{
public:
	virtual void slot1(int id) = 0;
};
class Rva004708BCModuleHead
{
public:
	virtual void moduleHeadAnchor();
	void *m_04;
	void *m_08;
};
class Rva004708BCBehaviorIface : public Rva00468D11Slots<5>
{
public:
	virtual Rva004708BCSlot5Iface *slot5() = 0;
};
class Rva004708BCBehavior : public Rva004708BCModuleHead, public Rva004708BCBehaviorIface
{
};
class Rva004708BCTail : public Rva00468D11Slots<4>
{
public:
	virtual void slot4(int a1) = 0;
};
class Rva004708BCTail121 : public Rva00468D11Slots<121>
{
public:
	virtual void slot121() = 0;
};
class Rva004708BCContain : public Rva00468D11Slots<31>
{
public:
	virtual Rva004708BCTail *slot31() = 0;
};
class Rva00466FE0Iface
{
public:
	virtual Object *rva00466FE0(const ThingTemplate *tmpl, Rva0046A2ECContain *contain, Object *obj, const char *name, int a5) = 0;
};
struct ContainIface93 : public Rva00468D11Slots<93>
{
public:
	virtual void slot93(int *a1, int a2) = 0;
};
struct HordeContainModuleDataFields;
class ModuleData : public Rva00468D11Slots<21>
{
public:
	virtual const HordeContainModuleDataFields *slot21() const = 0;
};
template <int N> class Rva0046BB38Slots : public Rva0046BB38Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046BB38Slots<0>
{
};
class Rva0046BB38Iface6 : public Rva0046BB38Slots<0>
{
public:
	virtual void rva00472329(const Coord3D *pos, int unused) = 0;
	virtual void attackTargetNow(Object *target, int select) = 0; virtual void rva00472235() = 0; virtual void rva0046E253() = 0; virtual void returnToFormation(bool reposition) = 0; virtual void rva004726DD(Object *target) = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void assignSpotToUnit(Object *obj) = 0; virtual void rva00469F2F(Object *obj) = 0; virtual void notifyOfMemberDeath(Object *) = 0;
	virtual void removeMemberFromHorde(Object *obj) = 0; virtual void gap15() = 0; virtual void performReform() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual Object *rva0046CC09() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup) = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void rva00473799(const _STL::list<Object *> &items) = 0; virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3) = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void rva0046BEAC(Object *obj) = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void rva0046E7E3(const UpgradeTemplate *upgrade, bool all) = 0; virtual void gap47() = 0; virtual void rva004707DB(Object *obj, float amount) = 0; virtual void rva004739B4() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void rva0046C3FE(Player *player) = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual bool rva0046AAB8() = 0; virtual void rva004738B6(Object *target) = 0; virtual void gap64() = 0; virtual unsigned int rva0046F7F8() const = 0;
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p) = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual void gap69() = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void startMeleeAttack(Object *target) = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool canEngageInMelee(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual Object *rva004708BC(const Matrix3D *mtx) = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
	virtual void rva0046A712(int unused) = 0; virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer) = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual bool rva0046992C() = 0;
	virtual void gap126() = 0; virtual bool rva004698BC() = 0; virtual const void *rva004698D6() = 0; virtual const void *rva004698E2() = 0;
	virtual void rva00469967() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
	virtual void gap134() = 0; virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after) = 0; virtual bool rva0046F8CD() = 0; virtual Rva002390CB rva0046EC7C(Object *obj) = 0;
	virtual ObjectID rva0046DEA1(ObjectID want) = 0; virtual bool rva0046DF9A(Coord3D *center) = 0; virtual bool rva0046E113(Coord3D *center) = 0; virtual void rva004690D0(int value) = 0;
	virtual bool rva00468C37() = 0; virtual void rva00468BDC(int on) = 0;
	virtual float rva00468B5B(float value) = 0;
	virtual void rva00468C60(const Coord3D *pos) = 0;
	virtual bool rva00468C7B(Coord3D *pos) = 0;
	virtual bool isFlankedBy(Object *attacker) = 0;
	virtual void rva0046E2BC() = 0;
	virtual void gap149() = 0;
	virtual float rva0046F8DA() = 0;
	virtual float rva0046F8E7() = 0;
	virtual void gap152() = 0;
	virtual float rva0046B850() = 0;
	virtual void endMove() = 0;
};
class UpdateModule : public Rva00468D11Slots<32>
{
public:
	virtual void slot32(Object *obj) = 0;
	virtual void slot33(int a1) = 0;
	virtual void rva0046AF85() = 0;
	virtual void gap35() = 0;
	virtual void gap36() = 0;
	virtual bool rva00470B21() = 0;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
	unsigned char m_pad14[0x20 - 0x14];
};
typedef void (*ContainIterateFunc)(Object *obj, void *userData);
class ContainModuleInterface : public Rva00468D11Slots<38>
{
public:
	virtual bool slot38(Object *obj, int a2, int a3) = 0;
	virtual void cgap39() = 0; virtual void cgap40() = 0; virtual void slot41(const Object *obj, int a2) = 0; virtual void cgap42() = 0; virtual void cgap43() = 0; virtual void cgap44() = 0; virtual void cgap45() = 0; virtual void cgap46() = 0; virtual void cgap47() = 0; virtual void cgap48() = 0; virtual void cgap49() = 0; virtual void cgap50() = 0; virtual void cgap51() = 0; virtual void cgap52() = 0; virtual void cgap53() = 0; virtual void cgap54() = 0; virtual void cgap55() = 0; virtual void cgap56() = 0; virtual void cgap57() = 0; virtual void cgap58() = 0; virtual void cgap59() = 0; virtual void cgap60() = 0; virtual void cgap61() = 0; virtual void cgap62() = 0; virtual void cgap63() = 0; virtual void cgap64() = 0; virtual void cgap65() = 0; virtual void cgap66() = 0; virtual void cgap67() = 0;
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);
	virtual int slot69(int a1) = 0;
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
	virtual void cgap71() = 0; virtual void cgap72() = 0; virtual void cgap73() = 0; virtual void cgap74() = 0; virtual void cgap75() = 0; virtual void cgap76() = 0; virtual void cgap77() = 0;
	virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim) = 0;
};
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
public:
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual void gatherUnitBack(Object *obj) = 0;
private:
	unsigned char m_pad024[0x11C - 0x24];
};
struct HordeBannerCarrierUpdateData
{
	unsigned char m_pad00[0x10];
	int m_value;
};
struct HordeBannerCarrierUpdate
{
	void *m_vtbl;
	const HordeBannerCarrierUpdateData *m_data;
};
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned int m_bits[7];
};
template <int N> class BitFlags
{
	unsigned int m_bits[7];
};
extern BitFlags<116> KINDOFMASK_NONE;
extern PartitionManager *ThePartitionManager;
class BfmeThingBQA
{
public:
	int bfmeGoBQA() throw();
};
struct Rva004598F2Point : public Coord3D
{
};
class SiegeDockingBehavior
{
public:
	Rva004598F2Point rva004598F2(int index);
	Rva004598F2Point rva0045992F(int index);
};
class Rva00468CB6A;
class Rva0046D946
{
public:
	Object *rva0046D946(Object *obj);
};
class Rva00471FFAVictimChooser : public Rva00468D11Slots<18>
{
public:
	virtual Object *slot18(int a1, const Coord3D *pos, float range, Object *source, bool flag) = 0;
	virtual void gap19() = 0; virtual void gap20() = 0; virtual void gap21() = 0; virtual void gap22() = 0;
	virtual void gap23() = 0; virtual void gap24() = 0; virtual void gap25() = 0; virtual void gap26() = 0;
	virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0; virtual void gap30() = 0;
	virtual void gap31() = 0; virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0;
	virtual void gap35() = 0; virtual void gap36() = 0; virtual void gap37() = 0; virtual void gap38() = 0;
	virtual void gap39() = 0; virtual void gap40() = 0; virtual void gap41() = 0; virtual void gap42() = 0;
	virtual void gap43() = 0; virtual void gap44() = 0; virtual void gap45() = 0; virtual void gap46() = 0;
	virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0; virtual void gap50() = 0;
	virtual void gap51() = 0; virtual void gap52() = 0; virtual void gap53() = 0; virtual void gap54() = 0;
	virtual void gap55() = 0; virtual void gap56() = 0; virtual void gap57() = 0; virtual void gap58() = 0;
	virtual void gap59() = 0; virtual void gap60() = 0; virtual void gap61() = 0; virtual void gap62() = 0;
	virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0; virtual void gap66() = 0;
	virtual void gap67() = 0;
	virtual Object *slot68() = 0;
};
struct Rva0046E6EAObject; struct Rva0046E6EACoord;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *obj, const Rva0046E6EACoord *pos, Rva0046E6EACoord *out, bool flag); };
class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	virtual void attackTargetNow(Object *target, int select);
	virtual void rva004726DD(Object *target);
	virtual void rva0046E7E3(const UpgradeTemplate *upgrade, bool all);
	virtual void removeMemberFromHorde(Object *obj);
	bool rva00468CB6(Rva00468CB6A *,Object *);
	void rva00468B24(float value);
	unsigned char usingMeleeAttack();
	void rva0046A893(Object *obj);
	void checkSpecialUnitDeath(Object *obj);
	void refreshDrawable(Drawable *drawable);
	void *rva0046AF12();
	int getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate);
	HordeBannerCarrierUpdate *rva00468E26(Object *obj);
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);
	virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
	virtual bool rva0046BB38(Object *other);
	virtual void rva0046FE99(_STL::list<Object *> &out);
	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
	virtual bool isFlankedBy(Object *attacker);
	virtual void rva004738B6(Object *target);
	bool rva00468F0F(Object *obj, Object *target);
	virtual AsciiString rva0046D1AC();
	virtual void rva0046F7C9(Object *obj);
	virtual void rva00469F2F(Object *obj);
 virtual void notifyOfMemberDeath(Object *obj);
	void rva00469886(Object *obj);
	void rva00469F3A(Object *obj);
	virtual int rva0046979B();
	virtual void *rva004696CD();
	virtual void rva004696E5();
	virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource);
	virtual bool rva00468D11();
	virtual bool rva00468D2C();
	virtual bool rva0046F8A5();
	virtual bool rva0046F8F4();
	virtual Object *rva0046D372();
	virtual void rva0046F8B2();
	virtual int rva004697CD();
	virtual int rva00468F68();
	virtual int rva00468F7E();
	virtual Object *rva004708BC(const Matrix3D *mtx);
	virtual bool rva004698BC();
	virtual const void *rva004698D6();
	virtual const void *rva004698E2();
	virtual void rva00469967();
	virtual void rva004690A9(const Coord3D *pos);
	virtual bool rva0046F8CD();
	virtual bool rva00468C37();
	virtual void rva004690D0(int value);
	virtual float rva00468B5B(float value);
	virtual void rva00468C60(const Coord3D *pos);
	virtual bool rva00468C7B(Coord3D *pos);
	virtual float rva0046F8DA();
	virtual float rva0046F8E7();
	virtual bool rva0046C65C();
	virtual bool rva0046C71E();
	virtual bool rva0046C6E7();
	virtual void rva00468FDC();
	virtual bool rva0046A46F();
	virtual bool rva0046A416();
	virtual bool canEngageInMelee(Object *obj, int a2);
	virtual bool rva00468DCD(Object *obj);
	virtual bool rva0046A4C8();
	virtual void rva00468D7D(Object *obj);
	virtual void rva0046981C();
	virtual void rva00469851();
	virtual void rva00468BDC(int on);
	virtual void rva0046AF85();
	virtual void rva00473ADF();
	virtual bool rva0046A6C1();
	virtual bool rva0046A677();
	virtual Object *rva0046D27A();
	virtual void rva0046D7AF(int a1);
	virtual void rva0046DDC5(int a1, int a2);
	virtual void rva0046D384(Team *team);
	virtual void rva004730B0(Object *target);
	virtual void rva0046DE2D(const FXList *fx);
	virtual void rva0046A712(int unused);
	virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer);
	virtual bool rva0046C5D7(int value);
	virtual bool rva0046A2EC(Object *target);
	virtual bool rva0046A381(Object *target);
	virtual void rva0046BEAC(Object *obj);
	virtual void rva0046BD70();
	virtual void rva0046BE0E();
	virtual void rva0046BA56(Object *source, int unused);
	void rva0046BACD();
	virtual void rva0046C3FE(Player *player);
	virtual void rva004707DB(Object *obj, float amount);
	virtual void rva004739B4();
	virtual void rva00473799(const _STL::list<Object *> &items);
	virtual void rva0046D8AE();
	virtual Object *rva0046CB2C();
	virtual bool rva0046D80B();
	virtual bool rva0046BB6F(int *out, unsigned int frame);
	virtual int rva0046D3FC(Rva2225E0Filter *filter);
	virtual bool rva0046A2A7();
	virtual void rva0046E2BC();
	virtual void endMove();
	virtual bool rva0046992C();
	virtual Object *rva0046CC09();
	virtual Object *rva0046CBCA();
	virtual void rva0046C327();
	virtual void rva0046C20B();
	virtual ObjectID rva0046DEA1(ObjectID want);
	virtual bool rva0046DF9A(Coord3D *center);
	virtual bool rva0046E113(Coord3D *center);
	virtual void rva0046A78F(const Matrix3D *mtx);
	virtual void rva00472329(const Coord3D *pos, int unused);
	virtual void rva00472235();
	virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3);
	virtual void slot42(const Object *obj);
	virtual void assignSpotToUnit(Object *obj);
	virtual void startMeleeAttack(Object *target);
	virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup);
	virtual float rva0046B850();
	virtual void rva0046D1F7(_STL::list<const Object *> &out);
	virtual void rva0046E253();
	virtual void returnToFormation(bool reposition);
	void rva0046AA85();
	virtual bool rva0046CDC9();
	virtual bool rva0046CCEF(const ThingTemplate *tmpl);
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual bool rva0046B9DC(int a1);
	virtual bool rva0046B95E(int a1);
	virtual void rva00468CA3(const Rva00468CA3Arg *arg);
	virtual bool rva0046AAB8();
	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3);
	virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter);
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p);
	virtual Rva002390CB rva0046EC7C(Object *obj);
	Rva0046D158Record *rva0046D158(AsciiString name);
	virtual void performReform();
	virtual bool rva00470B21();
	Coord2D *rva0046A5B1(Coord2D *offset, int index);
	bool rva004723F2(Object *, const AsciiString &);
private:
	__forceinline const _STL::list<Object *> *containedItems()
	{
		Rva0046247DPair p;
		((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
		return p.m04;
	}
	const HordeContainModuleDataFields *fields() const { return (const HordeContainModuleDataFields *)m_moduleData; }
	bool m_120;
	bool m_121;
	unsigned char m_pad122[0x170 - 0x122];
	_STL::set<int> m_170;
	_STL::map<int, int> m_17C;
	Rva00472329Record *begin188() { return m_188Begin; }
	Rva00472329Record &rec188(unsigned int n) { return *(begin188() + n); }
	Rva00472329Record *m_188Begin;
	Rva00472329Record *m_188End;
	Rva00472329Record *m_188Cap;
	_STL::list<int> m_194;
	bool m_198;
	unsigned char m_pad199[0x19C - 0x199];
	int m_19C;
	unsigned char m_pad1A0[0x1AC - 0x1A0];
	ObjectID m_1AC;
	ObjectID m_1B0;
	int m_1B4;
	unsigned char m_pad1B8[0x200 - 0x1B8];
	int m_200;
	unsigned char m_pad204[0x24C - 0x204];
	_STL::map<int, void *> m_24C;
	_STL::map<unsigned short, float, Rva00470041Less> m_258;
	void *m_264;
	unsigned char m_pad268[0x26C - 0x268];
	ObjectID m_26C;
	struct BannerIndexEntry
	{
		const ThingTemplate *m_template;
		int m_index;
	};
	_STL::vector<BannerIndexEntry *> m_bannerIndices;
	int m_27C;
	unsigned char m_pad280[0x288 - 0x280];
	int m_288;
	unsigned int m_28C;
	unsigned char m_pad290[0x294 - 0x290];
	bool m_294;
	unsigned char m_pad295[0x298 - 0x295];
	unsigned int m_298;
	int m_29C;
	int m_2A0;
	bool m_2A4;
	unsigned char m_pad2A5[0x2B8 - 0x2A5];
	Coord3D m_2B8;
	bool m_2C4;
	unsigned char m_pad2C5[0x2C8 - 0x2C5];
	Rva00468FDCHelper *m_2C8;
	float *m_2CCBegin;
	float *m_2CCEnd;
	float *m_2CCCap;
	unsigned char m_pad2D8[0x2DC - 0x2D8];
	_STL::map<int, Rva00462D35Mapped> m_2DC;
	bool m_2E8;
	unsigned char m_pad2E9[0x2EC - 0x2E9];
	float m_2EC;
	int m_2F0;
	unsigned char m_pad2F4[0x2F8 - 0x2F4];
	Coord3D m_2F8;
	bool m_304;
};
bool Rva004693AD::rva004693AD(Rva004693ADArg *arg)
{
	int value = arg->m_74;
	if (m_264 == value || m_26C == value || (arg->m_04->m_flags & 8) != 0)
		return true;
	return false;
}
struct Rva00463D9BElement { char bytes[8]; };
typedef _STL::_Rb_tree<Rva00463D9BElement,Rva00463D9BElement,_STL::_Identity<Rva00463D9BElement>,_STL::less<Rva00463D9BElement>,_STL::allocator<Rva00463D9BElement> > Rva00463D9BTree;
namespace _STL { template<> unsigned int Rva00463D9BTree::erase(const Rva00463D9BElement &); }
class HordeDeathDrawable { public: void rva00272945(unsigned); char pad[0x43c]; bool refresh; };
class HordeDeathControl : public Rva00468D11Slots<6> { public: virtual void slot6(Object *) = 0; };
class HordeDeathBody : public Rva00468D11Slots<15> { public: virtual const unsigned *slot15() = 0; };
class HordeDeathInterface : public Rva00468D11Slots<96> { public: virtual unsigned slot96(int) = 0; };
class HordeDeathHeight : public Rva00468D11Slots<7> { public: virtual float height(float, float, int, bool, bool) = 0; };
struct HordeDeathDataView { char prefix[0x248]; int deathEvent; };
enum HordeDeathKind { HORDE_DEATH_KIND = 0x1bb };
enum EvaEventID { EVA_EVENT_NONE=0 };
class Eva {public:bool reportEvaEvent(EvaEventID,const Coord3D*,const Coord3D*);};
extern Eva *TheEva;
class Rva00265254 { public: Rva00265254(unsigned, unsigned, unsigned, unsigned); int words[19]; };
class Rva001E42F2 { public: void rva001E42F2(const int *); };
__forceinline void HordeContain::refreshDrawable(Drawable *drawable)
{
	if (drawable && ((HordeDeathDrawable *)drawable)->refresh)
		drawable->rva00272945(rva0046D3FC(0));
}
void HordeContain::notifyOfMemberDeath(Object *obj)
{
	union { Rva0046247DPair pair; struct { int pad; int id; } words; } scratch;
	scratch.pair.m04 = 0;
	if (!obj)
		return;
	((HordeDeathControl *)m_2C8)->slot6(obj);
	if (!((Rva004693AD *)(UpdateModule *)this)->rva004693AD((Rva004693ADArg *)obj)) {
		scratch.words.id = obj->getID();
		m_194.push_front(m_17C[scratch.words.id]);
	}
	if (obj->isKindOf(KINDOF_HORDE_DEATH)) {
		Object *other = TheGameLogic->findObjectByID((ObjectID)obj->getID());
		if (other) {
			((Rva001E42F2 *)other)->rva001E42F2(Rva00265254(0, 0x67, 0x69, 0x1bb).words);
			((Thing *)other)->setPositionZ(((HordeDeathHeight *)TheTerrainLogic)->height(obj->m_position.x, obj->m_position.y, obj->rva0028B511(), false, true));
		}
	}
	if (Rva0046B850Module *body = obj->m_254) {
		const unsigned *data = ((HordeDeathBody *)body)->slot15();
		if (data)
			m_29C = data[2];
		else
			m_29C = 0;
	}
	scratch.words.id = obj->getID();
	((Rva00463D9BTree *)&m_17C)->erase(*(const Rva00463D9BElement *)&scratch.words.id);
	scratch.words.id = obj->getID();
	m_170.erase(scratch.words.id);
	while (rva00470B21()) {
	}
	const _STL::list<Object *> *items = ((Rva0046247DPair *)((Rva0046247D *)this)->rva0046247D(scratch.pair))->m04;
	if (items->empty() && m_170.empty()) {
		const HordeDeathDataView *data = (const HordeDeathDataView *)m_moduleData;
		TheEva->reportEvaEvent((EvaEventID)data->deathEvent, &obj->m_position, 0);
		TheGameLogic->destroyObject(m_object);
	}
	m_298 = TheGameLogic->m_frame;
	if (TheWritableGlobalData->m_9A6) {
		refreshDrawable(((Thing *)m_object)->getDrawable());
	}
	checkSpecialUnitDeath(obj);
	const HordeContainModuleDataFields *md = fields();
	if (md && !md->m_1D8) {
		_STL::list<const Object *> contained;
		rva0046D1F7(contained);
		if (contained.size() < (unsigned)md->m_268)
			rva004696E5();
	}
}
