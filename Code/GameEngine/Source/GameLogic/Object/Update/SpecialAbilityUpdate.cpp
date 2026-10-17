// cl: /O1 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// SpecialAbilityUpdate.cpp: bodies retail links from this TU (tu_map approved),
// folded from three split units with these exact flags. The two
// address-named helper classes keep their names (their rows are mangled with
// them); Object and Overridable are shared views: object model-condition
// words at +0x10C and the status-base pointer at +0x04, final-override kind
// at +0x1C.

#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_18 = 0x18,
	OBJECT_STATUS_46 = 0x46
};
enum KindOfType
{
	KINDOF_INVALID = -1
};
enum SpecialPowerType {};
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
class Module;
class Drawable
{
public:
	void rva002723C0(int frames);		// rowed: the animation length in frames
};
class Thing
{
public:
	Drawable *getDrawable() const;
	void setOrientation(float);
};
class Player
{
public:
	bool isLocalPlayer() const;
};
enum EvaEventID { EVA_EVENT_STUB = 0 };
class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *secondPosition);
};
extern Eva *TheEva;
// The one-Drawable list the voice responses hand out; its destructor is the
// shared out-of-line pointer-list destructor 0x00239AF4.
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	void *m_specialPowerTemplate; // +0x0C
	const void *m_10; // +0x10
	Coord3D m_position;
	unsigned int m_unmodelled_20;
};
class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DD = 0x7DD,
		MSG_BFME2_0x7DE = 0x7DE
	};
};
bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);
// The rowed setter that stamps an audio event with its owning object.
class Rva002D9531
{
public:
	void rva002D9531(int objectID);
};
// The rowed two-bit mask builder (0x001E4912) behind the pack conditions.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned int m_bits[19];
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
class Object;
class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms);
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPositionSA(const Coord3D *pos, int cmdSource);
	void rva0044FFD9(Object *obj, CommandSourceType cmdSource);
	void rva0045003E(int value, CommandSourceType cmdSource);
};
// AIUpdateInterface: an update module whose AICommandInterface base is at +0x20.
class AIUpdateModuleView
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual bool rvaSlot168(); // +0x168
	unsigned char m_pad04[0x20 - 4];
};
class AIUpdateInterface : public AIUpdateModuleView, public AICommandInterface
{
public:
	void ignoreObstacle(const Object *obj);
};
class Object;
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
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void useTarget(Object *target); // slot 59 (+0xEC)
};
class SpecialPowerModuleInterface
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
	virtual void markSpecialPowerTriggered(const Coord3D *location); // slot 14 (+0x38)
};
// The rowed two-bit status mask (0x00391F4E) read as the status setter's mask.
class Rva00346BC0;
class Rva00391F4E
{
public:
	Rva00391F4E(int a, int b, int c);
	unsigned int m_bits[4];
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Rva00373EC6;
// Container whose flag byte +0x115 bit 0x20 redirects the special target.
struct ApproachTargetContainer
{
	unsigned char m_pad00[4];
	unsigned char *m_data; // +0x04
	unsigned char m_pad08[0x74 - 8];
	unsigned int m_targetID; // +0x74
};
class Object : public Thing
{
	friend class SpecialAbilityUpdate;
public:
	Rva00373EC6 *rva0028F4BC();
	Player *getControllingPlayer() const;
	bool isLocallyControlled() const;
	Relationship getRelationship(const Object *that) const;
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	bool isKindOf(KindOfType kindOf) const;
	int rva0028B511() const;
	bool getWorldspaceBestContactPoint(Coord3D *pos, const Coord3D *from, const char *bone, int a, int b, bool c) const;
	// rowed 0x0028CFB2: clears the first mask's conditions, sets the second's
	void rva0028CFB2(const int *clearMask, const int *setMask);
	// Zero Hour's inline Object::clearAndSetModelConditionState.
	void clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028AE6D();
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[4];
	unsigned char *m_base4; // +0x04 status base (bytes +0x108/+0x114 read)
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position; // +0x38
	float m_orientation44; // +0x44: native orientation used by the packing flips
	unsigned char m_pad048[0x74 - 0x48];
	int m_id; // +0x74
	unsigned char m_pad078[8];
	int m_captor80; // +0x80: native captor ID
	unsigned char m_pad084[0x10C - 0x84];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	unsigned char *m_ai; // +0x258 AIUpdateInterface (command interface at +0x20)
	AIUpdateInterface *getAI() const { return (AIUpdateInterface *)m_ai; }
	void *getTeam() const { return m_team; }
	unsigned char m_pad25C[0x274 - 0x25C];
	ApproachTargetContainer *m_targetContainer; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	void *m_team; // +0x304
	unsigned char m_pad308[0x484 - 0x308];
	unsigned int m_specialTargetID; // +0x484
protected:
	Module *findModule(NameKeyType key) const;
};
class SpecialDisguiseUpdate
{
public:
	void rva004B05F5(bool disguise);
};
struct Rva004CE41ECondition
{
	ModelConditionFlagType m_type; // +0x00
	unsigned int m_frames; // +0x04
};
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
	unsigned char m_pad20[0x44 - 0x20];
	int m_evaEvent44; // +0x44
};
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x8];
	OpaqueRefElement4 m_packSound; // +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	OpaqueRefElement4 m_prepSoundLoop; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
	unsigned int m_20; // +0x20
	unsigned char m_pad24[0x38 - 0x24];
	Overridable *m_specialPowerTemplate; // +0x38
	unsigned char m_pad3C[0x4C - 0x3C];
	float m_approachRange; // +0x4C
	unsigned char m_pad50[0x54 - 0x50];
	float m_packUnpackVariationFactor; // +0x54
	unsigned char m_pad58[0x6C - 0x58];
	int m_6C; // +0x6C ability condition selector (1..6)
	unsigned char m_pad70[0x74 - 0x70];
	unsigned int m_preparationFrames; // +0x74
	unsigned char m_pad78[0x84 - 0x78];
	unsigned int m_packTime; // +0x84
	unsigned int m_unpackTime; // +0x88
	unsigned int m_preTriggerUnstealthFrames; // +0x8C
	unsigned char m_pad090[0xAC - 0x90];
	bool m_flipAfterPacking; // +0xAC
	bool m_flipAfterUnpacking; // +0xAD
	char m_pad0AE[2];
	bool m_loseStealth; // +0xB0
	unsigned char m_padB1[0xBC - 0xB1];
	AsciiString m_targetBone; // +0xBC
};
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
typedef unsigned int AudioHandle;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
	unsigned int getFrame() const { return m_frame; }
};
class AudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *event); virtual void vslot26();
	virtual void removeAudioEvent(AudioHandle handle); // slot 27 (+0x6C)
};
extern AudioManager *TheAudio;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class Rva0044E9C7
{
public:
	Rva0044E9C7 *rva0044E9C7(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o);
	unsigned int m_bits[19];
};
class Rva0028F59A
{
public:
	Rva0028F59A(int a, int bit);
	unsigned int m_bits[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
__forceinline void Object::clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set)
{
	rva0028CFB2((const int *)&Rva0028F59A(0, clr), (const int *)&Rva0028F59A(0, set));
}
class SpecialAbilityUpdate : public BehaviorModule
{
public:
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void onExit(bool cleanup, bool b); // +0x34
	SpecialPowerType getSpecialPowerType() const;
	bool rva00450AE9();
	bool rva0044E85E(Coord3D *pos, float range);
protected:
	bool handlePackingProcessing();
public:
	void rva0044EE07();
	void rva0044EE80();
	void rva0044F72E();
	virtual void v14();
	virtual void startPreparation();
	virtual void startPacking(bool success);
protected:
public:
	Object *rva0044FEB6();
protected:
	bool initLaser(Object *specialObject, Object *target);
public:
	virtual void startUnpacking();
protected:
	void endPreparation();
private:
	unsigned char m_pad0C[0x28 - 0x0C];
	unsigned int m_animFrames; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	int m_packingState; // +0x30
	AudioHandle m_prepSoundLoop; // +0x34
	AudioHandle m_packSoundHandle; // +0x38
	unsigned int m_prepFrames; // +0x3C
	ObjectID m_targetID; // +0x40
	Coord3D m_targetPos; // +0x44
	Coord3D m_previousTarget; // +0x50
	unsigned char m_pad5C[0x78 - 0x5C];
	unsigned int m_approachFrames; // +0x78
	unsigned char m_pad7C[0x83 - 0x7C];
	bool m_approached; // +0x83
	unsigned int m_84; // +0x84
};

extern GameLogic *TheGameLogic;

class Rva0044F633Inner
{
public:
	char m_pad0[0x38];
	Overridable *m_override38;
	char m_pad1[0x74 - 0x38 - 4];
	void *m_fallback74;
};

class Rva0044F633
{
public:
	void *rva0044F633();

private:
	char m_pad0[4];
	Rva0044F633Inner *m_inner4;
	char m_pad1[0x40 - 8];
	ObjectID m_target40;
};

// Retail 0x0044EE07 (121 bytes): SpecialAbilityUpdate::rva0044EE07, the
// partner of rva0044EE80 below (same module data +0x18/+0x1C pair). Clears the
// fourteen ability model conditions (0x60 0x5E 0x29 0x76 0x5F 0x84 0x61..0x63
// 0x249..0x24B 0x6E 0x6F) on the Object through the rowed mask clear 0x001E42F2
// with the rowed 0x0044E9C7 mask builder, then, for an untimed module-data
// condition, clears that one through the one-bit mask ctor 0x0028F59A and
// zeroes +0x84. Called by 0x004500A3 with the module as this.
void SpecialAbilityUpdate::rva0044EE07()
{
	{
		Rva0044E9C7 mask;
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)mask.rva0044E9C7(0,
			0x60, 0x5e, 0x29, 0x76, 0x5f, 0x84, 0x61, 0x62, 0x63,
			0x249, 0x24a, 0x24b, 0x6e, 0x6f));
	}
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	if (data->m_18 != MODELCONDITION_INVALID && data->m_1C == 0)
	{
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)&Rva0028F59A(0, data->m_18));
		m_84 = 0;
	}
}

