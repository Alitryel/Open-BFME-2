// cl: /O1 /MD
// ??_GRva004D6208@@MAEPAXI@Z @0x004D6AB9 28B
// Deleting dtor slot 0 of vtable 0x00860484; calls rowed ??1Rva004D6208@@MAE@XZ at 0x004D6208 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class Rva004D6208 { public: Rva004D6208(EmitVtableTag *); protected: virtual ~Rva004D6208(); };
// ?<Rva004D6208::Rva004D6208> absent-from-retail
Rva004D6208::Rva004D6208(EmitVtableTag *) {}
