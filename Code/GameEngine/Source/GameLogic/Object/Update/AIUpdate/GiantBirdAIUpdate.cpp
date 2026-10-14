// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0036AE79@GiantBirdAIUpdate@@QAEXXZ, retail 0x0036AE79..0x0036B103
// (650 bytes, EH): the grab toss of the giant bird, called only from the
// unrowed GiantBirdAIUpdate update body at 0x0036B1A9.
//
// Target facts: this is the GiantBirdAIUpdate primary (+0x4B8 flag word
// whose bit 6 onCollide also tests, +0x4BC timer, +0x4C0 and +0x4C4 words
// the constructor zeroes, +0x538 real, +0x30 state machine, +0x1F0 pointer).
// While bit 6 is set and the Object's contain module (+0x250) holds riders
// (slot 69, getContainCount), the timer advances by 1 / logic frame rate.
// When GrabTossTimeTrigger (module data +0x6C) is positive and exceeded,
// or GrabTossHeightTrigger (+0x70, compared as a double) is positive and
// the height above terrain exceeds it, bit 6 is cleared and the contained
// list (slot 70 by value, then the rowed 0x0036AE51) is searched for the
// rider whose Object +0x74 word equals +0x4C4. That rider is removed from
// the container (slot 41, false) and turned to the bird's Z rotation; the
// state machine's slot 14 gets 0. With a rider physics module (+0x25C) and
// a +0x1F0 pointer, the bird's unit direction scaled by half +0x538, with z
// -6, goes to the pinned 0x003909FA (vector, 0, 0) and the rowed
// PhysicsBehavior::rva00390629(true); TossFX (+0x80) plays on the rider and
// the bird, and with bit 8 the pinned 0x00294D61 reports the rider and sets
// physics byte +0x5F. Then model condition bit 72 (the Object +0x10C
// words; notifier 0x0028AE6D), setStatus(0x3C, false), and unless the
// rider's template has KindOf bit 0x5A its body (+0x254) slot 33
// (setIndestructible) gets false.
// The timer otherwise resets when no riders remain.
//
// Identity: the module data field names come from the GiantBirdAIUpdate
// field parse table 0x00C178D8; the function name is address-derived (WB
// 0x00F3B0A0 is the same body, unnamed). The other field names and the
// slot meanings are structural inferences.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../Include/GameLogic/ContainmentListView.h"

namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

extern int BfmeLogicFramesPerSecond;

inline void scaleCoord(Coord3D &c, Real s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

enum ObjectStatusTypes { OBJECT_STATUS_BFME_3C = 0x3C };
enum { BFME_MODELCONDITION_72 = 2 * 32 + 8 };

class FXList;
class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;
private:
	Real Row[3][4];
};

class ThingTemplateView
{
public:
	Bool isKindOf5A() const { return (m_kindOf[0x5A >> 3] & (1 << (0x5A & 7))) != 0; }
private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class Thing
{
public:
	Bool isAboveTerrain() const;
	Real getHeightAboveTerrain() const;
	void setOrientation(Real angle);
	void getUnitDirectionVector3D(Coord3D &dir) const;
	const ThingTemplateView *getTemplate() const { return m_template; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	void *m_vptr;
	const ThingTemplateView *m_template; // +0x04
	Matrix3D m_transform; // +0x08
};

class BodyModuleInterface
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual void gap04(); virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13(); virtual void gap14(); virtual void gap15();
	virtual void gap16(); virtual void gap17(); virtual void gap18(); virtual void gap19();
	virtual void gap20(); virtual void gap21(); virtual void gap22(); virtual void gap23();
	virtual void gap24(); virtual void gap25(); virtual void gap26(); virtual void gap27();
	virtual void gap28(); virtual void gap29(); virtual void gap30(); virtual void gap31();
	virtual void gap32();
	virtual void setIndestructible(Bool indestructible) = 0; // +0x84
};

class ContainModuleInterface
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual void gap04(); virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13(); virtual void gap14(); virtual void gap15();
	virtual void gap16(); virtual void gap17(); virtual void gap18(); virtual void gap19();
	virtual void gap20(); virtual void gap21(); virtual void gap22(); virtual void gap23();
	virtual void gap24(); virtual void gap25(); virtual void gap26(); virtual void gap27();
	virtual void gap28(); virtual void gap29(); virtual void gap30(); virtual void gap31();
	virtual void gap32(); virtual void gap33(); virtual void gap34(); virtual void gap35();
	virtual void gap36(); virtual void gap37(); virtual void gap38(); virtual void gap39();
	virtual void gap40();
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits) = 0; // +0xA4
	virtual void gap42(); virtual void gap43(); virtual void gap44(); virtual void gap45();
	virtual void gap46(); virtual void gap47(); virtual void gap48(); virtual void gap49();
	virtual void gap50(); virtual void gap51(); virtual void gap52(); virtual void gap53();
	virtual void gap54(); virtual void gap55(); virtual void gap56(); virtual void gap57();
	virtual void gap58(); virtual void gap59(); virtual void gap60(); virtual void gap61();
	virtual void gap62(); virtual void gap63(); virtual void gap64(); virtual void gap65();
	virtual void gap66(); virtual void gap67(); virtual void gap68();
	virtual UnsignedInt getContainCount(Int unused) const = 0; // +0x114
	virtual Rva0036AE51ListView getContainedItemsView() = 0; // +0x118
};

