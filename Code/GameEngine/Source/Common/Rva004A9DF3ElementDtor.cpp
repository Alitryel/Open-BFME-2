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

// ?bfmeAnchorRva004A9DF3ElementDtor absent-from-retail
void bfmeAnchorRva004A9DF3ElementDtor(Rva004A9DF3Element *p)
{
	p->Rva004A9DF3Element::~Rva004A9DF3Element();
}

