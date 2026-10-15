// cl: /O1 /MD
// ??_GGrantUpgradeCreateModuleData@@UAEPAXI@Z @0x004B912F
// Deleting dtor slot 0 of vtable 0xC594E0; calls the rowed ??1 at 0x4B914B.
struct EmitVtableTag;

class GrantUpgradeCreateModuleData { public: GrantUpgradeCreateModuleData(EmitVtableTag *); virtual ~GrantUpgradeCreateModuleData(); };
// ?<GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData> absent-from-retail
GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData(EmitVtableTag *) {}
