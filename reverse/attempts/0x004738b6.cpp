// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.995 date=2026-10-15
// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.995 date=2026-10-15
// cl: (home unit) Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
//
// d2w4 seat7: EXACT 254/254 in the home unit except one REL32: the callee at
// 0x00468F0F must be VISIBLE in this unit as a thiscall HordeContain member
// (retail does lea ecx,[edi-0x11c] before the call and keeps the target in EDX
// across it, which cl only does when it has compiled the callee's body in the
// same TU). The visible copy below compiles to retail 0x00468F0F exactly
// (explain_mismatch: exact match, 89 B). LAND-BLOCKER: 0x00468F0F is rowed as
// the free stdcall ?Rva00468F0FInRange@@YG_NPAVObject@@0@Z in
// Code/GameEngine/Source/GameLogic/Object/Update/Rva00468F0FCheck.cpp, so the
// owner row must be renamed/moved to ?rva00468F0F@HordeContain@@QAE_NPAVObject@@0@Z
// in the home unit (and the stub file retired) -- a symbol rename, which the
// seat rules leave to the orchestrator.
//
// Home-unit edits (unified diff against 069d40a806 follows the body):
//  - iface Rva0046BB38Iface11C: gap63 -> virtual void rva004738B6(Object *target),
//    gap65 -> virtual unsigned int rva0046F7F8() const (retail 0x0046F7F8, ICF twin
//    of Object::dlink_next_TeamMemberList);
//  - HordeContain: virtual void rva004738B6(Object *target);
//    bool rva00468F0F(Object *obj, Object *target);
//  - view class Rva0046A2ECSlot39 : Rva00468D11Slots<39> { virtual void slot39(Object *obj) = 0; }
__declspec(noinline) bool HordeContain::rva00468F0F(Object *obj, Object *target)
{
	float dx = obj->m_position.x - target->m_position.x;
	float dy = obj->m_position.y - target->m_position.y;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return false;
	float r = ((const float *)ai->m_1F0)[0x3C / 4];
	float distSq = dy * dy;
	distSq = distSq + dx * dx;
	return distSq < r * r;
}
// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z @0x004738B6: slot 63 of the
// +0x11C interface.
void HordeContain::rva004738B6(Object *target)
{
	unsigned int remaining = TheWritableGlobalData->m_1230;
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); )
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		++k;
		if (!obj)
			continue;
		if (rva00468F0F(obj, target) == true)
		{
			Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
			if (contain)
			{
				contain->slot39(obj);
				continue;
			}
		}
		if (rva0046F7F8() && remaining > 0)
		{
			unsigned int now = TheGameLogic->m_frame;
			if (now - rva0046F7F8() > (unsigned int)TheWritableGlobalData->m_1234)
			{
				Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
				if (contain)
				{
					contain->slot39(obj);
					--remaining;
					continue;
				}
			}
		}
		AIUpdateInterface *ai = obj->m_ai;
		if (ai && ai->rva0047306ESlot110())
			ai->m_command.rva0026C347(target, CMD_FROM_AI);
	}
}

#if 0
diff --git a/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp b/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
index cd0435f917..3a072b69d0 100644
--- a/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
+++ b/Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
@@ -462,6 +462,12 @@ class Rva0046A2ECContain : public Rva00468D11Slots<58>
 public:
 	virtual bool slot58(Object *other) = 0;
 };
+// The same module's slot 39, handed a member Object.
+class Rva0046A2ECSlot39 : public Rva00468D11Slots<39>
+{
+public:
+	virtual void slot39(Object *obj) = 0;
+};
 // The weapon's float range query is the rowed 0x002C9B80 (its row names the
 // owner Rva002C9B80Owner).
 class Object;
@@ -930,7 +936,7 @@ public:
 	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void rva0046C3FE(Player *player) = 0;
 	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
 	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
-	virtual bool rva0046AAB8() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
+	virtual bool rva0046AAB8() = 0; virtual void rva004738B6(Object *target) = 0; virtual void gap64() = 0; virtual unsigned int rva0046F7F8() const = 0;
 	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p) = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual void gap69() = 0;
 	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
 	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void startMeleeAttack(Object *target) = 0;
@@ -1134,6 +1140,8 @@ public:
 	virtual void rva0046FE99(_STL::list<Object *> &out);
 	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
 	virtual bool isFlankedBy(Object *attacker);
+	virtual void rva004738B6(Object *target);
+	bool rva00468F0F(Object *obj, Object *target);
 	virtual AsciiString rva0046D1AC();
 	virtual void rva0046F7C9(Object *obj);
 	virtual void rva00469F2F(Object *obj);
@@ -2698,6 +2706,58 @@ bool HordeContain::isFlankedBy(Object *attacker)
 	return false;
 }
 
+__declspec(noinline) bool HordeContain::rva00468F0F(Object *obj, Object *target)
+{
+	float dx = obj->m_position.x - target->m_position.x;
+	float dy = obj->m_position.y - target->m_position.y;
+	AIUpdateInterface *ai = obj->m_ai;
+	if (ai == 0)
+		return false;
+	float r = ((const float *)ai->m_1F0)[0x3C / 4];
+	float distSq = dy * dy;
+	distSq = distSq + dx * dx;
+	return distSq < r * r;
+}
+// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z @0x004738B6: slot 63 of the
+// +0x11C interface.
+void HordeContain::rva004738B6(Object *target)
+{
+	unsigned int remaining = TheWritableGlobalData->m_1230;
+	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); )
+	{
+		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
+		++k;
+		if (!obj)
+			continue;
+		if (rva00468F0F(obj, target) == true)
+		{
+			Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
+			if (contain)
+			{
+				contain->slot39(obj);
+				continue;
+			}
+		}
+		if (rva0046F7F8() && remaining > 0)
+		{
+			unsigned int now = TheGameLogic->m_frame;
+			if (now - rva0046F7F8() > (unsigned int)TheWritableGlobalData->m_1234)
+			{
+				Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
+				if (contain)
+				{
+					contain->slot39(obj);
+					--remaining;
+					continue;
+				}
+			}
+		}
+		AIUpdateInterface *ai = obj->m_ai;
+		if (ai && ai->rva0047306ESlot110())
+			ai->m_command.rva0026C347(target, CMD_FROM_AI);
+	}
+}
+
 // ?endMove@HordeContain@@UAEXXZ @0x0046A0B2: slot 154; while our Object's
 // AI is moving, runs the rowed AIUpdateInterface rva00262D2D on every
 // contained Object's AI and then on ours.
#endif
