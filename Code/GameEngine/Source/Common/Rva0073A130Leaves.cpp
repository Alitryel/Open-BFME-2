// cl: /O2 /DNDEBUG /MD
// Two RET4 leaves between the rowed PartitionData / Gen_008F7B50 helpers and
// the Gen_008F7BE0 link bodies. Retail bytes establish every shape; owners
// are not recovered, so classes and names are address-derived.

// ?state@Rva0073A130Table@@QBEHH@Z @ 0x0073A130 (36B): reads the 16-bit word
// at +4 of the argument's 8-byte entry: 2 for 0xFFFF, else whether it is 0.
class Rva0073A130Table
{
public:
	int state(int index) const;
private:
	struct Entry
	{
		int m_value;
		unsigned short m_word;
		unsigned short m_pad;
	};
	Entry m_entries[1];
};

int Rva0073A130Table::state(int index) const
{
	unsigned short word = m_entries[index].m_word;
	if (word == 0xFFFF)
		return 2;
	return word == 0;
}

// ?set@Rva0073A160Field@@QAE_NH@Z @ 0x0073A160 (28B): stores the argument at
// +0xA4 and reports whether it changed.
class Rva0073A160Field
{
public:
	bool set(int value);
private:
	char m_pad[0xA4];
	int m_value;
};

bool Rva0073A160Field::set(int value)
{
	if (value != m_value)
	{
		m_value = value;
		return true;
	}
	return false;
}
