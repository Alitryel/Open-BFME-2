// ?rva0029D9F9@InGameUI@@QAE?AVCoord2D@@XZ
// partial score=0.94 date=2026-10-16
// ?rva0029D9F9@InGameUI@@QAE?AVCoord2D@@XZ
// partial W9-O1 2026-10-16 (nn 21 of 360 B, clen 355): hack-free rebuild on Lib/Coord2DCtorView.h (the
// user copy constructor gives retail's NRV/cached-copy fld/fstp + mov shape) with the WB 0x00DC3470
// MathCoord2D inlines as TU-local helpers: GetLengthSqrd = y*y + x*x (the sqrt argument then loads y
// first like retail), Scale must touch y before x (gives retail's dir.x home xmm0). Residue: an XMM
// permutation only - retail threshold xmm1 / dir.y xmm3 / y*y temp xmm2 (top) and y reloaded into xmm3
// before the inverse store with y*inv in place (tail); ours threshold xmm2 / y xmm1 / temp xmm3.
// Tried: ctor vs member stores vs Set order, threshold local, /2.0f vs *0.5f, normalize via scale,
// fused x/y products, statement orders.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
// InGameUI formation-facing direction, retail 0x0029D9F9..0x0029DB61 (360 B,
// ret 4: a Coord2D returned through the hidden result pointer). The
// WorldBuilder twin 0x00DC3470 is the same body with BFME 2's MathCoord2D.h
// inlines expanded (Coord2D(x, y), GetLengthSqrd, Set, Add, Normalize, scale):
// the drag vector from the formation start (+0x990) to the drag end (+0x99C);
// while it is shorter than the formation assistant's threshold (+0x2C) the
// cached direction (+0x9A8, valid flag +0x98D) is returned, or else the sum of
// the start-minus-object offsets over the selected drawables (virtual slot
// 0x124), normalized and scaled to half the threshold; a long enough drag
// marks the cache valid. Either way the direction is cached and returned.
// Callers: 0x0029DB61 (rowed) and 0x002A4E1F. The name stays address-derived:
// no symbol for it survives.
#include "Lib/Coord2DCtorView.h"
#include "Lib/Coord3D.h"


typedef float Real;

extern "C" double __cdecl sqrt(double);

// BFME 2's MathCoord2D.h inlines (WorldBuilder 0x00DC3470 expands them).
static inline Real coord2DLengthSqrd(const Coord2D &c) { return c.y * c.y + c.x * c.x; }
static inline void coord2DAdd(Coord2D &c, const Coord2D &a) { c.x += a.x; c.y += a.y; }
static inline void coord2DScale(Coord2D &c, Real s) { c.y *= s; c.x *= s; }
static inline void coord2DNormalize(Coord2D &c)
{
	Real len = (Real)sqrt(coord2DLengthSqrd(c));
	Real inv = 1.0f / len;
	c.x *= inv;
	c.y *= inv;
}

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	char m_pad[0x38];
	Coord3D m_position; // +0x38
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	char m_pad[0xFC];
	Object *m_object; // +0xFC
};

struct DrawableListNode
{
	DrawableListNode *m_next;
	DrawableListNode *m_prev;
	Drawable *m_drawable;
};

struct DrawableList
{
	DrawableListNode *m_head;
};

class Rva0022AD10Subsystem
{
public:
	char m_pad[0x2C];
	Real m_threshold; // +0x2C
};
extern Rva0022AD10Subsystem *TheFormationAssistant;

template <int N> class InGameUIDirectionSlots : public InGameUIDirectionSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class InGameUIDirectionSlots<0>
{
};

class InGameUI : public InGameUIDirectionSlots<73>
{
public:
	virtual const DrawableList *getAllSelectedDrawables(); // +0x124
	Coord2D rva0029D9F9();
private:
	char m_pad004[0x98D - 4];
	bool m_formationDirectionValid; // +0x98D
	char m_pad98E[0x990 - 0x98E];
	Coord2D m_formationStart; // +0x990
	char m_pad998[0x99C - 0x998];
	Coord2D m_formationEnd; // +0x99C
	char m_pad9A4[0x9A8 - 0x9A4];
	Coord2D m_formationDirection; // +0x9A8
};

Coord2D InGameUI::rva0029D9F9()
{
	Coord2D dir(m_formationEnd.x - m_formationStart.x, m_formationEnd.y - m_formationStart.y);
	if (coord2DLengthSqrd(dir) < TheFormationAssistant->m_threshold * TheFormationAssistant->m_threshold)
	{
		if (m_formationDirectionValid)
			return m_formationDirection;
		dir.x = 0.0f;
		dir.y = 0.0f;
		const DrawableList *list = getAllSelectedDrawables();
		for (DrawableListNode *node = list->m_head->m_next; node != list->m_head; node = node->m_next)
		{
			Object *obj = node->m_drawable->getObject();
			if (obj)
			{
				Coord2D delta(m_formationStart.x - obj->getPosition()->x, m_formationStart.y - obj->getPosition()->y);
				coord2DAdd(dir, delta);
			}
		}
		coord2DNormalize(dir);
		coord2DScale(dir, TheFormationAssistant->m_threshold * 0.5f);
	}
	else
	{
		m_formationDirectionValid = true;
	}
	m_formationDirection = dir;
	return dir;
}
