//
// ?rebuildMask@@YAXXZ
// retail 0x000AA5E1, 100 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/Rva00785FD0AptFlush.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). The donor file carries this single definition, so the
// dedicated TU is that body verbatim.
// cl: -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
//
// APT queued-primitive flush at 0x00785FD0.  Dirty byte 0x01306950, renderer
// 0x01306954 with a __fastcall mode setter (edx = mode) reached via ILT
// 0x0003DDED, stencil helper ILT 0x00041EC0 -> 0x0078B280, queue sentinel
// 0x01306978, element cleanup ILT 0x00049062 -> 0x00785300.

class Rva00785FD0Renderer
{
public:
	void stencil();
	void __fastcall setMode(int mode);
};

class AptShapeContainer
{
public:
	void render();
};

struct Rva00785FD0Node
{
	Rva00785FD0Node *next;
	char pad[4];
	AptShapeContainer *item;
};

extern char g_rva00785FD0Dirty;
class BfmeHub982;
class W3DAptAux
{
	friend void rebuildMask();
	static BfmeHub982 *s_renderer;
};
// The renderer is the existing W3DAptAux singleton at VA 0x00DE6170.
// This unit uses its renderer-method view only at the call sites.
// g_rva00785FD0Queue is only an alias of the owned global g_Va00DE6194 (ledger names column); this unit reads the owner through its own view type.
extern unsigned int g_Va00DE6194;
#define g_rva00785FD0Queue (*(Rva00785FD0Node * *)&g_Va00DE6194)

void rebuildMask()
{
	if (g_rva00785FD0Dirty == 0)
		return;

	if (g_rva00785FD0Queue->next == g_rva00785FD0Queue)
	{
		((Rva00785FD0Renderer *)W3DAptAux::s_renderer)->setMode(0);
		return;
	}

	g_rva00785FD0Dirty = 0;
	((Rva00785FD0Renderer *)W3DAptAux::s_renderer)->stencil();
	((Rva00785FD0Renderer *)W3DAptAux::s_renderer)->setMode(2);
	for (Rva00785FD0Node *n = g_rva00785FD0Queue->next; n != g_rva00785FD0Queue; n = n->next)
		n->item->render();
	((Rva00785FD0Renderer *)W3DAptAux::s_renderer)->setMode(1);
}
