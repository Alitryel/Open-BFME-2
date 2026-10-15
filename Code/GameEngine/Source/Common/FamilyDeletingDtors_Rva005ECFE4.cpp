// cl: /O1 /MD
// ??_GRva005ECFE4@@MAEPAXI@Z @0x005ECFC8 28B: deleting dtor calls rowed dtor 0x005ECFE4 then operator delete 0x0002FD60 on flag. Evidence: vtable slot 0 of 0x008785B4; chain from 0x005ECFE4.
// placeholder ??1 duplicates owner for codegen only.
struct EmitVtableTag;

class Rva005ECFE4 { public: Rva005ECFE4(EmitVtableTag *); protected: virtual ~Rva005ECFE4(); };
// ?<Rva005ECFE4::Rva005ECFE4> absent-from-retail
Rva005ECFE4::Rva005ECFE4(EmitVtableTag *) {}
