// cl: /DNDEBUG /MD
//
// ?isIdle@AIGroup@@QBE_NXZ, retail 0x0036DF4D, 69B.
// BFME1 AIGroupStatePredicates donor isIdle (0x151280 73B) via ZH AIGroup.
// Evidence: same list loop as groupAttackTeam/groupHunt in AIGroupAttackTeam;
// Object+0x258 AIUpdate (existing) plus +0x438 bit0 EFFECTIVELY_DEAD (Turret
// precedent); AIUpdateInterface::isIdle virtual slot 110 (+0x1b8) for BFME2
// (BFME1 slot 96); callers at 0x20C9E0 0x20CCAF 0x2624DF 0x372C08 0x378A38.

#include <list>

typedef bool Bool;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual Bool isIdle() const;
};

class Object
{
public:
	__declspec(dllimport) __forceinline const AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	char m_pad258[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;
};

class AIGroup
{
public:
	Bool isIdle() const;
	void setMineClearingDetail(Bool set);

private:
	std::list<Object *> m_memberList;
};

Bool AIGroup::isIdle() const
{
	Bool isIdle = true;
	std::list<Object *>::const_iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		Object *obj = *i;
		if (!obj) {
			continue;
		}

		const AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}

		isIdle = ai->isIdle() || obj->isEffectivelyDead();
		if (!isIdle) {
			return false;
		}
	}

	return isIdle;
}

// ZH names the dispatcher MSG_SET_MINE_CLEARING_DETAIL operation. BFME2's
// implementation is empty: WB table F54016 sends message 1099 to F4E9D0,
// which passes true to EEAB50 (only a debug frame and RET4). The retail
// case at 7793CA passes the same selected-group receiver and true to the
// shared RET4 at 87A69C. No AIGroup layout is accessed by this method.
void AIGroup::setMineClearingDetail(Bool set)
{
}
