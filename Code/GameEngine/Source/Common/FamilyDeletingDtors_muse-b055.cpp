// cl: /O1 /MD
// ??_GShipSlowDeathBehaviorModuleData@@UAEPAXI@Z @0x0045E98E
// Deleting dtor slot 0 of vtable 0x842E98; calls ??1 at 0x461FED (twin-pinned
// as ??1ShipSlowDeathBehaviorModuleData; body rowed as
// ??1GiantBirdSlowDeathBehaviorModuleData).
struct EmitVtableTag;

class ShipSlowDeathBehaviorModuleData { public: ShipSlowDeathBehaviorModuleData(EmitVtableTag *); virtual ~ShipSlowDeathBehaviorModuleData(); };
// ?<ShipSlowDeathBehaviorModuleData::ShipSlowDeathBehaviorModuleData> absent-from-retail
ShipSlowDeathBehaviorModuleData::ShipSlowDeathBehaviorModuleData(EmitVtableTag *) {}
