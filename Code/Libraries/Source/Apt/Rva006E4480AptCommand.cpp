// cl: /MD /O2 /arch:SSE
// Native 0x006E4480 (98B). The same receiver calls rowed Rva006E34D0::rva006E34D0; retail writes records at +0x7C/+0x8C for IDs 0x1F5/0x1F6.
// The complete caller6CC9F0 copies a sixteen-byte aggregate to this method.
// Its first two words and byte8 feed the native records; word12 is the ID.
// Grouping the parameters correctly preserves this whole98B callee.
struct Rva006CC9F0Input { int first,second; unsigned char flag; char pad09[3]; int eventId; };
class Rva006E34D0
{
public:
	void rva006E34D0(int value);
	void rva006E4480(Rva006CC9F0Input input);

private:
	char pad00[0x3c];
	int m_count;
	int *m_arr;
	char pad44[0x7c - 0x44];
	int m_7c;
	int m_80;
	unsigned char m_84;
	char pad85[7];
	int m_8c;
	int m_90;
	unsigned char m_94;
	char pad95[0xac - 0x95];
	int m_cap;
};

void Rva006E34D0::rva006E4480(Rva006CC9F0Input input)
{
	if (input.eventId == 0x1f5)
	{
		m_7c = input.first;
		m_80 = input.second;
		m_84 = input.flag;
	}
	else if (input.eventId == 0x1f6)
	{
		m_8c = input.first;
		m_90 = input.second;
		m_94 = input.flag;
	}
	int packed = input.eventId;
	packed <<= 15;
	packed |= input.flag;
	packed <<= 2;
	packed |= 1;
	rva006E34D0(packed);
}
