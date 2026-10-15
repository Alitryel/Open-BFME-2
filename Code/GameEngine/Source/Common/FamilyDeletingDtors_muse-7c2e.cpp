// cl: /O1 /MD
// ??_GCommandPointsUpgradeModuleData@@UAEPAXI@Z @0x0025593D 28B
// Deleting dtor slot 0 of vtable 0x007F2658; calls rowed ??1 at 0x00255959 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class CommandPointsUpgradeModuleData { public: CommandPointsUpgradeModuleData(EmitVtableTag *); virtual ~CommandPointsUpgradeModuleData(); };
// ?<CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData> absent-from-retail
CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData(EmitVtableTag *) {}
// ??_GRefundDieModuleData@@UAEPAXI@Z @0x0025504B 28B
// Deleting dtor slot 0 of vtable 0x007F0660; calls rowed ??1 at 0x00255067 then rowed operator delete at 0x0002FD60.
class RefundDieModuleData { public: RefundDieModuleData(EmitVtableTag *); virtual ~RefundDieModuleData(); };
// ?<RefundDieModuleData::RefundDieModuleData> absent-from-retail
RefundDieModuleData::RefundDieModuleData(EmitVtableTag *) {}
