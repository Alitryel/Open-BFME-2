// cl: /MD
// ??_GRespawnUpdateModuleData@@UAEPAXI@Z @0x004AFBE3, 28B.
// Scalar deleting dtor slot 0 of vtable 0x008556F8; calls rowed ??1 at
// 0x004AFBFF plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

// ??_GRespawnUpdateModuleData@@UAEPAXI@Z @0x004AFBE3 present-unmatched
class RespawnUpdateModuleData { public: RespawnUpdateModuleData(EmitVtableTag *); virtual ~RespawnUpdateModuleData(); };
// ?<RespawnUpdateModuleData::RespawnUpdateModuleData> absent-from-retail
RespawnUpdateModuleData::RespawnUpdateModuleData(EmitVtableTag *) {}
