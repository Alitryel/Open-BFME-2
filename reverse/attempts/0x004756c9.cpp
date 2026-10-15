// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.94 date=2026-10-15
// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.94 date=2026-10-15
// cl: (home unit) Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
//
// d2w4 seat7 home-unit port (no hacks): 525/525 size-exact; identical to retail
// through the +0x1A0 goal-map operator[] and the attacker-relative direction
// (delta register copy then dir.set(&delta) gives retail's x/y/z order). Left:
// (1) the operator[] REL32: map<int,Rva00469155>::operator[] is the unrowed body
// 0x00473F81 already pinned as the placeholder ?rva00473F81@Rva00473F81@@QAEAAVRva00469155@@ABH@Z
// (callee of the rowed HordeContain::xfer) -> needs a fold-proof pin from this unit
// or a rename of that pin; (2) the goal position block after Coord3D::normalize:
// retail loads obj.y/obj.z, then s=distance*10, multiplies the offset x,y,z and
// loads obj.x only for the x add (xmm0 reused); every spelling tried (set(ptr),
// set(x,y,z), member stores in y/z/x order, pos before/after the offset, add/+=,
// by-value add, offset.add(pos)) loads obj.x first -> 9 instructions of register
// numbering. Body below + unified diff of the home-unit edits (iface gap103 ->
// backAwaySomeMembersFrom, module data m_1DC..m_1F0, HordeContain m_1A0 map and
// m_2B0, class Rva00469155).
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z @0x004756C9: slot 103
// of the +0x11C interface.
void HordeContain::backAwaySomeMembersFrom(Object *attacker)
{
	if (!attacker)
		return;
	Coord3D attackerPos;
	attackerPos.set(attacker->getPosition());
	const _STL::list<Object *> *items = containedItems();
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	bool disabled = m_object->testStatus((ObjectStatusTypes)0x45);
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (!disabled && !obj->testStatus((ObjectStatusTypes)0x45) && data->m_1F0 == 0.0f)
		{
			if (GetGameLogicRandomValueReal(0.0f, 1.0f, HORDECONTAIN_SOURCE_FILE, 8016) > data->m_1EC)
				continue;
		}
		float distance = GetGameLogicRandomValueReal(data->m_1E4, data->m_1E8, HORDECONTAIN_SOURCE_FILE, 8021);
		int frames = GetGameLogicRandomValue(data->m_1DC, data->m_1E0, HORDECONTAIN_SOURCE_FILE, 8022);
		Rva00469155 &goal = m_1A0[obj->getID()];
		Coord3D delta;
		delta.set(obj->getPosition());
		delta.sub(&attackerPos);
		Coord3D dir;
		dir.set(&delta);
		dir.normalize();
		Coord3D offset;
		offset.set(&dir);
		Coord3D pos;
		pos.set(obj->getPosition());
		offset.scale(distance * 10.0f);
		pos.add(&offset);
		goal.m_pos = pos;
		goal.m_0C = frames;
	}
	m_2B0 = attacker->getID();
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp b/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
index cd0435f917..78b2721f3d 100644
--- a/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
+++ b/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
@@ -788,7 +788,14 @@ struct HordeContainModuleDataFields
 	_STL::map<int, int> m_1B8; // +0x1B8
 	unsigned char m_pad1C4[0x1D8 - 0x1C4];
 	bool m_1D8; // +0x1D8
-	unsigned char m_pad1D9[0x224 - 0x1D9];
+	unsigned char m_pad1D9[0x1DC - 0x1D9];
+	int m_1DC; // +0x1DC (back-away frames, low)
+	int m_1E0; // +0x1E0 (back-away frames, high)
+	float m_1E4; // +0x1E4 (back-away distance, low)
+	float m_1E8; // +0x1E8 (back-away distance, high)
+	float m_1EC; // +0x1EC (back-away chance)
+	float m_1F0; // +0x1F0
+	unsigned char m_pad1F4[0x224 - 0x1F4];
 	union
 	{
 		struct
@@ -940,7 +947,7 @@ public:
 	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
 	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
 	virtual int rva00468F7E() = 0; virtual Object *rva004708BC(const Matrix3D *mtx) = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
-	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
+	virtual void gap102() = 0; virtual void backAwaySomeMembersFrom(Object *attacker) = 0; virtual void gap104() = 0; virtual void gap105() = 0;
 	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
 	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
 	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
@@ -1113,6 +1120,14 @@ public:
 	virtual void gap67() = 0;
 	virtual Object *slot68() = 0;
 };
