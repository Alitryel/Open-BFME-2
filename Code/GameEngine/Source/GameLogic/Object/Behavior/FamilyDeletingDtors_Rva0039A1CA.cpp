// cl: /MD
//
// ??_GRva0039A1CA@@UAEPAXI@Z, retail 0x0039A1AE (28 bytes).
// Deleting dtor for Rva0039A1CA whose ??1 is rowed at 0x0039A1CA; the call
// resolves through that row. Placeholder ??1 is a duplicate kept only to emit
// the deleting copy, following FamilyDeletingDtors.cpp.
struct EmitVtableTag;

class Rva0039A1CA { public: Rva0039A1CA(EmitVtableTag *); virtual ~Rva0039A1CA(); };
// ?<Rva0039A1CA::Rva0039A1CA> absent-from-retail
Rva0039A1CA::Rva0039A1CA(EmitVtableTag *) {}
