// ?attemptDamage@ActiveBody@@UAEXPAVDamageInfo@@@Z
// partial score=0.8504100587141394 date=2026-10-16
// cl: /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include












// stlport
#include <vector>
#include <algorithm>

namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; } }
#include <string.h>
#include <list>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };
enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };
enum ArmorSetType { ARMORSET_VETERAN, ARMORSET_ELITE, ARMORSET_HERO };
enum MaxHealthChangeType { SAME_CURRENTHEALTH, PRESERVE_RATIO };

enum DamageType { DAMAGE_4 = 4, DAMAGE_6 = 6, DAMAGE_HEALING = 7, DAMAGE_UNRESISTABLE = 8, DAMAGE_23 = 0x17 };
enum KindOfType { KINDOF_4 = 4, KINDOF_220 = 0x220, KINDOF_14A = 0x14A };
enum ObjectID { INVALID_ID = 0 };
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_4 = 4,
	OBJECT_STATUS_8 = 8,
	OBJECT_STATUS_24 = 24,
	OBJECT_STATUS_60 = 0x3C,
	OBJECT_STATUS_65 = 0x41,
	OBJECT_STATUS_77 = 0x4D,
	OBJECT_STATUS_83 = 0x53
};


#define COORD3D_VIEW_DTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Matrix3D;
class ParticleSystemTemplate;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};



void XferBodyDamageType(Xfer *xfer, Int *value);
void XferBodySideDestroyedType(Xfer *xfer, Int *value);
void XferDamageFXType(Xfer *xfer, Int *value);
void XferParticleSystemID(Xfer *xfer, Int *value);
void XferObjectID(Xfer *xfer, ObjectID *value);



struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};

class Object;
class Drawable;
class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}

public:
	char m_pad00[0xA8];
	ParticleSystemID m_systemID;
};
ParticleSystem *Make001FCBD7();



class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

extern Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);
#define GameClientRandomValue(lo, hi) \
	GetGameClientRandomValue((lo), (hi), __FILE__, __LINE__)




class Rva004BDA0C
{
public:
	__declspec(dllimport) __forceinline virtual ~Rva004BDA0C() {}

	ParticleSystemID m_particleSystemID;
	Rva004BDA0C *m_next;
};
typedef Rva004BDA0C BodyParticleSystem;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class DamageInfoInput
{
public:
	UnsignedInt m_field00;
	ObjectID m_sourceID;
	UnsignedInt m_field08;
	DamageType m_damageType;
	Int m_damageFXType;
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_kill;
	unsigned char m_pad21[0x28 - 0x21];
	Int m_creationType;
};



class DamageInfo
{
public:
	virtual void xfer(Xfer *xfer);
	DamageInfoInput in;
	unsigned char m_pad30[0x70 - 0x30];
	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	unsigned char m_pad78[4];
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
};

class BehaviorModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual DamageModuleInterface *getDamage();
};

class BehaviorModule
{
public:
	unsigned char m_pad00[0x0C];
	BehaviorModuleInterface m_iface;
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};




struct BfmeShapeE15
{
	unsigned char m_pad00[0x1C];
	AsciiString m_name;
	unsigned char m_pad20[4];
};
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	Int getNumShapes() const { return m_finish - m_start; }

	unsigned char m_pad00[0x2C];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};
class BfmeStrF9;
class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &name, char flag);
};
struct BfmeCopyElementA;

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	Real getStructureRubbleHeight() const { return (Real)m_structureRubbleHeight; }

	unsigned char m_pad000[0xA0];
	GeometryInfo m_geometryInfo;
	unsigned char m_pad0A1[0x108 - 0xA1];
	UnsignedInt m_kindOf[0x10];
	unsigned char m_pad148[0x5F7 - 0x148];
	signed char m_structureRubbleHeight;
	unsigned char m_pad5F8[0x632 - 0x5F8];
	Bool m_byte632;
};

class BodyModuleInterface;
class ActiveBody;

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_SCRIPT, CMD_FROM_AI };
enum DisabledType { DISABLED_8 = 8 };
enum NameKeyType { NAMEKEY_INVALID = 0 };




