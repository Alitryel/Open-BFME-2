// ?rva00470DC1@HordeContain@@UAEXXZ
// partial score=0.93 date=2026-10-20
// ?rva00470DC1@HordeContain@@UAEXXZ, retail 0x470DC1 (1699 B). Fragment bank: apply the view patch below to
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp, then append the body (build/nbr/r28/470dc1/gen.py).
// Compiles 1688/1699, all calls resolved, no hacks; all 148 home rows stay exact.
// claude-opus-5-5: view patch makes GameLogic::findObjectByID visible (header inline over the STLport hash_map at +0xB4, byte-equal to 0x00049DC5/0x002888D4),
// respells 0x0046DEA1's member test (148/148 home rows exact); body reads TheGameLogic twice as WB does. 1683/1699. reverse/attempt_support/0x00470dc1_20261020_visible_lookup.md
#if 0 /* view patch */
--- Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
+++ build/w6_470dc1/full_best.cpp
@@ -32,6 +32,7 @@
 }
 
 #include <map>
+#include <hash_map>
 #include <set>
 #include <vector>
 // Import-inline: this unit's bfmealloc _Vector_base<Object*> dtor copy is not retail's
@@ -192,6 +193,7 @@
 {
 public:
 	bool IsPointOnWall(int pos, bool flag);
+	void AdjustLayer(Object *obj);
 	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
 	bool IsPointOnRamp(const Coord3D *pos);
 	void RemoveObjectFromPathfindMap(Object *object);
@@ -668,14 +670,27 @@
 	friend class HordeContain;
 	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
 };
+typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;
+// findObjectByID is the header inline over the object hash map at +0xB4;
+// cl calls its out-of-line copy 0x00049DC5.
 class GameLogic
 {
 public:
-	Object *findObjectByID(ObjectID id);
+	Object *findObjectByID(ObjectID id)
+	{
+		if (id == INVALID_ID)
+			return 0;
+		ObjectPtrHash::iterator it = m_objHash.find(id);
+		if (it == m_objHash.end())
+			return 0;
+		return (*it).second;
+	}
 	void destroyObject(Object *);
 	void rva0023D0C2(Object *obj, int value);
 	unsigned char m_pad00[0x40];
 	unsigned int m_frame; // +0x40
+	unsigned char m_pad44[0xB4 - 0x44];
+	ObjectPtrHash m_objHash; // +0xB4
 };
 extern GameLogic *TheGameLogic;
 class ThingFactory
@@ -839,7 +854,8 @@
 	_STL::map<int, int> m_1B8; // +0x1B8
 	unsigned char m_pad1C4[0x1D8 - 0x1C4];
 	bool m_1D8; // +0x1D8
-	unsigned char m_pad1D9[0x1F4 - 0x1D9];
+	unsigned char m_pad1D9[0x1F0 - 0x1D9];
+	float m_1F0; // +0x1F0
 	Rva00469851Names m_1F4;
 	unsigned char m_pad200[0x218 - 0x200];
 	Rva00469851Names m_218;
@@ -1029,8 +1045,8 @@
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
@@ -1144,6 +1160,16 @@
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
@@ -1310,6 +1336,7 @@
 	Rva0046D158Record *rva0046D158(AsciiString name);
 	virtual void performReform();
 	virtual bool rva00470B21();
+	virtual void rva00470DC1();
 	Coord2D *rva0046A5B1(Coord2D *offset, int index);
 	bool rva004723F2(Object *, const AsciiString &);
 private:
@@ -1335,7 +1362,7 @@
 	bool m_198; // +0x198
 	unsigned char m_pad199[0x19C - 0x199];
 	int m_19C; // +0x19C
-	unsigned char m_pad1A0[0x1AC - 0x1A0];
+	_STL::map<int, int> m_1A0; // +0x1A0
 	ObjectID m_1AC; // +0x1AC
 	ObjectID m_1B0; // +0x1B0
 	int m_1B4; // +0x1B4
@@ -1364,7 +1391,9 @@
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
@@ -3652,9 +3681,9 @@
 	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
 	{
 		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
-		Rva0046B850Module *module = member->m_254;
-		if (module)
-		{
+		if (member->m_254)
+		{
+			Rva0046B850Module *module = member->m_254;
 			ObjectID id = module->slot18();
 			Object *obj = TheGameLogic->findObjectByID(id);
 			if (obj && obj->m_274)
@@ -4690,3 +4719,169 @@
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
+					Object *attacker = TheGameLogic->findObjectByID(m_1B0);
+					Object *target = TheGameLogic->findObjectByID(m_1AC);
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
+							HordeOffset3D scaled(side);
+							scaled.scale((float)(side.x * toClosest.x + side.z * toClosest.z + side.y * toClosest.y > 0.0f ? -4 : 4));
+							pos.add(&scaled);
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
					Object *attacker = TheGameLogic->findObjectByID(m_1B0);
					Object *target = TheGameLogic->findObjectByID(m_1AC);
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
							HordeOffset3D scaled(side);
							scaled.scale((float)(side.x * toClosest.x + side.z * toClosest.z + side.y * toClosest.y > 0.0f ? -4 : 4));
							pos.add(&scaled);
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
