#pragma once

// Shared accessed receiver for the existing destructor, decal and transfer rows.
// Native rows place Object at +0x08, the update interfaces at +0x0C/+0x10,
// state at +0x20, the boolean at +0x40 and the decal array at +0x50.
// Preserve the seed's incomplete base interfaces and existing member names;
// this does not adopt the separate update donor's interface declarations.
// Keep Xfer operands beside its include to withstand merge include hoisting.

class AsciiString;
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

#include "../../../../Include/Common/BfmeXfer.h"


class Xfer;
class Thing;

class ModuleData;

class Player;

class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() {}
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() {}
};

struct Coord3D;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
};

class RadiusDecal
{
public:
	void clear();
public:
	void setPosition(const Coord3D &pos);
	void setOpacity(float opacity);
private:
	const void *m_template;
private:
	void *m_decal;
private:
	unsigned char m_empty;
private:
	unsigned char m_pad_09[3];
private:
	float m_unknown0C;
public:
	RadiusDecal();
public:
	~RadiusDecal();
};

class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *owningPlayer, RadiusDecal &result) const;
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	virtual ~DynamicShroudClearingRangeUpdate();
public:
	void killGridDecals();
	void rva0048B256();
	void xfer(Xfer *xfer);
private:
	int m_state;
private:
	int m_stateCountDown;
private:
	int m_totalFrames;
private:
	unsigned int m_growStartDeadline;
private:
	unsigned int m_sustainDeadline;
private:
	unsigned int m_shrinkStartDeadline;
private:
	unsigned int m_doneForeverFrame;
private:
	unsigned int m_changeIntervalCountdown;
private:
	bool m_decalsCreated;
private:
	unsigned char m_pad_41[3];
private:
	float m_visionChangePerInterval;
private:
	float m_nativeClearingRange;
private:
	float m_currentClearingRange;
private:
	RadiusDecal m_gridDecal[30];
public:
	void createGridDecals(const RadiusDecalTemplate &tmpl, float radius, const Coord3D &pos);
};
