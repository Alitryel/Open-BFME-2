// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E8B47@Rva002E8B47@@QBEHPBQAPAURva002E8B47Record@@0@Z, retail
// 0x002E8B47 (31B, RET8).
// Target evidence: a const two-argument comparator that dereferences each
// argument twice to a record and compares the 16-bit field at +0x10 of the
// first with the second's (unsigned), returning first > second as 0/1 via
// sbb/neg. Owner, record type and field meaning are unresolved (pathfinder
// region).
struct Rva002E8B47Record
{
	char m_pad00[0x10];
	unsigned short m_10;
};

class Rva002E8B47
{
public:
	int rva002E8B47(Rva002E8B47Record **const *lhs, Rva002E8B47Record **const *rhs) const;
};

int Rva002E8B47::rva002E8B47(Rva002E8B47Record **const *lhs, Rva002E8B47Record **const *rhs) const
{
	return (**lhs)->m_10 > (**rhs)->m_10;
}
