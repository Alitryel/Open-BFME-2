// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva00392092@Rva00392092Target@@QAEXXZ 101B @0x00392092: array init allocating Rva00391FC4 array sized GlobalData count stride 0x1C via new[]. Layout count at +0 array at +8 from dtor row at 0x0039205C. Evidence: dtor call at 0x003920A2 plus GlobalData+0xA94 plus UU at 0x0002FDE0 plus LL at 0x00629512 plus LINK BONUS 5 files.
// The iterator's constructor callback is the rowed 0x00391FC4, not the
// unrelated forty-byte record constructor at 0x000AF215. Its owned provider
// establishes four floats, a byte at +0x10, AsciiString at +0x14 and int +0x18.
// The implicit string cleanup reproduces the shared +0x14 tail destructor;
// sharing cleanup code does not establish a shared constructor identity.
#include "ascii_string.h"
extern class GlobalData *TheWritableGlobalData;

// Without these MSVC routes new T[n] to scalar ??2 (0x0002FDA0); retail uses array ??_U (0x0002FDE0).
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};

// The element ctor retail hands the vector-new iterator, 0x00391FC4, is rowed
// as ??0Rva004D9A3C (GapBodiesGE14.cpp).
class Rva004D9A3C
{
public:
	Rva004D9A3C();
};

class Rva00391FC4
{
public:
	Rva00391FC4() { ((Rva004D9A3C *)this)->Rva004D9A3C::Rva004D9A3C(); }
private:
	float m_float00, m_float04, m_float08;
	float m_float0C;
	unsigned char m_byte10;
	char m_pad11[3];
	AsciiString m_string14;
	int m_int18;
};

class Rva0039205C
{
public:
	~Rva0039205C();
private:
	int m_count00;
	int m_pad04;
	Rva00391FC4 *m_array08;
};

class Rva00392092Target
{
public:
	void rva00392092();
private:
	int m_count00;
	int m_pad04;
	Rva00391FC4 *m_array08;
};

void Rva00392092Target::rva00392092()
{
	((Rva0039205C *)this)->~Rva0039205C();
	unsigned int count = TheWritableGlobalData->m_count;
	m_array08 = new Rva00391FC4[count];
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0Rva00391FC4@@QAE@XZ=?ji_00629182@@YAXXZ")
