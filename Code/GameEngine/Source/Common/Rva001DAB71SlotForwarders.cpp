// cl: /DNDEBUG /MD /EHsc
//
// 0x001DAB71 / 0x001DAB88 / 0x001DAB9F (23B each): three thiscall forwarders
// right after the range helper Rva001DAB3F (0x001DAB3F, Rva001DAB3FRangeSum.cpp),
// one per (target, total) slot pair at +0x50/+0x5C, +0x60/+0x6C and
// +0x70/+0x7C of their receiver; each hands its range argument and the slot
// pair to the helper. Frameless, unlike the helper's /Oy- unit, so they live in
// their own TU. The owning class is not recovered: address-derived names.

class Rva001DA112;
void Rva001DAB3F(int *range, Rva001DA112 *a, Rva001DA112 *b);

struct Rva001DAB71Slot
{
	char target[0x0C];									// +0x00
	char total[0x04];									// +0x0C
};

class Rva001DAB71
{
public:
	void rva001DAB71(int *range);
	void rva001DAB88(int *range);
	void rva001DAB9F(int *range);
private:
	char m_pad00[0x50];
	Rva001DAB71Slot m_50;
	Rva001DAB71Slot m_60;
	Rva001DAB71Slot m_70;
};

void Rva001DAB71::rva001DAB71(int *range)
{
	Rva001DAB3F(range, (Rva001DA112 *)m_50.target, (Rva001DA112 *)m_50.total);
}

void Rva001DAB71::rva001DAB88(int *range)
{
	Rva001DAB3F(range, (Rva001DA112 *)m_60.target, (Rva001DA112 *)m_60.total);
}

void Rva001DAB71::rva001DAB9F(int *range)
{
	Rva001DAB3F(range, (Rva001DA112 *)m_70.target, (Rva001DA112 *)m_70.total);
}
