// ?computeApproachTarget@Weapon@@QBE_NPBVObject@@0PBUCoord3D@@MAAU3@@Z
// partial score=0.85 date=2026-10-14
// ?computeApproachTarget@Weapon@@QBE_NPBVObject@@0PBUCoord3D@@MAAU3@@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
#include "Code/Libraries/Include/Lib/Coord3D.h"

float Cos(float);
float Sin(float);
extern "C" float atan2f(float, float);
extern "C" double fabs(double);

void clipToTerrainExtent(Coord3D &pos);

class WeaponTemplate
{
public:
	float getMinimumAttackRange() const;
};

class Object;
class Pathfinder
{
public:
	bool AdjustTargetDestination(Object *source, int target, int pos, int weapon, const Coord3D *approachTargetPos);
};

class AI;
class Thing
{
public:
	bool isAboveTerrain() const;
};

class AIUpdateInterface
{
public:
	bool isAircraftThatAdjustsDestination() const;
};

class Object : public Thing
{
public:
	Coord3D *rva00265514(Coord3D *out, const Object *that) const;
	Coord3D *rva002C986B(Coord3D *out, const Coord3D *pos) const;
};

class Rva002C9BC3Owner
{
public:
	float rva002C9BC3(void *a, void *b);
};

class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *a, float b);
};

class Weapon
{
public:
	bool computeApproachTarget(const Object *source, const Object *target, const Coord3D *pos, float angleOffset, Coord3D &approachTargetPos) const;
private:
	void *m_pad00;
	WeaponTemplate *m_template;
};

struct AIView { char pad[0x10]; Pathfinder *m_pathfinder; };
extern AI *TheAI;

bool Weapon::computeApproachTarget(const Object *source, const Object *target, const Coord3D *pos, float angleOffset, Coord3D &approachTargetPos) const
{
	const Coord3D *targetPos;
	Coord3D dir;
	if (target)
	{
		targetPos = (const Coord3D *)((const char *)target + 0x38);
		Coord3D raw;
		target->rva00265514(&raw, source);
		dir = raw;
	}
	else if (pos)
	{
		targetPos = pos;
		Coord3D raw;
		source->rva002C986B(&raw, pos);
		dir = raw;
		dir.x = -dir.x;
		dir.y = -dir.y;
		dir.z = -dir.z;
	}
	else
	{
		approachTargetPos.x = 0.0f;
		approachTargetPos.y = 0.0f;
		approachTargetPos.z = 0.0f;
		return false;
	}

	float dist = dir.length();
	float minAttackRange = m_template->getMinimumAttackRange();
	if (minAttackRange > 10.0f && dist < minAttackRange)
	{
		const Coord3D *srcPos = (const Coord3D *)((const char *)source + 0x38);
		dir.x = srcPos->x - targetPos->x;
		dir.y = srcPos->y - targetPos->y;
		dir.z = srcPos->z - targetPos->z;
		dir.normalize();

		if (source->isAboveTerrain())
		{
			float angle = atan2f(-dir.y, -dir.x);
			float relAngle = *(const float *)((const char *)source + 0x44) - angle;
			if (relAngle > 6.2831855f)
				relAngle -= 6.2831855f;
			if (relAngle < -6.2831855f)
				relAngle += 6.2831855f;
			if (fabs(relAngle) < 1.5707964f)
			{
				dir.x = -dir.x;
				dir.y = -dir.y;
				dir.z = -dir.z;
			}
		}

		if (angleOffset != 0.0f)
		{
			float angle = atan2f(dir.y, dir.x);
			dir.x = Cos(angle + angleOffset);
			dir.y = Sin(angle + angleOffset);
		}

		float attackRange = (((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)source, (void *)targetPos) + minAttackRange) / 2.0f;
		for (int i = 0; i < 10; ++i)
		{
			if (target)
				attackRange += *(const float *)((const char *)target + 0xbc);
			attackRange += *(const float *)((const char *)source + 0xbc);
			float newRange = ((Rva002C9B80Owner *)this)->rva002C9B80((void *)source, -attackRange * dir.z);
			if (attackRange <= newRange)
				break;
			attackRange = newRange;
		}

		approachTargetPos.x = attackRange * dir.x + targetPos->x;
		approachTargetPos.y = attackRange * dir.y + targetPos->y;
		approachTargetPos.z = attackRange * dir.z + targetPos->z;
		clipToTerrainExtent(approachTargetPos);
		return false;
	}

	if (dist < 0.001f)
	{
		approachTargetPos = *(const Coord3D *)((const char *)source + 0x38);
		return true;
	}

	dir.x /= dist;
	dir.y /= dist;
	dir.z /= dist;

	if (angleOffset != 0.0f)
	{
		float angle = atan2f(dir.y, dir.x);
		dir.x = Cos(angle + angleOffset);
		dir.y = Sin(angle + angleOffset);
	}

	float attackRange = ((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)source, (void *)targetPos) * 0.9f;
	if (dir.z != 0.0f)
	{
		for (int i = 0; i < 10; ++i)
		{
			float newRange = ((Rva002C9B80Owner *)this)->rva002C9B80((void *)source, -attackRange * dir.z);
			if (attackRange <= newRange)
				break;
			attackRange = newRange * 0.9f;
		}
	}

	approachTargetPos.x = attackRange * dir.x + targetPos->x;
	approachTargetPos.y = attackRange * dir.y + targetPos->y;
	approachTargetPos.z = attackRange * dir.z + targetPos->z;

	AIUpdateInterface *ai = *(AIUpdateInterface *const *)((const char *)source + 0x258);
	if (ai && ai->isAircraftThatAdjustsDestination())
		((AIView *)TheAI)->m_pathfinder->AdjustTargetDestination((Object *)source, (int)target, (int)pos, (int)this, &approachTargetPos);
	return false;
}
