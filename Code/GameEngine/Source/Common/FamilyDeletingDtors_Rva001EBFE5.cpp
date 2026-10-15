// cl: /MD
// ??_GRva001EBFE5@@UAEPAXI@Z @0x001EBFC9, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at
// 0x001EBFE5 plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

class Rva001EBFE5 { public: Rva001EBFE5(EmitVtableTag *); virtual ~Rva001EBFE5(); };
// ?<Rva001EBFE5::Rva001EBFE5> absent-from-retail
Rva001EBFE5::Rva001EBFE5(EmitVtableTag *) {}
