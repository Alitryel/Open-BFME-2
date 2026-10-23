//
// ?Rva000518E0Thunk@@YGXPAX@Z @0x000518E0 12B
// Thunk forwarding void* to vtable slot 2. Evidence: free-function via
// single stack arg plus ret-4 (__stdcall); mov ecx plus mov eax plus call
// [eax+8]; 5 callers including rowed W3DDebrisDraw dtor plus Rva003FB640;
// pin ?handle@Gen0003AC38@@QAEXPAX@Z names a thiscall method while retail
// is a free thunk so the pin is not used; name stays address-derived.
class Rva000518E0Base
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

void __stdcall Rva000518E0Thunk(void *p)
{
	((Rva000518E0Base *)p)->slot2();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?handle@Gen0003AC38@@QAEXPAX@Z=?Rva000518E0Thunk@@YGXPAX@Z")
