// BFME 2 RVA 0x00675400 (27 bytes), transferred byte-identically from
// reference/open-bfme-1/game/GameEngine/Source/Common/U2HandleLeaves.cpp
// (donor RVA 0x00809500). Only this wrapper has a BFME 2 row in this unit.
// The donor's unrelated release and comparison leaves are not retained here.
// Identity is not recovered; the existing address-derived names and opaque
// types are carried from the donor.
//
// A lookup whose result is used only if it is
// non-null.  The lookup takes ONE argument and cleans it itself, so it is
// __stdcall and not the cdecl a plain free function would be; the second call
// takes the same argument but puts the lookup's result in ecx, so that one is a
// __thiscall member on the object just found.  The wrapper's own argument is
// passed on unchanged to both.
struct Rva00809500Entry
{
	char m_body[4];
};

struct Rva00809500Sink
{
	void accept(Rva00809500Entry *entry);
};

extern Rva00809500Sink *__stdcall Rva00809010Find(Rva00809500Entry *entry);

struct Rva00809500Owner
{
	void give(Rva00809500Entry *entry);
};

void Rva00809500Owner::give(Rva00809500Entry *entry)
{
	Rva00809500Sink *sink = Rva00809010Find(entry);
	if (sink != 0)
		sink->accept(entry);
}
