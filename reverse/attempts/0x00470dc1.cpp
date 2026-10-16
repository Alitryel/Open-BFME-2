// ?rva00470DC1@HordeContain@@UAEXXZ
// partial score=0.8 date=2026-10-16
// ?rva00470DC1@HordeContain@@UAEXXZ
// FRAGMENT bank (home TU Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// is 159 KB, over the attempt cap). Apply the view patch below to the home TU, append
// the function, and score with SRC=<home TU> SYM=?rva00470DC1@HordeContain@@UAEXXZ RVA=0x470DC1 SIZE=1699.
// State: compiles, all calls resolve, 1700/1699 B, nd179 (W9-O1 scorer). Retail facts: primary
// vtable 0x00C45050 slot 35 (this body) calls slot 36 (unrowed 0x474842, virtual so no reloc);
// +0x11C interface slot 7 (by-value Coord3D) / slot 60 (rva0046F8F4) / slot 107 (rva0046D8AE);
// constants 410 (attack range), 20 (pairing offset), 55 (closest-member spacing), 5 (held
// offset), 0.9 double (held release factor), 2*pi. Open residue: frame slots shifted 4 B (id/
// attacker sharing), slot-60 dir x/y order, TheGameLogic kept in esi across the attack pair
// lookups, +0x120 bit test as shr/test al (ours folds to test byte), angle store tail merges.
//
// ---- view patch (unified diff against the home TU) ----
// --- Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp	2026-10-16 09:39:04.258645917 +0200
// +++ build/o1/hc/c2.cpp	2026-10-16 20:02:54.205685412 +0200
// @@ -185,6 +185,7 @@
//  {
//  public:
//  	bool IsPointOnWall(int pos, bool flag);
// +	void AdjustLayer(Object *obj);
//  	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
//  	bool IsPointOnRamp(const Coord3D *pos);
//  	void RemoveObjectFromPathfindMap(Object *object);
// @@ -581,7 +582,9 @@
//  			unsigned int m_110; // +0x110
//  		};
//  	};
// -	unsigned char m_pad114[0x244 - 0x114];
// +	unsigned char m_pad114[0x120 - 0x114];
// +	unsigned int m_120; // +0x120 (status bits)
// +	unsigned char m_pad124[0x244 - 0x124];
//  	Rva004708BCBehavior **m_244; // +0x244
//  	unsigned char m_pad248[0x250 - 0x248];
//  	Rva0046A2ECContain *m_250; // +0x250
// @@ -814,7 +817,9 @@
//  	_STL::map<int, int> m_1B8; // +0x1B8
//  	unsigned char m_pad1C4[0x1D8 - 0x1C4];
//  	bool m_1D8; // +0x1D8
// -	unsigned char m_pad1D9[0x224 - 0x1D9];
// +	unsigned char m_pad1D9[0x1F0 - 0x1D9];
// +	float m_1F0; // +0x1F0 (held-slot release range)
// +	unsigned char m_pad1F4[0x224 - 0x1F4];
//  	union
//  	{
//  		struct
// @@ -998,8 +1003,8 @@
//  	virtual void slot32(Object *obj) = 0;
//  	virtual void slot33(int a1) = 0;
//  	virtual void rva0046AF85() = 0;
// -	virtual void gap35() = 0;
// -	virtual void gap36() = 0;
// +	virtual void rva00470DC1() = 0;
// +	virtual void rva00474842(Object *obj, const Coord3D *pos, float angle, bool stopped) = 0;
//  	virtual bool rva00470B21() = 0;
//  protected:
//  	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
// @@ -1113,6 +1118,21 @@
//  class Rva00468CB6A;
//  // The rowed 0x0046D946 on the HordeContain base: the contained Object
//  // closest to the argument.
// +// The rowed squared distance from an Object to a point (0x002615E3).
// +class Rva000CBA20Point;
// +class Rva000CBA20 { public: float distSq(const Rva000CBA20Point *p); };
// +// The rowed per-Object formation-slot setter (0x001E431E).
// +class Rva001E431E { public: void rva001E431E(const int *slot); };
// +// The rowed post-update refresh of the horde (0x0046A024).
// +class Rva0046A024 { public: void rva0046A024(); };
// +float ACos(float x);
// +// A +0x1A0 record: the member's held formation position and remaining hold
// +// count (target node +0x14).
// +struct Rva00470DC1Slot
// +{
// +	Coord3D m_position; // +0x00
// +	int m_count; // +0x0C
// +};
//  class Rva0046D946
//  {
//  public:
// @@ -1277,6 +1297,7 @@
//  	Rva0046D158Record *rva0046D158(AsciiString name);
//  	virtual void performReform();
//  	virtual bool rva00470B21();
// +	virtual void rva00470DC1();
//  	Coord2D *rva0046A5B1(Coord2D *offset, int index);
//  	bool rva004723F2(Object *, const AsciiString &);
//  private:
// @@ -1302,7 +1323,7 @@
//  	bool m_198; // +0x198
//  	unsigned char m_pad199[0x19C - 0x199];
//  	int m_19C; // +0x19C
// -	unsigned char m_pad1A0[0x1AC - 0x1A0];
// +	_STL::map<int, int> m_1A0; // +0x1A0 (per-member formation slot: position and hold count)
//  	ObjectID m_1AC; // +0x1AC
//  	ObjectID m_1B0; // +0x1B0
//  	int m_1B4; // +0x1B4
// @@ -1331,7 +1352,9 @@
//  	int m_29C; // +0x29C
//  	int m_2A0; // +0x2A0
//  	bool m_2A4; // +0x2A4
// -	unsigned char m_pad2A5[0x2B8 - 0x2A5];
// +	unsigned char m_pad2A5[0x2B0 - 0x2A5];
// +	ObjectID m_2B0; // +0x2B0 (the formation leader)
// +	unsigned char m_pad2B4[0x2B8 - 0x2B4];
//  	Coord3D m_2B8; // +0x2B8
//  	bool m_2C4; // +0x2C4
//  	unsigned char m_pad2C5[0x2C8 - 0x2C5];
// @@ -4532,3 +4555,163 @@
//  			draw->rva0027541E(&color, 4, 4, 15);
//  	}
//  }
// +
// ?rva00470DC1@HordeContain@@UAEXXZ @0x00470DC1: slot 35 of the primary
// vtable (0x00C45050). Places every contained member that is not keyed in the
// +0x170 tree: the +0x11C interface's slot 7 gives its formation position and
// angle; a facing horde (+0x11C slot 60) faces the leader's heading along the
// offset, otherwise the angle is relative to the horde's Object and is
// adjusted for the +0x24C attack pairing (+0x1AC target, +0x1B0 attacker),
// the +0x1A0 held slots (leader +0x2B0, module data +0x1F0 range) or the
// +0x2B8 rally point; slot 36 then moves the member, standing when the
// horde's AI is idle. The rowed 0x0046A024 refresh follows.
void HordeContain::rva00470DC1()
{
	Rva0046247DPair p;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	Object *self = m_object;
	TheAI->pathfinder()->AdjustLayer(self);
	float baseAngle = self->m_orientation;
	AIUpdateInterface *ai = self->m_ai;
	if (!ai)
		return;
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	Object *leader = TheGameLogic->findObjectByID(m_2B0);
	for (; it != p.m04->end(); )
	{
		Object *obj = *it;
		++it;
		int id = obj->getID();
		if (m_170.find(id) != m_170.end())
			continue;
		float angle = 0.0f;
		Coord3D pos = slot7(obj, &angle);
		if (rva0046F8F4())
		{
			Coord3D dir;
			dir.x = pos.x - self->m_position.x;
			dir.y = pos.y - self->m_position.y;
			dir.z = 0.0f;
			if (dir.y * dir.y + dir.x * dir.x == 0.0f)
				angle = self->m_orientation;
			else
			{
				dir.Normalize2D();
				float a = ACos(dir.x);
				angle = (dir.y < 0.0f) ? 6.2831855f - a : a;
			}
		}
		else
		{
			angle += baseAngle;
			if (m_24C.size())
			{
				if ((unsigned char)(obj->m_120 >> 10) & 1)
				{
					rva0046D8AE();
					break;
				}
				Object *attacker = TheGameLogic->findObjectByID(m_1B0);
				Object *target = TheGameLogic->findObjectByID(m_1AC);
				if (!target || !attacker)
				{
					rva0046D8AE();
					break;
				}
				const Coord3D *targetPos = target->getPosition();
				float dist = ((Rva000CBA20 *)attacker)->distSq((const Rva000CBA20Point *)targetPos);
				if (obj == attacker)
				{
					if (dist < 410.0f)
					{
						((Rva001E431E *)obj)->rva001E431E(&m_1B4);
						angle = obj->GetRelativeAngle(targetPos) + obj->m_orientation;
					}
				}
				else if (obj == target)
				{
					if (dist < 410.0f)
						((Rva001E431E *)obj)->rva001E431E(&m_1B4);
					pos = obj->m_position;
					pos -= attacker->m_position;
					pos.normalize();
					pos *= 20.0f;
					pos += attacker->m_position;
					angle = obj->GetRelativeAngle(&attacker->m_position) + obj->m_orientation;
				}
				else if (dist < 410.0f)
				{
					int slot = reinterpret_cast<_STL::map<int, int> &>(m_24C)[obj->getID()];
					((Rva001E431E *)obj)->rva001E431E(&m_200);
					const Coord3D *attackerPos = &attacker->m_position;
					angle = obj->GetRelativeAngle(attackerPos) + obj->m_orientation;
					pos = obj->m_position;
					pos -= *attackerPos;
					pos.normalize();
					pos *= (float)slot;
					pos += *attackerPos;
					Object *closest = ((Rva0046D946 *)(UpdateModule *)this)->rva0046D946(obj);
					if (closest && ((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)closest->getPosition()) < 55.0f)
					{
						float dx = obj->m_position.x - attackerPos->x;
						float dy = obj->m_position.y - attackerPos->y;
						float dz = obj->m_position.z - attackerPos->z;
						Coord3D side;
						side.x = 0.0f * dz - dy;
						side.y = dx - 0.0f * dz;
						side.z = 0.0f * dy - 0.0f * dx;
						Coord3D toClosest = *closest->getPosition();
						toClosest -= obj->m_position;
						side.normalize();
						float sign = (side.x * toClosest.x + side.z * toClosest.z + side.y * toClosest.y > 0.0f) ? -4 : 4;
						pos.x += sign * side.x;
						pos.y += side.y * sign;
						pos.z += side.z * sign;
					}
				}
			}
			else if (m_1A0.size())
			{
				_STL::map<int, int>::iterator held = m_1A0.find(obj->getID());
				if (held != m_1A0.end())
				{
					Rva00470DC1Slot *slot = (Rva00470DC1Slot *)&held->second;
					if (leader && data->m_1F0 != 0.0f)
					{
						Coord3D offset = obj->m_position;
						offset -= leader->m_position;
						float length = offset.length();
						if (data->m_1F0 * 0.9 > length)
						{
							pos = offset;
							pos.normalize();
							pos.x = pos.x * 5.0f + obj->m_position.x;
							pos.y = pos.y * 5.0f + obj->m_position.y;
							pos.z = pos.z * 5.0f + obj->m_position.z;
						}
						else if (data->m_1F0 > length)
							pos = slot->m_position;
					}
					else
					{
						if (slot->m_count > 0)
						{
							--slot->m_count;
							continue;
						}
						pos = slot->m_position;
					}
				}
				if (leader)
					angle = obj->GetRelativeAngle(leader->getPosition()) + obj->m_orientation;
			}
			else if (m_2C4)
				angle = obj->GetRelativeAngle(&m_2B8) + obj->m_orientation;
		}
		rva00474842(obj, &pos, angle, !ai->isMoving());
	}
	((Rva0046A024 *)(UpdateModule *)this)->rva0046A024();
}
