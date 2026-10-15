// cl: /O1 /MD
// ??_GRva0014F699@@UAEPAXI@Z @0x0014DC3F 28B.
// Target: calls rowed ??1Rva0014F699 at 0x0014D1E3, then operator delete
// 0x0002FD60 when flag bit 0 is set. The native destructor is owned by
// Rva0014F699Assign.cpp; its novtable view does not emit a deleting thunk.
// Like the neighboring Rva00150558/8E emitters, this declaration-only view
// describes the one virtual cleanup slot, without claiming a complete layout.
// The unused tag constructor makes MSVC emit that slot and its deleting thunk.
// No local destructor body: the former copy added a non-retail vptr store.

struct EmitVtableTag;

class Rva0014F699
{
public:
	Rva0014F699(EmitVtableTag *);
	virtual ~Rva0014F699();
};

// ?<Rva0014F699::Rva0014F699> absent-from-retail
Rva0014F699::Rva0014F699(EmitVtableTag *) {}
