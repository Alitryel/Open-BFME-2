// ??0Rva004E18A2@@QAE@ABV0@@Z @0x0052BB6D 45B copy ctor vtable 0x00861C30 int plus Rva0036CA00Str plus byte via rowed 0x000A8C7C caller 0x0052BD22
// cl: /GX- /MD /DNDEBUG
class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
private:
	int m_00;
};

class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();
	Rva004E18A2(const Rva004E18A2 &other);
private:
	int m_04;
	Rva0036CA00Str m_08;
	unsigned char m_0C;
};

Rva004E18A2::Rva004E18A2(const Rva004E18A2 &other) : m_04(other.m_04), m_08(other.m_08), m_0C(other.m_0C)
{
}