class Rva004BFD27
{
public:
	void rva004BFD27(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	virtual void a000(); virtual void a001(); virtual void a002(); virtual void a003();
	virtual void a004(); virtual void a005(); virtual void a006(); virtual void a007();
	virtual void a008(); virtual void a009(); virtual void a010(); virtual void a011();
	virtual void a012(); virtual void a013(); virtual void a014(); virtual void a015();
	virtual void a016(); virtual void a017(); virtual void a018(); virtual void a019();
	virtual void a020(); virtual void a021(); virtual void a022(); virtual void a023();
	virtual void a024(); virtual void a025(); virtual void a026(); virtual void a027();
	virtual void a028(); virtual void a029(); virtual void a030(); virtual void a031();
	virtual void a032(); virtual void a033(); virtual void a034(); virtual void a035();
	virtual void a036(); virtual void a037(); virtual void a038(); virtual void a039();
	virtual void a040(); virtual void a041(); virtual void a042(); virtual void a043();
	virtual void a044(); virtual void a045(); virtual void a046(); virtual void a047();
	virtual void a048(); virtual void a049(); virtual void a050(); virtual void a051();
	virtual void a052(); virtual void a053(); virtual void a054(); virtual void a055();
	virtual void a056(); virtual void a057(); virtual void a058(); virtual void a059();
	virtual void a060(); virtual void a061(); virtual void a062(); virtual void a063();
	virtual void a064(); virtual void a065(); virtual void a066(); virtual void a067();
	virtual void a068(); virtual void a069(); virtual void a070(); virtual void a071();
	virtual void a072(); virtual void a073(); virtual void a074(); virtual void a075();
	virtual void a076(); virtual void a077(); virtual void a078(); virtual void a079();
	virtual void a080(); virtual void a081(); virtual void a082(); virtual void a083();
	virtual void a084(); virtual void a085(); virtual void a086(); virtual void a087();
	virtual void a088(); virtual void a089(); virtual void a090(); virtual void a091();
	virtual void a092(); virtual void a093(); virtual void a094(); virtual void a095();
	virtual void a096(); virtual void a097(); virtual void a098(); virtual void a099();
	virtual void a100(); virtual void a101(); virtual void a102(); virtual void a103();
	virtual void a104(); virtual void a105(); virtual void a106(); virtual void a107();
	virtual void a108(); virtual void a109();
	virtual Bool isIdle() const;


	int rva002632C7() const;
	unsigned char rva002632C7Bool() const { return (unsigned char)rva002632C7(); }
	void rva002632E1();
	Rva004BFD27 *getCommandInterface() { return (Rva004BFD27 *)&m_commandInterface; }

	unsigned char m_pad04[0x20 - 0x04];
	void *m_commandInterface;
	unsigned char m_pad24[0x34 - 0x24];
	Int m_field34;
};




class Rva004BFE07ContainHelper : public VSlots<14>
{
public:
	virtual void onClippedDamage(Object *obj);
};
class ContainModuleInterface : public VSlots<26>
{
public:
	virtual void onContainedDamage(Object *obj, ActiveBody *body, DamageInfo *damageInfo);
	virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
	virtual Rva004BFE07ContainHelper *getDamageHelper();
	virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
	virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
	virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
	virtual void c44(); virtual void c45(); virtual void c46(); virtual void c47();
	virtual void c48(); virtual void c49(); virtual void c50(); virtual void c51();
	virtual void c52(); virtual void c53(); virtual void c54(); virtual void c55();
	virtual void c56(); virtual void c57(); virtual void c58(); virtual void c59();
	virtual void c60(); virtual void c61(); virtual void c62(); virtual void c63();
	virtual void c64(); virtual void c65(); virtual void c66(); virtual void c67();
	virtual void c68();
	virtual UnsignedInt getContainCount(Int arg);
};




class Rva0028C1A9Result
{
public:
	virtual void r0(); virtual void r1(); virtual void r2();
	virtual Bool shouldKill(Object *victim);
	virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
	virtual void onKill(Object *victim);
};

class Rva004BFE07Flagged
{
public:
	unsigned char m_pad00[0x5C];
	Bool m_byte5C;
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_pad00[0x54];
	Int m_playerIndex;
};

class Module;

class Object
{
public:
	Bool isKindOf(KindOfType kindOf) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void setEffectivelyDead(Bool dead);
	Bool rva0028F518();
	void setStatus(ObjectStatusTypes bit, Bool set);
	void rva0028AB75(Bool flag);
	void rva0028ABFC(Real z);
	void rva0029895A(BfmeCopyElementA *geom);
	Bool addAttributeModifierToPool(const AsciiString &name, Int duration);
	void removeAttributeModifierFromPool(const AsciiString &name);
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool testStatusBit(Int bit) const { return (m_status >> bit) & 1; }
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones, Coord3D *positions,
		Matrix3D *transforms, Bool convertToWorld, Int extra) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Int getID() const { return m_id; }
	Bool testStatusBit6() const { return (m_status >> 6) & 1; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Drawable *getDrawable() const;
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *rva002931F5(Bool flag);
	void *rva0028C1A9() const;
	Bool rva0028D491() const;
	void rva0028B1D4(Int damageInfo, Int victim) const;
	Player *getControllingPlayer() const;
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	void onDie(DamageInfo *damageInfo);
protected:
	friend class ActiveBody;
	Module *findModule(NameKeyType key) const;
public:
	const Coord3D *getPosition() const { return (const Coord3D *)m_cachedPos; }

	void *m_vptr;
	const ThingTemplate *m_template;
	Real m_transform[3][4];
	Real m_cachedPos[3];
	unsigned char m_pad44[0x74 - 0x44];
	Int m_id;
	unsigned char m_pad78[0x94 - 0x78];
	UnsignedInt m_status;
	unsigned char m_pad98[0xA8 - 0x98];
	BfmeObjE15 m_geometry;
	unsigned char m_padDC[0x10C - 0xDC];
	unsigned char m_kindOfMask[0x4C];
	unsigned char m_pad158[0x244 - 0x158];
	BehaviorModule **m_behaviors;
	unsigned char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	Rva004BFE07Flagged *m_field25C;
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy;
	unsigned char m_pad278[0x280 - 0x278];
	Int m_field280;
	unsigned char m_pad284[0x438 - 0x284];
	UnsignedInt m_flags438;
};



class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB() { if (m_04.referent != 0) m_04.referent->Release_Ref(); }
	char m_pad00[4];
	OpaqueRefElement4 m_04;
};
class Drawable
{
public:
	Rva002390CB rva004BE152();
	Rva002390CB rva004BE16B();
	Rva002390CB rva004BE184();
	Rva002390CB rva004BE120();
	Rva002390CB rva004BE139();
	Object *getObject() const { return m_object; }

	unsigned char m_pad00[0xFC];
	Object *m_object;
};



class Rva002D9C2F { public: OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other); };
class Rva002D9531 { public: void rva002D9531(int v); };

class AudioManager : public VSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
};
extern AudioManager *TheAudio;

class InGameUI : public VSlots<70>
{
public:
	virtual Int getSelectCount();
	virtual void u71(); virtual void u72(); virtual void u73(); virtual void u74();
	virtual Drawable *getFirstSelectedDrawable();
};
extern InGameUI *TheInGameUI;

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }

	unsigned char m_pad00[0x28];
	Bool m_UIDirty;
};
extern ControlBar *TheControlBar;

class DOTManager
{
public:
	UnsignedInt rva0043B72D(Int id);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);

	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;
	unsigned char m_pad44[0x174 - 0x44];
	DOTManager *m_dotManager;
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
	void RemoveObjectFromPathfindMap(Object *obj);
};
class AIData
{
public:
	unsigned char m_pad00[0x64];
	Bool m_enableRepulsors;
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() const { return m_aiData; }

	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
	unsigned char m_pad14[4];
	AIData *m_aiData;
};
extern AI *TheAI;

class GlobalData
{
public:
	unsigned char m_pad000[0xAD4];
	Real m_healthBonus[4];
	Real m_defaultStructureRubbleHeight;
};
extern GlobalData *TheWritableGlobalData;







class Rva004BDA29
{
public:
	Int rva004BDA29() const;

private:
	void *m_vptr;
	unsigned char m_pad04[0x14];
	Real m_health;
	unsigned char m_pad1C[4];
	Real m_maxHealth;
	Real m_damagedThresh;
	Real m_reallyDamagedThresh;
};


class Rva004BDA67
{
public:
	void rva004BDA67();
};

class DamageFX
{
public:
	Bool rva003608DF(Int damageType, Real amount, const Object *source, const Object *victim);
};

class Rva003605D5
{
public:
	Int rva003605D5(Int damageType, Int source);
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
};

struct DamageCreation
{
	ObjectCreationList *m_ocl;
	Int m_type;
	Int m_stage;
};

class Armor
{
public:
	Real adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const;

private:
	void *m_name;
};



struct BfmeBodyDataPair8 { float value; unsigned word; BfmeBodyDataPair8() {} __forceinline BfmeBodyDataPair8(const BfmeBodyDataPair8 &that): value(that.value), word(that.word) {} };





class Rva003427DD { public: Rva003427DD &operator=(const Rva003427DD &other); };
class Rva00294D61 { public: void report(Object *victim, Int flag); };
class Rva0028B749Host { public: void rva0028B749(Int victim, Real ratio); };
class Rva002AA201IndexedByteField { public: void set(int index); };
class Gen_003bcb40 { public: void m(Int frame); };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;





class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) throw();
private:
	unsigned int m_bits[19];
};
class Rva00263546 { public: bool rva00263546(const Rva00263546 *other) const; };
class Rva0044EAF3
{
public:
	Rva0044EAF3 *rva0044EAF3(int a, unsigned int b, unsigned int c, unsigned int d) throw();
	unsigned int m_bits[4];
};
class Rva00331682Holder { public: bool test(const void *other) const; };

