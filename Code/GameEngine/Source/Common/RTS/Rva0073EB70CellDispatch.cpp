// cl: /O2 /Ob0
// ?dispatch@Rva0073EB70CellDispatch@@QAEXIIH@Z @0x0073EB70 58B (RET 0xC).
// Ported from the Open-BFME-1 body Rva008FC250CellDispatch.cpp (BFME 1 RVA
// 0x008FC250), whose instruction skeleton retail reproduces here with
// the same offsets: when the type matches +0x64, turn the coordinate's
// distance from the +0x2C origin into a 0xA8-byte cell index (BFME 2 cells are 0xA8, the stride
// BfmeCellAt.cpp walks; the donor divides by 104) and call the
// +0x6C callback with (column, row, player) over the +0x24 width. Donor
// identity and field names are carried, not established for BFME 2; the
// class keeps an address-derived name. Neighbours are ShroudManagerImpl
// element bodies (0x0073EA40.. and the xfer at 0x0073EBB0).
class Rva0073EB70CellDispatch
{
	unsigned char m_prefix[0x24];
	unsigned m_width;
	unsigned char m_gap1[4];
	int m_origin;
	unsigned char m_gap2[0x64 - 0x30];
	unsigned m_type;
	unsigned char m_gap3[4];
	void (__cdecl *m_callback)(unsigned column, unsigned row, unsigned player);
public:
	void dispatch(unsigned type, unsigned player, int coordinate);
};

void Rva0073EB70CellDispatch::dispatch(unsigned type, unsigned player, int coordinate)
{
	if (type == m_type) {
		unsigned position = (coordinate - m_origin) / 0xA8;
		m_callback(position % m_width, position / m_width, player);
	}
}
