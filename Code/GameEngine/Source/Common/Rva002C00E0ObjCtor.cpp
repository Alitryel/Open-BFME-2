// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ??0Rva002C00E0Obj@@QAE@PBH@Z retail 0x002BEF29 (26B): the out-of-line copy
// of the 12-byte object's constructor that Rva005CBB0AWrap.cpp inlines into
// rva002C00E0: install the vtable 0x00BFE4F4 and take the two words the
// pointer names. Retail keeps it uncalled beside the vtable's slot bodies
// (0x002BEECD, 0x002BEF43). The class keeps its address-derived name.

class Rva002C00E0Obj
{
public:
	virtual ~Rva002C00E0Obj() {}
	int m_a;
	int m_b;
	Rva002C00E0Obj(const int *src);
};

Rva002C00E0Obj::Rva002C00E0Obj(const int *src) : m_a(src[0]), m_b(src[1])
{
}
