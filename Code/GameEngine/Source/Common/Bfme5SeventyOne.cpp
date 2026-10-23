// Two more: the twin of the owner unlink and a bounds update.

class Gen_003F6A20
{
public:
	void bfmeDetach(void);
};

class FadeInTextRender
{
public:
	void bfmeExtend(int left, int top, int right, int bottom);

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeLeft;						// +0x08
	int m_bfmeTop;						// +0x0C
	int m_bfmeRight;					// +0x10
	int m_bfmeBottom;					// +0x14
};

// ?bfmeExtend@FadeInTextRender@@QAEXHHHH@Z
void FadeInTextRender::bfmeExtend(int left, int top, int right, int bottom)
{
	if (m_bfmeLeft > left)
		m_bfmeLeft = left;

	if (m_bfmeRight < right)
		m_bfmeRight = right;

	if (m_bfmeTop > top)
		m_bfmeTop = top;

	if (m_bfmeBottom < bottom)
		m_bfmeBottom = bottom;
}
