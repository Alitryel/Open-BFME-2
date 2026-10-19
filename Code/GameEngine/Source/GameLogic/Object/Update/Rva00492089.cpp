// cl: /MD
// ?moveToStuff@Rva00492089@@QAEXPAX@Z @0x00492089 44B
// Evidence: callees rowed BeginTemporaryStateMachine 0x002632EE and rva00352ECA 0x00352ECA; caller 0x00492114 passes factory pointer; [esi+8]+0x258 AI pointer with +0x20 command iface.
// Links: no literals, callees by row names.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_PLAYER2 = 2
};

class Object;

class AICommandInterface
{
public:
	void aiMoveToObject(Object *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	void BeginTemporaryStateMachine();
private:
	char m_pad[0x20];
public:
	AICommandInterface m_cmd;
};

class Thing
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class Rva00492089
{
public:
	char m_pad[8];
	Thing *m_thing;
	void moveToStuff(void *arg);
};

void Rva00492089::moveToStuff(void *arg)
{
	m_thing->m_ai->BeginTemporaryStateMachine();
	m_thing->m_ai->m_cmd.aiMoveToObject((Object *)arg, CMD_FROM_PLAYER2);
}