// Retail 0x0044EE80 (74 bytes): SpecialAbilityUpdate::rva0044EE80, a
// non-virtual helper called with the module as this by the SpecialAbilityUpdate
// slot-22 base 0x004508B7 and by 0x00451FA2 (SpecialAbilityUpdate block). Name
// by address. Sets the model condition named by the module data +0x18 on the
// Object (directly, notifier as a tail jump) or times it through the matched
// Object::setSpecialModelConditionState 0x0028AEB2 when the +0x1C frames are
// non-zero. Object condition words at +0x10C, masked-word accessors.
void SpecialAbilityUpdate::rva0044EE80()
{
	Object *object = m_object;
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	ModelConditionFlagType mc = data->m_18;
	if (mc == MODELCONDITION_INVALID)
		return;
	if (data->m_1C == 0)
		object->setModelConditionState(mc);
	else
		object->setSpecialModelConditionState(mc, data->m_1C);
}

// WorldBuilder 10E7F90 names this const getter and reads the template's
// final-override type at1C. Native44EF2C independently proves moduleData+4,
// template+38 and owned override walk288609. BFME1 CEE35B7D's named donor
// supplies the same null-template behavior with different target offsets.
SpecialPowerType SpecialAbilityUpdate::getSpecialPowerType() const
{
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Overridable *o = data->m_specialPowerTemplate;
	if (o == 0)
		return (SpecialPowerType)0;
	return (SpecialPowerType)o->friend_getFinalOverride()->m_val1C;
}

