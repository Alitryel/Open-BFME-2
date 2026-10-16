// cl: /MD
// ??_GRva00205224@@UAEPAXI@Z @0x00205208 28B: scalar deleting dtor calling the
// rowed ??1Rva00205224 0x00205224 then operator delete. Family block
// per §4.3 (public for UAE).

struct EmitVtableTag;

class Rva0020479E { public: Rva0020479E(EmitVtableTag *); virtual ~Rva0020479E(); };
// ?<Rva0020479E::Rva0020479E> absent-from-retail
Rva0020479E::Rva0020479E(EmitVtableTag *) {}
