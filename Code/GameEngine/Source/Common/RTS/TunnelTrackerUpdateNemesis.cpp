// cl: /DNDEBUG /MD
//
// ?updateNemesis@TunnelTracker@@QAEXPBVObject@@@Z @0x004F5935 (74B).
// TunnelTracker nemesis refresh: when no current nemesis and the target
// carries a vehicle/structure/infantry/aircraft kind bit in its template
// dword at +0x108, takes its ID at +0x74 into +0x20; when the current
// nemesis equals the target, refreshes the timestamp at +0x24 from the
// GameLogic frame at +0x40. Rowed getCurNemesis 0x004F5684 twice, rowed
// TheGameLogic. Donors BFME1 TunnelTracker.cpp:130 and ZH variant.

class Object
{
public:
	void rva0028FB6F(void *param);
	int getID() const { return m_id; }
	char m_pad00[4];
	void *m_template;
	char m_pad08[0x74 - 8];
	int m_id;
	char m_pad78[0x274 - 0x78];
	void *m_274;
};

struct ObjectTemplate
{
	char m_pad[0x108];
	unsigned int m_kind;
};

#include "../GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

typedef void (__cdecl *ContainIterateFunc)(Object *object, void *userData);

struct TunnelContainedNode
{
    TunnelContainedNode *m_next;
    TunnelContainedNode *m_prev;
    Object *m_object;
};

class TunnelTracker
{
public:
    void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
    void healObjects(float frames);
    static void healObject(Object *object, void *frames);
    Object *getCurNemesis();
    void updateNemesis(const Object *target);
private:
    char m_unrecovered00[0x10];
    TunnelContainedNode *m_containHead;
    char m_unrecovered14[0x20 - 0x14];
    int m_curNemesisID;
    unsigned int m_nemesisTimestamp;
};

void TunnelTracker::updateNemesis(const Object *target)
{
	if (getCurNemesis() == 0) {
		if (target != 0) {
			unsigned int kind = ((ObjectTemplate *)*(void *const *)((const char *)target + 4))->m_kind;
			if (((kind >> 8) & 0x13) == 0 && (kind & 0x80) == 0)
				return;
			m_curNemesisID = target->getID();
			m_nemesisTimestamp = TheGameLogic->getFrame();
		}
	} else if (getCurNemesis() == target) {
		m_nemesisTimestamp = TheGameLogic->getFrame();
	}
}
