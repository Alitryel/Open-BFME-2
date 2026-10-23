// cl: /DNDEBUG /MD
//
// ?rva00373EB6@Rva00373EB6@@QAEEXZ @0x00373EB6 (16B).
// Unsigned-char compare: TheGameLogic+0x40 >= this+0x28 via sbb/inc.
// Evidence: TheGameLogic rowed global, caller 0x0053CE7F, abuts 0x00373EC6.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Rva00373EB6
{
public:
	unsigned char rva00373EB6();
private:
	char m_pad0[0x28];
	unsigned int m_28;
};

unsigned char Rva00373EB6::rva00373EB6()
{
	return TheGameLogic->getFrame() >= m_28;
}
