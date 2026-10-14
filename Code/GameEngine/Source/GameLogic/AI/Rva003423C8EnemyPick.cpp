// cl: /MD /GX
//
// Retail 0x003423C8..0x00342469 (161 bytes, RET 4), AIStates.cpp line 16798
// (the GetGameLogicRandomValue file/line pair; WorldBuilder 0x00E31180,
// unnamed, line 16787). A thiscall member that ignores `this`: with even
// odds it asks TheAI first for the closest enemy (AI::findClosestEnemy
// 0x002FFFA3, qualifier 2, no priority, no filter) and falls back to the
// rowed AI::rva002FDBC4 0x002FDBC4, or the reverse, each within twice the
// object's vision range. It lies between AIFaceState::onExit and
// AIRampageState::xfer; its owner and name are not established, so they are
// address-derived.
class Object
{
public:
	float getVisionRange() const;
};

class AttackPriorityInfo;
class PartitionFilter;

class AI
{
public:
	Object *rva002FDBC4(const Object *me, float range, unsigned int flags);
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int bfmeArg);
};
extern AI *TheAI;

int GetGameLogicRandomValue(int low, int high, char *file, int line);

class Rva003423C8
{
public:
	Object *rva003423C8(Object *obj);
};

Object *Rva003423C8::rva003423C8(Object *obj)
{
	Object *victim;
	if (GetGameLogicRandomValue(1, 2,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp",
		16798) == 1)
	{
		victim = TheAI->findClosestEnemy(obj, obj->getVisionRange() * 2.0f, 2, 0, 0, 0);
		if (victim == 0)
			return TheAI->rva002FDBC4(obj, obj->getVisionRange() * 2.0f, 2);
	}
	else
	{
		victim = TheAI->rva002FDBC4(obj, obj->getVisionRange() * 2.0f, 2);
		if (victim == 0)
			return TheAI->findClosestEnemy(obj, obj->getVisionRange() * 2.0f, 2, 0, 0, 0);
	}
	return victim;
}
