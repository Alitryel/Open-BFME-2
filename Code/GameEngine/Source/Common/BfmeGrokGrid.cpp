// flags: region default (reverse/retail_inventory/flag_regions.csv)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// The walk calls the actual same-receiver plane owner at native ADCE3.
class Rva000AD9AB { public: void rva000ADCE3(int x, int y); };

class BfmeGridWM
{
public:
	void walk();
	unsigned char rva000AE18D(int xIndex, int yIndex);

private:
	int m_pad0;
	int m_pad1;
	int m_w;
	int m_h;
	char m_pad10[0x24];
	int m_34;
	char m_pad38[0x30];
	unsigned char *m_data;
	unsigned char *m_dataEnd;
};

void BfmeGridWM::walk()
{
	for (int x = 0; x < m_w - 1; ++x)
		for (int yIndex = 0; yIndex < m_h - 1; ++yIndex)
			((Rva000AD9AB *)this)->rva000ADCE3(x, yIndex);
}

unsigned char BfmeGridWM::rva000AE18D(int xIndex, int yIndex)
{
	if (xIndex < 0 || yIndex < 0 || yIndex >= m_h || xIndex >= m_w)
		return 0;
	int byteIdx = m_34 * yIndex + (xIndex >> 3);
	if ((unsigned int)byteIdx >= (unsigned int)(m_dataEnd - m_data))
		return 0;
	_ReadWriteBarrier();
	unsigned int mask = 1u << (xIndex & 7);
	return (m_data[byteIdx] & mask) != 0;
}
