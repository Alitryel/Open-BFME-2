// The BFME 1 copyFields donors at 0x808F70 and 0x808F90 are ICF-folded;
// their names do not identify the target owner. Retail at 0x674E90 is
// bracketed by int3 bytes and copies the three dwords after a 4-byte header.
struct Rva00674E90
{
	unsigned int m_header;
	unsigned int m_fields[3];
	void copyFields(const Rva00674E90 &source);
};

void Rva00674E90::copyFields(const Rva00674E90 &source)
{
	m_fields[0] = source.m_fields[0];
	m_fields[1] = source.m_fields[1];
	m_fields[2] = source.m_fields[2];
}
