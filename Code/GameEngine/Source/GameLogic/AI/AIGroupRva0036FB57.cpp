// cl: /DNDEBUG /MD
// ?rva0036FB57@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@H@Z @0x0036FB57 110B
// Evidence: pin AIGroup; BfmeC986 ready guard 0x0036E357 plus step 0x005494A0; same list-at-+0 plus Object+0x258 plus +0x20 subobject mode switch as Rva0036FAF8Group (mode1 rowed rva00352F9D with 0x7FFFFFFF mode0 rowed aiFollowWaypointPathAsTeam); no m_410 clear like AIGroupWaypointMode; callers 0x003BF4B0 0x003BF5DE.
#include <list>

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Rva00352F9D
{
public:
	void rva00352F9D(const void *waypoint, int intVal, CommandSourceType cmdSource);
};

class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	union
	{
		AICommandInterface m_commands;
		Rva00352F9D m_rvaHolder;
	};
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void rva0036FB57(const Waypoint *waypoint, CommandSourceType cmdSource, int mode);
	void createFormation(int a, int b);
	bool rva0036E357();	// 0x0036E357
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FB57(const Waypoint *waypoint, CommandSourceType cmdSource, int mode)
{
	if (!rva0036E357())
		return;
	createFormation(cmdSource, mode);
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai == 0)
			continue;
		switch (mode)
		{
		case 1:
			reinterpret_cast<Rva00352F9D*>(&ai->m_commands)->rva00352F9D(waypoint, 0x7FFFFFFF, cmdSource);
			break;
		case 0:
			ai->m_commands.aiFollowWaypointPathAsTeam(waypoint, cmdSource);
			break;
		default:
			break;
		}
	}
}
