// Retail 0x00079985, 16 bytes. Name unknown. If the horde model-draw manager
// singleton TheW3DHordeModelDrawManager (0x00DE1FB8) exists, tail-jump into
// its matched clear member 0x00079911 (two vector releases plus list clear).
// Sole caller 0x0004C3C4. Kept out of Rva00079911Clear.cpp so the callee is
// not visible (it would inline) -- retail jumps to it.

class W3DHordeModelDrawManager;
extern W3DHordeModelDrawManager *TheW3DHordeModelDrawManager;

class W3DHordeModelDrawManager
{
public:
	void rva00079911();
};

void Rva00079985Clear(void)
{
	if (TheW3DHordeModelDrawManager)
		TheW3DHordeModelDrawManager->rva00079911();
}
