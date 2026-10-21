// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030B831Equal@@YAHPBURva0030B831Item@@0@Z @0x0030B831 41B
// Range-plus-int equality via rowed 0x0030B6A6 then field 0x28.
// Evidence: calls rowed Rva0030B6A6Equal; cmp [+0x28]; caller none; unblocks none.
// Precedent Rva0030B6A6Equal 61B same shape with xor/inc.
struct Rva0030B6A6Range
{
	const float *begin;
	const float *end;
};
struct Rva0030B831Item
{
	Rva0030B6A6Range range;
	char m_pad[0x28 - 8];
	int m_28;
};
int __cdecl Rva0030B6A6Equal(const Rva0030B6A6Range *lhs, const Rva0030B6A6Range *rhs);
int __cdecl Rva0030B831Equal(const Rva0030B831Item *lhs, const Rva0030B831Item *rhs)
{
	if ((unsigned char)Rva0030B6A6Equal(&lhs->range, &rhs->range) && lhs->m_28 == rhs->m_28)
		return 1;
	return 0;
}
