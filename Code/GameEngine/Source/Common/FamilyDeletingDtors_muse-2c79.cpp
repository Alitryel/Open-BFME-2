// cl: /O1 /MD
// ??_GMonitorConditionUpdate@@UAEPAXI@Z @0x00491750 28B
// Deleting dtor slot 0 of vtable 0x0084DAD8; calls rowed ??1 at 0x004916AC then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class MonitorConditionUpdate { public: MonitorConditionUpdate(EmitVtableTag *); virtual ~MonitorConditionUpdate(); };
// ?<MonitorConditionUpdate::MonitorConditionUpdate> absent-from-retail
MonitorConditionUpdate::MonitorConditionUpdate(EmitVtableTag *) {}
// ??_GDamageFieldUpdateModuleData@@UAEPAXI@Z @0x0049114E 28B
// Deleting dtor slot 0 of vtable 0x0084D8E8; calls rowed ??1 at 0x0049116A then rowed operator delete at 0x0002FD60.
class DamageFieldUpdateModuleData { public: DamageFieldUpdateModuleData(EmitVtableTag *); virtual ~DamageFieldUpdateModuleData(); };
// ?<DamageFieldUpdateModuleData::DamageFieldUpdateModuleData> absent-from-retail
DamageFieldUpdateModuleData::DamageFieldUpdateModuleData(EmitVtableTag *) {}