class KindOfMaskType : public Rva00265254
{
public:
	KindOfMaskType(unsigned int a, unsigned int b, unsigned int c, unsigned int d) : Rva00265254(a, b, c, d) {}
	Bool anyIntersectionWith(const void *bits) const
	{
		return ((const Rva00263546 *)this)->rva00263546((const Rva00263546 *)bits);
	}
};
class ObjectStatusMaskType : public Rva0044EAF3
{
public:
	ObjectStatusMaskType(int a, unsigned int b, unsigned int c, unsigned int d) { rva0044EAF3(a, b, c, d); }
	Bool testForAny(const void *bits) const { return ((const Rva00331682Holder *)this)->test(bits); }
};



class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo;
class GameMessage
{
public:
	enum Type { MSG_BFME2_0x7E0 = 0x7E0 };
};
bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

struct BfmeDelayedLuaEvent
{
	unsigned char m_pad00[0x0C];
	Int m_value;
	unsigned char m_pad10[4];
	Int m_type;
};
struct BfmeDelayedLuaEventList;
struct DelayedLuaEventList
{
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
	BfmeDelayedLuaEvent m_events[3];
};
class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class ActiveBodyModuleData
{
public:
	unsigned char m_pad00[0x1C];
	UnsignedInt m_damagedDisableFrames;
	UnsignedInt m_reallyDamagedDisableFrames;
	UnsignedInt m_damageDelayFrames;
	unsigned char m_pad28[0x30 - 0x28];
	AsciiString m_damagedAttributeModifier;
	AsciiString m_reallyDamagedAttributeModifier;
	unsigned char m_pad38[0x40 - 0x38];
	BfmeBodyDataPair8 m_pair40;
	const FXList *m_healingFX;
	unsigned char m_pad4C[0x51 - 0x4C];
	Bool m_byte51;
	unsigned char m_pad52[0x54 - 0x52];
	const FXList *m_clippedDamageFX;
};





class Rva0028F528
{
public:
	Int rva0028F528();
};
class Rva004BE0C7
{
public:
	void *rva004BE0C7(UnsignedInt i);
};
class Rva004BE722
{
public:
	void rva004BE722(void *xfer);
};

template <int NUMBITS> class BitFlags
{
public:
	enum { NUMWORDS = (NUMBITS + 31) / 32 };
	BitFlags() {}
	__forceinline BitFlags(const BitFlags &that) { memcpy(m_bits, that.m_bits, sizeof(m_bits)); }

	Int count() { return ((Rva0028F528 *)this)->rva0028F528(); }
	const char *getBitNameIfSet(Int i) { return (const char *)((Rva004BE0C7 *)this)->rva004BE0C7(i); }
	Bool setBitByName(const char *token);
	void clear() { memset(m_bits, 0, sizeof(m_bits)); }
	void set(unsigned bit) { m_bits[bit >> 5] |= 1U << (bit & 31); }
	void reset(unsigned bit) { m_bits[bit >> 5] &= ~(1U << (bit & 31)); }
	void xfer(Xfer *xfer);

private:
	UnsignedInt m_bits[NUMWORDS];
};
typedef BitFlags<21> ArmorSetFlags;



class BodyModule
{
public:
	virtual void m00(); virtual void m01(); virtual void m02();
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void onDelete();
	virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12();
	virtual void rva004BE69C();
	virtual void m14(); virtual void m15();
	virtual void m16();
	virtual void validateArmorAndDamageFX() const;
	virtual void doDamageFX(const DamageInfo *damageInfo) = 0;
	virtual void m19();
	virtual void deleteAllParticleSystems();
	virtual void rvaSlot21(Int arg);
	virtual void rva004BF9ED();

protected:
	const ActiveBodyModuleData *m_moduleData;
	Object *m_object;
	void *m_vptr0C;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual Real estimateDamage(DamageInfoInput &damageInfo) const;
	virtual void i03();
	virtual Real getHealth() const;
	virtual Real getHealthRatio() const;
	virtual Real getMaxHealth() const;
	virtual void i07();
	virtual void i08();
	virtual void setDamageState(BodyDamageType newState);
	virtual void i10();
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);
	virtual void setArmorSetFlag(ArmorSetType ast);
	virtual void clearArmorSetFlag(ArmorSetType ast);
	virtual ArmorSetFlags rva004BF8F5(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual ObjectID rva004BF897(); virtual void i19();
	virtual Bool getBackCrushed() const;
	virtual void setInitialHealth(Real initialPercent, Bool directional);
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType);
	virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual BfmeBodyDataPair8 rva004BDC56();
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);
	virtual void i33(); virtual void i34(); virtual void i35();
	virtual void rvaSlot36();
	virtual void i37(); virtual void i38();
	virtual void rvaSlot39(BodyDamageType state);
	virtual void rvaSlot40(Real health, Bool healing);
};

class ActiveBody : public BodyModule, public BodyModuleInterface
{
public:
	virtual void setInitialHealth(Real initialPercent, Bool directional);
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual Real estimateDamage(DamageInfoInput &damageInfo) const;
	virtual void setDamageState(BodyDamageType newState);
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);
	virtual ArmorSetFlags rva004BF8F5();
	virtual ObjectID rva004BF897();
	virtual Bool getBackCrushed() const;
	virtual BfmeBodyDataPair8 rva004BDC56();
	virtual void setArmorSetFlag(ArmorSetType ast);
	virtual void clearArmorSetFlag(ArmorSetType ast);

	virtual void rva004BE69C();
	virtual void onDelete();
	void setCorrectDamageState(Bool arg);
	void rva004BFB1C(Real amount, const Coord3D *pos);
	void rva004BFCD4(Real amount, DamageInfo *damageInfo);

protected:
	virtual void xfer(Xfer *xfer);
	static Bool shouldRetaliate(Object *obj);
	virtual void doDamageFX(const DamageInfo *damageInfo);
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	const ActiveBodyModuleData *getActiveBodyModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	Real m_damageScalar;
	Real m_currentHealth;
	Real m_prevHealth;
	Real m_maxHealth;
	Real m_damagedRatio;
	Real m_reallyDamagedRatio;
	Real m_initialHealth;
	BodyDamageType m_curDamageState;
	Int m_field34;
	UnsignedInt m_nextDamageFXTime;
	Int m_lastDamageFXDone;
	DamageInfo m_lastDamageInfo;
	UnsignedInt m_lastDamageTimestamp;
	UnsignedInt m_lastHealingTimestamp;
	Bool m_frontCrushed;
	Bool m_backCrushed;
	Bool m_lastDamageCleared;
	Bool m_indestructible;
	BodyParticleSystem *m_particleSystems;
	Real m_damageStateValues[4];
	Bool m_damageStateFlags[4];
	DamageCreation *m_damageCreationBegin;
	DamageCreation *m_damageCreationEnd;
	unsigned char m_padE8[4];
	ObjectID m_linkedObjectID;
	ArmorSetFlags m_curArmorSetFlags;
	const void *m_curArmorSet;
	Armor m_curArmor;
	DamageFX *m_curDamageFX;
};





