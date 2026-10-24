// cl: /MD
// ?rva0006AB98@Rva0006AB98@@QAEEHH@Z @0x0006AB98 79B evidence: bounds at +0x8 +0xc; stride at +0x34; buffer at +0x74 size via +0x78; bit test via and-7 shl setne; caller 0x0006B1F1.
// Honest-address bit test (naming rule). The read/write barrier before the
// final load keeps `this` in esi (retail's shape); it emits no code.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0006AB98
{
public:
	unsigned char rva0006AB98(int xIndex, int yIndex);
private:
	char m_pad00[8];
	int m_08;
	int m_0C;
	char m_pad10[0x34 - 0x10];
	int m_34;
	char m_pad38[0x74 - 0x38];
	unsigned char *m_74;
	unsigned char *m_78;
};

unsigned char Rva0006AB98::rva0006AB98(int xIndex, int yIndex)
{
	if (xIndex < 0 || yIndex < 0)
		return 0;
	if (yIndex >= m_0C || xIndex >= m_08)
		return 0;
	unsigned idx = (unsigned)(m_34 * yIndex + (xIndex >> 3));
	if (idx >= (unsigned)(m_78 - m_74))
		return 0;
	_ReadWriteBarrier();
	return (m_74[idx] & (1 << (xIndex & 7))) != 0;
}
