// cl: /O1 /MD
//
// ??_GRva00426EB0@@UAEPAXI@Z, retail 0x00426E94, 28 bytes. Deleting dtor for
// Rva00426EB0 whose ??1 is rowed at 0x00426EB0. Calls ??1Rva00426EB0@@UAE@XZ
// then operator delete ??3@YAXPAX@Z at 0x0002FD60 when flag set.
// Evidence: call to rowed 0x00426EB0; test [esp+8] flag; ret 4; chain from
// 0x00426EB0 landing. Placeholder ~Rva00426EB0 duplicates the real ??1.
struct EmitVtableTag;

class Rva00426EB0 { public: Rva00426EB0(EmitVtableTag *); virtual ~Rva00426EB0(); };
// ?<Rva00426EB0::Rva00426EB0> absent-from-retail
Rva00426EB0::Rva00426EB0(EmitVtableTag *) {}