Real ActiveBody::estimateDamage(DamageInfoInput &damageInfo) const
{
	validateArmorAndDamageFX();
	return m_curArmor.adjustDamage(&damageInfo, getObject(), true);
}





void ActiveBody::onDelete()
{
	Object *obj = getObject();
	if (!(obj->m_flags438 & 1) && !obj->getTemplate()->testKindOf(25) && !obj->getTemplate()->testKindOf(89))
		rva004BF9ED();
	deleteAllParticleSystems();
}


void ActiveBody::setDamageState(BodyDamageType newState)
{
	switch (newState)
	{
	case BODY_PRISTINE:
		internalChangeHealth(m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_DAMAGED:
		internalChangeHealth(m_damagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_REALLYDAMAGED:
		internalChangeHealth(m_reallyDamagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_RUBBLE:
		internalChangeHealth(0.0f - m_currentHealth, 0);
		break;
	}
	rvaSlot21(0);
}











void ActiveBody::attemptHealing(DamageInfo *damageInfo)
{
	validateArmorAndDamageFX();

	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	Object *obj = getObject();
	if (md->m_byte51 && obj->isKindOf(KINDOF_220))
		return;

	if (damageInfo == 0)
		return;

	if (damageInfo->in.m_damageType != DAMAGE_HEALING)
	{
		attemptDamage(damageInfo);
		return;
	}

	const ThingTemplate *tmpl = obj->getTemplate();
	if (!tmpl->m_byte632 && !tmpl->testKindOf(150) && !tmpl->testKindOf(22) && !tmpl->testKindOf(24)
		&& (obj->m_flags438 & 1))
		return;

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;

	Real amount = m_curArmor.adjustDamage(&damageInfo->in, getObject(), false);
	if (amount > 0.0f)
	{
		BodyDamageType oldState = m_curDamageState;
		internalChangeHealth(amount, damageInfo);

		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;
		m_lastHealingTimestamp = TheGameLogic->getFrame();

		if (m_currentHealth > m_prevHealth)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onHealing(damageInfo);
			}

			if (!obj->getTemplate()->testKindOf(7) && md->m_healingFX && !obj->testStatusBit6())
				FXList::doFXObj(md->m_healingFX, obj, 0);

			TheGameLogic->m_dotManager->rva0043B72D(obj->getID());
		}

		if (m_curDamageState != oldState)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}

			if (m_linkedObjectID)
			{
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked && linked->getBodyModule())
					linked->getBodyModule()->rvaSlot39(m_curDamageState);
			}
		}
	}

	doDamageFX(damageInfo);
}








void ActiveBody::doDamageFX(const DamageInfo *damageInfo)
{
	DamageFX *fx = m_curDamageFX;
	Int type = damageInfo->in.m_damageFXType;
	if (fx)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (type == m_lastDamageFXDone && m_nextDamageFXTime > now)
			return;
		Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
		if (fx->rva003608DF(type, damageInfo->m_actualDamageDealt, source, getObject()))
		{
			m_lastDamageFXDone = type;
			m_nextDamageFXTime = ((Rva003605D5 *)m_curDamageFX)->rva003605D5(type, (Int)source) + now;
		}
	}

	for (DamageCreation *it = m_damageCreationBegin; it != m_damageCreationEnd; ++it)
	{
		DamageCreation c = *it;
		if (c.m_type == damageInfo->in.m_creationType && c.m_stage == 0 && c.m_ocl)
			c.m_ocl->create(getObject(), 0, 0);
	}
}





void ActiveBody::createParticleSystems(const AsciiString &boneBaseName,
	const ParticleSystemTemplate *systemTemplate, Int maxSystems)
{
	Object *us = getObject();
	if (systemTemplate == 0)
		return;

	enum { MAX_BONES = 16 };
	Coord3D bonePositions[MAX_BONES];
	Int numBones = us->getMultiLogicalBonePosition(boneBaseName.str(), MAX_BONES, bonePositions, 0, false, 0);
	if (numBones == 0)
		return;
	if (numBones < maxSystems)
		maxSystems = numBones;

	Bool usedBoneIndices[MAX_BONES] = {};
	for (Int i = 0; i < maxSystems; ++i)
	{
#line 1514 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, numBones - 1);
		for (Int j = 0; j < numBones; ++j)
		{
			if (usedBoneIndices[boneIndex] != true)
			{
				const Coord3D *pos = &bonePositions[boneIndex];
				usedBoneIndices[boneIndex] = true;
				if (pos)
				{
					BfmeParticleSystemHandle particleSystem =
						TheParticleSystemManager->createParticleSystem(systemTemplate, true);
					if (particleSystem)
					{
						particleSystem->setPosition(pos);
						particleSystem->attachToObject(us);

						BodyParticleSystem *newEntry = new BodyParticleSystem;
						newEntry->m_particleSystemID = particleSystem->m_systemID;
						newEntry->m_next = m_particleSystems;
						m_particleSystems = newEntry;
					}
				}
				break;
			}
			boneIndex = (boneIndex + 1) % numBones;
		}
	}
}








void ActiveBody::onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel)
{
	if (oldLevel == newLevel)
		return;

	if (oldLevel < newLevel)
	{
		Drawable *draw = getObject()->getDrawable();
		if (draw)
		{
			BfmeAudioEventPrefix136 veterancyChanged((const OpaqueRefElement4 &)BfmePoolRef08(), 0);
			switch (newLevel)
			{
			case LEVEL_VETERAN:
				((Rva002D9C2F *)&veterancyChanged)->rva002D9C2F(draw->rva004BE152().m_04);
				break;
			case LEVEL_ELITE:
				((Rva002D9C2F *)&veterancyChanged)->rva002D9C2F(draw->rva004BE16B().m_04);
				break;
			case LEVEL_HEROIC:
				((Rva002D9C2F *)&veterancyChanged)->rva002D9C2F(draw->rva004BE184().m_04);
				break;
			}
			((Rva002D9531 *)&veterancyChanged)->rva002D9531(getObject()->getID());
			TheAudio->addAudioEvent(&veterancyChanged);
		}

		Object *obj = getObject();
		Drawable *selected = TheInGameUI->getFirstSelectedDrawable();
		if (selected)
		{
			Object *checkFrontObj = selected->getObject();
			if (checkFrontObj == obj)
			{
				TheControlBar->markUIDirty();
			}
			else
			{
				const Object *containObj = obj->getContainedBy();
				if (containObj && TheInGameUI->getSelectCount() == 1)
				{
					if (checkFrontObj == containObj)
						TheControlBar->markUIDirty();
				}
			}
		}
	}

	Real oldBonus = TheWritableGlobalData->m_healthBonus[oldLevel];
	Real newBonus = TheWritableGlobalData->m_healthBonus[newLevel];
	Real mult = newBonus / oldBonus;
	setMaxHealth(m_maxHealth * mult, PRESERVE_RATIO);

	switch (newLevel)
	{
	case LEVEL_REGULAR:
		clearArmorSetFlag(ARMORSET_VETERAN);
		clearArmorSetFlag(ARMORSET_ELITE);
		clearArmorSetFlag(ARMORSET_HERO);
		break;
	case LEVEL_VETERAN:
		setArmorSetFlag(ARMORSET_VETERAN);
		clearArmorSetFlag(ARMORSET_ELITE);
		clearArmorSetFlag(ARMORSET_HERO);
		break;
	case LEVEL_ELITE:
		clearArmorSetFlag(ARMORSET_VETERAN);
		setArmorSetFlag(ARMORSET_ELITE);
		clearArmorSetFlag(ARMORSET_HERO);
		break;
	case LEVEL_HEROIC:
		clearArmorSetFlag(ARMORSET_VETERAN);
		clearArmorSetFlag(ARMORSET_ELITE);
		setArmorSetFlag(ARMORSET_HERO);
		break;
	}
}

