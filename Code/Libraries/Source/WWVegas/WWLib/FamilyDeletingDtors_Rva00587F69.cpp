// cl: /MD
// ??_GRva00587F69@@UAEPAXI@Z, retail 0x00587F4D 28B.
// Deleting dtor for Rva00587F69 whose ??1 is rowed at 0x00587F69; placeholder ~ is duplicate.
struct EmitVtableTag;

class Rva00587F69 { public: Rva00587F69(EmitVtableTag *); virtual ~Rva00587F69(); };
// ?<Rva00587F69::Rva00587F69> absent-from-retail
Rva00587F69::Rva00587F69(EmitVtableTag *) {}
