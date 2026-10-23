// cl: /O2 /DNDEBUG /MD
// ?rva005F55D6@Rva005F55D6@@QAEXXZ, retail 0x005F55D6 (8 bytes): forwards
// to the +0x04 swapper's rowed army-unit validation 0x005F5537 (tail jump).
// Caller: the refresh step 0x005E589E. Names address-derived.
class Rva005F5537
{
public:
	void rva005F5537();
};

class Rva005F55D6
{
public:
	void rva005F55D6();
private:
	int m_00;
	Rva005F5537 *m_04;	// +0x04
};

void Rva005F55D6::rva005F55D6()
{
	m_04->rva005F5537();
}