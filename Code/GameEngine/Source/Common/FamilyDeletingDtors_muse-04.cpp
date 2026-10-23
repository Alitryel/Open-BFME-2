// cl: /MD
// ??_GRva0026AF86@@UAEPAXI@Z @0x0026AF6A 28B
// Deleting dtor; calls rowed ??1Rva0026AF86@@UAE@XZ at 0x0026AF86 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class Rva0026AF86 { public: Rva0026AF86(EmitVtableTag *); virtual ~Rva0026AF86(); };
// ?<Rva0026AF86::Rva0026AF86> absent-from-retail
Rva0026AF86::Rva0026AF86(EmitVtableTag *) {}