// ?rva0044F633@Rva0044F633@@QAEPAXXZ, retail 0x0044F633, 70 bytes.
// Leaf __thiscall: reads this+4 (holder) and this+0x40 (ObjectID), resolves
// the object via TheGameLogic->findObjectByID (rowed 0x00049DC5), then checks
// the holder's Overridable final override (rowed friend_getFinalOverride
// 0x00288609) for kind 0x27 and the target's status bytes at +0x108/+0x114.
// Returns null when all checks pass, else holder+0x74. Evidence: packet
// disassembly, callee rows, TheGameLogic extern in use, SpecialAbilityUpdate
// m_40 ObjectID at +0x40 in neighbour SpecialAbilityUpdateXfer.cpp.
void *Rva0044F633::rva0044F633()
{
	Rva0044F633Inner *inner = m_inner4;
	Object *obj = TheGameLogic->findObjectByID(m_target40);
	const Overridable *ov = inner->m_override38->friend_getFinalOverride();
	if (ov->m_val1C == 0x27) {
		if (obj) {
			unsigned char *base = obj->m_base4;
			if ((base[0x108] & 0x40) == 0) {
				if ((base[0x114] & 8) == 0)
					return 0;
			}
		}
	}
	return inner->m_fallback74;
}

// Retail 0x0044F81E (99 bytes): ZH SpecialAbilityUpdate::endPreparation. Clears
// object status 0x18 via the rowed Object::setStatus, drops the prep sound loop
// handle at +0x34 through TheAudio slot 0x6C and clears model condition 0x5F
// through the rowed mask helpers 0x0028F59A / 0x001E42F2 (BFME2 additions);
// then switches on the special power type and for types 0x15 0x1A 0x1D runs
// the rowed 0x0044F72E (ZH killSpecialObjects position in the switch).
void SpecialAbilityUpdate::endPreparation()
{
	getObject()->setStatus(OBJECT_STATUS_18, false);
	TheAudio->removeAudioEvent(m_prepSoundLoop);
	((Rva001E42F2 *)getObject())->rva001E42F2((const int *)&Rva0028F59A(0, 0x5f));
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	switch (data->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C)
	{
	case 0x15:
	case 0x1a:
	case 0x1d:
		rva0044F72E();
		break;
	}
}

