// cl: /O1 /G7 /arch:SSE /MD
// ActionManager receiver proven by native488B2E and WB11CB926. BFME1
// a7c38d3b2597 ActionManager_canResumeConstructionOf_Thunk.cpp establishes
// the same operation; BFME2 retains its own template/status/object offsets.
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2
};

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x109];
	unsigned char m_flags109;               // +0x109 bit 0x40
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
	bool testStatus(ObjectStatusTypes s) const;
	ObjectID getSoleHealingBenefactor() const;

	unsigned char m_pad00[4];
	ThingTemplate *m_template;               // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;                           // +0x74
	unsigned char m_pad78[0x438 - 0x78];
	unsigned char m_flags438;                // +0x438 bit0
};

enum CommandSourceType { CMD_FROM_UNRECONSTRUCTED = 0 };
class ActionManager {
public:
 bool canResumeConstructionOf(const Object *a, const Object *b, CommandSourceType);
};

bool ActionManager::canResumeConstructionOf(const Object *a, const Object *b, CommandSourceType)
{
	if (a == 0 || b == 0)
		return false;
	if ((a->m_template->m_flags109 & 0x40) == 0)
		return false;
	Relationship r = a->getRelationship(b);
	if (r != ALLIES)
		return false;
	if (!b->testStatus((ObjectStatusTypes)r))
		return false;
	if ((a->m_flags438 & 1) != 0)
		return false;
	ObjectID ben = b->getSoleHealingBenefactor();
	if (ben != 0 && ben != a->m_id)
		return false;
	return true;
}
