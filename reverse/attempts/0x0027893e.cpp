// ?onComingOutOfShroud@Drawable@@AAEXXZ
// partial score=0.995 date=2026-10-22
// ?onComingOutOfShroud@Drawable@@AAEXXZ
// stlport
// cl: /O1 /Ob1 /d2inlS100 /D_STLP_USE_STATIC_LIB /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// Retail: 0x0027893E..0x00278C29 (747 B). WB twin: 0x00CA3700.
// Target offsets are measured from retail; KindOf's 218-bit size has ledger
// support. ZH BitFlags supplies the checked-test semantic guide only.
// Handoff: reverse/attempt_support/drawable-shroud-tail-20261022.md
// Destination: Code/GameEngine/Source/GameClient/Drawable.cpp (not integrated).
#include <bitset>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Player;
class Drawable;

class ThingTemplate
{
public:
	__forceinline bool testKindInView(int kind) const
	{ return m_kindOf.test(kind); }
	char m_pad000[0x108];
	std::bitset<218> m_kindOf; // +0x108
	char m_pad124[0x59C - 0x124];
	int m_sightedEvent; // +0x59C
	int m_sightedEventAlt; // +0x5A0
	int m_revealedEvent; // +0x5A4
	int m_shroudedEvent; // +0x5A8
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

enum EvaEventID
{
	EVA_EVENT_INVALID = -1
};

class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *position2);
};
extern Eva *TheEva;

struct ModuleData
{
	char pad[0x4C];
	int m_campSightedEvent; // +0x4C
};

class Module
{
public:
	void *m_vtable;
	const ModuleData *m_moduleData; // +0x04
	char pad08[0x18 - 0x08];
	ObjectID m_castleID; // +0x18
};

class Rva003974CE
{
public:
	int apply(int (*func)(Object *obj, int arg), int arg);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Rva004A1828Holder
{
public:
	virtual ObjectID getID();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool isReady();
};
struct Rva004A1828Owner;
int Rva004A1828Get(Rva004A1828Owner *owner);

class Object
{
	friend class Drawable;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	bool rva00294471(void *player, int arg);
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
protected:
	Module *findModule(NameKeyType key) const;
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0x438 - 0x44];
	unsigned char m_privateStatus; // +0x438
};

class Player
{
public:
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
private:
	char m_pad000[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002706A8
{
public:
	void rva002706A8();
};

int rva00272A6A(Object *obj, void *userData);
int rva002706F0(Object *obj, int arg);

class Drawable
{
public:
	Object *rva00272AD5();
private:
	void onComingOutOfShroud();
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0xFC - 0x08];
	Object *m_object; // +0xFC
	char m_pad100[0x114 - 0x100];
	unsigned int m_status; // +0x114
	unsigned char m_pad118[0x445 - 0x118];
	bool m_sightReported; // +0x445
	bool m_useAltSightedEvent; // +0x446
};

struct SightedEventData
{
	Drawable *drawable;
	int event;
};

void Drawable::onComingOutOfShroud()
{
	const ThingTemplate *tmpl = m_template;

	Object *obj = m_object;


	int notifyEvent;
	Player *localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
	if (!tmpl || !obj || !localPlayer || !TheGameLogic || TheGameLogic->getFrame() <= 5)
		return;

	if (obj->rva00294471(localPlayer, 1)) {
		if (!obj->isEffectivelyDead() && tmpl->m_sightedEvent != -1 && !tmpl->testKindInView(47) && !m_sightReported) {
			Rva004A1828Holder *holder = (Rva004A1828Holder *)Rva004A1828Get((Rva004A1828Owner *)obj);
			bool skip;
			if (holder && holder->isReady()) {
				skip = false;
			} else {
				Player *controller = obj->getControllingPlayer();
				if (controller) {
					int dataEvent = tmpl->m_sightedEvent;
					SightedEventData data;
					data.drawable = this;
					data.event = dataEvent;
					if (controller->iterateObjects(rva00272A6A, &data) == 1)
						skip = false;
					else
						skip = true;
				} else {
					skip = true;
				}
			}
			if (!skip) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest) {
					int event = tmpl->m_sightedEvent;
					if (m_useAltSightedEvent && tmpl->m_sightedEventAlt != -1)
						event = tmpl->m_sightedEventAlt;
					if (TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition()) && holder && holder->isReady()) {
						m_sightReported = true;
						Object *holderObject = TheGameLogic->findObjectByID(holder->getID());
						if (holderObject) {
							Drawable *draw = holderObject->getDrawable();
							if (draw)
								((Rva002706A8 *)draw)->rva002706A8();
						}
					}
				}
			}
		}

		int mask80 = 0x80;

		if ((((const unsigned char *)&tmpl->m_kindOf)[0] & mask80) && !(m_status & 0x40)) {
			static NameKeyType key_CastleMemberBehavior = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			Module *member = obj->findModule(key_CastleMemberBehavior);
			if (member) {
				Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
				if (castle) {
					Module *castleBehavior = castle->findModule(CastleBehavior::rva0003955DA());
					if (castleBehavior) {
						int event = castleBehavior->m_moduleData->m_campSightedEvent;
						if (event != -1) {
							Drawable *castleDraw = castle->getDrawable();
							if (castleDraw) {
								if (!(castleDraw->m_status & 0x40)) {
									Object *nearest = ((Drawable *)obj)->rva00272AD5();
									if (nearest)
										TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition());
								}
								((Rva003974CE *)castleBehavior)->apply(rva002706F0, 0);
							}
						}
					}
				}
			}
		}

		if (!(m_status & mask80) && !obj->isEffectivelyDead()) {
			m_status |= mask80;
			notifyEvent = tmpl->m_revealedEvent;
			goto completeNotify;
		}
	} else {
		if (((Rva00270260 *)this)->rva00270260())
			return;
		int mask80 = 0x80;
		if (!(m_status & mask80) && !obj->isEffectivelyDead()) {
			m_status |= mask80;
			notifyEvent = tmpl->m_shroudedEvent;
			goto completeNotify;
		}
	}
	return;
completeNotify:
	if (notifyEvent != -1) {
		Object *nearest = ((Drawable *)obj)->rva00272AD5();
		if (nearest)
			TheEva->reportEvaEvent((EvaEventID)notifyEvent, nearest->getPosition(), obj->getPosition());
	}
}
