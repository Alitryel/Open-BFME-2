// cl: /O1 /MD
// ??_GRva00150558@@UAEPAXI@Z @0x00150DE1, 28B.
// Scalar deleting dtor; calls rowed ??1 at 0x00150558 plus rowed delete at 0x0002FD60.
// Evidence: retail calls 0x00150558 (rowed ??1Rva00150558@@UAE@XZ) and 0x0002FD60 (rowed ??3@YAXPAX@Z); same 28B ??_G shape as family.

struct EmitVtableTag;

class Rva00150558 { public: Rva00150558(EmitVtableTag *); virtual ~Rva00150558(); };
// ?<Rva00150558::Rva00150558> absent-from-retail
Rva00150558::Rva00150558(EmitVtableTag *) {}
