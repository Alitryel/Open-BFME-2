// cl: /MD
// ??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z @0x004B954D, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00859768; calls rowed ??1 at
// 0x004B9569 plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

// ??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z @0x004B954D
class InheritUpgradeCreateModuleData { public: InheritUpgradeCreateModuleData(EmitVtableTag *); virtual ~InheritUpgradeCreateModuleData(); };
// ?<InheritUpgradeCreateModuleData::InheritUpgradeCreateModuleData> absent-from-retail
InheritUpgradeCreateModuleData::InheritUpgradeCreateModuleData(EmitVtableTag *) {}
