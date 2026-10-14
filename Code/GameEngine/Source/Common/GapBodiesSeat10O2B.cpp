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

// ?rva006200A0@Rva006200A0@@QBEPAXXZ @0x006200A0 6B: address 12 bytes into the
// record held at +0.
struct Rva006200A0Record
{
	char m_00[0x0c];
	char m_0c[4];
};
class Rva006200A0
{
public:
	void *rva006200A0() const;
private:
	Rva006200A0Record *m_00;
};
void *Rva006200A0::rva006200A0() const
{
	return m_00->m_0c;
}

// ?rva006C1840@Rva006C1840@@QAEXXZ @0x006C1840 14B: clear +0, the +4 byte, +8 and +0x10.
class Rva006C1840
{
public:
	void rva006C1840();
private:
	int m_00;
	unsigned char m_04;
	int m_08;
	int m_0c;
	int m_10;
};
void Rva006C1840::rva006C1840()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_10 = 0;
}

// ??ERva006CD4B0@@QAEAAV0@XZ @0x006CD4B0 6B and ??FRva006CD4B0@@QAEAAV0@XZ
// @0x006CD5E0 6B: pre-increment / pre-decrement of a pointer over 8-byte
// elements, returning this.
struct Rva006CD4B0Element
{
	int m_words[2];
};
class Rva006CD4B0
{
public:
	Rva006CD4B0 &operator++();
	Rva006CD4B0 &operator--();
private:
	Rva006CD4B0Element *m_cur;
};
Rva006CD4B0 &Rva006CD4B0::operator++()
{
	++m_cur;
	return *this;
}
Rva006CD4B0 &Rva006CD4B0::operator--()
{
	--m_cur;
	return *this;
}

// ?rva006CFE30@Rva006CFE30@@QAE?AURva006CFE30Iterator@@H@Z @0x006CFE30 16B:
// unlink the head node (next at +4) and return it by value; the word
// argument is unused (same shape as the rowed 0x002C1F6F).
struct Rva006CFE30Node
{
	int m_00;
	Rva006CFE30Node *m_next;
};
struct Rva006CFE30Iterator
{
	Rva006CFE30Iterator(Rva006CFE30Node *node) : m_node(node) {}
	Rva006CFE30Node *m_node;
};
class Rva006CFE30
{
public:
	Rva006CFE30Iterator rva006CFE30(int unused);
private:
	Rva006CFE30Node *m_head;
};
Rva006CFE30Iterator Rva006CFE30::rva006CFE30(int)
{
	Rva006CFE30Node *node = m_head;
	m_head = node->m_next;
	return Rva006CFE30Iterator(node);
}

// ?rva006E0160@Rva006E0160@@QBEHH@Z @0x006E0160 18B: the signed low 24 bits of
// the +0x1C word masked by the argument.
class Rva006E0160
{
public:
	int rva006E0160(int mask) const;
private:
	char m_pad[0x1c];
	int m_low : 24;
};
int Rva006E0160::rva006E0160(int mask) const
{
	return m_low & mask;
}

// ?rva0073B640@Rva0073B640@@QBEHHH@Z @0x0073B640 19B: entry [row][column] of a
// table of four 16-bit entries per row starting at +6.
class Rva0073B640
{
public:
	int rva0073B640(int row, int column) const;
private:
	char m_pad[6];
	unsigned short m_table[1][4];
};
int Rva0073B640::rva0073B640(int row, int column) const
{
	return m_table[row][column];
}
