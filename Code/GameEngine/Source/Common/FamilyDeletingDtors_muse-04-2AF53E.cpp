// cl: /MD
// ??_GRva002AE627@@UAEPAXI@Z @0x002AF53E, 28B.
// Scalar deleting dtor slot 0 of vtable 0x007FDDB4; calls rowed ??1 at
// 0x002AE627 plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

// ??_GRva002AE627@@UAEPAXI@Z @0x002AF53E present-unmatched
class Rva002AE627 { public: Rva002AE627(EmitVtableTag *); virtual ~Rva002AE627(); };
// ?<Rva002AE627::Rva002AE627> absent-from-retail
Rva002AE627::Rva002AE627(EmitVtableTag *) {}