static inline const Real &healthMax(const Real &a, const Real &b)
{
	return a > b ? a : b;
}








void ActiveBody::internalChangeHealth(Real delta, DamageInfo *damageInfo)
{
	m_prevHealth = m_currentHealth;
	m_currentHealth += delta;

	Real maxHealth = m_maxHealth;
	if (m_currentHealth > maxHealth)
	{
		m_currentHealth = maxHealth;
		for (Int i = 0; i < 4; ++i)
			m_damageStateValues[i] = 0.0f;
	}
	else if (m_prevHealth == 0.0f)
	{
		Real v = getMaxHealth() * 0.25f;
		v = v * 0.75f - 1.0f;
		for (Int i = 0; i < 4; ++i)
			m_damageStateValues[i] = v;
	}
	else if (delta > 0.0f)
	{
		Real reduce = delta * 0.25f;
		reduce *= 0.75f;
		for (Int i = 0; i < 4; ++i)
		{
			m_damageStateValues[i] -= reduce;
			m_damageStateValues[i] = healthMax(0.0f, m_damageStateValues[i]);
		}
	}

	if (m_currentHealth < 0.0f)
		m_currentHealth = 0.0f;

	BodyDamageType oldState = m_curDamageState;
	Int oldField34 = m_field34;
	rvaSlot21(0);

	Object *us = getObject();
	if (m_curDamageState != oldState || m_field34 != oldField34)
	{
		if (m_currentHealth <= 0.0f || !us->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			rvaSlot36();
	}

	us->setEffectivelyDead(m_currentHealth <= 0.0f);

	if (m_linkedObjectID)
	{
		Object *other = TheGameLogic->findObjectByID(m_linkedObjectID);
		if (other)
		{
			BodyModuleInterface *body = other->getBodyModule();
			if (body)
			{
				body->rvaSlot40(m_currentHealth, delta > 0.0f);
				other->m_field280 = getObject()->m_field280;
			}
		}
	}
}






Bool ActiveBody::shouldRetaliate(Object *obj)
{
	const ThingTemplate *tmpl = obj->getTemplate();
	if (tmpl->testKindOf(173))
		return false;
	if (tmpl->testKindOf(2))
		return false;

	AIUpdateInterface *ai = obj->getAI();
	if (ai != 0 && ai->m_field34 != 0)
		return false;
	AIUpdateInterface *aiForIdle = obj->getAI();
	if (aiForIdle == 0 || !aiForIdle->isIdle())
		return false;

	if (obj->rva0028F518())
		return false;

	if (obj->testStatusBit(15) && !obj->testStatusBit(17))
		return false;

	if (obj->testStatus(OBJECT_STATUS_24))
		return false;
	return true;
}





void ActiveBody::rva004BE69C()
{
	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	switch (m_curDamageState)
	{
	case BODY_DAMAGED:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->addAttributeModifierToPool(md->m_damagedAttributeModifier, -1);
		break;
	case BODY_REALLYDAMAGED:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->removeAttributeModifierFromPool(md->m_damagedAttributeModifier);
		if (!((const StringBase<char> &)md->m_reallyDamagedAttributeModifier).isEmpty())
			getObject()->addAttributeModifierToPool(md->m_reallyDamagedAttributeModifier, -1);
		return;
	default:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->removeAttributeModifierFromPool(md->m_damagedAttributeModifier);
		break;
	}
	if (!((const StringBase<char> &)md->m_reallyDamagedAttributeModifier).isEmpty())
		getObject()->removeAttributeModifierFromPool(md->m_reallyDamagedAttributeModifier);
}






template <int NUMBITS>
void BitFlags<NUMBITS>::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	if (xfer->IsLightCRC())
	{
		((Rva004BE722 *)this)->rva004BE722(xfer);
	}
	else if (xfer->IsStoring())
	{
		Int c = count();
		*xfer == c;
		for (Int i = 0; i < NUMBITS; ++i)
		{
			const char *bitName = getBitNameIfSet(i);
			if (bitName == 0)
				continue;
			AsciiString bitNameA = bitName;
			*xfer == bitNameA;
			--c;
		}
	}
	else
	{
		clear();
		Int c;
		*xfer == c;
		AsciiString string;
		for (Int i = 0; i < c; ++i)
		{
			*xfer == string;
			Bool ok = setBitByName(string.str());
			if (ok == false)
				throw XferException(0, 0);
		}
	}
}









void ActiveBody::xfer(Xfer *xfer)
{
	BodyModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	*xfer == m_currentHealth;
	*xfer == m_prevHealth;
	*xfer == m_maxHealth;
	*xfer == m_damagedRatio;
	*xfer == m_reallyDamagedRatio;
	*xfer == m_initialHealth;
	XferBodyDamageType(xfer, (Int *)&m_curDamageState);
	XferBodySideDestroyedType(xfer, &m_field34);
	*xfer == m_nextDamageFXTime;
	XferDamageFXType(xfer, &m_lastDamageFXDone);
	DamageInfo *lastDamageInfo = &m_lastDamageInfo;
	lastDamageInfo->xfer(xfer);
	*xfer == m_lastDamageTimestamp;
	*xfer == m_lastHealingTimestamp;
	*xfer == m_frontCrushed;
	*xfer == m_backCrushed;
	*xfer == m_lastDamageCleared;
	*xfer == m_indestructible;

	if (!xfer->IsCRC())
	{
		BodyParticleSystem *system;
		UnsignedShort particleSystemCount = 0;
		for (system = m_particleSystems; system; system = system->m_next)
			particleSystemCount++;
		*xfer == particleSystemCount;

		if (xfer->IsStoring())
		{
			for (system = m_particleSystems; system; system = system->m_next)
				XferParticleSystemID(xfer, (Int *)&system->m_particleSystemID);
		}
		else
		{
			ParticleSystemID particleSystemID;
			if (m_particleSystems != 0)
				throw XferException(5, 0);
			for (UnsignedShort i = 0; i < particleSystemCount; ++i)
			{
				XferParticleSystemID(xfer, (Int *)&particleSystemID);
				BodyParticleSystem *newEntry = new BodyParticleSystem;
				newEntry->m_particleSystemID = particleSystemID;
				newEntry->m_next = m_particleSystems;
				m_particleSystems = newEntry;
			}
		}
	}

	for (Int i = 0; i < 4; ++i)
	{
		*xfer == m_damageStateValues[i];
		*xfer == m_damageStateFlags[i];
	}
	m_curArmorSetFlags.xfer(xfer);
	XferObjectID(xfer, &m_linkedObjectID);
}








