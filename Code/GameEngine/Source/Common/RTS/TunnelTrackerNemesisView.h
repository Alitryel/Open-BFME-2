#pragma once

// Shared accessed prefixes from the three matched TunnelTracker consumers.
// Traversal proves contain-head +0x10; nemesis methods prove ID/time +0x20/+0x24.
// Object fields retain their existing target offsets; complete types are unknown.

class Object;
class Player;

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

class Object
{
public:
	void rva0028FB6F(void *param);
	bool rva002943B2(const Player *viewer);
	bool isEffectivelyDead() const { return (m_deadFlag & 1) != 0; }
	int getID() const { return m_id; }
	char m_pad00[4];
	void *m_template;
	char m_pad08[0x74 - 8];
	int m_id;
	char m_pad78[0x274 - 0x78];
	void *m_274;
	char m_pad278[0x438 - 0x278];
	unsigned char m_deadFlag;
};

