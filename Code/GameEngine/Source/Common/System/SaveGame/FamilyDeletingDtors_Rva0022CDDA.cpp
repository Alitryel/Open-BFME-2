// cl: /MD
// ??_GRva0022CDDA@@UAEPAXI@Z @0x0022CDBE 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x0022CDDA plus rowed delete at 0x0002FD60. Evidence: chain packet calls rowed 0x0022CDDA; ??_G shape with test byte [esp+8] 1.
// ??_GRva0022CDDA@@UAEPAXI@Z @0x0022CDBE present-unmatched
struct EmitVtableTag;

class Rva0022CDDA { public: Rva0022CDDA(EmitVtableTag *); virtual ~Rva0022CDDA(); };
// ?<Rva0022CDDA::Rva0022CDDA> absent-from-retail
Rva0022CDDA::Rva0022CDDA(EmitVtableTag *) {}