Int Rva004BDA29::rva004BDA29() const
{
	if (m_health == 0.0f)
		return 3;
	else if (m_reallyDamagedThresh * m_maxHealth >= m_health)
		return 2;
	else if (m_damagedThresh * m_maxHealth >= m_health)
		return 1;
	else
		return 0;
}

void ActiveBody::setCorrectDamageState(Bool arg)
{
	BodyDamageType oldState = m_curDamageState;
	m_curDamageState = (BodyDamageType)((const Rva004BDA29 *)this)->rva004BDA29();
	if (m_curDamageState != oldState)
		rva004BE69C();

	Object *obj = getObject();
	if (obj->getTemplate()->testKindOf(60))
	{
		if (m_curDamageState < BODY_RUBBLE)
		{
			if (oldState == BODY_RUBBLE)
				obj->rva0029895A((BfmeCopyElementA *)&obj->getTemplate()->getTemplateGeometryInfo());
		}
		else
		{
			obj->rva0028ABFC(TheWritableGlobalData->m_defaultStructureRubbleHeight);
		}

		if (m_curDamageState > oldState && m_curDamageState == BODY_RUBBLE)
		{
			TheAI->pathfinder()->RemoveObjectFromPathfindMap(getObject());
			getObject()->setStatus(OBJECT_STATUS_4, true);
			getObject()->setStatus(OBJECT_STATUS_77, true);
			BfmeObjE15 &geom = getObject()->m_geometry;
			Int count = geom.getNumShapes();
			for (Int i = 0; i < count; ++i)
			{
				BfmeShapeE15 *shape = geom.bfmeAtE15(i);
				if (((const StringBase<char> &)shape->m_name).compare("Bookend") == 0)
				{
					((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 0);
					m_curDamageState = BODY_PRISTINE;
					getObject()->rva0028AB75(true);
					m_curDamageState = BODY_RUBBLE;
					getObject()->setStatus(OBJECT_STATUS_83, true);
					break;
				}
			}
		}
		else if (m_curDamageState < oldState && m_curDamageState == BODY_PRISTINE)
		{
			TheAI->pathfinder()->RemoveObjectFromPathfindMap(getObject());
			getObject()->setStatus(OBJECT_STATUS_77, false);
			getObject()->setStatus(OBJECT_STATUS_83, false);
			TheAI->pathfinder()->AddObjectToPathfindMap(getObject());
		}
		else if (m_curDamageState < oldState && oldState == BODY_RUBBLE)
		{
			getObject()->setStatus(OBJECT_STATUS_77, true);
			getObject()->setStatus(OBJECT_STATUS_83, false);
			TheAI->pathfinder()->RemoveObjectFromPathfindMap(getObject());
			BfmeObjE15 &geom = getObject()->m_geometry;
			((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 1);
			getObject()->rva0028AB75(true);
			getObject()->setStatus(OBJECT_STATUS_4, false);
		}
		m_field34 = 0;
	}
	else if (getObject()->getTemplate()->testKindOf(7))
	{
		if (m_curDamageState > oldState && m_curDamageState == BODY_RUBBLE)
		{
			BfmeObjE15 &geom = obj->m_geometry;
			Int count = geom.getNumShapes();
			for (Int i = 0; i < count; ++i)
			{
				BfmeShapeE15 *shape = geom.bfmeAtE15(i);
				if (((const StringBase<char> &)shape->m_name).compare("Bookend") == 0)
				{
					((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 0);
					m_curDamageState = BODY_PRISTINE;
					getObject()->rva0028AB75(true);
					m_curDamageState = BODY_RUBBLE;
					getObject()->setStatus(OBJECT_STATUS_83, true);
					break;
				}
			}
		}
		if (m_curDamageState < BODY_RUBBLE && oldState == BODY_RUBBLE)
		{
			obj->rva0028ABFC(getObject()->getTemplate()->getTemplateGeometryInfo().getMaxHeightAbovePosition());
			TheAI->pathfinder()->AddObjectToPathfindMap(obj);
			obj->setStatus(OBJECT_STATUS_4, false);
		}
		else if (m_curDamageState == BODY_RUBBLE)
		{
			Real rubbleHeight = getObject()->getTemplate()->getStructureRubbleHeight();
			if (rubbleHeight <= 0.0f)
				rubbleHeight = TheWritableGlobalData->m_defaultStructureRubbleHeight;
			obj->rva0028ABFC(rubbleHeight);
			TheAI->pathfinder()->RemoveObjectFromPathfindMap(obj);
			TheAI->pathfinder()->AddObjectToPathfindMap(obj);
			((Rva004BDA67 *)this)->rva004BDA67();
			obj->setStatus(OBJECT_STATUS_4, true);
			m_field34 = 0;
			return;
		}
	}

	if (!getObject()->isKindOf(KINDOF_4))
		return;
	if (oldState != m_curDamageState && !arg)
		return;

	Real threshold = 0.75f * (getMaxHealth() * 0.25f);
	if (!m_damageStateFlags[0] && m_damageStateValues[0] >= threshold)
	{
		m_field34 = 1;
		m_damageStateFlags[0] = true;
	}
	else if (!m_damageStateFlags[1] && m_damageStateValues[1] >= threshold)
	{
		m_field34 = 2;
		m_damageStateFlags[1] = true;
	}
	else if (!m_damageStateFlags[2] && m_damageStateValues[2] >= threshold)
	{
		m_field34 = 3;
		m_damageStateFlags[2] = true;
	}
	else if (!m_damageStateFlags[3] && m_damageStateValues[3] >= threshold)
	{
		m_field34 = 4;
		m_damageStateFlags[3] = true;
	}
	else
	{
		return;
	}
	if (!arg)
	{
		for (DamageCreation *it = m_damageCreationBegin; it != m_damageCreationEnd; ++it)
		{
			DamageCreation c = *it;
			if (c.m_stage == m_field34 && c.m_ocl)
				c.m_ocl->create(getObject(), 0, 0);
		}
	}
}




struct ActiveBodySidePoint
{
	Real x, y, z;
	ActiveBodySidePoint() {}
	ActiveBodySidePoint(const ActiveBodySidePoint &r)
	{ x = r.x; y = r.y; z = r.z; }
	~ActiveBodySidePoint() {}
};
struct ActiveBodyDamageVector
{
	Real x, y, z;
	ActiveBodyDamageVector(Real a, Real b, Real c) : x(a), y(b), z(c) {}
};

extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file, Int line);
#define GameLogicRandomValueReal(lo, hi) \
	GetGameLogicRandomValueReal((lo), (hi), __FILE__, __LINE__)




void ActiveBody::rva004BFCD4(Real amount, DamageInfo *damageInfo)
{
	Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	if (source)
	{
		ActiveBodySidePoint pos;
		pos.x = source->m_transform[0][3];
		pos.y = source->m_transform[1][3];
		pos.z = source->m_transform[2][3];
		rva004BFB1C(amount, (const Coord3D *)&pos);
	}
}





void ActiveBody::setInitialHealth(Real initialPercent, Bool directional)
{
	if (initialPercent > 100.0f)
		m_maxHealth = m_maxHealth * initialPercent * 0.01f;
	Real factor = initialPercent * 0.01f;
	if (directional)
	{
		m_prevHealth = m_currentHealth;
		m_currentHealth += m_maxHealth * (initialPercent * 0.01f) - m_currentHealth;
		ActiveBodySidePoint pos(*(const ActiveBodySidePoint *)getObject()->getPosition());
#line 1279 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		pos.x += GameLogicRandomValueReal(-1.0f, 1.0f);
		pos.y += GameLogicRandomValueReal(-1.0f, 1.0f);
		pos.z += GameLogicRandomValueReal(-1.0f, 1.0f);
		ActiveBodyDamageVector jittered(pos.x, pos.y, pos.z);
		rva004BFB1C((1.0f - initialPercent * 0.01f) * m_maxHealth, (const Coord3D *)&jittered);
	}
	else
	{
		internalChangeHealth(factor * m_initialHealth - m_currentHealth, 0);
	}
}






ArmorSetFlags ActiveBody::rva004BF8F5() { return m_curArmorSetFlags; }
ObjectID ActiveBody::rva004BF897() { if (m_lastDamageCleared) return INVALID_ID; m_lastDamageCleared=true; return m_lastDamageInfo.in.m_sourceID; }
Bool ActiveBody::getBackCrushed() const { return m_backCrushed; }
BfmeBodyDataPair8 ActiveBody::rva004BDC56() { return getActiveBodyModuleData()->m_pair40; }







void ActiveBody::setArmorSetFlag(ArmorSetType ast) { m_curArmorSetFlags.set((unsigned)ast); }
void ActiveBody::clearArmorSetFlag(ArmorSetType ast) { m_curArmorSetFlags.reset((unsigned)ast); }








class Vector3
{
public:
	float X, Y, Z;
	Vector3() {}
	Vector3(const Vector3 &r) { X = r.X; Y = r.Y; Z = r.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &r)
	{ X = r.X; Y = r.Y; Z = r.Z; return *this; }
	Vector3 operator-() const { return Vector3(-X, -Y, -Z); }
	static float Dot_Product(const Vector3 &a, const Vector3 &b)
	{ return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
};
inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{ return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }

class Vector4
{
public:
	float X, Y, Z, W;
	Vector4() {}
	Vector4(const Vector4 &r) { X = r.X; Y = r.Y; Z = r.Z; W = r.W; }
	__forceinline Vector4 &operator=(const Vector4 &r)
	{ X = r.X; Y = r.Y; Z = r.Z; W = r.W; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
};

class Matrix3D
{
public:
	Vector4 Row[3];
	__forceinline Matrix3D(const Matrix3D &m)
	{ Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }
	Vector3 Get_X_Vector() const
	{ return Vector3(Row[0][0], Row[1][0], Row[2][0]); }
	Vector3 Get_Y_Vector() const
	{ return Vector3(Row[0][1], Row[1][1], Row[2][1]); }
	Vector3 Get_Translation() const
	{ return Vector3(Row[0][3], Row[1][3], Row[2][3]); }
};








void ActiveBody::rva004BFB1C(Real amount, const Coord3D *pos)
{
	const Matrix3D matrix = *(const Matrix3D *)getObject()->m_transform;
	Vector3 forward = matrix.Get_X_Vector();
	Vector3 dir(matrix.Row[0][3] - pos->x,
		matrix.Row[1][3] - pos->y, matrix.Row[2][3] - pos->z);
	Real sides[4];
	sides[0] = Vector3::Dot_Product(-forward, dir);
	sides[1] = Vector3::Dot_Product(matrix.Get_Y_Vector(), dir);
	sides[2] = -sides[0];
	sides[3] = -sides[1];

	_STL::vector<long> order;
	for (long i = 0; i < 4; ++i)
	{
		Bool inserted = false;
		for (_STL::vector<long>::iterator it = order.begin(); it != order.end(); ++it)
		{
			Int other = *it;
			if (sides[i] > sides[other])
			{
				order.insert(it, i);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			order.push_back(i);
	}

	Real maxPerSide = getMaxHealth() * 0.25f;
	maxPerSide *= 0.75f;
	Real remaining = amount;
	for (Int k = 0; remaining > 0.0f; ++k)
	{
		if (k >= 4)
			break;
		Real &health = m_damageStateValues[order[k]];
		Real room = maxPerSide - health;
		Real take = _STL::min(remaining, room);
		if (take > 0.0f)
		{
			health = health + take;
			remaining -= take;
		}
	}
}

static inline const Real &healthMin(const Real &a,const Real &b) { return b<a?b:a; }














void ActiveBody::attemptDamage(DamageInfo *damageInfo)
{
	validateArmorAndDamageFX();

	Object *obj = getObject();
	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	if (damageInfo == 0)
		return;
	if (m_indestructible)
		return;
	if (obj->isKindOf(KINDOF_14A))
		return;
	if (obj->testStatus(OBJECT_STATUS_60) && damageInfo->in.m_damageType != DAMAGE_UNRESISTABLE)
		return;

	Object *container = obj->getContainedBy();
	if (container && !obj->getTemplate()->testKindOf(55) && container->getContain())
		container->getContain()->onContainedDamage(obj, this, damageInfo);

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;

	if (obj->m_flags438 & 1)
		return;

	Real amount = m_curArmor.adjustDamage(&damageInfo->in, obj, false);
	switch (damageInfo->in.m_damageType)
	{
	case DAMAGE_HEALING:
		if (!damageInfo->in.m_kill)
			attemptHealing(damageInfo);
		return;
	}
	if (damageInfo->in.m_damageType != DAMAGE_UNRESISTABLE)
		amount *= m_damageScalar;

	Object *damager = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	if (damager && damager->testStatus(OBJECT_STATUS_65))
	{
		Object *resolved = damager->rva002931F5(false);
		if (resolved)
		{
			Rva0028C1A9Result *result = (Rva0028C1A9Result *)resolved->rva0028C1A9();
			if (result && result->shouldKill(obj))
			{
				damageInfo->in.m_kill = true;
				result->onKill(obj);
			}
		}
	}

	Rva004BFE07ContainHelper *helper = 0;
	Bool clipped = false;
	if (amount > 0.0f || damageInfo->in.m_kill)
	{
		Object *outer = obj->getContainedBy();
		if (outer)
			helper = outer->getContain()->getDamageHelper();

		static const KindOfMaskType s_unclippedKinds(0, 0x81, 0x67, 0x69);
		static const ObjectStatusMaskType s_unclippedStatus(0, 0x3A, 0x3D, 0x5A);
		if (obj->getAI() && md->m_byte51
			&& !((const Rva00331682Holder *)&s_unclippedStatus)->test(&obj->m_status)
			&& !((const Rva00263546 *)&s_unclippedKinds)->rva00263546((const Rva00263546 *)obj->m_kindOfMask)
			&& (damageInfo->in.m_damageType == DAMAGE_6 || damageInfo->in.m_damageType == DAMAGE_23)
			&& !(obj->m_field25C && obj->m_field25C->m_byte5C)
			&& (!outer || helper))
		{
			Real limit = getHealth() - 1.0f;
			Real clippedAmount = healthMin(limit, amount);
			if (clippedAmount != amount)
			{
				amount = clippedAmount;
				clipped = true;
			}
		}

		BodyDamageType oldState = m_curDamageState;
		if (damageInfo->in.m_kill)
			amount = m_currentHealth;

		if (damageInfo->in.m_damageType == DAMAGE_4)
			rva004BFCD4(amount, damageInfo);

		internalChangeHealth(0.0f - amount, damageInfo);

		if (md->m_damageDelayFrames > 0)
			((Gen_003bcb40 *)obj)->m(TheGameLogic->getFrame() + md->m_damageDelayFrames);

		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;

		if (m_lastDamageTimestamp != TheGameLogic->getFrame() && m_lastDamageTimestamp != TheGameLogic->getFrame() - 1)
		{
			*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
			m_lastDamageCleared = false;
			m_lastDamageTimestamp = TheGameLogic->getFrame();
		}
		else
		{
			Object *srcObj1 = TheGameLogic->findObjectByID(m_lastDamageInfo.in.m_sourceID);
			Object *srcObj2 = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
			if (srcObj2)
			{
				if (srcObj1)
				{
					if (srcObj2->getTemplate()->testKindOf(9) || srcObj2->getTemplate()->testKindOf(8)
						|| srcObj2->rva0028D491())
					{
						*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
						m_lastDamageCleared = false;
						m_lastDamageTimestamp = TheGameLogic->getFrame();
					}
				}
				else
				{
					*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
					m_lastDamageCleared = false;
					m_lastDamageTimestamp = TheGameLogic->getFrame();
				}
			}
		}

		Object *srcObj = 0;
		if (m_lastDamageInfo.in.m_sourceID != INVALID_ID)
		{
			srcObj = TheGameLogic->findObjectByID(m_lastDamageInfo.in.m_sourceID);
			if (srcObj)
				((Rva002AA201IndexedByteField *)obj->getControllingPlayer())->set(srcObj->getControllingPlayer()->getPlayerIndex());
		}

		if (m_currentHealth < m_prevHealth)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onDamage(damageInfo);
			}

			if (damager)
				damager->rva0028B1D4((Int)damageInfo, (Int)obj);
		}

		if (m_curDamageState != oldState)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}

			if (m_curDamageState == BODY_DAMAGED && md->m_damagedDisableFrames > 0.0f)
				obj->setDisabledUntil(DISABLED_8, TheGameLogic->getFrame() + md->m_damagedDisableFrames);
			else if (m_curDamageState == BODY_REALLYDAMAGED && md->m_reallyDamagedDisableFrames > 0.0f)
				obj->setDisabledUntil(DISABLED_8, TheGameLogic->getFrame() + md->m_reallyDamagedDisableFrames);

			Drawable *draw = obj->getDrawable();
			if (draw)
			{
				if (m_curDamageState == BODY_DAMAGED)
				{
					BfmeAudioEventPrefix136 damaged(draw->rva004BE120().m_04, 0);
					((Rva002D9531 *)&damaged)->rva002D9531(obj->getID());
					TheAudio->addAudioEvent(&damaged);
				}
				else if (m_curDamageState == BODY_REALLYDAMAGED)
				{
					BfmeAudioEventPrefix136 reallyDamaged(draw->rva004BE139().m_04, 0);
					((Rva002D9531 *)&reallyDamaged)->rva002D9531(obj->getID());
					TheAudio->addAudioEvent(&reallyDamaged);
				}
			}

			if (m_linkedObjectID)
			{
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked && linked->getBodyModule())
					linked->getBodyModule()->rvaSlot39(m_curDamageState);
			}
		}

		if (m_prevHealth / m_maxHealth >= 0.35f && m_currentHealth / m_maxHealth < 0.35f && m_currentHealth > 0.0f)
		{
			DrawableList drawList;
			drawList.push_back(obj->getDrawable());
			pickAndPlayUnitVoiceResponse(&drawList, GameMessage::MSG_BFME2_0x7E0, 0);
		}

		if (clipped || (m_currentHealth <= 0.0f && m_prevHealth > 0.0f))
		{
			if (damager)
				((Rva00294D61 *)damager)->report(obj, 1);

			if (!clipped)
			{
				static NameKeyType s_respawnKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
				if (!obj->findModule(s_respawnKey))
				{
					Object *outerObj = obj->getContainedBy();
					Bool contained = outerObj != 0;
					if (contained && outerObj->getContain() && outerObj->getContain()->getContainCount(0) < 2)
						contained = false;

					obj->onDie(damageInfo);

					if (m_linkedObjectID)
					{
						Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
						if (linked)
						{
							linked->onDie(damageInfo);
							linked->setEffectivelyDead(true);
						}
					}

					if (!contained && damageInfo->in.m_sourceID != INVALID_ID
						&& !obj->getTemplate()->testKindOf(25) && !obj->getTemplate()->testKindOf(89))
						rva004BF9ED();
				}
			}
		}

		if (damager)
		{
			Real ratio = damageInfo->m_actualDamageClipped / m_maxHealth;
			if (ratio > 1.0f)
				ratio = 1.0f;
			if (ratio > 0.0f)
				((Rva0028B749Host *)damager)->rva0028B749((Int)obj, ratio);
		}

		DelayedLuaEventList events;
		if (srcObj)
		{
			events.m_events[0].m_value = srcObj->getID();
			events.m_events[0].m_type = 3;
		}
		((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(0, obj, (BfmeDelayedLuaEventList *)&events);
	}

	doDamageFX(damageInfo);

	if (TheAI->getAiData()->m_enableRepulsors && obj->getTemplate()->testKindOf(45))
		obj->setStatus(OBJECT_STATUS_8, true);

	if (clipped)
	{
		if (helper)
			helper->onClippedDamage(obj);
		if (obj->getAI()->rva002632C7Bool())
			obj->getAI()->rva002632E1();
		obj->getAI()->getCommandInterface()->rva004BFD27(CMD_FROM_AI);
		if (md && md->m_clippedDamageFX)
			FXList::doFXObj(md->m_clippedDamageFX, obj, 0);
	}
}
