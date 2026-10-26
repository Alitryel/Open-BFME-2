#pragma once

// Shared accessed prefixes from the matched traversal, nemesis and contain bodies.
// Traversal proves contain-head +0x10; nemesis methods prove ID/time +0x20/+0x24.
// Object fields retain their existing target offsets; complete types are unknown.

class Object;
class Player;
class BodyModuleInterface;

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
    int getContainMax() const;
    void addToContainList(Object *object);
    void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
    void healObjects(float frames);
    static void healObject(Object *object, void *frames);
    Object *getCurNemesis();
    void updateNemesis(const Object *target);
private:
    char m_unrecovered00[0x10];
    TunnelContainedNode *m_containHead;
    char m_unrecovered14[4];
    int m_containListSize;
    unsigned int m_tunnelCount;
    int m_curNemesisID;
    unsigned int m_nemesisTimestamp;
};

class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void rva0028FB6F(void *param);
	bool rva002943B2(const Player *viewer);
	bool isEffectivelyDead() const { return (m_deadFlag & 1) != 0; }
	int getID() const { return m_id; }
	char m_pad00[4];
	void *m_template;
	char m_pad08[0x74 - 8];
	int m_id;
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254, healing callback
	char m_pad258[0x274 - 0x258];
	void *m_274;
	char m_pad278[4];
	unsigned int m_containedByFrame; // +0x27C, healing callback
	char m_pad280[0x438 - 0x280];
	unsigned char m_deadFlag;
};

