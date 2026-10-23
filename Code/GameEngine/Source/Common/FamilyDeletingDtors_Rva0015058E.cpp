// cl: /O1 /MD
// ??_GRva0015058E@@UAEPAXI@Z @0x001510A6, 28B.
// Scalar deleting dtor; calls rowed ??1 at 0x0015058E plus rowed delete at 0x0002FD60.
// Evidence: retail calls 0x0015058E (rowed ??1Rva0015058E@@UAE@XZ) and 0x0002FD60 (rowed ??3@YAXPAX@Z); same 28B ??_G shape as family.
struct EmitVtableTag;

class Rva0015058E { public: Rva0015058E(EmitVtableTag *); virtual ~Rva0015058E(); };
// ?<Rva0015058E::Rva0015058E> absent-from-retail
Rva0015058E::Rva0015058E(EmitVtableTag *) {}
