// Small unrowed .text bodies from the 0x00684BB0..0x0073EE20 (/O2) region.
// Retail bytes establish every shape; no caller is recovered and the owning
// classes are unknown, so each keeps an address-derived name and a view of
// only the fields it touches.

// ?rva006CBDD0@Rva006CBDD0@@QBEIXZ @0x006CBDD0 9B: low 16 bits of the +0x5C word.
class Rva006CBDD0
{
public:
	unsigned rva006CBDD0() const;
private:
	char m_pad[0x5c];
	unsigned m_5c;
};
unsigned Rva006CBDD0::rva006CBDD0() const
{
	return m_5c & 0xffff;
}

// ?rva006F6960@Rva006F6960@@QBEIXZ @0x006F6960 9B: bit 0 of the byte at +0x5E
// (same shape as the rowed Rva006FBCF0ByteBit::bit 0x006FBCF0).
class Rva006F6960
{
public:
	unsigned rva006F6960() const;
private:
	char m_pad[0x5e];
	unsigned char m_bits;
};
unsigned Rva006F6960::rva006F6960() const
{
	return m_bits & 1;
}

// ?Rva00698A30@@YAHPBURva00698A30Record@@@Z @0x00698A30 8B: cdecl read of the
// +0x58 word of the argument.
struct Rva00698A30Record
{
	char m_pad[0x58];
	int m_58;
};
int Rva00698A30(const Rva00698A30Record *record)
{
	return record->m_58;
}

// ?rva006D6350@Rva006D6350@@QAEAAVEAStringC@@ABV2@@Z @0x006D6350 8B: assign
// the +0x08 EAStringC through the rowed EAStringC::operator= 0x006D3030.
class EAStringC
{
	void *m_data;
public:
	EAStringC &operator=(const EAStringC &other);
};
class Rva006D6350
{
public:
	EAStringC &rva006D6350(const EAStringC &value);
private:
	char m_pad[0x08];
	EAStringC m_08;
};
EAStringC &Rva006D6350::rva006D6350(const EAStringC &value)
{
	return m_08 = value;
}
