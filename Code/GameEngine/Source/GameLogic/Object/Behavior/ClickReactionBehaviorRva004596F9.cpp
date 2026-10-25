// cl: /DNDEBUG /MD /EHsc
//
// ?rva004596F9@ClickReactionBehavior@@UAEXXZ, retail 0x004596F9 (363 bytes).
// Slot 1 of the ClickReactionBehavior interface at +0x20 (vtable 0x00841188;
// slot 0 is the unrowed 0x004543E3, slot 2 the rowed 0x00459864 that the
// matched ctor 0x0045961D's sibling slots reach). Its fields are the two the
// ctor clears and the rowed xfer 0x00459579 saves: the click count at +0x24
// and the reaction cool-down at +0x28.
//
// A click is counted when the owner has a drawable, is not in the status
// bit 8 / model conditions 162 and 172 states and is idle (AI slot 110): the
// module data's +0x08 weight is added to the count, which is clamped to five
// times the weight (std::min over addresses, as WB 0x01178F60 shows). With no
// cool-down running the reaction number is count / weight; at three or less it
// is rerolled with GetGameLogicRandomValue(1, 3). Reactions 1..5 set model
// conditions 164..168 (word +0x120 bits 4..8), the drawable's pending
// conditions are applied (0x00274176 false) and the cool-down becomes the
// module data's per-reaction frame count (+0x0C array of five).
// WB's debug body gives the order; retail's identity beyond that is not
// established, so the name stays address-derived. Retail's dec chain tests
// reactions 1..5 and has no branch after the fifth test: the switch's
// `default` repeats case 5's statement, which cl tail-merges into the same
// block (a lone default drops the fifth test, a lone case 5 keeps a jne).

class Thing;
class ModuleData;
class Drawable;

#include "ClickReactionObjectView.h"

struct ClickReactionBehaviorModuleData
{
	unsigned char m_pad00[0x08];
	int m_weight; // +0x08
	int m_cooldown[5]; // +0x0C
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class ClickReactionBehaviorIface
{
public:
	virtual void slot0();
	virtual void rva004596F9();
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

class UpdateModuleView : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ClickReactionBehavior : public UpdateModuleView, public ClickReactionBehaviorIface
{
public:
	virtual void slot0();
	virtual void rva004596F9();
private:
	int m_clicks; // +0x24
	int m_cooldown; // +0x28
};

static __forceinline const int &minRef(const int &a, const int &b)
{
	if (a < b)
		return a;
	return b;
}

// ?rva004596F9@ClickReactionBehavior@@UAEXXZ @0x004596F9
void ClickReactionBehavior::rva004596F9()
{
	const ClickReactionBehaviorModuleData *data = (const ClickReactionBehaviorModuleData *)m_moduleData;
	Object *obj = m_object;
	if (!obj)
		return;
	Drawable *draw = obj->getDrawable();
	if (!draw)
		return;
	if (testWordBit((const unsigned int *)((Rva0028B7AELeaGetter *)obj)->get(), 8))
		return;
	if (obj->testCondition(162))
		return;
	if (obj->testCondition(172))
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai || !ai->isIdle())
		return;
	int weight = data->m_weight;
	if (weight <= 0)
		return;
	m_clicks += weight;
	int limit = weight * 5;
	{
		const int &chosen = minRef(limit, m_clicks);
		m_clicks = chosen;
	}
	if (m_cooldown > 0)
		return;
	int reaction = m_clicks / weight;
	if (reaction <= 3)
		reaction = GetGameLogicRandomValue(1, 3, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\ClickReactionBehavior.cpp", 116);
	if (reaction <= 0)
		return;
	__assume(reaction <= 5);
	switch (reaction)
	{
	case 1:
		obj->setModelConditionState(164);
		break;
	case 2:
		obj->setModelConditionState(165);
		break;
	case 3:
		obj->setModelConditionState(166);
		break;
	case 4:
		obj->setModelConditionState(167);
		break;
	case 5:
		obj->setModelConditionState(168);
		break;
	default:
		obj->setModelConditionState(168);
		break;
	}
	draw->rva00274176(false);
	int index = reaction - 1;
	if (index >= 0 && index < 5)
		m_cooldown = data->m_cooldown[index];
}
