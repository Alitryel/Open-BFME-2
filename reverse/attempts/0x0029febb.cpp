// ?rva0029FEBB@Rva0029FEBB@@QAEXUICoord2D@@@Z
// partial score=0.98 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// stlport
// ?rva0029FEBB@Rva0029FEBB@@QAEXUICoord2D@@@Z retail 0x0029FEBB 324B (RET 8)
// d3 seat7 rebuild from WB twin 0xDB6240: by-value ICoord2D argument copied to a local pos (that alone fixes
// the 0x1c frame and the EDI/EBX/ESI register map earlier banks missed), list<ICoord2D> at +0x910, IRegion-like
// lo/hi ints at +0x914..+0x920, TheMouse drag tolerance (+0x12e8) / 3, length/normalize rowed, scale inlined.
// Residue: retail loads TheMouse->m_dragTolerance BEFORE the vec.x store; cl keeps it after (alias order). 2 insns.
// Landing also needs a fold-proof pin ?push_back@?$list@UICoord2D@@...=0x004DE74D (insert/_M_create_node
// for ICoord2D are already pinned at 0x0036E30E/0x002DBEDD).
#include <list>
#include "Lib/Coord3D.h"
#include "Lib/ICoord2D.h"

class Mouse
{
public:
	char m_pad[0x12e8];
	unsigned int m_dragTolerance; // +0x12e8
};
extern Mouse *TheMouse;

class Rva0029FEBB
{
public:
	void rva0029FEBB(ICoord2D in);
private:
	char m_pad[0x910];
	_STL::list<ICoord2D> m_points; // +0x910
	int m_loX; // +0x914
	int m_loY; // +0x918
	int m_hiX; // +0x91c
	int m_hiY; // +0x920
};

void Rva0029FEBB::rva0029FEBB(ICoord2D in)
{
	ICoord2D pos = in;
	if (m_points.size() == 0)
	{
		m_loX = pos.x;
		m_hiX = pos.x;
		m_loY = pos.y;
		m_hiY = pos.y;
	}
	else
	{
		const ICoord2D &last = m_points.back();
		ICoord2D delta;
		delta.x = pos.x - last.x;
		delta.y = pos.y - last.y;
		Coord3D vec;
		vec.x = (float)delta.x;
		unsigned int tol = TheMouse->m_dragTolerance;
		vec.y = (float)delta.y;
		int thresh = tol / 3;
		vec.z = 0.0f;
		if (vec.length() < thresh)
			return;
		if (vec.length() > thresh * 10.0f)
		{
			vec.normalize();
			float s = thresh * 9.9f;
			pos.x = (int)(s * vec.x) + last.x;
			pos.y = (int)(s * vec.y) + last.y;
		}
		if (pos.x < m_loX)
			m_loX = pos.x;
		else if (pos.x > m_hiX)
			m_hiX = pos.x;
		if (pos.y < m_loY)
			m_loY = pos.y;
		else if (pos.y > m_hiY)
			m_hiY = pos.y;
	}
	m_points.push_back(pos);
}
