// cl: /MD
// ??0Rva00431920@@QAE@PAXHPAUICoord2D@@HH@Z @0x00431920 53B: ctor storing vtable g_00C3C994 plus 5 args with 8B struct copy to +0xc. Evidence: unlock lane unblocks 0x00431AEC; caller passes outer+4; g_00C3C994.
#include "../../../Libraries/Include/Lib/ICoord2D.h"

// The retail table at RVA 0x0083C994: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva004318D8@@QAEPAXI@Z")();
void __identifier("?Update@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEXXZ")();
void __identifier("?rva00432038@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z")();
void __identifier("?rva00431E5A@Rva00431E5A@@QAEXXZ")();
void __identifier("?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z")();
}
extern const void *const g_waitForSecondButtonDownStateHandlerVtable[6] = {
	(const void *)&__identifier("??_GRva004318D8@@QAEPAXI@Z"), // slot 0 0x00431A64
	(const void *)&__identifier("?Update@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEXXZ"), // slot 1 0x00431B76
	(const void *)&__identifier("?rva00432038@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z"), // slot 2 0x00432038
	(const void *)&__identifier("??_GRva004318D8@@QAEPAXI@Z"), // slot 3 0x00431A64
	(const void *)&__identifier("?rva00431E5A@Rva00431E5A@@QAEXXZ"), // slot 4 0x00431E5A
	(const void *)&__identifier("?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z"), // slot 5 0x004320B1
};

class Rva00431920
{
	void *m_00;
	void *m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
public:
	Rva00431920(void *translator, int msgType, ICoord2D *position, int modifiers, int time);
};

Rva00431920::Rva00431920(void *translator, int msgType, ICoord2D *position, int modifiers, int time)
{
	m_04 = translator;
	m_08 = msgType;
	m_00 = (void *)g_waitForSecondButtonDownStateHandlerVtable;
	m_0C = position->x;
	m_10 = position->y;
	m_14 = modifiers;
	m_18 = time;
}
