// cl: /MD
//
// ??1Rva004A9DF3Element@@QAE@XZ, retail 0x000A9DF3, 5 bytes. 5B jmp thunk to
// rowed ??1BfmeRefVGO@@QAE@XZ at 0x000A9822. Evidence: retail FUN_004a9df3 is
// jmp 0xa9822; LINK BONUS names this address ??1Rva004A9DF3Element@@QAE@XZ from
// ModuleTagStringDtor call at 0x006CE82A; pin ??1Rva008A2BA0Handle@@QAE@XZ at
// same address describes same tail-jump handle shape shared by 33 sites.

class BfmeRefVGO
{
public:
	~BfmeRefVGO();
};

class Rva004A9DF3Element : public BfmeRefVGO
{
public:
	~Rva004A9DF3Element();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva004A9DF3Element::~Rva004A9DF3Element()
{
}

// The same 5B tail jump under the two other names pinned at this address (the
// counted key of the Apt units and the Rva008A2C80 handle). Their units inline
// the release, so without these the link kept one of their non-retail copies;
// retail kept this /O1 jump for every name.
class Rva006D07E0Key : public BfmeRefVGO
{
public:
	~Rva006D07E0Key();
};

class Rva008A2BA0Handle : public BfmeRefVGO
{
public:
	~Rva008A2BA0Handle();
};

__declspec(noinline) inline Rva006D07E0Key::~Rva006D07E0Key()
{
}

__declspec(noinline) inline Rva008A2BA0Handle::~Rva008A2BA0Handle()
{
}

// ?bfmeAnchorRva004A9DF3ElementDtor absent-from-retail
void bfmeAnchorRva004A9DF3ElementDtor(Rva004A9DF3Element *p)
{
	p->Rva004A9DF3Element::~Rva004A9DF3Element();
}

// ?bfmeAnchorRva004A9DF3FoldedDtors absent-from-retail
void bfmeAnchorRva004A9DF3FoldedDtors(Rva006D07E0Key *key, Rva008A2BA0Handle *handle)
{
	key->Rva006D07E0Key::~Rva006D07E0Key();
	handle->Rva008A2BA0Handle::~Rva008A2BA0Handle();
}

