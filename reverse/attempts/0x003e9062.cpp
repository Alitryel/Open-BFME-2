// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.949 date=2026-10-15
// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// Append to Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp
// with these TU additions: Parameter gets `unsigned char m_pad1C[4]; int m_cachedFrame; // +0x20`
// after m_afterString[8]; ObjectStatusTypes gets OBJECT_STATUS_02 = 0x02 (and forward-declare
// SpecialPowerModuleInterface/SpecialPowerTemplate after the enum); Object gets
// `SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;` and
// `inline bool isDisabled() const;`, defined after KindOfMaskType as the rowed BitFlags<11>::any
// (0x0023C58B) on +0x1C8; BitFlags<N> gets `bool any() const;`; ScriptConditions gets the
// member declaration. Residue: object loop shape (see re_attempts.log); the done()+if(!pObj)
// spelling instead gives retail's loop but swaps EDI to the list iterator.
// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9062 404B
class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual bool isReady() const;
	virtual void slot08();
	virtual void slot0C();
	virtual unsigned int getReadyFrame() const;
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
	bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *power);
};
extern SpecialPowerStore *TheSpecialPowerStore;
extern int BfmeLogicFramesPerSecond;

bool ScriptConditions::evaluateSkirmishSpecialPowerIsReady(Parameter *pSkirmishPlayerParm, Parameter *pPower)
{
	if (pPower->m_cachedFrame == -1)
		return false;
	if (pPower->m_cachedFrame > 0 && (unsigned int)pPower->m_cachedFrame > TheGameLogic->getFrame())
		return false;
	unsigned int nextFrame = BfmeLogicFramesPerSecond * 10 + TheGameLogic->getFrame();
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(pPower->getString());
	if (power == 0) {
		pPower->m_cachedFrame = -1;
		return false;
	}

	PlayerTeamList::const_iterator it;
	int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer == 0)
			continue;
		for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
			for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
				Team *team = iter.cur();
				if (!team)
					continue;
				Object *pObj;
				for (DLINK_ITERATOR<Object> oiter = team->iterate_TeamMemberList(); (pObj = oiter.cur()) != 0; oiter.advance()) {
					if (pObj->testStatus(OBJECT_STATUS_02) || pObj->isDisabled())
						continue;
					SpecialPowerModuleInterface *mod = pObj->getSpecialPowerModule(power);
					if (mod) {
						if (!TheSpecialPowerStore->canUseSpecialPower(oiter.cur(), power))
							continue;
						if (mod->isReady())
							return true;
						if (mod->getReadyFrame() < nextFrame)
							nextFrame = mod->getReadyFrame();
					}
				}
			}
		}
	}
	pPower->m_cachedFrame = nextFrame;
	return false;
}
