// ?rva00470DC1@HordeContain@@UAEXXZ
// partial score=0.9 date=2026-10-20
// ?rva00470DC1@HordeContain@@UAEXXZ, retail 0x470DC1 (1699 B). Fragment bank: apply the view patch below to
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp, then append the body (build/nbr/r28/470dc1/gen.py).
// Compiles 1688/1699, all calls resolved, no hacks; all 148 home rows stay exact.
#if 0 /* view patch */
--- Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp	2026-10-19 21:52:59.962668500 +0200
+++ build/nbr/r28/470dc1/HordeContainIface11CSlots.best.cpp	2026-10-20 01:07:16.167880200 +0200
@@ -192,6 +192,7 @@
 {
 public:
 	bool IsPointOnWall(int pos, bool flag);
+	void AdjustLayer(Object *obj);
 	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
 	bool IsPointOnRamp(const Coord3D *pos);
 	void RemoveObjectFromPathfindMap(Object *object);
@@ -839,7 +840,8 @@
 	_STL::map<int, int> m_1B8; // +0x1B8
 	unsigned char m_pad1C4[0x1D8 - 0x1C4];
 	bool m_1D8; // +0x1D8
-	unsigned char m_pad1D9[0x1F4 - 0x1D9];
+	unsigned char m_pad1D9[0x1F0 - 0x1D9];
+	float m_1F0; // +0x1F0
 	Rva00469851Names m_1F4;
 	unsigned char m_pad200[0x218 - 0x200];
 	Rva00469851Names m_218;
@@ -1029,8 +1031,8 @@
 	virtual void slot32(Object *obj) = 0;
 	virtual void slot33(int a1) = 0;
 	virtual void rva0046AF85() = 0;
-	virtual void gap35() = 0;
-	virtual void gap36() = 0;
+	virtual void rva00470DC1() = 0;
+	virtual void rva00474842(Object *obj, const Coord3D *pos, float angle, bool stopped) = 0;
 	virtual bool rva00470B21() = 0;
 protected:
 	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
@@ -1144,6 +1146,16 @@
 class Rva00468CB6A;
 // The rowed 0x0046D946 on the HordeContain base: the contained Object
 // closest to the argument.
+class Rva000CBA20Point;
+class Rva000CBA20 { public: float distSq(const Rva000CBA20Point *p); };
+class Rva001E431E { public: void rva001E431E(const int *slot); };
+class Rva0046A024 { public: void rva0046A024(); };
+float ACos(float x);
+struct Rva00470DC1Slot
+{
+	Coord3D m_position; // +0x00
+	unsigned int m_count; // +0x0C
+};
 class Rva0046D946
 {
 public:
@@ -1310,6 +1322,7 @@
 	Rva0046D158Record *rva0046D158(AsciiString name);
 	virtual void performReform();
 	virtual bool rva00470B21();
+	virtual void rva00470DC1();
 	Coord2D *rva0046A5B1(Coord2D *offset, int index);
 	bool rva004723F2(Object *, const AsciiString &);
 private:
@@ -1335,7 +1348,7 @@
 	bool m_198; // +0x198
 	unsigned char m_pad199[0x19C - 0x199];
 	int m_19C; // +0x19C
-	unsigned char m_pad1A0[0x1AC - 0x1A0];
+	_STL::map<int, int> m_1A0; // +0x1A0
 	ObjectID m_1AC; // +0x1AC
 	ObjectID m_1B0; // +0x1B0
 	int m_1B4; // +0x1B4
@@ -1364,7 +1377,9 @@
 	int m_29C; // +0x29C
 	int m_2A0; // +0x2A0
 	bool m_2A4; // +0x2A4
-	unsigned char m_pad2A5[0x2B8 - 0x2A5];
+	unsigned char m_pad2A5[0x2B0 - 0x2A5];
+	ObjectID m_2B0; // +0x2B0
+	unsigned char m_pad2B4[0x2B8 - 0x2B4];
 	Coord3D m_2B8; // +0x2B8
 	bool m_2C4; // +0x2C4
 	unsigned char m_pad2C5[0x2C8 - 0x2C5];
@@ -4684,3 +4699,169 @@
 		return false;
 	return true;
 }
+
+// ?rva00470DC1@HordeContain@@UAEXXZ (scratch, WB 0x010B73E0 literal)
+struct HordeOffset3D : public Coord3D { HordeOffset3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; } };
+static __forceinline bool hordeTestCondition(const Object *obj, int bit)
+{
+	return ((obj->m_conditionWords[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
+}
+void HordeContain::rva00470DC1()
+{
+	Rva0046247DPair p;
+	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
+	_STL::list<Object *>::const_iterator it = p.m04->begin();
+	Object *self = getObject();
+	TheAI->pathfinder()->AdjustLayer(self);
+	float baseAngle = self->m_orientation;
+	AIUpdateInterface *ai = self->m_ai;
+	if (!ai)
+		return;
+	const HordeContainModuleDataFields *data = fields();
+	if (!data)
+		return;
+	Object *leader = TheGameLogic->findObjectByID(m_2B0);
+	while (it != p.m04->end())
+	{
+		Object *obj = *it;
+		it++;
+		if (m_170.find(obj->getID()) == m_170.end())
+		{
+			float angle = 0.0f;
+			Coord3D pos = slot7(obj, &angle);
+			if (rva0046F8F4())
+			{
+				HordeOffset3D dir(self->m_position);
+				dir.z = 0.0f;
+				dir.x = pos.x - dir.x;
+				dir.y = pos.y - dir.y;
+				if (dir.y * dir.y + dir.x * dir.x == 0.0f)
+					angle = self->m_orientation;
+				else
+				{
+					dir.Normalize2D();
+					float a = ACos(dir.x);
+					if (dir.y < 0.0f)
+						a = 6.2831855f - a;
+					angle = a;
+				}
+			}
+			else
+			{
+				angle += baseAngle;
+				if (!m_24C.empty())
+				{
+					if (hordeTestCondition(obj, 170))
+					{
+						rva0046D8AE();
+						break;
+					}
+					GameLogic *logic = TheGameLogic;
+					Object *attacker = logic->findObjectByID(m_1B0);
+					Object *target = logic->findObjectByID(m_1AC);
+					if (!target || !attacker)
+					{
+						rva0046D8AE();
+						break;
+					}
+					float dist = ((Rva000CBA20 *)attacker)->distSq((const Rva000CBA20Point *)target->getPosition());
+					if (obj == attacker)
+					{
+						if (dist < 410.0f)
+						{
+							((Rva001E431E *)obj)->rva001E431E(&m_1B4);
+							angle = obj->GetRelativeAngle(target->getPosition());
+							angle += obj->m_orientation;
+						}
+					}
+					else if (obj == target)
+					{
+						if (dist < 410.0f)
+							((Rva001E431E *)obj)->rva001E431E(&m_1B4);
+						pos = obj->m_position;
+						pos.sub(&attacker->m_position);
+						pos.normalize();
+						pos.scale(20.0f);
+						pos.add(&attacker->m_position);
+						angle = obj->GetRelativeAngle(&attacker->m_position);
+						angle += obj->m_orientation;
+					}
+					else if (dist < 410.0f)
+					{
+						int slot = reinterpret_cast<_STL::map<int, int> &>(m_24C)[obj->getID()];
+						((Rva001E431E *)obj)->rva001E431E(&m_200);
+						angle = obj->GetRelativeAngle(&attacker->m_position);
+						angle += obj->m_orientation;
+						pos = obj->m_position;
+						pos.sub(&attacker->m_position);
+						pos.normalize();
+						pos.scale((float)slot);
+						pos.add(&attacker->m_position);
+						Object *closest = ((Rva0046D946 *)(UpdateModule *)this)->rva0046D946(obj);
+						if (closest && ((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)closest->getPosition()) < 55.0f)
+						{
+							HordeOffset3D delta(obj->m_position);
+							delta.sub(&attacker->m_position);
+							Coord3D side;
+							side.x = 0.0f * delta.z - delta.y;
+							side.y = delta.x - 0.0f * delta.z;
+							side.z = 0.0f * delta.y - 0.0f * delta.x;
+							HordeOffset3D toClosest(closest->m_position);
+							toClosest.sub(&obj->m_position);
+							side.normalize();
+							side.scale((float)(side.x * toClosest.x + side.z * toClosest.z + side.y * toClosest.y > 0.0f ? -4 : 4));
+							pos.add(&side);
+						}
+					}
+				}
+				else if (!m_1A0.empty())
+				{
+					_STL::map<int, int>::iterator held = m_1A0.find(obj->getID());
+					if (held != m_1A0.end())
+					{
+						if (leader && data->m_1F0 != 0.0f)
+						{
+							HordeOffset3D offset(obj->m_position);
+							offset.sub(&leader->m_position);
+							float length = offset.length();
+							if (length < data->m_1F0 * 0.9)
+							{
+								pos = offset;
+								pos.normalize();
+								const Coord3D *op = &obj->m_position;
+								pos.x = pos.x * 5.0f + op->x;
+								pos.y = pos.y * 5.0f + op->y;
+								pos.z = pos.z * 5.0f + op->z;
+							}
+							else if (length < data->m_1F0)
+								pos = obj->m_position;
+						}
+						else
+						{
+							Rva00470DC1Slot *slot = (Rva00470DC1Slot *)&held->second;
+							if (slot->m_count <= 0)
+								pos = slot->m_position;
+							else
+							{
+								slot->m_count--;
+								continue;
+							}
+						}
+					}
+					if (leader)
+					{
+						angle = obj->GetRelativeAngle(leader->getPosition());
+						angle += obj->m_orientation;
+					}
+				}
+				else if (m_2C4)
+				{
+					angle = obj->GetRelativeAngle(&m_2B8);
+					angle += obj->m_orientation;
+				}
+			}
+			rva00474842(obj, &pos, angle, !ai->isMoving());
+		}
+	}
+	((Rva0046A024 *)(UpdateModule *)this)->rva0046A024();
+}
#endif
// ?rva00470DC1@HordeContain@@UAEXXZ (scratch, WB 0x010B73E0 literal)
struct HordeOffset3D : public Coord3D { HordeOffset3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; } };
static __forceinline bool hordeTestCondition(const Object *obj, int bit)
{
	return ((obj->m_conditionWords[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
}
void HordeContain::rva00470DC1()
{
	Rva0046247DPair p;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	Object *self = getObject();
	TheAI->pathfinder()->AdjustLayer(self);
	float baseAngle = self->m_orientation;
	AIUpdateInterface *ai = self->m_ai;
	if (!ai)
		return;
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	Object *leader = TheGameLogic->findObjectByID(m_2B0);
	while (it != p.m04->end())
	{
		Object *obj = *it;
		it++;
		if (m_170.find(obj->getID()) == m_170.end())
		{
			float angle = 0.0f;
			Coord3D pos = slot7(obj, &angle);
			if (rva0046F8F4())
			{
				HordeOffset3D dir(self->m_position);
				dir.z = 0.0f;
				dir.x = pos.x - dir.x;
				dir.y = pos.y - dir.y;
				if (dir.y * dir.y + dir.x * dir.x == 0.0f)
					angle = self->m_orientation;
				else
				{
					dir.Normalize2D();
					float a = ACos(dir.x);
					if (dir.y < 0.0f)
						a = 6.2831855f - a;
					angle = a;
				}
			}
			else
			{
				angle += baseAngle;
				if (!m_24C.empty())
				{
					if (hordeTestCondition(obj, 170))
					{
						rva0046D8AE();
						break;
					}
					GameLogic *logic = TheGameLogic;
					Object *attacker = logic->findObjectByID(m_1B0);
					Object *target = logic->findObjectByID(m_1AC);
					if (!target || !attacker)
					{
						rva0046D8AE();
						break;
					}
					float dist = ((Rva000CBA20 *)attacker)->distSq((const Rva000CBA20Point *)target->getPosition());
					if (obj == attacker)
					{
						if (dist < 410.0f)
						{
							((Rva001E431E *)obj)->rva001E431E(&m_1B4);
							angle = obj->GetRelativeAngle(target->getPosition());
							angle += obj->m_orientation;
						}
					}
					else if (obj == target)
					{
						if (dist < 410.0f)
							((Rva001E431E *)obj)->rva001E431E(&m_1B4);
						pos = obj->m_position;
						pos.sub(&attacker->m_position);
						pos.normalize();
						pos.scale(20.0f);
						pos.add(&attacker->m_position);
						angle = obj->GetRelativeAngle(&attacker->m_position);
						angle += obj->m_orientation;
					}
					else if (dist < 410.0f)
					{
						int slot = reinterpret_cast<_STL::map<int, int> &>(m_24C)[obj->getID()];
						((Rva001E431E *)obj)->rva001E431E(&m_200);
						angle = obj->GetRelativeAngle(&attacker->m_position);
						angle += obj->m_orientation;
						pos = obj->m_position;
						pos.sub(&attacker->m_position);
						pos.normalize();
						pos.scale((float)slot);
						pos.add(&attacker->m_position);
						Object *closest = ((Rva0046D946 *)(UpdateModule *)this)->rva0046D946(obj);
						if (closest && ((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)closest->getPosition()) < 55.0f)
						{
							HordeOffset3D delta(obj->m_position);
							delta.sub(&attacker->m_position);
							Coord3D side;
							side.x = 0.0f * delta.z - delta.y;
							side.y = delta.x - 0.0f * delta.z;
							side.z = 0.0f * delta.y - 0.0f * delta.x;
							HordeOffset3D toClosest(closest->m_position);
							toClosest.sub(&obj->m_position);
							side.normalize();
							side.scale((float)(side.x * toClosest.x + side.z * toClosest.z + side.y * toClosest.y > 0.0f ? -4 : 4));
							pos.add(&side);
						}
					}
				}
				else if (!m_1A0.empty())
				{
					_STL::map<int, int>::iterator held = m_1A0.find(obj->getID());
					if (held != m_1A0.end())
					{
						if (leader && data->m_1F0 != 0.0f)
						{
							HordeOffset3D offset(obj->m_position);
							offset.sub(&leader->m_position);
							float length = offset.length();
							if (length < data->m_1F0 * 0.9)
							{
								pos = offset;
								pos.normalize();
								const Coord3D *op = &obj->m_position;
								pos.x = pos.x * 5.0f + op->x;
								pos.y = pos.y * 5.0f + op->y;
								pos.z = pos.z * 5.0f + op->z;
							}
							else if (length < data->m_1F0)
								pos = obj->m_position;
						}
						else
						{
							Rva00470DC1Slot *slot = (Rva00470DC1Slot *)&held->second;
							if (slot->m_count <= 0)
								pos = slot->m_position;
							else
							{
								slot->m_count--;
								continue;
							}
						}
					}
					if (leader)
					{
						angle = obj->GetRelativeAngle(leader->getPosition());
						angle += obj->m_orientation;
					}
				}
				else if (m_2C4)
				{
					angle = obj->GetRelativeAngle(&m_2B8);
					angle += obj->m_orientation;
				}
			}
			rva00474842(obj, &pos, angle, !ai->isMoving());
		}
	}
	((Rva0046A024 *)(UpdateModule *)this)->rva0046A024();
}
