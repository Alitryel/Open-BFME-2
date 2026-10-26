// cl: /O1 /MD /G7 /D_STLP_USE_STATIC_LIB
// stlport
// TunnelContain.cpp: TunnelContain overrides retail links from this TU (tu_map
// approved), folded from two split units with these exact flags. The contain
// interface at +0x34 carries both overrides: rva0047DE30 in slot 4 and
// iterateContained in slot 73.
//
// ?iterateContained@TunnelContain@@UAEXP6AXPAX0@Z0I@Z @0x0047DCDF 48B.
// Target evidence: the only reference to this body is slot 73 of the vtable
// 0x00C475A4, which the matched TunnelContain ctor 0x0047DC41 and dtor
// 0x0047DB3A install at +0x34 -- the contain interface base of the
// OpenContain-family layout (vptrs at +0, +0xC, +0x10, +0x20, +0x24, +0x28,
// +0x2C, +0x30, +0x34). It is therefore TunnelContain's override of that
// interface's slot 73; the slot's name is not established, hence the address
// name. cl 7.1 compiles an override of a non-primary base's virtual with the
// base subobject's this and folds the adjustment into the member accesses,
// which is why retail reads the Object pointer at TunnelContain+0x1C as
// [ecx-0x18] (no adjustor thunk; the honest class model reproduces it).
// Body: when bit 0 of the flags is set, forwards (callback, user data,
// bit 3 of the flags) to the rowed visitor 0x004F553F on the +0x2E8 member
// of the controlling player of the Object at +0x1C (that field's meaning is
// not asserted; it is the one the body dereferences). /G7 gives the byte
// form of the flag extraction (shr ebx,3; and bl,1).
#include "TunnelContainView.h"

void TunnelContain::iterateContained(Rva004F553FCb cb, void *user, unsigned int flags)
{
	if (!(flags & 1))
		return;
	Player *player = m_1C->getControllingPlayer();
	player->m_2E8->iterateContained((ContainIterateFunc)cb, user, (flags >> 3) & 1);
}

// ?rva0047DE30@TunnelContain@@UAEXXZ, retail 0x0047DE30, 60 bytes.
// TunnelContain chain method: virtual slot03 check then controlling-player 0x2E8 manager rva004F56FC add of m_object plus flag bytes at +0x9B0/+0x9B1.
// Layout: 8-base OpenContain family per TunnelContainRva0047DCDF (Iface34 at +0x34) so [esi-0x2C] is B00 m_object at +8; Player m_2E8 is Rva004F56FC per Rva004F56FCAdd caller 0x0047DE30; slot03 bool tentative. Evidence: chain via 0x004F56FC plus neighbours DCDF DF44.
void TunnelContain::rva0047DE30()
{
	if (!s03())
		return;
	m_flag9B0 = 0;
	Player *player = m_object->getControllingPlayer();
	if (player == 0)
		return;
	Rva004F56FC *mgr = (Rva004F56FC *)player->m_2E8;
	if (mgr == 0)
		return;
	mgr->rva004F56FC(m_object);
	m_flag9B1 = 1;
}

// ?addToContainList@TunnelContain@@UAEXPAVObject@@@Z, retail 0x0047DC75,
// 19 bytes: slot 40 of the contain interface at +0x34 (vtable 0x008475B8,
// whose slot 68 is iterateContained above). Zero Hour's TunnelContain::
// addToContainList: the object joins the owning player's tunnel system
// (+0x2E8, rowed TunnelTracker::addToContainList 0x004F56E5, reached by a
// tail jump). BFME 2 keeps no null checks, like iterateContained.
void TunnelContain::addToContainList(Object *obj)
{
	Player *owningPlayer = m_1C->getControllingPlayer();
	owningPlayer->m_2E8->addToContainList(obj);
}

// Three more slots of the contain interface at +0x34 (vtable 0x008475B8),
// each reading the owning player's tunnel tracker (+0x2E8) through the +0x1C
// object pointer:
// ?getContainMax@TunnelContain@@UBEHXZ 0x0047DDFF 19B, slot 28: Zero Hour's
// getContainMax, without its null checks: tail jump to the rowed
// TunnelTracker::getContainMax 0x004F5385.
int TunnelContain::getContainMax() const
{
	Player *owningPlayer = m_1C->getControllingPlayer();
	return owningPlayer->m_2E8->getContainMax();
}

// ?rva0047DDD9@TunnelContain@@UAEHPAX@Z 0x0047DDD9 38B, slot 69: with a
// player and a tracker, the tracker's rowed count 0x004F5436 over no table;
// else 0. The argument is unused.
int TunnelContain::rva0047DDD9(void *)
{
	Player *owningPlayer = m_1C->getControllingPlayer();
	if (owningPlayer && owningPlayer->m_2E8)
		return ((Rva004F5436 *)owningPlayer->m_2E8)->rva004F5436(0);
	return 0;
}

