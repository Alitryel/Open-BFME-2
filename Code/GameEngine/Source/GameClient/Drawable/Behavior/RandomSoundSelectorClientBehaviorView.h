// TU-private view shared by the selected-value and Xfer/reroll units.
// Target accesses establish chance +0x1D4, selected value +0x1D8, selected
// flag +0x1DC and reroll flag +0x1DD. The instance fields stay at +0x10/+0x14.
#ifndef BFME_RANDOM_SOUND_SELECTOR_CLIENT_BEHAVIOR_VIEW_H
#define BFME_RANDOM_SOUND_SELECTOR_CLIENT_BEHAVIOR_VIEW_H

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

class Thing;

class ModuleData;

class Object;

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad[0x1D4];
	float m_chance;
	unsigned int m_selectedValue;
	bool m_selectedFlag;
	bool m_rerollOnEveryFrame;
};

#include "../../../../Include/Common/BfmeXfer.h"

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SoundSelectorSecondary
{
public:
	virtual bool getSelectedValue(unsigned int *value);
};

class RandomSoundSelectorClientBehavior : public ObjectModule, public SoundSelectorSecondary
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual bool getSelectedValue(unsigned int *value);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void reroll();

	float m_randomSelection;
	unsigned int m_lastFrame;
};

#endif
