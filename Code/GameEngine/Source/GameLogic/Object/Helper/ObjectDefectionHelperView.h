#pragma once

// Shared accessed receiver view for the three ObjectDefectionHelper consumers.
// Native ctor 0x0028C955 and startDefectionTimer 0x004DF725 place the tail at
// +0x20/+0x24/+0x28/+0x2C. update 0x004DF547 enters through the +0x10
// interface. Member names come from the existing ZH-backed update source;
// this view does not claim the complete BFME 2 base-class interfaces.
// Keep Xfer operand declarations with its include so TU include hoisting
// cannot put BfmeXfer.h before its required operand types.

class Object;
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


enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	Object *getObject() const { return m_object; }

private:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

class ObjectDefectionHelper : public ObjectHelper
{
public:
	virtual UpdateSleepTime update();
	void startDefectionTimer(unsigned int duration, bool doFX);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_defectionDetectionStart;																		///< 0x20
	unsigned int m_defectionDetectionEnd;																			///< 0x24
	float m_defectionDetectionFlashPhase;																			///< 0x28
	bool m_doDefectorFX;																											///< 0x2C
};
