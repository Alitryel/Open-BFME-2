// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva0036247C@@QAE@XZ, retail 0x0036247C, 23 bytes. Leaf ctor storing
// vtable 0x00816FE8 at [this] and zeroing +0x04..+0x10. Prev is
// Rva003623E5MemberCtor.cpp with the same flags; next is
// SubsystemNameGetters4.cpp (TU default flags). Caller is unclaimed
// FUN_00762CF2 (51B) at 0x00362D4F.

class Rva0036247C
{
public:
	Rva0036247C();
private:
	const char *m_name;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
};

Rva0036247C::Rva0036247C()
	: m_name("s.v"),
	  m_04(0),
	  m_08(0),
	  m_0C(0),
	  m_10(0)
{
}

// ??0Rva00362D6C@@QAE@XZ, retail 0x00362D25, 65 bytes: the constructor of
// the class whose virtual destructor 0x00362D6C (Rva00362D6CDtor.cpp) is
// rowed, installing the same vtable 0x00C17068. It clears the byte at +4,
// the dwords +8..+1C and the float at +0x2C, constructs the +0x30 member
// through Rva0036247C's constructor above, then zeroes the three floats at
// +0x20 (the body's zero after the member, as a Coord3D-style zero()). Retail
// keeps edx and xmm0 live across that call, which needs the callee defined
// in this unit. Field meanings are not established.
struct Rva00362D25Coord
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Rva00362D6C
{
public:
	Rva00362D6C();
	virtual ~Rva00362D6C();
private:
	bool m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1C;
	Rva00362D25Coord m_20;
	float m_2C;
	Rva0036247C m_30;
};

Rva00362D6C::Rva00362D6C()
	: m_04(false),
	  m_08(0),
	  m_0C(0),
	  m_10(0),
	  m_14(0),
	  m_18(0),
	  m_1C(0),
	  m_2C(0.0f)
{
	m_20.zero();
}
