// cl: /DNDEBUG /MD /EHsc
//
// ?snapshotCreateView@GameWindow@@QAEXPAVGadgetCreateView@@_N@Z,
// retail 0x003146DC, 126 bytes. Dedicated TU.
//
// Snapshots the fields the gadget factory needs out of a live GameWindow
// into a 0x34-byte create view: the virtual slot-7 result, the words at
// +0x08/+0x0C/+0x10, an alias of the window block at +0x30 and the words at
// +0x1E0..+0x1F0. With clear set, the aliased block's word at +0x14 and its
// words at +0x19C/+0x1A0/+0x1A4 are zeroed.
//
// Codegen notes (all retail-measured): the view carries two spare words at
// +0x08/+0x0C (only offsets +0x00/+0x04/+0x10..+0x30 are touched here); the
// early copies run through eax while the window-block alias stays live in
// eax for the later ones; every read of the alias member reloads it, so it
// is volatile-qualified.
//
// Identity basis: the three callers (0x00317579, 0x0031C9DF, 0x0031CAD2)
// all pass the same register that the create wrapper also feeds to
// GameWindow::winGetUserData (0x005C4ACD), and all zero the view with the
// 0x34-byte zeroer at 0x0022239C first. Member names beyond offsets are
// provisional.

typedef int Int;

// The canonical 0x34-byte create record (registered in canonical_classes.csv).
// Offsets this body writes: +0x04 status, +0x10/+0x14 width/height, +0x18
// the slot-7 result, +0x1C system, +0x20..+0x2C the unknown32 words and
// +0x30 the aliased window block, which every read reloads (volatile access).
#include "GameWindowManagerRecordView.h"

// Opaque GameWindow stand-in: only the offsets this body touches exist.
// The real class is much larger; nothing else is spelled. The virtual at
// slot 7 (+0x1C) is declared after unused placeholders so the call below
// compiles to the retail indirect call; the placeholders are never defined
// or emitted.
class GameWindow
{
public:
	virtual void unusedSlot0();
	virtual void unusedSlot1();
	virtual void unusedSlot2();
	virtual void unusedSlot3();
	virtual void unusedSlot4();
	virtual void unusedSlot5();
	virtual void unusedSlot6();
	virtual void *fetchCreateInstance();
	void snapshotCreateView(GadgetCreateView *view, bool clear);
};

struct WindowBlockTail
{
	unsigned char m_pad[0x19C];
	Int m_clear0;
	Int m_clear1;
	Int m_clear2;
};

// ?snapshotCreateView@GameWindow@@QAEXPAVGadgetCreateView@@_N@Z
void GameWindow::snapshotCreateView(GadgetCreateView *view, bool clear)
{
	char *windowBlock;

	view->unknown24 = fetchCreateInstance();
	view->status = *(Int *)((char *)this + 0x08);
	view->width = *(Int *)((char *)this + 0x0C);
	view->height = *(Int *)((char *)this + 0x10);
	windowBlock = (char *)this + 0x30;
	*(char *volatile *)&view->instance = windowBlock;
	*(Int *)(view->unknown32 + 0) = *(Int *)((char *)this + 0x1E0);
	view->system = *(void **)((char *)this + 0x1E4);
	*(Int *)(view->unknown32 + 4) = *(Int *)((char *)this + 0x1E8);
	*(Int *)(view->unknown32 + 8) = *(Int *)((char *)this + 0x1EC);
	*(Int *)(view->unknown32 + 12) = *(Int *)((char *)this + 0x1F0);

	if (clear)
	{
		*(Int *)(windowBlock + 0x14) = 0;
		(*(WindowBlockTail *volatile *)&view->instance)->m_clear0 = 0;
		(*(WindowBlockTail *volatile *)&view->instance)->m_clear1 = 0;
		(*(WindowBlockTail *volatile *)&view->instance)->m_clear2 = 0;
	}
}