+// A back-away goal: a position and a frame count.
+class Rva00469155
+{
+public:
+	Rva00469155();
+	Coord3D m_pos; // +0x00
+	int m_0C; // +0x0C
+};
 class HordeContain : public TransportContain, public Rva0046BB38Iface11C
 {
 public:
@@ -1134,6 +1149,7 @@ public:
 	virtual void rva0046FE99(_STL::list<Object *> &out);
 	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
 	virtual bool isFlankedBy(Object *attacker);
+	virtual void backAwaySomeMembersFrom(Object *attacker);
 	virtual AsciiString rva0046D1AC();
 	virtual void rva0046F7C9(Object *obj);
 	virtual void rva00469F2F(Object *obj);
@@ -1269,7 +1285,7 @@ private:
 	bool m_198; // +0x198
 	unsigned char m_pad199[0x19C - 0x199];
 	int m_19C; // +0x19C
-	unsigned char m_pad1A0[0x1AC - 0x1A0];
+	_STL::map<int, Rva00469155> m_1A0; // +0x1A0 (back-away goals by member ID)
 	ObjectID m_1AC; // +0x1AC
 	ObjectID m_1B0; // +0x1B0
 	int m_1B4; // +0x1B4
@@ -1298,7 +1314,9 @@ private:
 	int m_29C; // +0x29C
 	int m_2A0; // +0x2A0
 	bool m_2A4; // +0x2A4
-	unsigned char m_pad2A5[0x2B8 - 0x2A5];
+	unsigned char m_pad2A5[0x2B0 - 0x2A5];
+	int m_2B0; // +0x2B0 (the last attacker backed away from)
+	unsigned char m_pad2B4[0x2B8 - 0x2B4];
 	Coord3D m_2B8; // +0x2B8
 	bool m_2C4; // +0x2C4
 	unsigned char m_pad2C5[0x2C8 - 0x2C5];
@@ -2698,6 +2716,50 @@ bool HordeContain::isFlankedBy(Object *attacker)
 	return false;
 }
 
+float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
+// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z @0x004756C9: slot 103
+// of the +0x11C interface.
+void HordeContain::backAwaySomeMembersFrom(Object *attacker)
+{
+	if (!attacker)
+		return;
+	Coord3D attackerPos;
+	attackerPos.set(attacker->getPosition());
+	const _STL::list<Object *> *items = containedItems();
+	const HordeContainModuleDataFields *data = fields();
+	if (!data)
+		return;
+	bool disabled = m_object->testStatus((ObjectStatusTypes)0x45);
+	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
+	{
+		Object *obj = *it;
+		if (!disabled && !obj->testStatus((ObjectStatusTypes)0x45) && data->m_1F0 == 0.0f)
+		{
+			if (GetGameLogicRandomValueReal(0.0f, 1.0f, HORDECONTAIN_SOURCE_FILE, 8016) > data->m_1EC)
+				continue;
+		}
+		float distance = GetGameLogicRandomValueReal(data->m_1E4, data->m_1E8, HORDECONTAIN_SOURCE_FILE, 8021);
+		int frames = GetGameLogicRandomValue(data->m_1DC, data->m_1E0, HORDECONTAIN_SOURCE_FILE, 8022);
+		Rva00469155 &goal = m_1A0[obj->getID()];
+		Coord3D delta;
+		delta.set(obj->getPosition());
+		delta.sub(&attackerPos);
+		Coord3D dir;
+		dir.set(&delta);
+		dir.normalize();
+		Coord3D offset;
+		offset.set(&dir);
+		Coord3D pos;
+		pos.set(obj->getPosition());
+		offset.scale(distance * 10.0f);
+		pos.add(&offset);
+		goal.m_pos = pos;
+		goal.m_0C = frames;
+	}
+	m_2B0 = attacker->getID();
+	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
+}
+
 // ?endMove@HordeContain@@UAEXXZ @0x0046A0B2: slot 154; while our Object's
 // AI is moving, runs the rowed AIUpdateInterface rva00262D2D on every
 // contained Object's AI and then on ours.
#endif
