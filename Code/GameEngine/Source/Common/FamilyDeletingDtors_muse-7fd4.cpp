// cl: /O1 /MD
// ??_GMissileUpdateModuleData@@UAEPAXI@Z @0x004A784D 28B
// Deleting dtor slot 0 of vtable 0x00853668; calls rowed ??1 at 0x004A7869 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class MissileUpdateModuleData { public: MissileUpdateModuleData(EmitVtableTag *); virtual ~MissileUpdateModuleData(); };
// ?<MissileUpdateModuleData::MissileUpdateModuleData> absent-from-retail
MissileUpdateModuleData::MissileUpdateModuleData(EmitVtableTag *) {}
