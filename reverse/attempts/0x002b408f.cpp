// ?rva002B408F@Rva002B408F@@QBEHH@Z
// partial score=0.9 date=2026-10-14
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B408F@Rva002B408F@@QBEHH@Z, retail 0x002B408F (32B, RET4).
// Target evidence: whether the index argument is a valid position in the
// 0x1C-byte-record vector at +0x18 (begin) / +0x1C (end): non-negative and
// below the signed element count; 1 or 0. Owner unresolved (LivingWorld
// region, between LivingWorldLogic rows).
struct Rva002B408FRecord
{
	char m_bytes[0x1C];
};

class Rva002B408F
{
public:
	int rva002B408F(int index) const;
private:
	char m_pad00[0x18];
	Rva002B408FRecord *m_begin;
	Rva002B408FRecord *m_end;
};

int Rva002B408F::rva002B408F(int index) const
{
	if (index >= 0 && index < m_end - m_begin)
		return 1;
	else
		return 0;
}
