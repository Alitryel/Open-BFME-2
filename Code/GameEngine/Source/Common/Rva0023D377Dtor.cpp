// cl: /MD
// ??1Rva0023D377@@QAE@XZ, retail 0x0023D377, 8 bytes.
// Dtor tail-jmp to the rowed record dtor ??1Rva004393D6@@QAE@XZ at 0x00438FC5;
// add ecx,4 then jmp. Member at +4 with 4B pad at +0; empty dtor lets the
// compiler tail-call. Deleting dtor at 0x0023DACC calls this plus rowed
// operator delete 0x0002FD60.
// Rva004393D6 is a reference-only view here: the only fact this body needs is
// the destructor address, so the view claims no members. Its real shape (a
// list base plus three ints) is in Rva00438FA7ListCtor.cpp and
// stlport_list_int_dtor.cpp, and no code in this TU constructs or sizes it.
class Rva004393D6
{
public:
	~Rva004393D6();
};

class Rva0023D377
{
public:
	~Rva0023D377();
private:
	unsigned int m_00;
	Rva004393D6 m_04;
};

Rva0023D377::~Rva0023D377()
{
}
