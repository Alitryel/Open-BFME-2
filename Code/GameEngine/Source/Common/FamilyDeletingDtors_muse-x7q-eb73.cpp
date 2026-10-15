// cl: /MD
// ??_GStealthUpdateModuleData@@UAEPAXI@Z @0x003759D9 28B
// Deleting dtor slot 0 of vtable 0x008184D8; calls rowed ??1 at 0x003759F5 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class StealthUpdateModuleData { public: StealthUpdateModuleData(EmitVtableTag *); virtual ~StealthUpdateModuleData(); };
// ?<StealthUpdateModuleData::StealthUpdateModuleData> absent-from-retail
StealthUpdateModuleData::StealthUpdateModuleData(EmitVtableTag *) {}
// ??_GEntEnragedUpdateModuleData@@UAEPAXI@Z @0x004B2706 28B
// Deleting dtor slot 0 of vtable 0x00856980; calls rowed ??1 at 0x004B2722 then rowed operator delete at 0x0002FD60.
class EntEnragedUpdateModuleData { public: EntEnragedUpdateModuleData(EmitVtableTag *); virtual ~EntEnragedUpdateModuleData(); };
// ?<EntEnragedUpdateModuleData::EntEnragedUpdateModuleData> absent-from-retail
EntEnragedUpdateModuleData::EntEnragedUpdateModuleData(EmitVtableTag *) {}
