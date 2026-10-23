// ?rva004B0DA0@Rva004B0DA0Holder@@QAEXH@Z, retail 0x004B0DA0, 12 bytes.
// Indexed byte clear in the 004B0Dxx cluster (after Disp32ByteGetters,
// before Bfme5TinyFifteen): clears the byte at this+index+0x24. Called via
// jmp at 0x0028ECA0. No donor; opaque holder (true class unproven).
// No // cl: line (defaults match the frameless twelve-byte shape).

typedef unsigned char Byte;

class Rva004B0DA0Holder
{
public:
	void rva004B0DA0(int index);

private:
	Byte m_pad[0x24];
	Byte m_flags[1]; // +0x24, indexed by arg
};

void Rva004B0DA0Holder::rva004B0DA0(int index)
{
	m_flags[index] = 0;
}
