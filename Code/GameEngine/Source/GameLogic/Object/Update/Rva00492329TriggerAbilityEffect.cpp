// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ?rva00492329@Rva00492179@@UAEXXZ, retail 0x00492329 (185 B): the slot-17
// (offset 0x44) override of SpecialAbilityUpdate (triggerAbilityEffect,
// pinned 0x0045108D) for the Rva00492179 class (ctor 0x00492179, vtable
// 0x0084DEF8). Target evidence: base slot call first, then the module
// data at +4 (AsciiString +0xC8, int +0xCC, bools +0xD0/+0xD1) and the
// object at +8 (AI holder +0x258 with its command interface at +0x20).
// The WorldBuilder twin (0x011E3630) spells the tail as two if/else arms
// that each test and set one model condition (0xBA or 0xDC); retail's cl
// merges the arms into one call pair with the condition in EBX.
#include "ascii_string.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KIND_BA = 0xBA,
	KIND_DC = 0xDC
};

enum ModelConditionFlagType
{
	MODELCOND_BA = 0xBA,
	MODELCOND_DC = 0xDC
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

struct Rva00492329AIHolder
{
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	bool addAttributeModifierToPool(const AsciiString &name, int v);

	unsigned char m_pad00[0x258];
	Rva00492329AIHolder *m_ai; // +0x258
};

class Rva00492179ModuleData
{
public:
	unsigned char m_pad[0xC8];
	AsciiString m_attributeModifier; // +0xC8
	int m_conditionFrames; // +0xCC
	bool m_D0;
	bool m_idleAI; // +0xD1
};

class SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();

protected:
	const Rva00492179ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x88 - 0x0C];
};

class Rva00492179 : public SpecialAbilityUpdate
{
public:
	virtual void rva00492329();
};

void Rva00492179::rva00492329()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const Rva00492179ModuleData *data = m_moduleData;
	Object *object = m_object;
	if (data->m_idleAI)
	{
		Rva00492329AIHolder *ai = object->m_ai;
		if (ai != 0)
			ai->m_commands.aiIdle(CMD_FROM_AI);
	}
	if (!((const StringBase<char> &)data->m_attributeModifier).isEmpty())
	{
		AsciiString name(((const StringBase<char> &)data->m_attributeModifier).str());
		object->addAttributeModifierToPool(name, -1);
	}
	if (data->m_D0)
	{
		if (!object->isKindOf(KIND_BA))
			object->setSpecialModelConditionState(MODELCOND_BA, (unsigned int)data->m_conditionFrames);
	}
	else
	{
		if (!object->isKindOf(KIND_DC))
			object->setSpecialModelConditionState(MODELCOND_DC, (unsigned int)data->m_conditionFrames);
	}
}
