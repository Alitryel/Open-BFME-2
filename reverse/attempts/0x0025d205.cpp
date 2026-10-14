// ?rva0025D205@W3DDisplay@@QAEXXZ
// partial score=0.6 date=2026-10-14
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0025D205@W3DDisplay@@QAEXXZ @0x0025D205 241B: W3DDisplay fade/countdown tick.
// While the fade alpha (+0x120) is positive: a nonzero frame counter (+0x110) is decremented
// and clamped to 0..45 with the alpha pinned to 1.0 and the alpha byte forced opaque;
// otherwise the alpha decays by the step at +0x11c, and when it runs out it is zeroed and
// the 0x18-byte image element at +0x124 is cleared. The alpha (<=1.0) scaled by 255 forms
// the high color byte; a nonzero alpha byte draws the element through rowed
// Rva0025C6E2Elem::rva0025C8D3 with id 1.
// Evidence: WB debug body 00D2D7D0 (unnamed) structure; element layout from the rowed
// 0x0025C776 setter (+0x124 image, floats +0x128..+0x134, id +0x138) and W3DDisplay view of
// rowed 0x0025D2F6; the meaning of the 0xffffff base color is inferred from the WB body.
class W3DDisplay;

class Rva0025C6E2Elem
{
public:
	void rva0025C8D3(W3DDisplay *disp, int id, int color);
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	int m_14;
};

class W3DDisplay
{
public:
	void rva0025D205();
private:
	unsigned char m_pad00[0x110];
	int m_110;
	unsigned char m_pad114[8];
	float m_11c;
	float m_120;
	Rva0025C6E2Elem m_124;
};

void W3DDisplay::rva0025D205()
{
	unsigned int color = 0xffffff;
	if (m_120 > 0.0f)
	{
		if (m_110)
		{
			m_110--;
			m_110 = m_110 < 0 ? 0 : m_110;
			m_110 = m_110 > 45 ? 45 : m_110;
			color |= 0xff000000;
			m_120 = 1.0f;
		}
		else if (m_120 > 0.0f)
		{
			m_120 -= m_11c;
			if (m_120 <= 0.0f)
			{
				m_120 = 0.0f;
				m_124.m_00 = 0;
				m_124.m_04 = 0.0f;
				m_124.m_08 = 0.0f;
				m_124.m_0c = 0.0f;
				m_124.m_10 = 0.0f;
				m_124.m_14 = 0;
			}
			m_120 = (1.0f < m_120) ? 1.0f : m_120;
			color |= (unsigned int)(int)(m_120 * 255.0f) << 24;
		}
		if (color & 0xff000000)
			m_124.rva0025C8D3(this, 1, color);
	}
}
