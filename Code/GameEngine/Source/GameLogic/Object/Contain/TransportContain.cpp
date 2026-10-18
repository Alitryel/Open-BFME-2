// cl: /O1 /G7 /arch:SSE /MD /EHsc /I.
// TransportContain: the update slot of its +0x10 UpdateModuleInterface
// (0x00468749) and the shared condition callback on the +0x20 interface
// (0x004673C0). Partial owner views; no vtable is emitted here.
//
// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00468749,
// 392 bytes (WB 0x0115B1B0, BitFlags<591> test inlined). The Zero Hour body
// (TransportContain.cpp update) with BFME2 deltas:
//  - the payload is created when module data byte +0x150 is set and the logic
//    frame (TheGameLogic +0x40) has reached the frame at module +0x108, through
//    primary vtable slot 29 (createPayload, 0x004670D6);
//  - the health regeneration keeps ZH's guard and expression verbatim
//    (if (moduleData && moduleData->m_healthRegen), max * regen / 100.0f *
//    seconds-per-frame) with SECONDS_PER_LOGICFRAME_REAL as the BFME2 runtime
//    global at 0x00DBA4F8; it heals every hurt contained object through the
//    rowed Object::attemptHealing 0x0028FE55;
//  - UpdateUpgradeCreationTriggers (0x00468045) runs;
//  - when the model-condition bit 61 (Object flags +0x110 bit 29) differs from
//    the byte at module +0x10C, the byte follows it and bit 89 (+0x114 bit 25)
//    of every contained object is set or cleared with the rowed model-condition
//    notifier 0x0028AE6D;
//  - OpenContain::update (0x004640BE) provides the result, followed by primary
//    vtable slot 30.
//
// rva004673C0, retail 0x004673C0, 76 bytes: the original callback name is
// unasserted. Target words at Object+10C clear bits 18/19/20, each notifying
// only if set (WB 0x0115C5C0: three Object::clearModelConditionState calls).
#define V(n) virtual void slot##n();

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class Object;

class Rva00263895Member;
class BodyModuleInterface
{
public:
	virtual void s00();
	virtual void attemptHealing(Rva00263895Member *);
	virtual void s02();
	virtual void s03();
	virtual float getHealth();
	virtual void s05();
	virtual float getMaxHealth();
};

struct TransportContainListNode
{
	TransportContainListNode *m_next;
	TransportContainListNode *m_prev;
	Object *m_data;
};

struct TransportContainList
{
	TransportContainListNode *m_head;
};

struct TransportContainItems
{
	void *m_lock;
	const TransportContainList *m_list;
};

class ContainModuleInterface
{
public:
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	virtual TransportContainItems getContainedItems();
#undef V10
};

