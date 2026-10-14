// ?rva0046ECDE@HordeContain@@UAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z
// partial score=0.95 date=2026-10-15
// Bank for 0x0046ECDE: apply to Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// (owner TU at seat3 base); the unified diff below adds the enum, the interface slot-111
// declaration, the moveThroughPortalWithMicropath spelling, the Rva0046E6EA view and the body.
#if 0
--- a/HordeContainIface11CSlots.cpp
+++ b/HordeContainIface11CSlots.cpp
@@ -136,6 +136,12 @@
 	void *GetCategoryContainer(int index);
 };
 extern AttributeModifierStore *TheAttributeModifierStore;
+enum PathfindLayerEnum
+{
+	LAYER_INVALID = 0,
+	LAYER_GROUND = 1
+};
+
 class AICommandInterface
 {
 public:
@@ -379,6 +385,8 @@
 	Rva00468C37Holder *m_1F0; // +0x1F0
 	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_1CC; }
 	void rva0026594F(const Coord3D *a1, const Coord3D *a2, int a3, int layer, const Coord3D *a5, const Coord3D *a6);
+	// The rowed 0x0026594F under its row spelling, for the slot-111 caller.
+	void moveThroughPortalWithMicropath(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer, const Coord3D *a5, const Coord3D *a6);
 	unsigned char m_pad1F4[0x1FC - 0x1F4];
 	int m_1FC; // +0x1FC
 };
@@ -939,7 +947,7 @@
 	virtual int rva00468F7E() = 0; virtual Object *rva004708BC(const Matrix3D *mtx) = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
 	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
 	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
-	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
+	virtual void rva0046A712(int unused) = 0; virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer) = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
 	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
 	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
 	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual bool rva0046992C() = 0;
@@ -1110,6 +1118,9 @@
 	virtual void gap67() = 0;
 	virtual Object *slot68() = 0;
 };
+struct Rva0046E6EAObject; struct Rva0046E6EACoord;
+class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *obj, const Rva0046E6EACoord *pos, Rva0046E6EACoord *out, bool flag); };
+
 class HordeContain : public TransportContain, public Rva0046BB38Iface11C
 {
 public:
@@ -1185,6 +1196,7 @@
 	virtual void rva004730B0(Object *target);
 	virtual void rva0046DE2D(const FXList *fx);
 	virtual void rva0046A712(int unused);
+	virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer);
 	virtual bool rva0046C5D7(int value);
 	virtual bool rva0046A2EC(Object *target);
 	virtual bool rva0046A381(Object *target);
@@ -2254,6 +2266,36 @@
 	}
 }
 
+// ?rva0046ECDE@HordeContain@@UAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z @0x0046ECDE:
+// slot 111. Sends every contained Object through a portal: its slot-7 spot
+// and angle, the rowed 0x0046E6EA fix-up against our Object, then the rowed
+// AIUpdateInterface::moveThroughPortalWithMicropath toward our position
+// (averaged with the second point off the ground layer).
+void HordeContain::rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer)
+{
+	const _STL::list<Object *> *items = containedItems();
+	Object *self = m_object;
+	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
+	{
+		Object *obj = *it;
+		if (obj)
+		{
+			AIUpdateInterface *ai = obj->m_ai;
+			float angle = 0.0f;
+			Coord3D pos;
+			pos = slot7(obj, &angle);
+			Coord3D dest = *self->getPosition();
+			if (layer != LAYER_GROUND)
+			{
+				dest.add(a2);
+				dest.scale(0.5f);
+			}
+			((Rva0046E6EA *)(UpdateModule *)this)->rva0046E6EA((Rva0046E6EAObject *)obj, (const Rva0046E6EACoord *)&pos, (Rva0046E6EACoord *)m_object, false);
+			ai->moveThroughPortalWithMicropath(a1, a2, a3, layer, &dest, &pos);
+		}
+	}
+}
+
 // ?rva0046C5D7@HordeContain@@UAE_NH@Z @0x0046C5D7: slot 58; whether a contained
 // Object, or the live Object of a +0x170 key, has +0x44C equal to the
 // (non-zero) argument.
#endif
