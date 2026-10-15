// cl: /O1 /MD
// ??_GDeflectSpecialPowerModuleData@@UAEPAXI@Z @0x004C5683 28B
// Deleting dtor slot 0 of vtable 0x0085DAB0; calls pinned ??1 at 0x004C64E9 (ICF twin of rowed SiegeDeployHordeSpecialPowerModuleData dtor) then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class DeflectSpecialPowerModuleData { public: DeflectSpecialPowerModuleData(EmitVtableTag *); virtual ~DeflectSpecialPowerModuleData(); };
// ?<DeflectSpecialPowerModuleData::DeflectSpecialPowerModuleData> absent-from-retail
DeflectSpecialPowerModuleData::DeflectSpecialPowerModuleData(EmitVtableTag *) {}
