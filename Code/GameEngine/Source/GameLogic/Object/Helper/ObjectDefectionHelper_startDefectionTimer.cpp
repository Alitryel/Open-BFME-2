// cl: /DNDEBUG /MD
// ?startDefectionTimer@ObjectDefectionHelper@@QAEXI_N@Z, RVA 0x004DF725, 73 bytes.
// ObjectDefectionHelper method over the rowed ObjectHelper base (0x20 bytes,
// Object at +8 via UpdateModule): Object+0x438 bit1 clear sleeps FOREVER via
// rowed UpdateModule::setWakeFrame 0x0044DF71, else current frame from
// TheGameLogic 0x009FE78C +0x40 seeds +0x20/+0x24 window plus arg, 0.0f at
// +0x28 plus bool at +0x2C, then wakes with delay 1. Layout is the rowed
// 0x30-byte class from ObjectDefectionHelperCtor.cpp. Callers at 0x0028C017
// and 0x00298D40 pass (uint, bool).
class Thing;
class ModuleData;

class Object
{
public:
	bool getIsUndetectedDefector() const { return (m_privateStatus & 2) != 0; }
	unsigned char m_pad00[0x438];
	unsigned char m_privateStatus; // +0x438 bit1
};

#include "ObjectDefectionHelperView.h"

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

void ObjectDefectionHelper::startDefectionTimer(unsigned int arg1, bool arg2)
{
	Object *obj = getObject();
	if (!obj->getIsUndetectedDefector()) {
		setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
		return;
	}
	unsigned int cur = TheGameLogic->getFrame();
	m_defectionDetectionStart = cur;
	m_defectionDetectionEnd = cur + arg1;
	m_defectionDetectionFlashPhase = 0.0f;
	m_doDefectorFX = arg2;
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
