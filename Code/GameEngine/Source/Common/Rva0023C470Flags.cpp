// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Two small thiscall bodies between the 0x0023C463 setter and
// SupplyTruckAIUpdate::setForceBusyState (0x0023C497):
// - 0x0023C470 (15B): the first time, raise the +0x5E byte and latch +0x5D;
// - 0x0023C47F (9B): the single-bit mask 1 << (+0x54).
// Retail bytes establish both shapes; the receivers are not recovered, so the
// names are address-derived.

class Rva0023C470
{
public:
	void rva0023C470();
	unsigned int rva0023C47F() const;
private:
	char m_pad00[0x54];
	int m_54;												// +0x54
	char m_pad58[0x5D - 0x58];
	bool m_5D;												// +0x5D
	bool m_5E;												// +0x5E
};

void Rva0023C470::rva0023C470()
{
	if (!m_5D) {
		m_5E = true;
		m_5D = true;
	}
}

unsigned int Rva0023C470::rva0023C47F() const
{
	return 1 << m_54;
}