// ?rva0047DE12@TunnelContain@@UAE?AVRva0036AE51ListView@@XZ 0x0047DE12 30B,
// slot 70: the tracker's list view by value (rowed 0x00466398), the twin of
// the primary-vtable slot 33 in TunnelContainContainedList.cpp.
Rva0036AE51ListView TunnelContain::rva0047DE12()
{
	Player *owningPlayer = m_1C->getControllingPlayer();
	return ((Rva00466398 *)owningPlayer->m_2E8)->rva00466398();
}

// ?onDie@TunnelContain@@UAEXPBVDamageInfo@@@Z, retail 0x0047DFD9, 38 bytes:
// the only slot of the die interface at +0x28 (vtable 0x008475B4). Zero
// Hour's TunnelContain::onDie: the module data's DieMuxData (+0x08) must
// apply to the object, then the unregistering Zero Hour does inline is the
// rowed rva0047DF81 0x0047DF81 on the whole object.
void TunnelContain::onDie(const DamageInfo *damageInfo)
{
	Object *obj = m_object;
	const TunnelContainModuleDataView *data = (const TunnelContainModuleDataView *)m_moduleData;
	if (!data->m_dieMuxData.isDieApplicable(obj, damageInfo))
		return;
	rva0047DF81();
}

// ZH TunnelContain onRemoving guides release/position/show; native base is GarrisonContain.
// Native reads454 and554/428 and dispatches primary58 after the +20 override.
void TunnelContain::onRemoving(Object *obj)
{
    GarrisonContain::onRemoving(obj);
    obj->clearDisabled(DISABLED_HELD);
    if (!obj->flag454) obj->rva0028DCC4();
    obj->setPosition(m_object->getPosition());
    if (obj->getDrawable()) {
        obj->safeOcclusionFrame = TheGameLogic->getFrame() + obj->getTemplate()->occlusionDelay;
        obj->getDrawable()->setDrawableHidden(false);
    }
    rvaPrimary58();
}

// ?update@TunnelContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0047E017, 183 bytes:
// slot 0 of the update interface at +0x10. Zero Hour's TunnelContain::update
// over the garrison base update (pinned 0x00479643): heal through the
// owner's tunnel system (+0x2E8) when the module data asks (+0x98, frames for
// a full heal +0xD4), and make an enemy that damaged the tunnel within the
// last second the system's nemesis. BFME 2 sleeps for good without an owner
// object or tunnel system.
extern int BfmeLogicFramesPerSecond;	// logic frames per second
UpdateSleepTime TunnelContain::update()
{
	// extending functionality to heal the units within the tunnel system
	GarrisonContain::update();
	Object *obj = m_object;
	if (!obj)
		return UPDATE_SLEEP_FOREVER;
	const TunnelContainModuleDataView *modData = (const TunnelContainModuleDataView *)m_moduleData;
	Player *controllingPlayer = obj->getControllingPlayer();
	if (!controllingPlayer)
		return UPDATE_SLEEP_NONE;
	TunnelTracker *tunnelSystem = controllingPlayer->m_2E8;
	if (!tunnelSystem)
		return UPDATE_SLEEP_FOREVER;
	if (modData->m_healTunnelSystem)
		tunnelSystem->healObjects(modData->m_framesForFullHeal);

	// check for attacked.
	BodyModuleInterface *body = obj->getBodyModule();
	if (body)
	{
		const TunnelDamageInfoView *info = body->getLastDamageInfo();
		if (info)
		{
			if (body->getLastDamageTimestamp() + BfmeLogicFramesPerSecond > TheGameLogic->getFrame())
			{
				// winner.
				Object *attacker = TheGameLogic->findObjectByID(info->sourceID);
				if (attacker)
				{
					if (obj->getRelationship(attacker) == ENEMIES)
						tunnelSystem->updateNemesis(attacker);
				}
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}

// ?isValidContainerFor@TunnelContain@@UAE_NPAVObject@@_N1@Z, retail 0x0047DDA2, 55 bytes:
// slot 38 of the contain interface at +0x34 (vtable 0x008475B8).
bool TunnelContain::isValidContainerFor(Object *obj, bool checkCapacity, bool a3)
{
	if (!HordeGarrisonContain::isValidContainerFor(obj, false, a3))
		return false;
	Player *owningPlayer = m_1C->getControllingPlayer();
	return owningPlayer->getTunnelSystem()->isValidContainerFor(obj, checkCapacity);
}

// ?onSelling@TunnelContain@@UAEXXZ, retail 0x0047E00F, 8 bytes:
// slot 25 of the contain interface at +0x20 (vtable 0x008475B8).
void TunnelContain::onSelling()
{
	rva0047DF81();
}

