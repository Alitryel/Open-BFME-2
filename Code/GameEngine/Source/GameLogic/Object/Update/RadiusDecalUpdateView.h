// Shared, TU-scoped RadiusDecalUpdate constructor/create prefix.
// Target constructor and destructor prove the base span 0x20, decal span 0x10
// and later flag at +0x30. The create body reads the decal byte at +0x28,
// distinct from that flag; RadiusDecal::clear/ctor establish its empty byte.
// These declarations preserve the existing constructor's interface spellings;
// they do not establish original BFME 2 header names or a canonical class.
#ifndef BFME_RADIUS_DECAL_UPDATE_VIEW_H
#define BFME_RADIUS_DECAL_UPDATE_VIEW_H

class Thing;
class ModuleData;
class Object;
class Player;
struct Coord3D;
enum UpdateSleepTime {};

class Object
{
public:
    Player *getControllingPlayer() const;
};

class RadiusDecal;

class RadiusDecalTemplate
{
public:
    void createRadiusDecal(const Coord3D &, float, const Player *, RadiusDecal &) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *, UpdateSleepTime);

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
    friend class RadiusDecalUpdate;
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate : public UpdateModule
{
public:
	RadiusDecalUpdate(Thing *, const ModuleData *);
	virtual ~RadiusDecalUpdate();
    void createRadiusDecal(const RadiusDecalTemplate &, float, const Coord3D &);
    void killRadiusDecal();

private:
	RadiusDecal m_deliveryDecal;
	bool m_killWhenNoLongerAttacking;
};


#endif