struct TransportContainModelFlags
{
	unsigned m_bits[19];
	__forceinline unsigned test(unsigned i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	__forceinline void set(unsigned i) { m_bits[i >> 5] |= 1u << (i & 31); }
	__forceinline void reset(unsigned i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }
	// Signed-index forms, as the matched TransportContainRiders/Locomotor helpers.
	unsigned testBit(int bit) const { return m_bits[bit >> 5] & (1U << (bit & 31)); }
	void clearBit(int bit) { m_bits[bit >> 5] &= ~(1U << (bit & 31)); }
};

class Object
{
public:
	void attemptHealing(float amount, const Object *source);	// 0x0028FE55
	int getID() const {return m_id;}
	void rva0028AE6D();
	__forceinline void clearModelConditionBit(int bit) { if (m_modelFlags.testBit(bit) != 0) { m_modelFlags.clearBit(bit); rva0028AE6D(); } }
	unsigned char m_pad00[0x74];
	int m_id;
	unsigned char m_pad78[0x10C-0x78];
	TransportContainModelFlags m_modelFlags;
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern float g_secondsPerLogicFrame;

struct TransportContainModuleDataView
{
	unsigned char m_pad00[0xA8];
	float m_healthRegen;
	unsigned char m_padAC[0x150 - 0xAC];
	bool m_createsPayload;
};


class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const void *m_moduleData;			// +0x04
	Object *m_object;					// +0x08
};

struct BehaviorModuleInterface { virtual void f0C(); };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class Rva004640BE : public UpdateModuleInterface
{
public:
	int rva004640BE();
};

// The update interface's tail keeps the condition interface at full object
// +0x20, where the constructor 0x00468559 stores its secondary table.
class TransportContainUpdate : public Rva004640BE { unsigned char m_pad14[0x20 - 0x14]; };
class TransportConditionInterface { public: virtual void rva004673C0() = 0; };

class TransportContain : public BehaviorModule, public BehaviorModuleInterface,
	public TransportContainUpdate, public TransportConditionInterface
{
public:
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28)
#undef V10
	virtual void createPayload();		// slot 29 (0x004670D6)
	virtual void slot30();
	virtual UpdateSleepTime update();
	void UpdateUpgradeCreationTriggers();	// 0x00468045
	virtual void rva004673C0();
private:
	unsigned char m_pad24[0x108 - 0x24];
	unsigned int m_payloadFrame;		// +0x108
	bool m_hiddenState;					// +0x10C
};

class Rva00263895Member
{
public:
	Rva00263895Member();

	char m_pad00[0x08];
	int m_sourceID; // +0x08
	char m_pad0C[0x04]; // +0x0C
	int m_damageType; // +0x10
	char m_pad14[0x08]; // +0x14..0x1B
	int m_deathType; // +0x1C
	float m_amount; // +0x20
	char m_pad24[0x7C - 0x24];
};

UpdateSleepTime TransportContain::update()
{
	const TransportContainModuleDataView *md = (const TransportContainModuleDataView *)m_moduleData;
	if (md->m_createsPayload && TheGameLogic->getFrame() >= m_payloadFrame)
		createPayload();

	if (md && md->m_healthRegen)
	{
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain)
		{
			TransportContainItems items = contain->getContainedItems();
			TransportContainListNode *head = items.m_list->m_head;
			for (TransportContainListNode *node = head->m_next; node != items.m_list->m_head;)
			{
				Object *object = node->m_data;
				node = node->m_next;
				BodyModuleInterface *body = object->m_body;
				if (body->getHealth() < body->getMaxHealth())
				{
					float regen = body->getMaxHealth() * md->m_healthRegen / 100.0f * g_secondsPerLogicFrame;
					object->attemptHealing(regen, m_object);
				}
			}
		}
	}

	UpdateUpgradeCreationTriggers();

	bool changed = false;
	bool hidden = (m_object->m_modelFlags.test(61) != 0);
	if (m_hiddenState && !hidden)
	{
		m_hiddenState = false;
		changed = true;
	}
	else if (!m_hiddenState && hidden)
	{
		m_hiddenState = true;
		changed = true;
	}
	if (changed)
	{
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain)
		{
			TransportContainItems items = contain->getContainedItems();
			TransportContainListNode *head = items.m_list->m_head;
			for (TransportContainListNode *node = head->m_next; node != items.m_list->m_head; node = node->m_next)
			{
				Object *object = node->m_data;
				if (!object)
					continue;
				if (m_hiddenState)
				{
					if (object->m_modelFlags.test(89))
						continue;
					object->m_modelFlags.set(89);
				}
				else
				{
					if (!object->m_modelFlags.test(89))
						continue;
					object->m_modelFlags.reset(89);
				}
				object->rva0028AE6D();
			}
		}
	}
	UpdateSleepTime result = (UpdateSleepTime)Rva004640BE::rva004640BE();
	slot30();
	return result;
}

void TransportContain::rva004673C0()
{
	Object *owner = m_object;
	owner->clearModelConditionBit(18);
	owner->clearModelConditionBit(19);
	owner->clearModelConditionBit(20);
}
