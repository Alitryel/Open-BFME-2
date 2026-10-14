// cl: /O1 /arch:SSE /G7 /MD
// Three small bodies at retail 0x003BA7D9..0x003BA7FF, before the rowed
// ObjectTypesTemp constructor 0x003BA7FF:
//  - 0x003BA7D9 (14B) and 0x003BA7E7 (14B): same-object forwarders that
//    clear one per-index flag through the pinned Rva004266A1 setters
//    0x0042682B (byte +5) and 0x00426914 (byte +6), passing the index and 0.
//  - 0x003BA7F5 (10B): store a byte at +0x2D.
// Owners and names are address-derived.
class Rva004266A1
{
public:
	void rva0042682B(int index, unsigned char value);
	void rva00426914(int index, unsigned char value);
	void rva003BA7D9(int index);
	void rva003BA7E7(int index);
};

void Rva004266A1::rva003BA7D9(int index)
{
	rva0042682B(index, 0);
}

void Rva004266A1::rva003BA7E7(int index)
{
	rva00426914(index, 0);
}

class Rva003BA7F5
{
public:
	void set(unsigned char value);
private:
	char m_pad00[0x2D];
	unsigned char m_2D;
};

void Rva003BA7F5::set(unsigned char value)
{
	m_2D = value;
}
