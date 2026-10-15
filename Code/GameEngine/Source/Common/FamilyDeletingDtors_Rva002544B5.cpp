// cl: /MD
//
// ??_GRva002544B5@@UAEPAXI@Z, retail 0x00254499, 28 bytes. Deleting dtor for
// Rva002544B5: calls rowed ??1Rva002544B5 60B at 0x002544B5 then operator
// delete 0x0002FD60 on flag. Chain from 0x002544B5. Public virtual (UAE).

struct EmitVtableTag;

class Rva002544B5 { public: Rva002544B5(EmitVtableTag *); virtual ~Rva002544B5(); };
// ?<Rva002544B5::Rva002544B5> absent-from-retail
Rva002544B5::Rva002544B5(EmitVtableTag *) {}