class PhysicsBehavior
{
public:
	void rva00390629(Bool flag);
	void setFlag5F() { m_5F = true; }
private:
	unsigned char m_pad00[0x5F];
	Bool m_5F; // +0x5F
};

// The pinned owner names of 0x003909FA and 0x00294D61.
class Rva003909FAObj { public: void consume(void *force, Int a, Int b); };
class Rva00294D61 { public: void report(Object *victim, Int flag); };

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
private:
	unsigned int m_words[19];
};

class Object : public Thing
{
public:
	UnsignedInt getID() const { return m_id; }
	void rva0028AE6D();
	__forceinline void setModelConditionState(unsigned int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	void setStatus(ObjectStatusTypes status, Bool set);
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	PhysicsBehavior *getPhysics() const { return m_physics; }
private:
	unsigned char m_pad038[0x74 - 0x38];
	UnsignedInt m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	void *m_ai; // +0x258
	PhysicsBehavior *m_physics; // +0x25C
};

class StateMachine
{
public:
	virtual void gap00(); virtual void gap01(); virtual void gap02(); virtual void gap03();
	virtual void gap04(); virtual void gap05(); virtual void gap06(); virtual void gap07();
	virtual void gap08(); virtual void gap09(); virtual void gap10(); virtual void gap11();
	virtual void gap12(); virtual void gap13();
	virtual void slot14(void *arg) = 0; // +0x38
};

struct GiantBirdAIUpdateModuleData
{
	unsigned char m_pad00[0x6C];
	Real m_grabTossTimeTrigger; // +0x6C GrabTossTimeTrigger
	Real m_grabTossHeightTrigger; // +0x70 GrabTossHeightTrigger
	unsigned char m_pad74[0x80 - 0x74];
	const FXList *m_tossFX; // +0x80 TossFX
};

class GiantBirdAIUpdate
{
public:
	void rva0036AE79();
	const GiantBirdAIUpdateModuleData *getGiantBirdAIUpdateModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	Bool testFlag(Int bit) const { return (m_4B8 >> bit) & 1; }
	void clearFlag(Int bit) { m_4B8 &= ~(1 << bit); }
private:
	void *m_vptr;
	const GiantBirdAIUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x30 - 0x0C];
	StateMachine *m_stateMachine; // +0x30
	unsigned char m_pad34[0x1F0 - 0x34];
	void *m_1F0; // +0x1F0
	unsigned char m_pad1F4[0x4B8 - 0x1F4];
	UnsignedInt m_4B8; // +0x4B8
	Real m_4BC; // +0x4BC
	Int m_4C0; // +0x4C0
	UnsignedInt m_4C4; // +0x4C4
	unsigned char m_pad4C8[0x538 - 0x4C8];
	Real m_538; // +0x538
};

void GiantBirdAIUpdate::rva0036AE79()
{
	if (!testFlag(6))
		return;
	Object *obj = getObject();
	Real height = obj->isAboveTerrain() ? obj->getHeightAboveTerrain() : 0.0f;
	ContainModuleInterface *contain = obj->getContain();
	if (contain && contain->getContainCount(0) > 0)
	{
		m_4BC += 1.0f / (Real)BfmeLogicFramesPerSecond;
		const GiantBirdAIUpdateModuleData *data = getGiantBirdAIUpdateModuleData();
		if ((data->m_grabTossTimeTrigger > 0.0f && m_4BC > data->m_grabTossTimeTrigger)
			|| (data->m_grabTossHeightTrigger > 0.0 && height > data->m_grabTossHeightTrigger))
		{
			clearFlag(6);
			ContainmentList riders = contain->getContainedItemsView().rva0036AE51();
			for (ContainmentList::iterator it = riders.begin(); it != riders.end(); )
			{
				Object *rider = (Object *)containmentFirstWord(*it);
				++it;
				if (rider->getID() == m_4C4)
				{
					m_4C4 = 0;
					contain->removeFromContain(rider, false);
					rider->setOrientation(obj->getTransformMatrix()->Get_Z_Rotation());
					getStateMachine()->slot14(0);
					void *p1F0 = m_1F0;
					PhysicsBehavior *phys = rider->getPhysics();
					if (phys && p1F0)
					{
						Coord3D dir;
						obj->getUnitDirectionVector3D(dir);
						scaleCoord(dir, m_538 / 2.0f);
						Coord3D force;
						force.x = dir.x;
						force.y = dir.y;
						force.z = -6.0f;
						((Rva003909FAObj *)phys)->consume(&force, 0, 0);
						phys->rva00390629(true);
						if (data->m_tossFX)
							FXList::doFXObj(data->m_tossFX, rider, obj);
						if (testFlag(8))
						{
							((Rva00294D61 *)obj)->report(rider, 1);
							phys->setFlag5F();
						}
					}
					rider->setModelConditionState(BFME_MODELCONDITION_72);
					rider->setStatus(OBJECT_STATUS_BFME_3C, false);
					if (!rider->getTemplate()->isKindOf5A())
					{
						BodyModuleInterface *body = rider->getBodyModule();
						if (body)
							body->setIndestructible(false);
					}
					m_4C0 = 0;
					m_4BC = 0.0f;
					break;
				}
			}
		}
	}
	else
	{
		m_4BC = 0.0f;
	}
}
