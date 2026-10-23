// cl: /MD
// ??_GPartTheHeavensUpdateModuleData@@UAEPAXI@Z @0x004ACCB1, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00854E38; calls rowed ??1 at
// 0x004ACCCD plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

// ??_GPartTheHeavensUpdateModuleData@@UAEPAXI@Z @0x004ACCB1
class PartTheHeavensUpdateModuleData { public: PartTheHeavensUpdateModuleData(EmitVtableTag *); virtual ~PartTheHeavensUpdateModuleData(); public:
	virtual void bfmeVtSlot1() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot2() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot3() = 0; // __purecall in every copy of this vtable
};
// ?<PartTheHeavensUpdateModuleData::PartTheHeavensUpdateModuleData> absent-from-retail
PartTheHeavensUpdateModuleData::PartTheHeavensUpdateModuleData(EmitVtableTag *) {}
