// ?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ
// ?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ retail 0x00271898 147B.
// A colour query on the 0x00271826-constructed envelope (Rva00271826.cpp):
// with both the +0x40 rate and the +0x3C depth non-zero, the +0x44 colour is
// the +0x28 colour scaled by 0.5 + 0.5 * depth * sin(frame * rate), the frame
// being TheGameLogic's +0x40 counter (unsigned); otherwise the +0x28 colour is
// returned as it is. The layout follows the constructor's view; the names stay
// address-derived.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <math.h>

class GameLogic; extern GameLogic *TheGameLogic;

struct Rva00271898Logic
{
	char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};

struct Rva00271898Color
{
	float red;
	float green;
	float blue;
};

class Rva00271826
{
public:
	const Rva00271898Color *rva00271898();
private:
	char m_pad00[0x28];
	Rva00271898Color m_28;
	int m_34;
	unsigned char m_38;
	bool m_39;
	float m_3C;
	float m_40;
	Rva00271898Color m_44;
};

const Rva00271898Color *Rva00271826::rva00271898()
{
	if (m_40 != 0.0f && m_3C != 0.0f) {
		Rva00271898Color *pulse = &m_44;
		pulse->red = m_28.red;
		pulse->green = m_28.green;
		pulse->blue = m_28.blue;
		float rate = (float)(double)(((Rva00271898Logic *)TheGameLogic)->m_frame * m_40);
		_ReadWriteBarrier();
		float scale = (0.5f * ((float)sin(rate)) * m_3C) + 0.5f;
		*(volatile float *)&pulse->red = pulse->red * scale;
		m_44.green = m_44.green * scale;
		m_44.blue = m_44.blue * scale;
		return pulse;
	}
	return &m_28;
}