// SpecialAbilityUpdate::startUnpacking, retail 0x004508B7 (562 bytes, vtable
// slot 22; WeaponFireSpecialAbilityUpdate overrides it under the same name).
// Zero Hour's startUnpacking reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startUnpacking.cpp): unpack state 2, a randomised
// unpack time, conditions 94 -> 96, and a selector-chosen ability condition.
// BFME2 adds the module-data condition (+0x18) set now or timed from +0x20,
// a target-dependent condition for power type 0x28 and the disguise drop for
// power type 0x84.
void SpecialAbilityUpdate::startUnpacking()
{
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Object *self = m_object;
	m_packingState = 2;
	float variation = GetGameLogicRandomValueReal(1.0f - d->m_packUnpackVariationFactor,
		1.0f + d->m_packUnpackVariationFactor,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",
		1370);
	m_animFrames = (unsigned int)(d->m_unpackTime * variation);
	self->rva0028CFB2((const int *)&Rva0028F59A(0, 0x5e), (const int *)&Rva0028F59A(0, 0x60));
	self->setStatus(OBJECT_STATUS_46, true);
	if (d->m_6C)
	{
		switch (d->m_6C)
		{
		case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
		case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
		case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
		case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
		case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
		case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
		}
	}
	if (d->m_18 != MODELCONDITION_INVALID)
	{
		if (d->m_20 == 0)
			rva0044EE80();
		else
			m_84 = d->m_20 + TheGameLogic->getFrame();
	}
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	int type = d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C;
	if (type == 0x28)
	{
		if (target && (target->m_base4[0x118] & 0x10))
			self->setModelConditionState((ModelConditionFlagType)176);
	}
	else if (type == 0x84)
	{
		if (self->isKindOf((KindOfType)0x12c))
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
			SpecialDisguiseUpdate *disguise = (SpecialDisguiseUpdate *)self->findModule(key);
			if (disguise)
				disguise->rva004B05F5(false);
		}
	}
	Drawable *draw = self->getDrawable();
	if (draw)
		draw->rva002723C0(m_animFrames);
	unsigned char *ai = self->m_ai;
	if (ai)
		((AICommandInterface *)(ai + 0x20))->rva0045003E(0, CMD_FROM_AI);
}

