#pragma once

// Shared measured receiver for the update and cached-name-key bodies only.
// Primary data +4, object +8, other interface +C, update interface +10;
// deposit state +20, flags +24/+25. Primary slots 0..3 remain incomplete;
// the existing pool key is slot 4 (re_attempts.log, 0x0049A1CA).
// No constructor or primary vtable is emitted through this partial view.
class ModuleData;
class Object;
class Player;
class AutoDepositUpdateModuleData;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

enum NameKeyType
{
    NK_UNKNOWN = 0
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	virtual void primarySlot1();
	virtual void primarySlot2();
	virtual void primarySlot3();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AutoDepositUpdate : public UpdateModule
{
public:
	void awardInitialCaptureBonus( Player *player );
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;

protected:
	const AutoDepositUpdateModuleData *getAutoDepositUpdateModuleData() const
	{
		return (const AutoDepositUpdateModuleData *)m_moduleData;
	}

	unsigned int m_depositOnFrame; // +0x20
	bool m_awardInitialCaptureBonus; // +0x24
	bool m_initialized; // +0x25
};

