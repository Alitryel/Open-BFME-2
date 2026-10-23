// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor through ILT 0x000212B5. The
// registration string and 0x24-byte allocation identify the retail-only
// DelayedWeaponSetUpgradeUpdate class.
//
// The base constructor call is retail's UpdateModule::UpdateModule at
// 0x00253390 (its own row in UpdateModuleCtor.cpp), so UpdateModule's
// constructor and destructor are declared, never defined here. The class
// view is the one DelayedWeaponSetUpgradeUpdateDtor.cpp uses: the
// UpdateModule middle slots at +0x0C/+0x10 and the
// DelayedUpgradeUpdateInterface slot at +0x20, then the most-derived class
// overwrites all four vftable slots.

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();

private:
	unsigned int m_storage[2];
};

class BehaviorModuleInterface
{
public:
	virtual void anchor();
};

class BehaviorModule : public Module, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void anchor();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

private:
	unsigned int m_storage[3];
};

class DelayedUpgradeUpdateInterface
{
public:
	virtual void setDelay();
};

class DelayedWeaponSetUpgradeUpdate : public UpdateModule, public DelayedUpgradeUpdateInterface
{
public:
	DelayedWeaponSetUpgradeUpdate(Thing *, const ModuleData *);

protected:
	virtual ~DelayedWeaponSetUpgradeUpdate();
};

// ??0DelayedWeaponSetUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DelayedWeaponSetUpgradeUpdate::DelayedWeaponSetUpgradeUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
}