// SpecialAbilityUpdate::startPacking, retail 0x00450635 (642 bytes; the
// WeaponFireSpecialAbilityUpdate slot override 0x004925DB forwards to it).
// Zero Hour's startPacking reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startPacking.cpp): pack state 1, a randomised pack
// time, conditions 96/118 -> 94, the selector condition, the pack sound with
// the old loop handle dropped, the drawable animation time, an AI command
// unless the power type is 0x2A, and on success a one-Drawable voice
// response (0x7DD for power types 0x1A/0x1D, else 0x7DE) plus an Eva event
// for the local player.
void SpecialAbilityUpdate::startPacking(bool success)
{
	Object *self = m_object;
	Player *player = self->getControllingPlayer();
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	m_packingState = 1;
	float variation = GetGameLogicRandomValueReal(1.0f - d->m_packUnpackVariationFactor,
		1.0f + d->m_packUnpackVariationFactor,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",
		1281);
	m_animFrames = (unsigned int)(d->m_packTime * variation);
	Rva001E4912 clearMask;
	self->rva0028CFB2((const int *)clearMask.rva001E4912(0, 0x60, 0x76), (const int *)&Rva0028F59A(0, 0x5e));
	self->setStatus(OBJECT_STATUS_46, true);
	if (d->m_6C)
	{
		switch (d->m_6C)
		{
		case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
		case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
		case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
		case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
		case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
		case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
		}
	}
	BfmeAudioEventPrefix136 sound(d->m_packSound, 0);
	((Rva002D9531 *)&sound)->rva002D9531(self->m_id);
	TheAudio->addAudioEvent(&sound);
	TheAudio->removeAudioEvent(m_packSoundHandle);
	m_packSoundHandle = 1;
	Drawable *draw = self->getDrawable();
	if (draw)
		draw->rva002723C0(m_animFrames);
	if (d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C != 0x2a)
	{
		unsigned char *ai = self->m_ai;
		if (ai)
			((AICommandInterface *)(ai + 0x20))->rva0045003E(0, CMD_FROM_AI);
	}
	if (success)
	{
		DrawableList list;
		list.push_back(draw);
		PickAndPlayInfo info;
		info.m_10 = d->m_specialPowerTemplate;
		if (d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C == 0x1a
			|| d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C == 0x1d)
			pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DD, &info);
		else
			pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DE, &info);
		if (player && player->isLocalPlayer())
		{
			int evaEvent = d->m_specialPowerTemplate->friend_getFinalOverride()->m_evaEvent44;
			TheEva->reportEvaEvent((EvaEventID)evaEvent, &self->m_position, 0);
		}
	}
}

// The rowed special-power-module lookup (0x0044E633), taking the update as
// this.
class Rva0044E633
{
public:
	void *rva0044E633();
};

