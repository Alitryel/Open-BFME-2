// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00415688@@QAE@XZ @0x00415688 52B.
// Default ctor of a record whose first member is the rowed 0x1C0-byte voice-slot
// array (ctor 0x00254FE4) followed at +0x1C0 by the 12-byte empty tree member
// (ctor 0x0024613C). Both layouts are the neutral views of BfmeObject544Ctor.cpp;
// the owner identity is open.
class Rva00254FE4Member
{
public:
	Rva00254FE4Member();
	~Rva00254FE4Member();
private:
	char m_pad[0x1C0];
};

class Rva0024613CMember
{
public:
	Rva0024613CMember();
	~Rva0024613CMember();
private:
	char m_pad[0x0C];
};

class Rva00415688
{
public:
	Rva00415688();
private:
	Rva00254FE4Member m_00;
	Rva0024613CMember m_1C0;
};

Rva00415688::Rva00415688()
{
}
