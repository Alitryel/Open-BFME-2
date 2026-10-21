// cl: /O2 /Ob0

class Rva003A6F70
{
public:
	virtual void dummy();
	int m_04, m_08, m_0C, m_10, m_14, m_18;
	char m_1C;
	Rva003A6F70(const Rva003A6F70 &other);
};

Rva003A6F70::Rva003A6F70(const Rva003A6F70 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
}

// ?dummy@Rva003A6F70@@UAEXXZ present-unmatched
void Rva003A6F70::dummy()
{
}