// SpecialAbilityUpdate::rva00450AE9, retail 0x00450AE9 (689 bytes): the
// approach step. A target that has not moved 5 units in two seconds of
// approach frames exits the ability; otherwise it moves the AI to the target
// (bone contact point, offset approach position or attack-move helper) or to
// the stored position.
extern int BfmeLogicFramesPerSecond; // VA 0x00DBA4E4
// Coord3D copy whose members load before the in-place subtraction stores.
struct SaCoordCopy : Coord3D
{
	__forceinline SaCoordCopy(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	__forceinline void sub(const Coord3D *o) { x -= o->x; y -= o->y; z -= o->z; }
};
bool SpecialAbilityUpdate::rva00450AE9()
{
	Object *self=m_object;
	const SpecialAbilityUpdateModuleData *data=(const SpecialAbilityUpdateModuleData*)m_moduleData;
	if(m_approachFrames>BfmeLogicFramesPerSecond*2) {
		Coord3D target={m_targetPos.x,m_targetPos.y,m_targetPos.z};
		Object *obj=TheGameLogic->findObjectByID(m_targetID);
		if(obj) target=obj->m_position;
		SaCoordCopy delta=m_previousTarget;
		delta.sub(&target);
		if(delta.GetLength()<5.0f){onExit(false,true);return false;}
	}
	++m_approachFrames;
	m_previousTarget=m_targetPos;
	if(m_targetID!=INVALID_OBJECT_ID) {
		Object *target=TheGameLogic->findObjectByID(m_targetID);
		if(target) {
			const Coord3D *targetPos=&target->m_position;
			m_previousTarget=*targetPos;
			Overridable *spTemplate=data->m_specialPowerTemplate;
			bool moveToPosition=data->m_approachRange>50.0f;
			if(spTemplate->friend_getFinalOverride()->m_val1C==0x27){
				ApproachTargetContainer *c=target->m_targetContainer;
				if(c && (c->m_data[0x115]&0x20)) self->m_specialTargetID=c->m_targetID;
				else self->m_specialTargetID=m_targetID;
			}
			AIUpdateInterface *ai=self->getAI();
			if(ai) {
				if(!((const StringBase<char>*)&data->m_targetBone)->isEmpty()) {
					Coord3D pos={0,0,0};
					if(target->getWorldspaceBestContactPoint(&pos,&self->m_position,data->m_targetBone.str(),0,0x2A,true)){
						ai->aiMoveToPositionSA(&pos,2);return true;
					}
				}
				ai->ignoreObstacle(target);
				if(!(target->m_base4[0x108]&0x80) && target->rva0028B511()!=1 && moveToPosition){
					Coord3D pos={targetPos->x,targetPos->y,targetPos->z};
					rva0044E85E(&pos,data->m_approachRange);
					ai->aiMoveToPositionSA(&pos,2);
					return true;
				}
				ai->rva0044FFD9(target,CMD_FROM_AI);
				return true;
			}
		}
	} else if(m_targetPos.x || m_targetPos.y || m_targetPos.z){
		AIUpdateInterface *ai=self->getAI();
		if(ai) {
			int type=data->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C;
			if(type==0x38 && ai->rvaSlot168())self->setStatus((ObjectStatusTypes)0x5B,true);
			ai->aiMoveToPositionSA(&m_targetPos,2);
			if(type==0x2A)m_approached=true;
			return true;
		}
	}
	return false;
}


// SpecialAbilityUpdate::startPreparation, retail 0x00450D9A (755 bytes,
// vtable slot 15; ArrowStormUpdate overrides it). Zero Hour's
// startPreparation reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startPreparation.cpp): with preparation frames the
// container uses the target and conditions 96/118 -> 95 plus the selector
// condition; per power type the laser (0x15), the same-team guard and
// condition swap (0x1D) or the relationship guard, laser and swap (0x1A),
// each with an Eva event 0x10 for a locally controlled target; then the
// power module is marked, the AI idled, statuses 0x18/0x46 set and the
// preparation sound started.
void SpecialAbilityUpdate::startPreparation()
{
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Overridable *power = d->m_specialPowerTemplate;
	m_prepFrames = (unsigned int)((Rva0044F633 *)this)->rva0044F633();
	if (m_prepFrames)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain && target)
			contain->useTarget(target);
		Object *self = m_object;
		Rva001E4912 clearMask;
		self->rva0028CFB2((const int *)clearMask.rva001E4912(0, 0x60, 0x76), (const int *)&Rva0028F59A(0, 0x5f));
		if (d->m_6C)
		{
			switch (d->m_6C)
			{
			case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
			case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
			case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
			case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
			case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
			case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
			}
		}
	}
	int type = power->friend_getFinalOverride()->m_val1C;
	if (type == 0x15)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			Object *special = rva0044FEB6();
			if (special && !initLaser(special, target))
				return;
		}
	}
	else if (type == 0x1d)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target && target->getTeam() == getObject()->getTeam())
			return;
		m_object->clearAndSetModelConditionState((ModelConditionFlagType)0x60, (ModelConditionFlagType)0x76);
		Drawable *draw = m_object->getDrawable();
		if (draw)
			draw->rva002723C0(d->m_preparationFrames);
		if (target && target->isLocallyControlled())
			TheEva->reportEvaEvent((EvaEventID)0x10, &target->m_position, 0);
	}
	else if (type == 0x1a)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			if (m_object->getRelationship(target) == ALLIES)
				return;
			Object *special = rva0044FEB6();
			if (special)
			{
				if (!initLaser(special, target))
					return;
				m_object->clearAndSetModelConditionState((ModelConditionFlagType)0x60, (ModelConditionFlagType)0x29);
			}
			if (target->isLocallyControlled())
				TheEva->reportEvaEvent((EvaEventID)0x10, &target->m_position, 0);
		}
	}
	SpecialPowerModuleInterface *module = (SpecialPowerModuleInterface *)((Rva0044E633 *)this)->rva0044E633();
	if (module)
		module->markSpecialPowerTriggered(0);
	if (getObject()->getAI())
		getObject()->getAI()->aiIdle(CMD_FROM_AI);
	Object *obj = m_object;
	obj->rva0028CDEB(*(const Rva00346BC0 *)&Rva00391F4E(0, 0x18, 0x46), true);
	BfmeAudioEventPrefix136 sound(d->m_prepSoundLoop, 0);
	((Rva002D9531 *)&sound)->rva002D9531(m_object->m_id);
	m_prepSoundLoop = TheAudio->addAudioEvent(&sound);
}


