// cl: /GX
// ?rva006C0DA0@TaintManagerImpl@@QAEXXZ @ 0x006C0DA0 76B
// Honest address name: thiscall grid iterator over width*height 12B records.
// Evidence: callers at 0x006C1132 and 0x006C0823; neighbours Bfme5SeventySix /GX
// and BfmeGridRasterCircle /GX; imul width*height lea *3 *4 end pointer;
// per-pixel cdecl callback at +0x2c with (x y byte) and 12B stride.
class TaintManagerImpl
{
public:
	void rva006C0DA0();
private:
	char m_pad00[0x20];
	int m_width;
	int m_height;
	unsigned char *m_data;
	void (__cdecl *m_cb)(int x, int y, unsigned char v);
};
void TaintManagerImpl::rva006C0DA0()
{
	unsigned char *end = m_data + (m_height * m_width * 3) * 4;
	unsigned char *p = m_data;
	int x = 0;
	int y = 0;
	if (p == end)
		return;
	do {
		int v = *p;
		m_cb(x, y, v);
		if (++x == m_width) {
			x = 0;
			++y;
		}
		p += 12;
	} while (p != end);
}
