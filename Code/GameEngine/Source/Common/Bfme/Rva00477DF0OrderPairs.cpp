// cl: /DNDEBUG /MD /EHsc

struct Rva00477DF0
{
	unsigned char m_unmodelled_000[0x14];
	int m_first;
	int m_third;
	int m_second;
	int m_fourth;

	void orderPairs();
};

void Rva00477DF0::orderPairs()
{
	if (m_first > m_second)
	{
		int value = m_first;
		m_first = m_second;
		m_second = value;
	}
	if (m_third > m_fourth)
	{
		int value = m_third;
		m_third = m_fourth;
		m_fourth = value;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?orderPairs@GameWindow@@QAEXXZ=?orderPairs@Rva00477DF0@@QAEXXZ")