// ZH SpecialAbilityUpdate::handlePackingProcessing supplies the transition
// behavior and method name. Native 44F0B3..44F28E independently establishes
// the eight-bit clear mask, target-capture handling and expanded stealth call.
// The native finish callback is virtual slot 19; use its call-site ABI view.
class Rva00265254 {public:Rva00265254(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);unsigned bits[19];};
class Rva001E431E {public:void rva001E431E(const int*);};
class StealthUpdate {public:void markAsDetected(unsigned,int,Object*,bool);};
class Rva00439E0C {public:bool rva00439E0C(Object*,Object*,int,int);};
struct SpecialGameLogicView {char opaque[0x178];Rva00439E0C *invisibility;};
template<int N> class SpecialPackingSlots:public SpecialPackingSlots<N-1> {public:virtual void gap(char(*)[N]);};
template<> class SpecialPackingSlots<0>{};
class SpecialPackingFinishView:public SpecialPackingSlots<19> {public:virtual void finish();};
bool SpecialAbilityUpdate::handlePackingProcessing()
{
 const SpecialAbilityUpdateModuleData *data=(const SpecialAbilityUpdateModuleData*)m_moduleData;
 if(m_animFrames>0) {
  --m_animFrames;
  if(m_animFrames==0) {
   Object *owner=getObject();
   ((Rva001E42F2*)owner)->rva001E42F2((const int*)&Rva00265254(0,0x60,0x61,0x62,0x63,0x249,0x24a,0x24b,0x5e));
   if(m_packingState==2) {
    if(data->m_flipAfterUnpacking)getObject()->setOrientation(getObject()->m_orientation44+3.14159265358979323846f);
    m_packingState=4;
   } else if(m_packingState==1) {
    if(data->m_flipAfterPacking)getObject()->setOrientation(getObject()->m_orientation44+3.14159265358979323846f);
    m_packingState=3;
    ((SpecialPackingFinishView*)this)->finish();return true;
   }
   if(data->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C==0x1d) {
    ObjectID saved=m_targetID;
    Object *target=TheGameLogic->findObjectByID(saved);
    if(!target){((SpecialPackingFinishView*)this)->finish();return true;}
    if(target->m_captor80 && target->m_captor80!=getObject()->m_id){((SpecialPackingFinishView*)this)->finish();return true;}
    Object *source=getObject();
    Object *same=TheGameLogic->findObjectByID(saved);
    ((Rva001E42F2*)target)->rva001E42F2((const int*)&Rva0028F59A(0,0x6f));
    target->m_captor80=getObject()->m_id;
    if(source->getTeam()!=same->getTeam())((Rva001E42F2*)target)->rva001E42F2((const int*)&Rva0028F59A(0,0x6e));
    ((Rva001E431E*)target)->rva001E431E((const int*)&Rva0028F59A(0,0x6e));
    ((Rva001E431E*)source)->rva001E431E((const int*)&Rva0028F59A(0,0x70));
   }
   return false;
  }
  if(data->m_loseStealth && m_animFrames<data->m_preTriggerUnstealthFrames) {
   StealthUpdate *stealth=(StealthUpdate*)getObject()->rva0028F4BC();
   if(stealth)stealth->markAsDetected(0,1,0,true);
   ((SpecialGameLogicView*)TheGameLogic)->invisibility->rva00439E0C(getObject(),0,0,1);
  }
  return true;
 }
 return false;
}
