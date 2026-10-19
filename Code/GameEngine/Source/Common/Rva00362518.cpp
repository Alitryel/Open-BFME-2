#include "../GameClient/BuffManager.h"
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /Ireference/shims/bfme2_ascii
// ?MakeNormalBuff@BuffInstance@@QAE_NHHPAX0H@Z retail 0x00362518 171 bytes. Chain from 0x0030682A which this calls. Evidence: callers 0x0036284D, callees rowed rva00419BA5 and addBuff, float 1.0f, TheGameLogic, g_00DFF190.
class BuffLogic
{
public:
	void *addBuff(void *a, void *b);
};

extern class BuffLogic *TheBuffLogic;

class Rva00419BA5
{
public:
	void rva00419BA5();
};

class GameLogic
{
public:
	char m_pad[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

struct DrawObj
{
	char m_pad[8];
	int effectState;
	float effectIntensity;
};



bool BuffInstance::MakeNormalBuff(int a, int b, void *c, void *d, int e)
{
	if (a >= 9 || a < 1)
		return false;
	if (c == 0)
		return false;
	if (d == 0)
		return false;
	if (m_glow == 0)
	{
		m_type = a;
		m_subType = b;
		m_thing = (const ThingTemplate *)c;
		m_glow = (Rva00419BA5 *)((BuffLogic *)TheBuffLogic)->addBuff(c, d);
	}
	else
	{
		if (c != m_thing)
		{
			((Rva00419BA5 *)m_glow)->rva00419BA5();
			m_glow = 0;
			m_type = a;
			m_subType = b;
			m_thing = (const ThingTemplate *)c;
			m_glow = (Rva00419BA5 *)((BuffLogic *)TheBuffLogic)->addBuff(c, d);
		}
		else if (((DrawObj *)m_glow)->effectState == 2)
		{
			((DrawObj *)m_glow)->effectState = 1;
			((DrawObj *)m_glow)->effectIntensity = 1.0f;
		}
	}
	if (m_glow != 0)
	{
		m_duration = e;
		m_active = true;
		m_frameLimit = TheGameLogic->m_40 + e;
		return true;
	}
	m_active = false;
	return false;
}
