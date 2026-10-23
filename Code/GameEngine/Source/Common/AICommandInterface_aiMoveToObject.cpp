// cl: /EHs /MD
// ?aiMoveToObject@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z @0x00352ECA 101B
// AICommandInterface::aiMoveToObject: command 0x01 is Zero Hour's AICMD_MOVE_TO_OBJECT,
// and ScriptActions::doMoveUnitTowardsNearest calls here where Zero Hour calls aiMoveToObject.
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x01 and src,
// m_obj from param1, virtual slot 0 call, then inlined vector-free via rowed free 0x00030830.
// Evidence: immediates 0x01 0x00351BD0 0x00030830; callers 0x003539E7 0x003C94F9 0x003C979D;
// precedent Rva0047ED64AICommand.cpp 101B same recipe with 0x2E, sibling 0x00352F9D 110B.
#include <stddef.h>

extern "C" void __cdecl free(void *p);

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_MOVE_TO_OBJECT = 1
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct RvaCoords
{
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;

	~RvaCoords()
	{
		if (m_start)
			free(m_start);
	}
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	void *m_obj;
	void *m_otherObj;
	const void *m_team;
	RvaCoords m_coords;
	char m_tail[0xC0 - 0x2C];
};

class Object;

class AICommandInterface
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void aiMoveToObject(Object *obj, CommandSourceType src);
};

void AICommandInterface::aiMoveToObject(Object *obj, CommandSourceType src)
{
	AICommandParms parms(AICMD_MOVE_TO_OBJECT, src);
	parms.m_obj = obj;
	rvaVirtual(&parms);
}
