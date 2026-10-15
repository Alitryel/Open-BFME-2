// cl: /MD
// ??_GRva00205224@@UAEPAXI@Z @0x00205208 28B: scalar deleting dtor calling the
// rowed ??1Rva00205224 0x00205224 then operator delete. Family block
// per §4.3 (public for UAE).

struct EmitVtableTag;

class Rva00205224 { public: Rva00205224(EmitVtableTag *); virtual ~Rva00205224(); };
// ?<Rva00205224::Rva00205224> absent-from-retail
Rva00205224::Rva00205224(EmitVtableTag *) {}
