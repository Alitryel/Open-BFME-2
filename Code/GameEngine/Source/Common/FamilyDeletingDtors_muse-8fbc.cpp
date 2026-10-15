// cl: /MD
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956 28B; calls rowed ??1W3DBufferManager@@QAE@XZ @0x001163E7 then operator delete 0x0002FD60.
// Evidence: retail push esi/mov esi,ecx/call/test [esp+8],1 pop-ecx shape; QAE non-virtual dtor so QAEPAXI; rowed dtor in W3DBufferManager.cpp.
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956
struct EmitVtableTag;

class W3DBufferManager { public: ~W3DBufferManager(); };
void famgenDelete(W3DBufferManager *p) { delete p; }

// ??_GOpenContainModuleData@@UAEPAXI@Z @0x00465221 28B; calls rowed ??1OpenContainModuleData@@UAE@XZ @0x00257481 then delete. Slot0 of vtable 0x00C43658 per ledger.
class OpenContainModuleData { public: OpenContainModuleData(EmitVtableTag *); virtual ~OpenContainModuleData(); };
// ?<OpenContainModuleData::OpenContainModuleData> absent-from-retail
OpenContainModuleData::OpenContainModuleData(EmitVtableTag *) {}

// ??_GSpecialPowerModuleData@@UAEPAXI@Z @0x00493333 28B; calls rowed ??1SpecialPowerModuleData@@UAE@XZ @0x0049334F then delete.
class SpecialPowerModuleData { public: SpecialPowerModuleData(EmitVtableTag *); virtual ~SpecialPowerModuleData(); };
// ?<SpecialPowerModuleData::SpecialPowerModuleData> absent-from-retail
SpecialPowerModuleData::SpecialPowerModuleData(EmitVtableTag *) {}
