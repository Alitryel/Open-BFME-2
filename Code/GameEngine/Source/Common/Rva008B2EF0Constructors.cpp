// cl: /DNDEBUG /MD /EHsc

// Rva008B38D0 constructor, retail 0x006F1E50 (27B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/Rva008B2EF0Constructors.cpp
// (BFME1 0x008B38D0). Only the placed delegating constructor is defined here;
// the donor's other three constructors stay declared-only, so the
// unmatched-definition gate passes. Retail forwards (0x21, argument0) to the
// pinned base constructor, then installs the derived vtable.

struct Rva00899560Value
{
	virtual ~Rva00899560Value();
	unsigned int m_flags;
};

struct Rva0089C860State
{
	Rva0089C860State(int value);
	int m_value;
	int m_first;
	int m_second;
	int m_third;
};

class Rva00899F00Base : public Rva00899560Value
{
public:
	Rva00899F00Base(unsigned int argument0, int argument1);
	virtual ~Rva00899F00Base();
	virtual void rva008991B0() = 0;

private:
	Rva0089C860State m_state;
	unsigned int m_stateBits;
	unsigned int m_bits;
};

class Rva008B2EF0 : public Rva00899F00Base {
public:
	__declspec(noinline) Rva008B2EF0(unsigned int argument0, unsigned int argument1);
private:
	unsigned int m_value20;
	unsigned int m_value24;
};

class Rva008B38D0 : public Rva008B2EF0 {
public:
	Rva008B38D0(unsigned int argument0);
};

// ??0Rva008B38D0@@QAE@I@Z, retail 0x006F1E50 (27B).
Rva008B38D0::Rva008B38D0(unsigned int argument0)
	: Rva008B2EF0(0x21, argument0) {}
