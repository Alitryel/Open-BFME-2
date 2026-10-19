// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetStatNameKey@Rva0040A7D5@@QBEHH@Z @0x0040A7D5 28B
// Evidence: unlock lane; begin-end at +0-+4 count sar 2; unsigned bounds check returns 0 else element; callers 0x40A973 0x40A980 0x40A9C0 0x40BB9D.
class Rva0040A7D5
{
public:
	int GetStatNameKey(int index) const;
private:
	const int *m_begin;
	const int *m_end;
};

int Rva0040A7D5::GetStatNameKey(int index) const
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	if ((unsigned int)index < count)
		return m_begin[index];
	return 0;
}
